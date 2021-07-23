#include "BitHacks.h"
#include "stdio.h"

/* Easy warm up problems */
//Pass in a string and reverse it in place
void reverseStr(char*inStr) {
	char *pBegin = inStr; 
	//Make sure to start end pointer on last char and not on null char
	char *pEnd = inStr + (strlen(inStr)-1); 
	char temp = 0; 

	//R e v e r s e \0 
   // ^           ^
  // pBegin	      pEnd 

	//Swap characters from outside, work are way inward 
	//when pBegin is equal to pEnd we've finished
	while(pBegin < pEnd) {
		temp = *pEnd; 
		*pEnd = *pBegin;
		*pBegin = temp;
		pBegin++;
		pEnd--;
	}
}


/** Easy **/
//Techie Delight Bit Hacks problems 
bool isBigEndian(void) {
	uint8_t i = 1; 

	return ((*(uint8_t*) &i) == 0);
}

/** Easy **/
//Techie Delight Bit Hacks problems 
//LSB for odd number is 1, even number its 0 
bool isOdd(int num) {

	return (num & 1) == 1; 
}

unsigned int checkParity(int num) {
	unsigned int result  = 0; 

	while(num) {
		result ^= 1;
		num = num & (num-1);
	}
	return result; 
}

/** Easy **/
//Techie Delight Bit Hacks problems 
bool areOppositeSigns(int a, int b) {
	//Negative number has 1 in MSB, positive number as 0
	//X ^ Y (if bits are different result is 1)
	//So if have opposite signs, MSB(X) ^ MSB (Y) --> results in 1 
	//Two positives will give MSB = 0;
	//Two negatives will give MSB = 0; 

	return ((a ^ b) < 0 ? true : false); 
}

/** Easy **/
//Techie Delight Bit Hacks problems 
char toUpper(char c) {
	return c | ' ';
}

/** Easy **/
//Techie Delight Bit Hacks problems 
char toLower(char c) {
	return c | '_';
}

/** Easy **/
//Techie Delight Bit Hacks problems 
char invertCase(char c) {
	return c & 31; 
} 

/** Easy **/
//Techie Delight Bit Hacks problems 
uint16_t reverseBytesUint16(uint16_t i) {

	uint8_t c1, c2 = 0;
	c1 = (i & 0xff); 
	c2 = (i >> 8) & 0xff; 

	return ((c1 << 8) + c2);
}

/** Easy **/
//Techie Delight Bit Hacks problems 
uint32_t reverseBytesUint32(uint32_t i) {
	uint8_t b1, b2, b3, b4 = 0; 

	b1 = (i & 0xff);
	b2 = (i >> 8) & 0xff; 
	b3 = (i >> 16) & 0xff; 
	b4 = (i >> 24) & 0xff; 

	return (uint32_t)((b1 << 24) | (b2 << 16) | (b3 << 8) | b4); 
}

/** Easy **/
//Techie Delight Bit Hacks problems 
void swapNums(unsigned int *a, unsigned int *b) {

	if(a != b) {

		*a = *a + *b; 
		*b = *a - *b; 
		*a = *a - *b; 
	}
}

/** Easy **/
//Techie Delight Bit Hacks problems 
void swapNumsXOR(unsigned int *a, unsigned int *b)
{        
	if(a != b) {
		*a ^= *b; 
		*b ^= *a; 
		*a ^= *b;
	}
 
}

/** Easy **/
unsigned int absBitwise(unsigned int n) {
	
	unsigned int bitWidth = sizeof(n) * 8 - 1;
	//To get negative version of positive number n
	//-n = ~n + 1 
  	//To get positive version of negative number n
  	//n = ~(-n - 1)

  	//So check if n is positive or not
  	//If n positive n >> 31 is 0, if negative, its all 1's --> -1 
  	// here if n is negative we return (n-1) ^ -1 (subtract one and flip bits)
  	return (n + (n >> bitWidth)) ^ (n >>bitWidth); 
}

