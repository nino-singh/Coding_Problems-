#include "CppUTest/TestHarness.h"

extern "C" {
#include "BitHacks.h"
}

TEST_GROUP(BitHacksTestSuite) {

	void setup() {
		//Run before every test
	}

	void teardown() {
		//Run after every test 
	}
}; 

TEST(BitHacksTestSuite, ReverseBytesUInt16Test) {
	LONGS_EQUAL(1536, reverseBytesUint16(6));
}

TEST(BitHacksTestSuite, ReverseBytesUInt32Test) {
	LONGS_EQUAL(67305985, reverseBytesUint32(0x01020304));
}

TEST(BitHacksTestSuite, ReverseBitsTest) {
	LONGS_EQUAL(0x60000000, reverseBits(0x00000006));
}

TEST(BitHacksTestSuite, ReverseBitsFasterTest) {
	LONGS_EQUAL(0x60000000, reverseBitsFaster(0x00000006));
}

TEST(BitHacksTestSuite, SwapXORTest) {
	unsigned int a = 12; 
	unsigned int b = 20; 
	swapNumsXOR(&a,&b);
	LONGS_EQUAL(20, a);
	LONGS_EQUAL(12, b);
}

TEST(BitHacksTestSuite, SwapNumsTest) {
	unsigned int a = 12; 
	unsigned int b = 20; 
	swapNums(&a,&b);
	LONGS_EQUAL(20, a);
	LONGS_EQUAL(12, b);
}
