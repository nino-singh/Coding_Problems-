#include "Arrays_Strings.h"

char charMap[256] = {0};

/* 
 * Check if string has all unique characters.
 */
bool isUnique(char *str) {

	//Not possible to have more than 256 unique chars if 
	//the string is made up of ASCII chars 
	if(strlen(str) > 256) {
		return false; 
	}

	for(int i=0; i<strlen(str); i++) {
		if(charMap[str[i]] > 0) {
			return false; 
		}
		charMap[str[i]]++;
	}

	return true;

	//Another way to reduce space use, if string is only composed of 
	//lower case letters a to z, than a to z can be represented by integers
	//from 0 to 25. We can use a 32 bit integer and use each bit position 
	//to encode if the letter has been seen more than once or not. 
	//
	//int32_t charMask = 0; 
	//for(int i = 0; i<strlen(str); i++) {
	//	if(charMask & (1 << (str[i]-'a')) > 0) {
	//		return false;
	//	}
	//	charMask |= (1 << (str[i] - 'a'));
	//}
	//return true;
	//
}


