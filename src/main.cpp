
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "BitHacks/BitHacks.h"

using namespace std;

int main(void) {
	
	char testStr[] = "Reverse";

	reverseStr(testStr); 
	printf("%s\n", testStr);
	return 0;

}
