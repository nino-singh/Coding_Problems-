#include "CppuTest/TestHarness.h"

extern "C" {
#include "ArraysAndStrings/Arrays_Strings.h"
}

//Global test parameters 
char testStr[] = "Reverse";
char testStr2[] = "Setup";
char testStrBig[257] = {0};

TEST_GROUP(StringsTestSuite) {

	void setup() {
		//Run before every test
	}

	void teardown() {
		//Run after every test 
	}
};

TEST(StringsTestSuite, isUniqueBasicTest) {
	CHECK_EQUAL(false, isUnique(testStr));
}

TEST(StringsTestSuite, isUniqueTrueTest) {	
	CHECK_EQUAL(true, isUnique(testStr2));
}