/** Easy **/
//Stanford graphics bit manipulation 
bool hasZeroByte(unsigned int num) {
	uint8_t *pByte = (uint8_t*) &num; 

	for(int i=0; i<sizeof(num); i++) {
		if(pByte[i] == 0) {
			return true;
		}
		pByte++;
	}
	return false; 
}

/** Easy **/
unsigned int reverseBits(unsigned int num) {
	unsigned int numBits = (sizeof(num) * 8) - 1; 
	unsigned int result = 0; 
	uint8_t bit = 0;

	for(int i=0; i<numBits; i++) {
		bit = num & 1; 
		//If bit is 1, swap ith bit with numBits-i position
		//If bit is zero, then prepending o doesnt matter because result already 
		//has zero at MSB since its unsigned 
		if(bit) {
			result |= (1 << (numBits - i));
		}
		
		num>>=1; 
	}

	return result; 

}

/** Medium **/
unsigned int reverseBitsFaster(unsigned int num) {
	unsigned int bitCnt = sizeof(num) * 8 - 1; 
	unsigned int result = num; 

	//Drop the first lsb since its already saved in reverse num
	num >>= 1; 

	// While there are still 1's in num continue looping 
	//Left shift by one to make room for each bit of num in the reverse num 
	//Keep track of how many shift we do, then at the end, shift reverse num by that many
	//times to push out the leading zeros of num which are left in reverse num. 
	while(num) {
		result <<= 1; 
		result |= (num & 1);
		num >>= 1; 
		bitCnt--; 
	}
	result <<= bitCnt; 

	return result; 

}

/** Medium **/
unsigned int swapTwoBitsAtPos(unsigned int num, unsigned int p, unsigned int q) {
    
    int result = num; 
    if(p == q) {
        return result; 
    }
    
    int bit1Mask = 1 << p;
    int bit2Mask = 1 << q;
    
    if(((num & bit1Mask) >> p) ^ ((num & bit2Mask) >> q)) {
       num ^= (1 << p);
       num ^= (1 << q);
       result = num;
    }
    return result; 
}

/** Medium **/
unsigned int swapAdjacentBits(unsigned int i) {
	return 0;
}

/** Hard **/
unsigned int swapIndividualBitsAtPos(unsigned int num, unsigned int p, unsigned int q) {
	return 0; 
}


// Subtraction of 1 from a number makes trailing zeros of that number one's
//up to the least significant one which becomes 0. The remaining signficant bits 
//are unchanged. So n-1 creates a mask that unsets n's least significant 1 from right to left 
// So we are incrementally unsetting each set bit until there arent any left 
//This will loop for exactly the number of set bits that are in num 

/** Easy **/
unsigned int countSetBits(unsigned int num) {
	unsigned int cnt = 0; 

	while(num) {
		num &= (num-1);
		cnt++;
	}
	return cnt; 
}

/** Medium Hard **/
unsigned int countSetBitsInMemory(uint8_t *pMem, unsigned int len, uint8_t* BitSetTable) {
	//Assuming we already have a look up table that stores number of set bits 
	//for every byte from 0 to 255, we just look up each byte of our memory chunk 
	//in the table and sum it up 
	unsigned int totalSetBits = 0; 
	unsigned int i = 0; 
	for(i = 0; i < len; i++) {
		totalSetBits += BitSetTable[pMem[i]]; 
	}
	return totalSetBits; 
}

/** Medium/Hard **/
unsigned int totalSetBitsUntilN(unsigned int N) {

	//Simple and slow way is to count set bits in each int using Brian Kernigans method 
	//and then sum up the counts

	//Harder but more efficient way is to sum up bits in each bit position across all numbers by
	//observing patterns about how 0's and 1's alternate. You don't have to count set bits in every
	//single number 

	//OR you can approach this byte by byte and say if we have a pre generated look up table (assuming)
	//we have the memory to store this, and its quick to generate it 
	//Look up table has number of set bits for each byte from 0 to 255 

	//Loop through all integers 1 to N, for each int n, extract each byte and index into look up table 
	//set bits for an integer n will be sum of set bits for each byte in N 

	return 0; 
}

