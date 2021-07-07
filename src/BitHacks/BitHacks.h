#ifndef __BIT_HACKS_H__
#define __BIT_HACKS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h> 

#define SET_BIT(X, N)			((X) |= (1 << (N)))
#define CLR_BIT(X, N)			((X) &= ~(1 << (N)))
#define CLR_N_TRAIL_BITS(X, N)	((X) &= (~0 << (N)))

#define SIZEOF(X)		((size_t)(&(X) + 1) - ((size_t)&(X))) 

bool isBigEndian(void);
bool isOdd(int num);
unsigned int checkParity(int num);
bool hasZeroByte(unsigned int num); 
bool areOppositeSigns(int a, int b);
char toUpper(char c); // c |= ' '
char toLower(char c); //c &= '_'
char invertCase(char c); //c ^= ' '
unsigned int absBitwise(unsigned int);
unsigned int getPosInAlphabet(char c); //c & ascii(31)
uint16_t reverseBytesUint16(uint16_t i); 
uint32_t reverseBytesUint32(uint32_t i);
unsigned int reverseBits(unsigned int i);
unsigned int reverseBitsFaster(unsigned int i);
unsigned int swapTwoBitsAtPos(unsigned int num, unsigned int p, unsigned int q);
unsigned int swapAdjacentBits(unsigned int i); 
unsigned int swapIndividualBitsAtPos(unsigned int num, unsigned int p, unsigned int q);
void swapNums(unsigned int *a, unsigned int *b);
void swapNumsXOR(unsigned int *a, unsigned int *b);
int negativeNum(unsigned int num);
unsigned int countSetBits(unsigned int num);
unsigned int countSetBitsInMemory(uint8_t *pMem, unsigned int len, uint8_t* BitSetTable);
unsigned int totalSetBitsUntilN(unsigned int N);
int clearBitsMsbToI(int num, unsigned int i); 
int clearBitsIToZero(unsigned int num, unsigned int i);
uint8_t sum(uint8_t a, uint8_t b);
unsigned int addBitwise(unsigned int a, unsigned int b);


/** Problems from Cracking the Coding Interview - Ch. 5 **/
int insertIntegerBits(int N, int M, unsigned int i, unsigned int j);
void printDecToBin(double num, int k_precision);
int flipBitToWin(int num);
void printNextNum(int num);
unsigned int numBitsConvertAToB(int A, int B);
int32_t swapBitsPairwise(int32_t num);
void drawLine(char *screen, int width, int x1, int x2, int y);

/* Related Problems in Chapter 16, Moderate level */
int getMaxNum(int a, int b);

/* Implement operations with only using add operation */
int negateNum(int a);
int multiply(int a, int b);
int subtract(int a, int b);
int divide(int a, int b);

#ifdef __cplusplus	
}
#endif
#endif 
