#include "stdafx.h"
#include "CppUnitTest.h"

using namespace CryptoPP;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CryptoPPTests
{
	TEST_CLASS(SymmetricTestVectorChecks)
	{
	public:
		
		TEST_METHOD(Threefish256TestVectorChecks)
		{
			const word64 InData[4] = {0};
			const word64 Tweak[3] = {0};
			const byte Key[32] = {0};
			word64 IntermediateData[4]={0};
			byte CompareData[32]={0};

			Threefish_256::Encryption Encryptor1(Key);
			Encryptor1.ProcessAndXorBlockWithTweak((byte*)InData,nullptr,(byte*)IntermediateData,(byte*)Tweak,16);
			Assert::IsTrue(IntermediateData[0]==0x94EEEA8B1F2ADA84,L"first word failed (1)",LINE_INFO());
			Assert::IsTrue(IntermediateData[1]==0xADF103313EAE6670,L"second word failed (1)",LINE_INFO());
			Assert::IsTrue(IntermediateData[2]==0x952419A1F4B16D53,L"third word failed (1)",LINE_INFO());
			Assert::IsTrue(IntermediateData[3]==0xD83F13E63C9F6B11,L"fourth word failed (1)",LINE_INFO());
			Threefish_256::Decryption Decryptor1(Key);
			Decryptor1.ProcessAndXorBlockWithTweak((byte*)IntermediateData,nullptr,CompareData,(byte*)Tweak,16);
			Assert::IsTrue(memcmp(CompareData,InData,32)==0,L"out != in",LINE_INFO());

			const word64 NonZeroInData[4] = {0xF8F9FAFBFCFDFEFF,0xF0F1F2F3F4F5F6F7,0xE8E9EAEBECEDEEEF,0xE0E1E2E3E4E5E6E7};
			const word64 NonZeroTweak[3] = {0x0706050403020100,0x0F0E0D0C0B0A0908,0x0808080808080808};
			const word64 NonZeroKey[4] = {0x1716151413121110,0x1F1E1D1C1B1A1918,0x2726252423222120,0x2F2E2D2C2B2A2928};

			Threefish_256::Encryption Encryptor2((byte*)NonZeroKey);
			Encryptor2.ProcessAndXorBlockWithTweak((byte*)NonZeroInData,nullptr,(byte*)IntermediateData,(byte*)NonZeroTweak,16);
			Assert::IsTrue(IntermediateData[0]==0xDF8FEA0EFF91D0E0,L"first word failed (2)",LINE_INFO());
			Assert::IsTrue(IntermediateData[1]==0xD50AD82EE69281C9,L"second word failed (2)",LINE_INFO());
			Assert::IsTrue(IntermediateData[2]==0x76F48D58085D869D,L"third word failed (2)",LINE_INFO());
			Assert::IsTrue(IntermediateData[3]==0xDF975E95B5567065,L"fourth word failed (2)",LINE_INFO());
			Threefish_256::Decryption Decryptor2((byte*)NonZeroKey);
			Decryptor2.ProcessAndXorBlockWithTweak((byte*)IntermediateData,nullptr,CompareData,(byte*)NonZeroTweak,16);
			Assert::IsTrue(memcmp(CompareData,NonZeroInData,32)==0,L"out != in",LINE_INFO());
		}

		TEST_METHOD(Threefish512TestVectorChecks)
		{
			const word64 InData[8] = {0};
			const word64 Tweak[2] = {0};
			const word64 Key[8] = {0};
			word64 IntermediateData[8]={0};
			byte CompareData[64]={0};

			Threefish_512::Encryption Encryptor1((byte*)Key);
			Encryptor1.ProcessAndXorBlockWithTweak((byte*)InData,nullptr,(byte*)IntermediateData,(byte*)Tweak,16);
			Assert::IsTrue(IntermediateData[0]==0xBC2560EFC6BBA2B1,L"first word failed (1)",LINE_INFO());
			Assert::IsTrue(IntermediateData[1]==0xE3361F162238EB40,L"second word failed (1)",LINE_INFO());
			Assert::IsTrue(IntermediateData[2]==0xFB8631EE0ABBD175,L"third word failed (1)",LINE_INFO());
			Assert::IsTrue(IntermediateData[3]==0x7B9479D4C5479ED1,L"fourth word failed (1)",LINE_INFO());
			Assert::IsTrue(IntermediateData[4]==0xCFF0356E58F8C27B,L"fifth word failed (1)",LINE_INFO());
			Assert::IsTrue(IntermediateData[5]==0xB1B7B08430F0E7F7,L"sixth word failed (1)",LINE_INFO());
			Assert::IsTrue(IntermediateData[6]==0xE9A380A56139ABF1,L"seventh word failed (1)",LINE_INFO());
			Assert::IsTrue(IntermediateData[7]==0xBE7B6D4AA11EB47E,L"eigth word failed (1)",LINE_INFO());
			           
			Threefish_512::Decryption Decryptor1((byte*)Key);
			Decryptor1.ProcessAndXorBlockWithTweak((byte*)IntermediateData,nullptr,CompareData,(byte*)Tweak,16);
			Assert::IsTrue(memcmp(CompareData,InData,32)==0,L"out != in",LINE_INFO());

			const word64 NonZeroInData[8] = {0xF8F9FAFBFCFDFEFF,0xF0F1F2F3F4F5F6F7,0xE8E9EAEBECEDEEEF,0xE0E1E2E3E4E5E6E7,0xD8D9DADBDCDDDEDF,0xD0D1D2D3D4D5D6D7,0xC8C9CACBCCCDCECF,0xC0C1C2C3C4C5C6C7};
			const word64 NonZeroTweak[2] = {0x0706050403020100,0x0F0E0D0C0B0A0908};
			const word64 NonZeroKey[8] = {0x1716151413121110,0x1F1E1D1C1B1A1918,0x2726252423222120,0x2F2E2D2C2B2A2928,0x3736353433323130,0x3F3E3D3C3B3A3938,0x4746454443424140,0x4F4E4D4C4B4A4948};

			Threefish_512::Encryption Encryptor2((byte*)NonZeroKey);
			Encryptor2.ProcessAndXorBlockWithTweak((byte*)NonZeroInData,nullptr,(byte*)IntermediateData,(byte*)NonZeroTweak,16);
			Assert::IsTrue(IntermediateData[0]==0x2C5AD426964304E3,L"first word failed (2)",LINE_INFO());
			Assert::IsTrue(IntermediateData[1]==0x9A2436D6D8CA01B4,L"second word failed (2)",LINE_INFO());
			Assert::IsTrue(IntermediateData[2]==0xDD456DB00E333863,L"third word failed (2)",LINE_INFO());
			Assert::IsTrue(IntermediateData[3]==0x794725970EB9368B,L"fourth word failed (2)",LINE_INFO());
			Assert::IsTrue(IntermediateData[4]==0x043546998D0A2A27,L"fifth word failed (2)",LINE_INFO());
			Assert::IsTrue(IntermediateData[5]==0x25A7C918EA204478,L"sixth word failed (2)",LINE_INFO());
			Assert::IsTrue(IntermediateData[6]==0x346201A1FEDF11AF,L"seventh word failed (2)",LINE_INFO());
			Assert::IsTrue(IntermediateData[7]==0x3DAF1C5C3D672789,L"eigth word failed (2)",LINE_INFO());

			Threefish_512::Decryption Decryptor2((byte*)NonZeroKey);
			Decryptor2.ProcessAndXorBlockWithTweak((byte*)IntermediateData,nullptr,CompareData,(byte*)NonZeroTweak,16);
			Assert::IsTrue(memcmp(CompareData,NonZeroInData,32)==0,L"out != in",LINE_INFO());
		}

		TEST_METHOD(Threefish1024TestVectorChecks)
		{
			const word64 InData[16] = {0};
			const word64 Tweak[2] = {0};
			const word64 Key[16] = {0};
			word64 IntermediateData[16]={0};
			byte CompareData[128]={0};

			Threefish_1024::Encryption Encryptor1((byte*)Key);
			Encryptor1.ProcessAndXorBlockWithTweak((byte*)InData,nullptr,(byte*)IntermediateData,(byte*)Tweak,16);
			Assert::IsTrue(IntermediateData[0]==0x04B3053D0A3D5CF0,L"first word failed (1)",LINE_INFO());
			Assert::IsTrue(IntermediateData[1]==0x0136E0D1C7DD85F7,L"second word failed (1)",LINE_INFO());
			Assert::IsTrue(IntermediateData[2]==0x067B212F6EA78A5C,L"third word failed (1)",LINE_INFO());
			Assert::IsTrue(IntermediateData[3]==0x0DA9C10B4C54E1C6,L"fourth word failed (1)",LINE_INFO());
			Assert::IsTrue(IntermediateData[4]==0x0F4EC27394CBACF0,L"fifth word failed (1)",LINE_INFO());
			Assert::IsTrue(IntermediateData[5]==0x32437F0568EA4FD5,L"sixth word failed (1)",LINE_INFO());
			Assert::IsTrue(IntermediateData[6]==0xCFF56D1D7654B49C,L"seventh word failed (1)",LINE_INFO());
			Assert::IsTrue(IntermediateData[7]==0xA2D5FB14369B2E7B,L"eigth word failed (1)",LINE_INFO());
			Assert::IsTrue(IntermediateData[8]==0x540306B460472E0B,L"ninth word failed (1)",LINE_INFO());
			Assert::IsTrue(IntermediateData[9]==0x71C18254BCEA820D,L"tenth word failed (1)",LINE_INFO());
			Assert::IsTrue(IntermediateData[10]==0xC36B4068BEAF32C8,L"eleventh word failed (1)",LINE_INFO());
			Assert::IsTrue(IntermediateData[11]==0xFA4329597A360095,L"12. word failed (1)",LINE_INFO());
			Assert::IsTrue(IntermediateData[12]==0xC4A36C28434A5B9A,L"13. word failed (1)",LINE_INFO());
			Assert::IsTrue(IntermediateData[13]==0xD54331444B1046CF,L"14. word failed (1)",LINE_INFO());
			Assert::IsTrue(IntermediateData[14]==0xDF11834830B2A460,L"15. word failed (1)",LINE_INFO());
			Assert::IsTrue(IntermediateData[15]==0x1E39E8DFE1F7EE4F,L"16. word failed (1)",LINE_INFO());

			Threefish_1024::Decryption Decryptor1((byte*)Key);
			Decryptor1.ProcessAndXorBlockWithTweak((byte*)IntermediateData,nullptr,CompareData,(byte*)Tweak,16);
			Assert::IsTrue(memcmp(CompareData,InData,32)==0,L"out != in",LINE_INFO());

			const word64 NonZeroInData[16] = {0xF8F9FAFBFCFDFEFF,0xF0F1F2F3F4F5F6F7,0xE8E9EAEBECEDEEEF,0xE0E1E2E3E4E5E6E7,0xD8D9DADBDCDDDEDF,0xD0D1D2D3D4D5D6D7,0xC8C9CACBCCCDCECF,0xC0C1C2C3C4C5C6C7,
				0xB8B9BABBBCBDBEBF,  0xB0B1B2B3B4B5B6B7,  0xA8A9AAABACADAEAF,  0xA0A1A2A3A4A5A6A7, 
				0x98999A9B9C9D9E9F,  0x9091929394959697,  0x88898A8B8C8D8E8F,  0x8081828384858687};
			const word64 NonZeroTweak[2] = {0x0706050403020100,0x0F0E0D0C0B0A0908};
			const word64 NonZeroKey[16] = {0x1716151413121110,0x1F1E1D1C1B1A1918,0x2726252423222120,0x2F2E2D2C2B2A2928,0x3736353433323130,0x3F3E3D3C3B3A3938,0x4746454443424140,0x4F4E4D4C4B4A4948,
				0x5756555453525150,  0x5F5E5D5C5B5A5958,  0x6766656463626160,  0x6F6E6D6C6B6A6968, 
				0x7776757473727170,  0x7F7E7D7C7B7A7978,  0x8786858483828180,  0x8F8E8D8C8B8A8988};

			Threefish_1024::Encryption Encryptor2((byte*)NonZeroKey);
			Encryptor2.ProcessAndXorBlockWithTweak((byte*)NonZeroInData,nullptr,(byte*)IntermediateData,(byte*)NonZeroTweak,16);
			Assert::IsTrue(IntermediateData[0]==0xB0C33CD7DB4D65A6,L"first word failed (2)",LINE_INFO());
			Assert::IsTrue(IntermediateData[1]==0xBC49A85A1077D75D,L"second word failed (2)",LINE_INFO());
			Assert::IsTrue(IntermediateData[2]==0x6855FCAFEA7293E4,L"third word failed (2)",LINE_INFO());
			Assert::IsTrue(IntermediateData[3]==0x1C5385AB1B7754D2,L"fourth word failed (2)",LINE_INFO());
			Assert::IsTrue(IntermediateData[4]==0x30E4AAFFE780F794,L"fifth word failed (2)",LINE_INFO());
			Assert::IsTrue(IntermediateData[5]==0xE1BBEE708CAFD8D5,L"sixth word failed (2)",LINE_INFO());
			Assert::IsTrue(IntermediateData[6]==0x9CA837B7423B0F76,L"seventh word failed (2)",LINE_INFO());
			Assert::IsTrue(IntermediateData[7]==0xBD1403670D4963B3,L"eigth word failed (2)",LINE_INFO());
			Assert::IsTrue(IntermediateData[8]==0x451F2E3CE61EA48A,L"ninth word failed (2)",LINE_INFO());
			Assert::IsTrue(IntermediateData[9]==0xB360832F9277D4FB,L"tenth word failed (2)",LINE_INFO());
			Assert::IsTrue(IntermediateData[10]==0x0AAFC7A65E12D688,L"eleventh word failed (2)",LINE_INFO());
			Assert::IsTrue(IntermediateData[11]==0xC8906E79016D05D7,L"12. word failed (2)",LINE_INFO());
			Assert::IsTrue(IntermediateData[12]==0xB316570A15F41333,L"13. word failed (2)",LINE_INFO());
			Assert::IsTrue(IntermediateData[13]==0x74E98A2869F5D50E,L"14. word failed (2)",LINE_INFO());
			Assert::IsTrue(IntermediateData[14]==0x57CE6F9247432BCE,L"15. word failed (2)",LINE_INFO());
			Assert::IsTrue(IntermediateData[15]==0xDE7CDD77215144DE,L"16. word failed (2)",LINE_INFO());

			Threefish_1024::Decryption Decryptor2((byte*)NonZeroKey);
			Decryptor2.ProcessAndXorBlockWithTweak((byte*)IntermediateData,nullptr,CompareData,(byte*)NonZeroTweak,16);
			Assert::IsTrue(memcmp(CompareData,NonZeroInData,32)==0,L"out != in",LINE_INFO());
		}

		TEST_METHOD(Skein256TestVectorChecks)
		{
			Skein Hasher(32,32); // Skein-256-256
			const byte TestData1[] = {0xFF};
			const byte TestVectorResult1[] = {
			0x0B, 0x98, 0xDC, 0xD1, 0x98, 0xEA, 0x0E, 0x50, 0xA7, 0xA2, 0x44, 0xC4, 0x44, 0xE2, 0x5C, 0x23,
			0xDA, 0x30, 0xC1, 0x0F, 0xC9, 0xA1, 0xF2, 0x70, 0xA6, 0x63, 0x7F, 0x1F, 0x34, 0xE6, 0x7E, 0xD2
			};
			Assert::IsTrue(Hasher.VerifyDigest(TestVectorResult1,TestData1,1),L"Skein-256-256 check failed.",LINE_INFO());
			const byte TestData2[] = {
			0xFF, 0xFE, 0xFD, 0xFC, 0xFB, 0xFA, 0xF9, 0xF8, 0xF7, 0xF6, 0xF5, 0xF4, 0xF3, 0xF2, 0xF1, 0xF0,
			0xEF, 0xEE, 0xED, 0xEC, 0xEB, 0xEA, 0xE9, 0xE8, 0xE7, 0xE6, 0xE5, 0xE4, 0xE3, 0xE2, 0xE1, 0xE0};
			const byte TestVectorResult2[] = {
			0x8D, 0x0F, 0xA4, 0xEF, 0x77, 0x7F, 0xD7, 0x59, 0xDF, 0xD4, 0x04, 0x4E, 0x6F, 0x6A, 0x5A, 0xC3,
			0xC7, 0x74, 0xAE, 0xC9, 0x43, 0xDC, 0xFC, 0x07, 0x92, 0x7B, 0x72, 0x3B, 0x5D, 0xBF, 0x40, 0x8B
			};
			Assert::IsTrue(Hasher.VerifyDigest(TestVectorResult2,TestData2,32),L"Skein-256-256 check failed.",LINE_INFO());
			const byte TestData3[] = {
			0xFF, 0xFE, 0xFD, 0xFC, 0xFB, 0xFA, 0xF9, 0xF8, 0xF7, 0xF6, 0xF5, 0xF4, 0xF3, 0xF2, 0xF1, 0xF0,
			0xEF, 0xEE, 0xED, 0xEC, 0xEB, 0xEA, 0xE9, 0xE8, 0xE7, 0xE6, 0xE5, 0xE4, 0xE3, 0xE2, 0xE1, 0xE0,
			0xDF, 0xDE, 0xDD, 0xDC, 0xDB, 0xDA, 0xD9, 0xD8, 0xD7, 0xD6, 0xD5, 0xD4, 0xD3, 0xD2, 0xD1, 0xD0,
			0xCF, 0xCE, 0xCD, 0xCC, 0xCB, 0xCA, 0xC9, 0xC8, 0xC7, 0xC6, 0xC5, 0xC4, 0xC3, 0xC2, 0xC1, 0xC0};
			const byte TestVectorResult3[] = {
			0xDF, 0x28, 0xE9, 0x16, 0x63, 0x0D, 0x0B, 0x44, 0xC4, 0xA8, 0x49, 0xDC, 0x9A, 0x02, 0xF0, 0x7A,
			0x07, 0xCB, 0x30, 0xF7, 0x32, 0x31, 0x82, 0x56, 0xB1, 0x5D, 0x86, 0x5A, 0xC4, 0xAE, 0x16, 0x2F
			};
			Assert::IsTrue(Hasher.VerifyDigest(TestVectorResult3,TestData3,64),L"Skein-256-256 check failed.",LINE_INFO());
		}

		TEST_METHOD(Skein512TestVectorChecks)
		{
			Skein Hasher(64,64); // Skein-512-512
			const byte TestData1[] = {0xFF};
			const byte TestVectorResult1[] = {
			0x71, 0xB7, 0xBC, 0xE6, 0xFE, 0x64, 0x52, 0x22, 0x7B, 0x9C, 0xED, 0x60, 0x14, 0x24, 0x9E, 0x5B,
			0xF9, 0xA9, 0x75, 0x4C, 0x3A, 0xD6, 0x18, 0xCC, 0xC4, 0xE0, 0xAA, 0xE1, 0x6B, 0x31, 0x6C, 0xC8,
			0xCA, 0x69, 0x8D, 0x86, 0x43, 0x07, 0xED, 0x3E, 0x80, 0xB6, 0xEF, 0x15, 0x70, 0x81, 0x2A, 0xC5,
			0x27, 0x2D, 0xC4, 0x09, 0xB5, 0xA0, 0x12, 0xDF, 0x2A, 0x57, 0x91, 0x02, 0xF3, 0x40, 0x61, 0x7A
			};
			Assert::IsTrue(Hasher.VerifyDigest(TestVectorResult1,TestData1,1),L"Skein-512-512 check failed.",LINE_INFO());
			const byte TestData2[] = {
			0xFF, 0xFE, 0xFD, 0xFC, 0xFB, 0xFA, 0xF9, 0xF8, 0xF7, 0xF6, 0xF5, 0xF4, 0xF3, 0xF2, 0xF1, 0xF0,
			0xEF, 0xEE, 0xED, 0xEC, 0xEB, 0xEA, 0xE9, 0xE8, 0xE7, 0xE6, 0xE5, 0xE4, 0xE3, 0xE2, 0xE1, 0xE0,
			0xDF, 0xDE, 0xDD, 0xDC, 0xDB, 0xDA, 0xD9, 0xD8, 0xD7, 0xD6, 0xD5, 0xD4, 0xD3, 0xD2, 0xD1, 0xD0,
			0xCF, 0xCE, 0xCD, 0xCC, 0xCB, 0xCA, 0xC9, 0xC8, 0xC7, 0xC6, 0xC5, 0xC4, 0xC3, 0xC2, 0xC1, 0xC0};
			const byte TestVectorResult2[] = {
			0x45, 0x86, 0x3B, 0xA3, 0xBE, 0x0C, 0x4D, 0xFC, 0x27, 0xE7, 0x5D, 0x35, 0x84, 0x96, 0xF4, 0xAC,
			0x9A, 0x73, 0x6A, 0x50, 0x5D, 0x93, 0x13, 0xB4, 0x2B, 0x2F, 0x5E, 0xAD, 0xA7, 0x9F, 0xC1, 0x7F,
			0x63, 0x86, 0x1E, 0x94, 0x7A, 0xFB, 0x1D, 0x05, 0x6A, 0xA1, 0x99, 0x57, 0x5A, 0xD3, 0xF8, 0xC9,
			0xA3, 0xCC, 0x17, 0x80, 0xB5, 0xE5, 0xFA, 0x4C, 0xAE, 0x05, 0x0E, 0x98, 0x98, 0x76, 0x62, 0x5B
			};
			Assert::IsTrue(Hasher.VerifyDigest(TestVectorResult2,TestData2,64),L"Skein-512-512 check failed.",LINE_INFO());
			const byte TestData3[] = {
			0xFF, 0xFE, 0xFD, 0xFC, 0xFB, 0xFA, 0xF9, 0xF8, 0xF7, 0xF6, 0xF5, 0xF4, 0xF3, 0xF2, 0xF1, 0xF0,
			0xEF, 0xEE, 0xED, 0xEC, 0xEB, 0xEA, 0xE9, 0xE8, 0xE7, 0xE6, 0xE5, 0xE4, 0xE3, 0xE2, 0xE1, 0xE0,
			0xDF, 0xDE, 0xDD, 0xDC, 0xDB, 0xDA, 0xD9, 0xD8, 0xD7, 0xD6, 0xD5, 0xD4, 0xD3, 0xD2, 0xD1, 0xD0,
			0xCF, 0xCE, 0xCD, 0xCC, 0xCB, 0xCA, 0xC9, 0xC8, 0xC7, 0xC6, 0xC5, 0xC4, 0xC3, 0xC2, 0xC1, 0xC0,
			0xBF, 0xBE, 0xBD, 0xBC, 0xBB, 0xBA, 0xB9, 0xB8, 0xB7, 0xB6, 0xB5, 0xB4, 0xB3, 0xB2, 0xB1, 0xB0,
			0xAF, 0xAE, 0xAD, 0xAC, 0xAB, 0xAA, 0xA9, 0xA8, 0xA7, 0xA6, 0xA5, 0xA4, 0xA3, 0xA2, 0xA1, 0xA0,
			0x9F, 0x9E, 0x9D, 0x9C, 0x9B, 0x9A, 0x99, 0x98, 0x97, 0x96, 0x95, 0x94, 0x93, 0x92, 0x91, 0x90,
			0x8F, 0x8E, 0x8D, 0x8C, 0x8B, 0x8A, 0x89, 0x88, 0x87, 0x86, 0x85, 0x84, 0x83, 0x82, 0x81, 0x80};
			const byte TestVectorResult3[] = {
			0x91, 0xCC, 0xA5, 0x10, 0xC2, 0x63, 0xC4, 0xDD, 0xD0, 0x10, 0x53, 0x0A, 0x33, 0x07, 0x33, 0x09,
			0x62, 0x86, 0x31, 0xF3, 0x08, 0x74, 0x7E, 0x1B, 0xCB, 0xAA, 0x90, 0xE4, 0x51, 0xCA, 0xB9, 0x2E,
			0x51, 0x88, 0x08, 0x7A, 0xF4, 0x18, 0x87, 0x73, 0xA3, 0x32, 0x30, 0x3E, 0x66, 0x67, 0xA7, 0xA2,
			0x10, 0x85, 0x6F, 0x74, 0x21, 0x39, 0x00, 0x00, 0x71, 0xF4, 0x8E, 0x8B, 0xA2, 0xA5, 0xAD, 0xB7
			};
			Assert::IsTrue(Hasher.VerifyDigest(TestVectorResult3,TestData3,128),L"Skein-512-512 check failed.",LINE_INFO());
		}

		TEST_METHOD(Skein1024TestVectorChecks)
		{
			FixedSizeSecBlock<byte,256> TestData;
			memset_z(TestData,0,256);
			TestData[0]=0xFF;

			Skein Hasher(128,128); // Skein-1024-1024
			const byte TestVectorResult[] = {
			0xE6, 0x2C, 0x05, 0x80, 0x2E, 0xA0, 0x15, 0x24, 0x07, 0xCD, 0xD8, 0x78, 0x7F, 0xDA, 0x9E, 0x35,
			0x70, 0x3D, 0xE8, 0x62, 0xA4, 0xFB, 0xC1, 0x19, 0xCF, 0xF8, 0x59, 0x0A, 0xFE, 0x79, 0x25, 0x0B,
			0xCC, 0xC8, 0xB3, 0xFA, 0xF1, 0xBD, 0x24, 0x22, 0xAB, 0x5C, 0x0D, 0x26, 0x3F, 0xB2, 0xF8, 0xAF,
			0xB3, 0xF7, 0x96, 0xF0, 0x48, 0x00, 0x03, 0x81, 0x53, 0x1B, 0x6F, 0x00, 0xD8, 0x51, 0x61, 0xBC,
			0x0F, 0xFF, 0x4B, 0xEF, 0x24, 0x86, 0xB1, 0xEB, 0xCD, 0x37, 0x73, 0xFA, 0xBF, 0x50, 0xAD, 0x4A,
			0xD5, 0x63, 0x9A, 0xF9, 0x04, 0x0E, 0x3F, 0x29, 0xC6, 0xC9, 0x31, 0x30, 0x1B, 0xF7, 0x98, 0x32,
			0xE9, 0xDA, 0x09, 0x85, 0x7E, 0x83, 0x1E, 0x82, 0xEF, 0x8B, 0x46, 0x91, 0xC2, 0x35, 0x65, 0x65,
			0x15, 0xD4, 0x37, 0xD2, 0xBD, 0xA3, 0x3B, 0xCE, 0xC0, 0x01, 0xC6, 0x7F, 0xFD, 0xE1, 0x5B, 0xA8};
			Assert::IsTrue(Hasher.VerifyDigest(TestVectorResult,TestData,1),L"Skein-1024-1024 check failed.",LINE_INFO());

			const byte TestData2 [] = {
			0xFF, 0xFE, 0xFD, 0xFC, 0xFB, 0xFA, 0xF9, 0xF8, 0xF7, 0xF6, 0xF5, 0xF4, 0xF3, 0xF2, 0xF1, 0xF0,
			0xEF, 0xEE, 0xED, 0xEC, 0xEB, 0xEA, 0xE9, 0xE8, 0xE7, 0xE6, 0xE5, 0xE4, 0xE3, 0xE2, 0xE1, 0xE0,
			0xDF, 0xDE, 0xDD, 0xDC, 0xDB, 0xDA, 0xD9, 0xD8, 0xD7, 0xD6, 0xD5, 0xD4, 0xD3, 0xD2, 0xD1, 0xD0,
			0xCF, 0xCE, 0xCD, 0xCC, 0xCB, 0xCA, 0xC9, 0xC8, 0xC7, 0xC6, 0xC5, 0xC4, 0xC3, 0xC2, 0xC1, 0xC0,
			0xBF, 0xBE, 0xBD, 0xBC, 0xBB, 0xBA, 0xB9, 0xB8, 0xB7, 0xB6, 0xB5, 0xB4, 0xB3, 0xB2, 0xB1, 0xB0,
			0xAF, 0xAE, 0xAD, 0xAC, 0xAB, 0xAA, 0xA9, 0xA8, 0xA7, 0xA6, 0xA5, 0xA4, 0xA3, 0xA2, 0xA1, 0xA0,
			0x9F, 0x9E, 0x9D, 0x9C, 0x9B, 0x9A, 0x99, 0x98, 0x97, 0x96, 0x95, 0x94, 0x93, 0x92, 0x91, 0x90,
			0x8F, 0x8E, 0x8D, 0x8C, 0x8B, 0x8A, 0x89, 0x88, 0x87, 0x86, 0x85, 0x84, 0x83, 0x82, 0x81, 0x80
			};

			const byte TestVectorResult2[] = {
			0x1F, 0x3E, 0x02, 0xC4, 0x6F, 0xB8, 0x0A, 0x3F, 0xCD, 0x2D, 0xFB, 0xBC, 0x7C, 0x17, 0x38, 0x00,
			0xB4, 0x0C, 0x60, 0xC2, 0x35, 0x4A, 0xF5, 0x51, 0x18, 0x9E, 0xBF, 0x43, 0x3C, 0x3D, 0x85, 0xF9,
			0xFF, 0x18, 0x03, 0xE6, 0xD9, 0x20, 0x49, 0x31, 0x79, 0xED, 0x7A, 0xE7, 0xFC, 0xE6, 0x9C, 0x35,
			0x81, 0xA5, 0xA2, 0xF8, 0x2D, 0x3E, 0x0C, 0x7A, 0x29, 0x55, 0x74, 0xD0, 0xCD, 0x7D, 0x21, 0x7C,
			0x48, 0x4D, 0x2F, 0x63, 0x13, 0xD5, 0x9A, 0x77, 0x18, 0xEA, 0xD0, 0x7D, 0x07, 0x29, 0xC2, 0x48,
			0x51, 0xD7, 0xE7, 0xD2, 0x49, 0x1B, 0x90, 0x2D, 0x48, 0x91, 0x94, 0xE6, 0xB7, 0xD3, 0x69, 0xDB,
			0x0A, 0xB7, 0xAA, 0x10, 0x6F, 0x0E, 0xE0, 0xA3, 0x9A, 0x42, 0xEF, 0xC5, 0x4F, 0x18, 0xD9, 0x37,
			0x76, 0x08, 0x09, 0x85, 0xF9, 0x07, 0x57, 0x4F, 0x99, 0x5E, 0xC6, 0xA3, 0x71, 0x53, 0xA5, 0x78};
			Assert::IsTrue(Hasher.VerifyDigest(TestVectorResult2,TestData2,128),L"Skein-1024-1024 check failed.",LINE_INFO());

			const byte TestData3 [] = {
			0xFF, 0xFE, 0xFD, 0xFC, 0xFB, 0xFA, 0xF9, 0xF8, 0xF7, 0xF6, 0xF5, 0xF4, 0xF3, 0xF2, 0xF1, 0xF0,
			0xEF, 0xEE, 0xED, 0xEC, 0xEB, 0xEA, 0xE9, 0xE8, 0xE7, 0xE6, 0xE5, 0xE4, 0xE3, 0xE2, 0xE1, 0xE0,
			0xDF, 0xDE, 0xDD, 0xDC, 0xDB, 0xDA, 0xD9, 0xD8, 0xD7, 0xD6, 0xD5, 0xD4, 0xD3, 0xD2, 0xD1, 0xD0,
			0xCF, 0xCE, 0xCD, 0xCC, 0xCB, 0xCA, 0xC9, 0xC8, 0xC7, 0xC6, 0xC5, 0xC4, 0xC3, 0xC2, 0xC1, 0xC0,
			0xBF, 0xBE, 0xBD, 0xBC, 0xBB, 0xBA, 0xB9, 0xB8, 0xB7, 0xB6, 0xB5, 0xB4, 0xB3, 0xB2, 0xB1, 0xB0,
			0xAF, 0xAE, 0xAD, 0xAC, 0xAB, 0xAA, 0xA9, 0xA8, 0xA7, 0xA6, 0xA5, 0xA4, 0xA3, 0xA2, 0xA1, 0xA0,
			0x9F, 0x9E, 0x9D, 0x9C, 0x9B, 0x9A, 0x99, 0x98, 0x97, 0x96, 0x95, 0x94, 0x93, 0x92, 0x91, 0x90,
			0x8F, 0x8E, 0x8D, 0x8C, 0x8B, 0x8A, 0x89, 0x88, 0x87, 0x86, 0x85, 0x84, 0x83, 0x82, 0x81, 0x80,
			0x7F, 0x7E, 0x7D, 0x7C, 0x7B, 0x7A, 0x79, 0x78, 0x77, 0x76, 0x75, 0x74, 0x73, 0x72, 0x71, 0x70,
			0x6F, 0x6E, 0x6D, 0x6C, 0x6B, 0x6A, 0x69, 0x68, 0x67, 0x66, 0x65, 0x64, 0x63, 0x62, 0x61, 0x60,
			0x5F, 0x5E, 0x5D, 0x5C, 0x5B, 0x5A, 0x59, 0x58, 0x57, 0x56, 0x55, 0x54, 0x53, 0x52, 0x51, 0x50,
			0x4F, 0x4E, 0x4D, 0x4C, 0x4B, 0x4A, 0x49, 0x48, 0x47, 0x46, 0x45, 0x44, 0x43, 0x42, 0x41, 0x40,
			0x3F, 0x3E, 0x3D, 0x3C, 0x3B, 0x3A, 0x39, 0x38, 0x37, 0x36, 0x35, 0x34, 0x33, 0x32, 0x31, 0x30,
			0x2F, 0x2E, 0x2D, 0x2C, 0x2B, 0x2A, 0x29, 0x28, 0x27, 0x26, 0x25, 0x24, 0x23, 0x22, 0x21, 0x20,
			0x1F, 0x1E, 0x1D, 0x1C, 0x1B, 0x1A, 0x19, 0x18, 0x17, 0x16, 0x15, 0x14, 0x13, 0x12, 0x11, 0x10,
			0x0F, 0x0E, 0x0D, 0x0C, 0x0B, 0x0A, 0x09, 0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 0x00
			};

			const byte TestVectorResult3[] = {
			0x84, 0x2A, 0x53, 0xC9, 0x9C, 0x12, 0xB0, 0xCF, 0x80, 0xCF, 0x69, 0x49, 0x1B, 0xE5, 0xE2, 0xF7,
			0x51, 0x5D, 0xE8, 0x73, 0x3B, 0x6E, 0xA9, 0x42, 0x2D, 0xFD, 0x67, 0x66, 0x65, 0xB5, 0xFA, 0x42,
			0xFF, 0xB3, 0xA9, 0xC4, 0x8C, 0x21, 0x77, 0x77, 0x95, 0x08, 0x48, 0xCE, 0xCD, 0xB4, 0x8F, 0x64,
			0x0F, 0x81, 0xFB, 0x92, 0xBE, 0xF6, 0xF8, 0x8F, 0x7A, 0x85, 0xC1, 0xF7, 0xCD, 0x14, 0x46, 0xC9,
			0x16, 0x1C, 0x0A, 0xFE, 0x8F, 0x25, 0xAE, 0x44, 0x4F, 0x40, 0xD3, 0x68, 0x00, 0x81, 0xC3, 0x5A,
			0xA4, 0x3F, 0x64, 0x0F, 0xD5, 0xFA, 0x3C, 0x3C, 0x03, 0x0B, 0xCC, 0x06, 0xAB, 0xAC, 0x01, 0xD0,
			0x98, 0xBC, 0xC9, 0x84, 0xEB, 0xD8, 0x32, 0x27, 0x12, 0x92, 0x1E, 0x00, 0xB1, 0xBA, 0x07, 0xD6,
			0xD0, 0x1F, 0x26, 0x90, 0x70, 0x50, 0x25, 0x5E, 0xF2, 0xC8, 0xE2, 0x4F, 0x71, 0x6C, 0x52, 0xA5};
			Assert::IsTrue(Hasher.VerifyDigest(TestVectorResult3,TestData3,256),L"Skein-1024-1024 check failed.",LINE_INFO());
		}

		TEST_METHOD(ScryptTestVectorChecks)
		{
			OriginalScrypt Instance;
			
			const byte TestVector1[]=
			{
				0x77, 0xd6, 0x57, 0x62, 0x38, 0x65, 0x7b, 0x20, 0x3b, 0x19, 0xca, 0x42, 0xc1, 0x8a, 0x04, 0x97,
				0xf1, 0x6b, 0x48, 0x44, 0xe3, 0x07, 0x4a, 0xe8, 0xdf, 0xdf, 0xfa, 0x3f, 0xed, 0xe2, 0x14, 0x42,
				0xfc, 0xd0, 0x06, 0x9d, 0xed, 0x09, 0x48, 0xf8, 0x32, 0x6a, 0x75, 0x3a, 0x0f, 0xc8, 0x1f, 0x17,
				0xe8, 0xd3, 0xe0, 0xfb, 0x2e, 0x0d, 0x36, 0x28, 0xcf, 0x35, 0xe2, 0x0c, 0x38, 0xd1, 0x89, 0x06
			};
			const byte TestVector2[]=
			{
				0xfd, 0xba, 0xbe, 0x1c, 0x9d, 0x34, 0x72, 0x00, 0x78, 0x56, 0xe7, 0x19, 0x0d, 0x01, 0xe9, 0xfe,
				0x7c, 0x6a, 0xd7, 0xcb, 0xc8, 0x23, 0x78, 0x30, 0xe7, 0x73, 0x76, 0x63, 0x4b, 0x37, 0x31, 0x62,
				0x2e, 0xaf, 0x30, 0xd9, 0x2e, 0x22, 0xa3, 0x88, 0x6f, 0xf1, 0x09, 0x27, 0x9d, 0x98, 0x30, 0xda,
				0xc7, 0x27, 0xaf, 0xb9, 0x4a, 0x83, 0xee, 0x6d, 0x83, 0x60, 0xcb, 0xdf, 0xa2, 0xcc, 0x06, 0x40
			};
			const byte TestVector3[]=
			{
				0x70, 0x23, 0xbd, 0xcb, 0x3a, 0xfd, 0x73, 0x48, 0x46, 0x1c, 0x06, 0xcd, 0x81, 0xfd, 0x38, 0xeb,
				0xfd, 0xa8, 0xfb, 0xba, 0x90, 0x4f, 0x8e, 0x3e, 0xa9, 0xb5, 0x43, 0xf6, 0x54, 0x5d, 0xa1, 0xf2,
				0xd5, 0x43, 0x29, 0x55, 0x61, 0x3f, 0x0f, 0xcf, 0x62, 0xd4, 0x97, 0x05, 0x24, 0x2a, 0x9a, 0xf9,
				0xe6, 0x1e, 0x85, 0xdc, 0x0d, 0x65, 0x1e, 0x40, 0xdf, 0xcf, 0x01, 0x7b, 0x45, 0x57, 0x58, 0x87
			};
			const byte TestVector4[]=
			{
				0x21, 0x01, 0xcb, 0x9b, 0x6a, 0x51, 0x1a, 0xae, 0xad, 0xdb, 0xbe, 0x09, 0xcf, 0x70, 0xf8, 0x81,
				0xec, 0x56, 0x8d, 0x57, 0x4a, 0x2f, 0xfd, 0x4d, 0xab, 0xe5, 0xee, 0x98, 0x20, 0xad, 0xaa, 0x47,
				0x8e, 0x56, 0xfd, 0x8f, 0x4b, 0xa5, 0xd0, 0x9f, 0xfa, 0x1c, 0x6d, 0x92, 0x7c, 0x40, 0xf4, 0xc3,
				0x37, 0x30, 0x40, 0x49, 0xe8, 0xa9, 0x52, 0xfb, 0xcb, 0xf4, 0x5c, 0x6f, 0xa7, 0x7a, 0x41, 0xa4
			};

			FixedSizeSecBlock<byte,64> Compare1,Compare2,Compare3,Compare4;

			const char TestStringPassword1[]="",TestStringPassword2[]="password",TestStringPassword3[]="pleaseletmein";
			const char TestStringSalt1[]="",TestStringSalt2[]="NaCl",TestStringSalt3[]="SodiumChloride";

			Instance.DeriveKey(Compare1,64,(byte*)TestStringPassword1,0,(byte*)TestStringSalt1,0,4,1,1);
			Instance.DeriveKey(Compare2,64,(byte*)TestStringPassword2,8,(byte*)TestStringSalt2,4,10,8,16);
			Instance.DeriveKey(Compare3,64,(byte*)TestStringPassword3,13,(byte*)TestStringSalt3,14,14,8,1);
			Instance.DeriveKey(Compare4,64,(byte*)TestStringPassword3,13,(byte*)TestStringSalt3,14,20,8,1);

			Assert::IsTrue(memcmp(Compare1,TestVector1,64)==0,L"scrypt test 1 failed.",LINE_INFO());
			Assert::IsTrue(memcmp(Compare2,TestVector2,64)==0,L"scrypt test 2 failed.",LINE_INFO());
			Assert::IsTrue(memcmp(Compare3,TestVector3,64)==0,L"scrypt test 3 failed.",LINE_INFO());
			Assert::IsTrue(memcmp(Compare4,TestVector4,64)==0,L"scrypt test 4 failed.",LINE_INFO());
		}

		/*TEST_METHOD(ScryptDebugChecks)
		{
			OriginalScrypt TestInstance;

			const word32 TestData[] =
			{
				0x7e879a21,0x4f3ec986,0x7ca940e6,0x41718f26,
				0xbaee555b,0x8c61c1b5,0x0df84611,0x6dcd3b1d,
				0xee24f319,0xdf9b3d85,0x14121e4b,0x5ac5aa32,
				0x76021d29,0x09c74829,0xedebc68d,0xb8b8c25e
			};
			const byte TestDataBytes[] =
			{
				0x7e,0x87,0x9a,0x21,0x4f,0x3e,0xc9,0x86,0x7c,0xa9,0x40,0xe6,0x41,0x71,0x8f,0x26,
				0xba,0xee,0x55,0x5b,0x8c,0x61,0xc1,0xb5,0x0d,0xf8,0x46,0x11,0x6d,0xcd,0x3b,0x1d,
				0xee,0x24,0xf3,0x19,0xdf,0x9b,0x3d,0x85,0x14,0x12,0x1e,0x4b,0x5a,0xc5,0xaa,0x32,
				0x76,0x02,0x1d,0x29,0x09,0xc7,0x48,0x29,0xed,0xeb,0xc6,0x8d,0xb8,0xb8,0xc2,0x5e
			};
			const word32 TestResult[]=
			{
				0xa41f859c,0x6608cc99,0x3b81cacb,0x020cef05,
				0x044b2181,0xa2fd337d,0xfd7b1c63,0x96682f29,
				0xb4393168,0xe3c9e6bc,0xfe6bc5b7,0xa06d96ba,
				0xe424cc10,0x2c91745c,0x24ad673d,0xc7618f81
			};
			const byte TestResultBytes[] =
			{
				0xa4,0x1f,0x85,0x9c,0x66,0x08,0xcc,0x99,0x3b,0x81,0xca,0xcb,0x02,0x0c,0xef,0x05,
				0x04,0x4b,0x21,0x81,0xa2,0xfd,0x33,0x7d,0xfd,0x7b,0x1c,0x63,0x96,0x68,0x2f,0x29,
				0xb4,0x39,0x31,0x68,0xe3,0xc9,0xe6,0xbc,0xfe,0x6b,0xc5,0xb7,0xa0,0x6d,0x96,0xba,
				0xe4,0x24,0xcc,0x10,0x2c,0x91,0x74,0x5c,0x24,0xad,0x67,0x3d,0xc7,0x61,0x8f,0x81
			};

			FixedSizeSecBlock<word32,16> IOBuf;

			memcpy(IOBuf,TestDataBytes,64);

			TestInstance.OptimizedSalsa208Core(IOBuf);
				
			Assert::IsTrue(memcmp(TestResultBytes,IOBuf,64)==0,L"Salsa 20/8 core failed.",LINE_INFO());
		}*/

		TEST_METHOD(HMACCheck)
		{
			HMAC<SHA512> Hasher512;
			std::shared_ptr<MessageAuthenticationCode> Hasher(new HMAC<SHA512>());

			const byte TestKey1[] = {0x0b,0x0b,0x0b,0x0b,0x0b,0x0b,0x0b,0x0b,0x0b,0x0b,0x0b,0x0b,0x0b,0x0b,0x0b,0x0b,
									0x0b,0x0b,0x0b,0x0b};
			const byte TestKey2[] = {0x4a,0x65,0x66,0x65};
			const byte TestKey3[] = {0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,0x10,
									 0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19};
			const byte TestResult1[] = {0x87,0xaa,0x7c,0xde,0xa5,0xef,0x61,0x9d,0x4f,0xf0,0xb4,0x24,0x1a,0x1d,0x6c,0xb0,
										0x23,0x79,0xf4,0xe2,0xce,0x4e,0xc2,0x78,0x7a,0xd0,0xb3,0x05,0x45,0xe1,0x7c,0xde,
										0xda,0xa8,0x33,0xb7,0xd6,0xb8,0xa7,0x02,0x03,0x8b,0x27,0x4e,0xae,0xa3,0xf4,0xe4,
										0xbe,0x9d,0x91,0x4e,0xeb,0x61,0xf1,0x70,0x2e,0x69,0x6c,0x20,0x3a,0x12,0x68,0x54};
			const byte TestResult2[] = {0x16,0x4b,0x7a,0x7b,0xfc,0xf8,0x19,0xe2,0xe3,0x95,0xfb,0xe7,0x3b,0x56,0xe0,0xa3,
										0x87,0xbd,0x64,0x22,0x2e,0x83,0x1f,0xd6,0x10,0x27,0x0c,0xd7,0xea,0x25,0x05,0x54,
										0x97,0x58,0xbf,0x75,0xc0,0x5a,0x99,0x4a,0x6d,0x03,0x4f,0x65,0xf8,0xf0,0xe6,0xfd,
										0xca,0xea,0xb1,0xa3,0x4d,0x4a,0x6b,0x4b,0x63,0x6e,0x07,0x0a,0x38,0xbc,0xe7,0x37};
			const byte TestResult3[] = {0xb0,0xba,0x46,0x56,0x37,0x45,0x8c,0x69,0x90,0xe5,0xa8,0xc5,0xf6,0x1d,0x4a,0xf7,
										0xe5,0x76,0xd9,0x7f,0xf9,0x4b,0x87,0x2d,0xe7,0x6f,0x80,0x50,0x36,0x1e,0xe3,0xdb,
										0xa9,0x1c,0xa5,0xc1,0x1a,0xa2,0x5e,0xb4,0xd6,0x79,0x27,0x5c,0xc5,0x78,0x80,0x63,
										0xa5,0xf1,0x97,0x41,0x12,0x0c,0x4f,0x2d,0xe2,0xad,0xeb,0xeb,0x10,0xa2,0x98,0xdd};
			const byte TestData1[] = {0x48,0x69,0x20,0x54,0x68,0x65,0x72,0x65};
			const byte TestData2[] = {0x77,0x68,0x61,0x74,0x20,0x64,0x6f,0x20,0x79,0x61,0x20,0x77,0x61,0x6e,0x74,0x20,
									  0x66,0x6f,0x72,0x20,0x6e,0x6f,0x74,0x68,0x69,0x6e,0x67,0x3f};
			const byte TestData3[] = {0xcd,0xcd,0xcd,0xcd,0xcd,0xcd,0xcd,0xcd,0xcd,0xcd,0xcd,0xcd,0xcd,0xcd,0xcd,0xcd,
									  0xcd,0xcd,0xcd,0xcd,0xcd,0xcd,0xcd,0xcd,0xcd,0xcd,0xcd,0xcd,0xcd,0xcd,0xcd,0xcd,
									  0xcd,0xcd,0xcd,0xcd,0xcd,0xcd,0xcd,0xcd,0xcd,0xcd,0xcd,0xcd,0xcd,0xcd,0xcd,0xcd,
									  0xcd,0xcd};

			Hasher512.SetKey(TestKey1,20);
			Hasher->SetKey(TestKey1,20);
			Assert::IsTrue(Hasher512.VerifyDigest(TestResult1,TestData1,8),L"HMAC-SHA-512 check 1 failed.",LINE_INFO());
			Assert::IsTrue(Hasher->VerifyDigest(TestResult1,TestData1,8),L"HMAC-SHA-512 check 2 failed.",LINE_INFO());

			Hasher512.SetKey(TestKey2,4);
			Hasher->SetKey(TestKey2,4);
			Assert::IsTrue(Hasher512.VerifyDigest(TestResult2,TestData2,28),L"HMAC-SHA-512 check 3 failed.",LINE_INFO());
			Assert::IsTrue(Hasher->VerifyDigest(TestResult2,TestData2,28),L"HMAC-SHA-512 check 4 failed.",LINE_INFO());

			Hasher512.SetKey(TestKey3,25);
			Hasher->SetKey(TestKey3,25);
			Assert::IsTrue(Hasher512.VerifyDigest(TestResult3,TestData3,50),L"HMAC-SHA-512 check 5 failed.",LINE_INFO());
			Assert::IsTrue(Hasher->VerifyDigest(TestResult3,TestData3,50),L"HMAC-SHA-512 check 6 failed.",LINE_INFO());

		}

		TEST_METHOD(VMACCheck)
		{
			AutoSeededRandomPool RNG;
			FixedSizeSecBlock<byte,32> Key;
			RNG.GenerateBlock(Key,Key.size());
			FixedSizeSecBlock<byte,16> Nonce0;
			RNG.GenerateBlock(Nonce0,Nonce0.size());
			FixedSizeSecBlock<byte,16> Nonce1;
			RNG.GenerateBlock(Nonce1,Nonce1.size());
			FixedSizeSecBlock<byte,8> Tag0;
			FixedSizeSecBlock<byte,8> Tag1;
			FixedSizeSecBlock<byte,64> TestData;
			RNG.GenerateBlock(TestData,TestData.size());

			VMAC<AES,64> Hasher;
			Hasher.SetKeyWithIV(Key,Key.size(),Nonce0,Nonce0.size());
			Hasher.CalculateDigest(Tag0,TestData,TestData.size());
			Hasher.Resynchronize(Nonce1,Nonce1.size());
			Hasher.CalculateDigest(Tag1,TestData,TestData.size());

			Assert::IsFalse(memcmp(Tag0,Tag1,Tag0.size())==0,L"VMAC check failed, digests are equal",LINE_INFO());
		}

		TEST_METHOD(BLAKE2bTestVectorChecks)
		{
			const byte TestKey[] =
			{
				0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1a,0x1b,0x1c,0x1d,0x1e,0x1f,0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2a,0x2b,0x2c,0x2d,0x2e,0x2f,0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3a,0x3b,0x3c,0x3d,0x3e,0x3f
			};

			BLAKE2bMAC Hasher(64,TestKey,64);

			const byte TestData2[]={0x00};

			const byte TestVectorResult1[]=
			{
				0x10,0xeb,0xb6,0x77,0x00,0xb1,0x86,0x8e,0xfb,0x44,0x17,0x98,0x7a,0xcf,0x46,0x90,0xae,0x9d,0x97,0x2f,0xb7,0xa5,0x90,0xc2,0xf0,0x28,0x71,0x79,0x9a,0xaa,0x47,0x86,0xb5,0xe9,0x96,0xe8,0xf0,0xf4,0xeb,0x98,0x1f,0xc2,0x14,0xb0,0x05,0xf4,0x2d,0x2f,0xf4,0x23,0x34,0x99,0x39,0x16,0x53,0xdf,0x7a,0xef,0xcb,0xc1,0x3f,0xc5,0x15,0x68
			};
			const byte TestVectorResult2[]=
			{
				0x96,0x1f,0x6d,0xd1,0xe4,0xdd,0x30,0xf6,0x39,0x01,0x69,0x0c,0x51,0x2e,0x78,0xe4,0xb4,0x5e,0x47,0x42,0xed,0x19,0x7c,0x3c,0x5e,0x45,0xc5,0x49,0xfd,0x25,0xf2,0xe4,0x18,0x7b,0x0b,0xc9,0xfe,0x30,0x49,0x2b,0x16,0xb0,0xd0,0xbc,0x4e,0xf9,0xb0,0xf3,0x4c,0x70,0x03,0xfa,0xc0,0x9a,0x5e,0xf1,0x53,0x2e,0x69,0x43,0x02,0x34,0xce,0xbd
			};

			Assert::IsTrue(Hasher.VerifyDigest(TestVectorResult1,nullptr,0),L"BLAKE2b test one failed.",LINE_INFO());
			Assert::IsTrue(Hasher.VerifyDigest(TestVectorResult2,TestData2,1),L"BLAKE2b test two failed.",LINE_INFO());
		}

		TEST_METHOD(BLAKE2sTestVectorChecks)
		{
			const byte TestKey[] =
			{
				0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1a,0x1b,0x1c,0x1d,0x1e,0x1f
			};

			BLAKE2sMAC Hasher(32,TestKey,32);

			const byte TestData2[]={0x00};

			const byte TestVectorResult1[]=
			{
				0x48,0xa8,0x99,0x7d,0xa4,0x07,0x87,0x6b,0x3d,0x79,0xc0,0xd9,0x23,0x25,0xad,0x3b,0x89,0xcb,0xb7,0x54,0xd8,0x6a,0xb7,0x1a,0xee,0x04,0x7a,0xd3,0x45,0xfd,0x2c,0x49
			};
			const byte TestVectorResult2[]=
			{
				0x40,0xd1,0x5f,0xee,0x7c,0x32,0x88,0x30,0x16,0x6a,0xc3,0xf9,0x18,0x65,0x0f,0x80,0x7e,0x7e,0x01,0xe1,0x77,0x25,0x8c,0xdc,0x0a,0x39,0xb1,0x1f,0x59,0x80,0x66,0xf1
			};

			Assert::IsTrue(Hasher.VerifyDigest(TestVectorResult1,nullptr,0),L"BLAKE2s test one failed.",LINE_INFO());
			Assert::IsTrue(Hasher.VerifyDigest(TestVectorResult2,TestData2,1),L"BLAKE2s test two failed.",LINE_INFO());
		}

		TEST_METHOD(BLAKE2bpTestVectorChecks)
		{
			const byte TestKey[] =
			{
				0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1a,0x1b,0x1c,0x1d,0x1e,0x1f,0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2a,0x2b,0x2c,0x2d,0x2e,0x2f,0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3a,0x3b,0x3c,0x3d,0x3e,0x3f
			};

			BLAKE2bpMAC Hasher(64,TestKey,64);

			const byte TestData2[]={0x00};

			const byte TestVectorResult1[]=
			{
				0x9d,0x94,0x61,0x07,0x3e,0x4e,0xb6,0x40,0xa2,0x55,0x35,0x7b,0x83,0x9f,0x39,0x4b,0x83,0x8c,0x6f,0xf5,0x7c,0x9b,0x68,0x6a,0x3f,0x76,0x10,0x7c,0x10,0x66,0x72,0x8f,0x3c,0x99,0x56,0xbd,0x78,0x5c,0xbc,0x3b,0xf7,0x9d,0xc2,0xab,0x57,0x8c,0x5a,0x0c,0x06,0x3b,0x9d,0x9c,0x40,0x58,0x48,0xde,0x1d,0xbe,0x82,0x1c,0xd0,0x5c,0x94,0x0a
			};
			const byte TestVectorResult2[]=
			{
				0xff,0x8e,0x90,0xa3,0x7b,0x94,0x62,0x39,0x32,0xc5,0x9f,0x75,0x59,0xf2,0x60,0x35,0x02,0x9c,0x37,0x67,0x32,0xcb,0x14,0xd4,0x16,0x02,0x00,0x1c,0xbb,0x73,0xad,0xb7,0x92,0x93,0xa2,0xdb,0xda,0x5f,0x60,0x70,0x30,0x25,0x14,0x4d,0x15,0x8e,0x27,0x35,0x52,0x95,0x96,0x25,0x1c,0x73,0xc0,0x34,0x5c,0xa6,0xfc,0xcb,0x1f,0xb1,0xe9,0x7e
			};
	
			Assert::IsTrue(Hasher.VerifyDigest(TestVectorResult1,nullptr,0),L"BLAKE2bp test one failed.",LINE_INFO());
			Assert::IsTrue(Hasher.VerifyDigest(TestVectorResult2,TestData2,1),L"BLAKE2bp test two failed.",LINE_INFO());
		}

		TEST_METHOD(BLAKE2spTestVectorChecks)
		{
			const byte TestKey[] =
			{
				0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1a,0x1b,0x1c,0x1d,0x1e,0x1f
			};

			BLAKE2spMAC Hasher(32,TestKey,32);

			const byte TestData2[]={0x00};

			const byte TestVectorResult1[]=
			{
				0x71,0x5c,0xb1,0x38,0x95,0xae,0xb6,0x78,0xf6,0x12,0x41,0x60,0xbf,0xf2,0x14,0x65,0xb3,0x0f,0x4f,0x68,0x74,0x19,0x3f,0xc8,0x51,0xb4,0x62,0x10,0x43,0xf0,0x9c,0xc6
			};
			const byte TestVectorResult2[]=
			{
				0x40,0x57,0x8f,0xfa,0x52,0xbf,0x51,0xae,0x18,0x66,0xf4,0x28,0x4d,0x3a,0x15,0x7f,0xc1,0xbc,0xd3,0x6a,0xc1,0x3c,0xbd,0xcb,0x03,0x77,0xe4,0xd0,0xcd,0x0b,0x66,0x03
			};
	
			Assert::IsTrue(Hasher.VerifyDigest(TestVectorResult1,nullptr,0),L"BLAKE2sp test one failed.",LINE_INFO());
			Assert::IsTrue(Hasher.VerifyDigest(TestVectorResult2,TestData2,1),L"BLAKE2sp test two failed.",LINE_INFO());
		}
	};
}