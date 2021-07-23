#ifndef _ARRAYS_AND_STRINGS_H_
#define _ARRAYS_AND_STRINGS_H_

#ifdef __cplusplus 
extern "C" {
#endif 

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

/*General common problem from GeeksForGeeks */
void reverseWord(char* inStr);

/* InterviewBit Amazon, Strings */
void reverseString(char* sentence);

/* Cracking the Coding Interview Problems P1.1 */
bool isUnique(char *str);

/* Cracking the Coding Interview Problems P1.2 */
bool IsPermutation(char *str1, char* str2);

/* InterviewBit, Amazon Strings, also same as EOPI, P7.1
 * Implement atoi function, ask clarifying questions for corner cases
 */
int strToInt(char* s);

/* EOPI, Strings P7.3 */
bool isPalindrome(char *str);

/* InterviewBit, Amazon Strings 
 * Also similar to EOPI (Elements of Programming Interviews) Strings P7.8
 * Convert integer to roman numeral 
 * */
void intToRoman(int num, char* outputRoman);

/* EOPI, Strings, P7.10, also same as LeetCode String Compression 
* Run length encode and decode functions */
void runLenEncode(char *inStr, char *compressed);
void runLenDecode(char *compressed, char* outStr);

/* EOPI, Strings, P7.11 
 * Implement Elias Gamma Encoding of positive ints */
void eliasGammaEncode(int num, char* outStr);

int longestConsecutiveSeq(int* arr);

#ifdef __cplusplus	
}
#endif 
#endif 
