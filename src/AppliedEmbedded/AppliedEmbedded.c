#include "CodingProblems.h"


/** 
* For every input num, sort it against a running list 
* Keeps state of previously sorted nums and saves current
* sorted list in sortedOutput
*/
void streamSort(StreamSorter_t* sorter, uint16_t num, uint16_t* sortedOutput) {

	static int counter = 0; 
	static uint16_t leftIdx = 0;
	static uint16_t rightIdx = 0;
 	
 	//First time sorter is called
	if(counter == 0) {
		memset(sorter->currSortedStream, 0, MAX_STREAM_BUFFER_SIZE); 
		sorter->currSortedStream[0] = num; 
		sortedOutput = sorter->currSortedStream; 
	} else if (counter >= MAX_STREAM_BUFFER_SIZE) {
		//Stream buffer cannot hold any more numbers to sort! 
		return; 
	} else {

		// ----- METHOD 1
		//Compare num to elements in the list and figure out where to insert it 
		//May need a linked list for this instead?

		//if num > last elem (max elem so far) in the list, add num to end of list
		//if num < first elem in list (add num to front of list)
		//Otherwise loop through and find out where to insert in the middle  

		//TODO

		// ---- METHOD 2 
		//If inserting in the middle, use binary search method? (See geeksforgeeks)
		//TODO

	}
}

bool binSearch(uint16_t *arr, uint16_t arrSize, uint16_t target) {
	uint16_t left = 0; 
	uint16_t right = arrSize - 1; 
	uint16_t mid = 0;

	if(arr == NULL) {
		return false; 
	}

	while(left <= right) {
		mid = (left + right)/2

		if(arr[mid] == target) {
			return true; 
		} else if(target < arr[mid]) {
			right = mid - 1; 
		}  else {
			left = mid + 1; 
		}
	}

	//Element not in list 
	return false;
}

//Search condition is to find the first or last occurrence of n
//in a array. This occurs if n is the last element in array or 
//number after n is bigger than n 
//if we havent met this search criteria, keep searching to the right,
//For first occurrence, if we find n and number at left neighbor is smaller than n
//or n is at first index, we found first occurrence 
int32_t binSearchFindBound(uint32_t n, bool isFirst, uint32_t left, uint32_t right, uint32_t* arr) {
	uint32_t mid = 0; 

	while(left <= right) {
		mid = (left + right)/2;

		if(isFirst) {

			//First occurrence found
			if((arr[mid] == n) && ((mid == 0) || arr[mid-1] < n)) {
				return mid;
			} 

			//Keep searching on left side of array
			right = mid -1; 
		} else {

			//Found last occurrence 
			if((arr[mid] == n) && (mid == (len-1) || arr[mid+1] > n)) {
				return mid; 
			}

			//Keep searching right side of array 
			left = mid + 1; 
		}


	}
	//Not found
	return -1; 
}

//Count total number of occurrences of n in array 
//Fastest and most efficient approach is to use binary search 
//to find first and last occurrence of n, subtract their indices 
//and add one and that gives total number of occurrences 
uint32_t countOccurrences(uint32_t n, uint32_t* arr, uint32_t len) {

	if((arr == NULL) || len == 0) {
		return 0; 
	}

	int32_t firstIdx = binSearchFindBound(n, true, 0, len-1, arr);
	int32_t lastIdx = binSearchFindBound(n, false, 0, len-1, arr);

	if(firstIdx < 0) {
		return 0; 
	} 

	if(lastIdx < 0) {
		return 1; //Only first occurrence found 
	} 

	return (lastidx-firstIdx) + 1; 
}


/** 
* Given API function unsigned int read4(unsigned char *buf4), 
* Which returns up to four chars at a time from a file
* Returns actual number of characters read
* Read(...) is a wrapper function to read n characters from file
* and return in buf. 
* 
* Read more characters that what's left in file 
* input = "abc"
* read4(buf4,4) --> 3,  "buf4 = abc"
* read4(buf4, 3) --> 0, "buf4 = "" 
* 
* input = "abcdefg"
* read4(buf4, 4) --> 4, buf4 = abcd
* read4(buf4, 4) --> 3, buf4 = efg
* read4(buf4, 2) --> 0, buf4 = ""
**/

//Dummy function - given to us 
unsigned int read4(uint8_t *buf4) {
	return 0; 
}

unsigned int read(uint8_t* buf, unsigned int n) {

	unsigned int totalRead = 0; 
	unsigned int numCharsRead4 = 1; //needs to start off, non-zero  

  	//While we havent read requested num of chars, and we havent reached end of file 
	while((totalRead < n) && numCharsRead4 != 0) {
		numCharsRead4 = read4(buf + totalRead);
		totalRead+=numCharsRead4; 
	}

	if(totalRead < n) {
		buf[n] ="\0";
		return totalRead;
	} 

	return n;
}


