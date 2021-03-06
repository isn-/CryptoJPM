// Fortuna.h - written and placed in the public domain by Jean-Pierre Muench

#ifndef CRYPTOPP_FORTUNA_H
#define CRYPTOPP_FORTUNA_H

#include "cryptlib.h"
#include "filters.h"
#include "aes.h"
#include "sha.h"
#include "sha3.h"
#include "dhash.h"
#include "hrtimer.h"
#include "misc.h"
#include "config.h"

#ifdef CRYPTOPP_BOOL_CPP11_THREAD_SUPPORTED
#include <thread>
#include <mutex>
#include <memory>
#include <atomic>
#endif

NAMESPACE_BEGIN(CryptoPP)

class CRYPTOPP_NO_VTABLE Fortuna_Base : public RandomNumberGenerator, public NotCopyable
{
public:
	CRYPTOPP_CONSTANT(MIN_POOL_SIZE = 64)
	CRYPTOPP_CONSTANT(MAX_EVENT_SIZE = 32) // should be a power of 2
	CRYPTOPP_CONSTANT(NUM_POOLS = 32)
	CRYPTOPP_CONSTANT(NUMBER_MILLISECONDS_BETWEEN_RESEEDS = 100)
public:
	Fortuna_Base();

	std::string AlgorithmName() const {return "Fortuna";}

	void IncorporateEntropy(const byte* Input,size_t length) {IncorporateEntropyEx(Input,length,0);}
	void IncorporateEntropyEx(const byte* Input,size_t length,byte SourceNumber);
	bool CanIncorporateEntropy() const {return true;}
	// maximal amount of bytes to be generated by GenerateSmallBlock()
	size_t MaxGenerateSize() const;
	// throws if size > MaxGenerateSize
	virtual void GenerateSmallBlock(byte* output,size_t size);
	// calls GenerateSmallBlock() multiple times to gather the data
	void GenerateBlock(byte* output,size_t size);

	virtual void GenerateSeedFile(byte* output,size_t length) {GenerateBlock(output,length);}
	// create a new seed file after you've used the old one
	virtual void ReadSeedFile(const byte* input,size_t length) {Reseed(input,length);}
protected:
	void IncorporateEntropySmall(const byte* Input,byte length,byte SourceNumber);
	void Reseed(const byte* NewSeed,size_t seedlen);
	void Initialize();
	// manually take care that calls to GetPoolHash are thread-safe
	virtual HashTransformation* GetPoolHash(byte i) =0;
	// initializes a new instance of the cipher and returns it
	virtual BlockCipher* GetNewCipher() =0;
	// initializes a new instance of the cipher and returns it
	virtual HashTransformation* GetNewReseedHash() =0;
	// can't modify state here
	virtual const BlockCipher* GetCipher() const =0;
private:
#if CRYPTOPP_BOOL_CPP11_THREAD_SUPPORTED
	std::recursive_mutex m_PoolMutex[NUM_POOLS];
	std::recursive_mutex m_GeneratorMutex;
	std::recursive_mutex m_ReseedCounterMutex;
#endif
	SecByteBlock m_Key;
	SecByteBlock m_Counter;
	byte m_PoolIndex;
	word64 m_ReseedCounter;
	FixedSizeSecBlock<word64,NUM_POOLS> m_PoolProcessedData;
	ThreadUserTimer m_ReseedTimer;
};

// note: digestsize of reseed hash must be longer than max keylength of the cipher
template<class CIPHER,class RESEED_HASH,class POOL_HASH = RESEED_HASH>
class Fortuna : public Fortuna_Base
{
public:
	Fortuna():Fortuna_Base(){ Initialize(); }
private:
	POOL_HASH m_PoolHashes[NUM_POOLS];
	HashTransformation* GetPoolHash(byte i) {if(i>=NUM_POOLS){throw(InvalidArgument("can not access a Fortuna-Pool beyond 32!"));}return &m_PoolHashes[i];}
	HashTransformation* GetNewReseedHash() {return new RESEED_HASH();}
	const typename CIPHER::Encryption m_InfoCipher;
	BlockCipher* GetNewCipher() {return new typename CIPHER::Encryption();}
	const BlockCipher* GetCipher() const {return &m_InfoCipher;}
};

// the original Fortuna as specified by Schneier, Fergueson and Kohno
typedef Fortuna<AES,DoubledHash<SHA256> > OriginalFortuna;