int clearBitsMsbToI(int num, unsigned int i) {

	//Clear bits from most significant bit to ith position
	//Create mask with 1 in ith position 
	//Subtracting mask by 1 will create leading zeros with last i bits set to 1's
	return (num & ((1 << i) - 1)); 

}

int clearBitsIToZero(unsigned int num, unsigned int i) {
	return (num & (~0 << (i+1))); 
}

//Given two integers, insert M into N, so that M starts at bit j and ends at bit i
//Cracking the Coding Interview, Chapter 5, problem 1
int insertIntegerBits(int N, int M, unsigned int i, unsigned int j) {

	//Zero out bits from j to i in N (mask with all 1's except 0's from j to i)
	//Create left bit mask 1111(j)00 .., create right bit make 000(i)11..
	//Merge left and right bit masks together to create full mask 

	//Ex. j=4, i=2, using bytes 

	int leftMask = ~0; 
	leftMask = (j < 31) ? (leftMask << (j + 1)) : 0;  //Ex with byte: (11111111) --> 11100000

	int rightMask = (1 << i) - 1; //Ex. with byte: (00000100 --> 00000011, subtract 1 will unset the 1 bit and flip all bits after it

	//Concat masks to create full zeroes mask from j to i
	int bitMask = leftMask | rightMask; //Ex. with byte: 11100011

	//Clear bits in N from pos j to i
	N &= bitMask; 

	//Shift M so that its LSB starts at i
	M <<= i; 

	//Merge M and N 
	return (N | M);
}

//Given a fractional number between 0 and 1, print its binary representation 
//Cracking the Coding Interview, Chapter 5, problem 2, only print up to 32 characters 
void printDecToBin(double num, int k_precision) {

	//Ex. num = 0.47 -->Get binary 0 and 1's to represent this number 
	//0.47 * 2 = 0.94 --> if(A >= 1) --> 1, otherwise 0 --> 0
	//A * 2 = B = 0.94 * 2 = 1.88 if(B >= 1) --> 1 B= (B-1) = 0.88 (get rid of integral part)
	//B * 2 = C = 0.88 *2 = 1.76, --> 1
	//.
	//.
	//.
	//Keep going until we've added reached k number of chars (precision)
	double r = num * 2;

	printf("%s", ".");

	while(k_precision) {
		if(r >= 1) {
			printf("%s", "1");
			num = r - 1; //subtract integral part out 
		} else {
			printf("%s", "0");
			num = r;
		}
		k_precision--; 
		r = num * 2; 
	}
	printf("\n");
}

//You can choose to flip one bit from 0 to 1 in the sequence such that 
//you create the longest sequence of 1's you can create 
//Cracking the Coding Interview, Chapter 5, problem 2,
int flipBitToWin(int num) {

	//Ex. 1775 (11011101111)
	//Ex. 111101011100110 (parenthesis indicate number of 1's), <bracket is number of 0's>
	//    (4)<1>(1)<1>(3)<2>(2)<1>
	// Longest 1's sequence is when there is a single 0 between two contiguous 1's sequences 
	// Every time we find this pattern, flip the 0 and keep track of the result as maxOnesSequence we've seen
	//so far, if we come across another one these patterns flip the bit and calculate to see if current one's
	//sequence would return higher max ones sequence 


	//You can flip one zero bit to 1 
	if(num == 0) {
		return 1;
	}

	//No need to flip a bit, this is sequence of all one's 
	if(num == -1) {
		return sizeof(num);
	}

	uint8_t bit = 0; 
	unsigned int prevOnes = 0;
	unsigned int currOnes = 0; 
	unsigned int maxOnesSequence = 1; //Can always flip a single zero to 1

	while(num) {
		if(num & 1) {
			currOnes++; 
		} else {
			//Current bit is 0, check next bit
			//if next bit is 1, save curr Ones sequence in previous before moving on 
			prevOnes = ((num & 2) == 0) ? 0 : currOnes;
			currOnes = 0; //reset currOnes sequence counter 
		}
		num = (int)((unsigned int) num >> 1);
		//num >>>=1; //Use logical shift because number could be negative 

		//Check if pattern of prevOnes, than zero, than currOnes (flip the zero) is greater than previous Max
		if((prevOnes + currOnes + 1) > maxOnesSequence) {
			maxOnesSequence = prevOnes + currOnes + 1; 
		}
	}

	return maxOnesSequence;
}