/**
 * The read4 API is defined in the parent class Reader4.
 *     int read4(char *buf4);
 *
Note:
The read function may be called multiple times.
The difference between this question and the first version is that the read() function will be called multiple times.
The trouble here will be as the following example if using the first version solution:
file: “abcdefg”
read(3) read(2) read(2) should be “abc” “de” “fg”
but using first version solution it will print “abc” “ef” “”
This is because when you use read4() to read, the pointer to read file has already moved to “e” after the first call of read4(). So it’s not correct any more.
In order to solve, we need to persist the characters that has been already read by using read4 but it’s not put into the result of read().
In the solution below, I am using a buf4[] to store the characters read by using read4 and also a buf4Size and buf4Index to keep track of the size of the buf4 and the next character to use in buf4[].
 */

//read(..) First version behavior
//read(3) will get "abcd" --> truncates and returns "abc" (internal fp now //at e
// read(2) will get "efg"--> truncates to "ef"

//Expected second version behavior
//read(3) should get "abc" (read4 returns abcd)
//read(2) should get "de"  (read4 returns efg, but our stored chars: //abcdefg), last call returned 0 to 2, pointer should start at 3 and then //return chars at 3,4
//read(2) should get "fg", (read4 returns "", 0 chars) (we already stored "abcdefg", internal pointer at 5, we return chars at 5,6)

/** 
* Add chars one by one into output buffer. When we call read4, cache the 
* returned chars into a buf4. Always read a char from our cached buf4
* to add to output buffer, before calling read4 again to get the next set 
* of 4 chars. 
*/

// New version needs to track internally, what was read from read4 
//each time read4 is called. 

typedef struct {
	char *buf4;
	unsigned int numCharsRead4;
	unsigned int readPos;  
} BufState_t;

unsigned int read(BufState_t *obj, char *buf, unsigned int n) {

    //Location of where to write next byte in output buf
    unsigned int writeIdx = 0;
    
    //While total chars read is less than requested number, n
    while(writeIdx < n) {
        
        //Check if we've written all bytes that were cached
        //in buf4, to output buf, if yes, call read4 again to
        //get next chunk of bytes
        //Reset read position
        if(obj->readPos == obj->numCharsRead4) {
            obj->readPos = 0;
            obj->numCharsRead4 = read4(obj->buf4); 
            
            //If we've reached end of file, return total chars read
            //which is write index
            if(obj->numCharsRead4 == 0) {
                return writeIdx;
            }
        } 
        //Copy each char from cached buf4, to output buf,
        //Increment buf4 read index
        buf[writeIdx] = obj->buf4[obj->readPos++];

        //Increment writeIdx 
        writeIdx++; 
    }
    
    return writeIdx;

}

//Compress/Encode input string using run length encoding algorithm
//for each group of consecutive repeating characters, if group len 1
//append char to output s, if group > 1, append char followed by group's length
#define MAX_CNT_LEN		50
char count[MAX_CNT_LEN] = {" "};

bool runLenEncoding(char *input, char *compressed) {

	if((strlen(input) == 0) || (compressed == NULL)) {
		return false; 
	}

	unsigned int rdIdx = 0; 
	unsigned int wrIdx = 0; 
	unsigned int cnt = 0; 

	//Put first char of input into output string 
	char c = input[rdIdx++];
	compressed[wrIdx++] = c;
	cnt++; 

	//Find out what the groups are and their lengths 
	for(int i=rdIdx; rdIdx<strlen(input); rdIdx++) {

		if(input[rdIdx] == c) {
			cnt++; 

		} else {
			//we found different char, save it temporarily
			c = input[rdIdx];

			//Check to see if we need to write count of previous char
			//Reset count variable	
			if(cnt != 1) {

				//Convert cnt to a string and then copy into compressed 
				sprintf(count, "%d", cnt);

				for(int k = 0; count[k] != " "; k++) {
					compressed[wrIdx++] = count[k];
				}
				
				cnt = 1;
			}
			//Write new char to output string 
			compressed[wrIdx++] = c; 

		}
	}
	compressed[wrIdx] = '\0';
	return true; 
}

bool transferChunkedEncoding(char *input, char *compressed, int compressedLen) {
	//Step 1: grab a chunk of bytes (based on chunk size it should be) from input stream 
	//Create compressed stream which has size of chunk (contained in 4 bytes), then the characters of the 
	//chunk 
	//Format: <hexadecimal format size of chunk><chunk itself>\r\n 
	//terminating chunk has length zero 
}

bool huffmanEncoding(char *input, char *compressed) {

}

//compression - reduce number of bits used to store data, can be lossy
//encoding - convert data to special format for secure transmission of data

//Fixed length encoding or variable length encoding 
//Fixed length - each char given a binary code with same number of bits 
//Huffman (variable length encoding)
//Chars that occur more frequently can use less bits to represent them 