//! autoseeded version of Fortuna, isn't located in osrng.h because it's much more complex than implementations there
class CRYPTOPP_NO_VTABLE AutoSeededFortuna_Base : public Fortuna_Base
{
public:
	// slow poll can only be activated if multithreading (MT) is allowed, if MT is off, slowpoll switch will be ignored
	// the compile-time switch for MT will always override this switch
	AutoSeededFortuna_Base(bool AllowSlowPoll=true,bool AllowMultithreading=true);
	// always use values from TrueCrypt's fast poll (in generation call if non-MT and in own thread if MT)
	// use values from TrueCrypt's slow poll if multithreading is allowed & slow polls are allowed
	// use keyboard and mouse data if multithreading is allowed
	// use values from other Fortuna-impl. if multithreading is allowed, except for some slow ones (ping, clsi, registry,...)
	// use values from other Fortuna-impl. if multithreading is allowed & slow polls are allowed

	// may incorporate some entropy before outputting data
	virtual void GenerateSmallBlock(byte* output,size_t size);
	// use "machine-sig" infos for reading the reseed file-data
	// create a new seed file after you've used the old one
	void ReadSeedFile(const byte* input,size_t length);

	// if multithreading is globally allowed, take care of sync issues (-> use mutexes)
protected:
	// adds some entropy by using machine-specific (random) data
	void GenerateMachineSignature();
	void PollFast();
private:
	const bool m_PollAtCalltime;
#if CRYPTOPP_BOOL_CPP11_THREAD_SUPPORTED
	
#endif
};

// note: digestsize of reseed hash must be longer than max keylength of the cipher
template<class CIPHER,class RESEED_HASH,class POOL_HASH = RESEED_HASH>
class AutoSeededFortuna : public AutoSeededFortuna_Base
{
public:
	AutoSeededFortuna(bool AllowSlowPoll=true,bool AllowMultithreading=true):AutoSeededFortuna_Base(AllowSlowPoll,AllowMultithreading){}
private:
	POOL_HASH m_PoolHashes[NUM_POOLS];
	HashTransformation* GetPoolHash(byte i) {if(i>=NUM_POOLS){throw(InvalidArgument("can not access a Fortuna-Pool beyond 32!"));}return m_PoolHashes[i];}
	HashTransformation* GetNewReseedHash() {return new RESEED_HASH();}
	const typename CIPHER::Encryption m_InfoCipher;
	BlockCipher* GetNewCipher() {return new typename CIPHER::Encryption();}
	const BlockCipher* GetCipher() const {return &m_InfoCipher;}
};

// equivalent to what was proposed by Schneier and Fergueson
typedef AutoSeededFortuna<AES,SHA256> StandardAutoSeededFortuna;

// if multithreading is allowed, the following class will instantiate a single Fortuna instance and feed it with all data available
// if multithreading isn't allowed, the following class will instantiate a single Fortuna instance and feed it with non-MT data only
// don't use this class if you can't guarantee consistent template-parameters
// note: digestsize of reseed hash must be longer than max keylength of the cipher
template<class CIPHER,class RESEED_HASH,class POOL_HASH = RESEED_HASH>
class AutoSeededFortunaSingleton : public RandomNumberGenerator, public NotCopyable
{
public:
	virtual void IncorporateEntropy(const byte *input, size_t length) {GetSingleton()->IncorporateEntropy(input,length);}
	virtual bool CanIncorporateEntropy() const {return GetSingleton()->CanIncorporateEntropy();}
	virtual void GenerateBlock(byte *output, size_t size) {GetSingleton()->GenerateBlock(output,size);}
	virtual void GenerateSeedFile(byte* output,size_t length) {GetSingleton()->GenerateSeedFile(output,length);}
	// create a new seed file after you've used the old one
	virtual void ReadSeedFile(const byte* input,size_t length) {GetSingleton()->ReadSeedFile(input,length);}
private:
	AutoSeededFortuna<CIPHER, RESEED_HASH, POOL_HASH>* GetSingleton() {return &Singleton<AutoSeededFortuna<CIPHER,RESEED_HASH,POOL_HASH> >().Ref();}
};

// use this typedef if you can't guarantee consistent template-parameters for AutoSeededFortunaSingleton
// equivalent to what was proposed by Schneier and Fergueson
typedef AutoSeededFortunaSingleton<AES,SHA256> StandardAutoSeededFortunaSingleton;

NAMESPACE_END

#endif