//Cracking the Coding Interview, Problem 5.4
//Print next smallest and next largest number that has same number of ones 
//as num 
void printNextNum(int num) {
	//Take a look at example numbers from 0 to 8
	// 0000, 0001, 0010,0011, 0100, 0101, 0110, 0111, 1000
	//If number is power of 2 it only has single set bit 
	//To get next smallest num is getting next smallest poewr of two, 
	//Example: num = 4 , next Biggest is (num <<= 1) (multiply 4 * 2^1 = 8)
	//next smalleset is num >>= 1 (Divide num/(2^1) = 2)

	//For numbers that are not power of 2, need a different approach 

}

unsigned int numBitsConvertAToB(int A, int B) {
	
	if(A == B) {
		return 0;
	}

	int mask = A ^ B; 
	unsigned int cnt = 0; 

	while(mask) {
		mask = mask & (mask -1);
		cnt++;
		mask = (int)((unsigned int) mask >> 1);
	}
	return cnt; 
}

/* Swap odd and even bits in an integer with as few 
 * instructions as possible. 
 */
int32_t swapBitsPairwise(int32_t num) {
	//Select all even bits and left shift them by one
	//so they are in odd bit positions 
	//Even bits mask 
	int32_t evenBits = (num & 0x55555555) << 1;
	
	//Select all odd bits and right shift them by one so
	//they are in even bit positions
	//For right shift, make it logical right shift, bc num could 
	//be negative. 
	int32_t oddBits = (int32_t)((uint32_t)(num & 0xaaaaaaaa) >> 1); 
	
	return (evenBits | oddBits);
}

void drawLine(char *screen, int width, int x1, int x2, int y) {
	return; 
}

/* Related Problems in Chapter 16, Moderate level */
int getMaxNum(int a, int b) {
	return 0; 
}

/* Implement operations with only using add operation */
int negateNum(int a) {
	return ~a+1;
}

int multiply(int a, int b) {
	unsigned posA = 0;

	if(a < 0) {
		posA = ~a + 1;
	}	

	for(int i=0; i<b; i++) {
		posA+=posA;
	}
	negateNum(posA);
}

int subtract(int a, int b) {
	return 0; 
}

int divide(int a, int b) {
	return 0;
}

/*InterviewBit Amazon Bit Manipulation problems */
//All integers in array appear twice except for one. It appears only once 
//Find that integer. 
int singleNumber(const int* arr, int len) {
	//We can use XOR to find the unique number 
	//arr = {7 ,3, 4, 3, 5, 6, 5, 6}
	//XOR properties: num ^ num = 0, num ^ 0 = num
	//XOR is commutative and associative, so if we were to rearrange numbers
	//7 ^ ( 3^3 ) ^ (4^4) ^ (5^5) ^ (6^6)
	//= 7 ^ 0 ^ 0 ^ 0 ^ 0
	//= 7 ^ 0 = 7
	int result = arr[0]; 

	for(int i=1; i<len; i++) {
		result ^=arr[i];
	}
	return result; 
}


//All integers in array appear thrice except one. It appears once.
//Find that integer 
int singleNumberII(const int*arr, int len)
{
	return 0; 
}

