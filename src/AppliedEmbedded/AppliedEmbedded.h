#ifndef __APPLIED_EMBEDDED_PROBLEMS_H__	
#define __APPLIED_EMBEDDED_PROBLEMS_H__	

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>

#define MAX_STREAM_BUFFER_SIZE	64

typedef struct {

	uint16_t currSortedStream[MAX_STREAM_BUFFER_SIZE];

} StreamSorter_t;

void streamSort(StreamSorter_t* sorter, uint16_t num, uint16_t* sortedOutput); 

//Do binary search to find if target num exists in arr
bool binSearch(uint16_t *arr, uint16_t arrSize, uint16_t target);

//Butterfly Network interviw question for Embedded Sw Engineer role 
//Find number of occurrences of integer n, in a sorted array 
//https://www.geeksforgeeks.org/count-number-of-occurrences-or-frequency-in-a-sorted-array/ 
//https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/
//Ex. 1,2,3,4....50.....78,78,78,78,78,79,79,80...100
//Do bin search to find an occurrence 
//Find first occurrence and last occurrence and subtract their indices to get 
//total number of occurrences of that number in the arrayś

//Binary search criteria: Look for number n, such that its left neighbor is n-1
	//Return index of n (this will be first occurrence of n)
//Binary search criteria: Look for number n, such that its right neighbor is n+1
	//Return index of n (this will be last occurrence of n)
int32_t binSearchFindBound(uint32_t n, bool isFirst, uint32_t left, uint32_t right, uint32_t* arr);
//Count total number of occurrences of n in array 
//Fastest and most efficient approach is to use binary search 
//to find first and last occurrence of n, subtract their indices 
//and add one and that gives total number of occurrences 
int countOccurrences(uint32_t n, uint32_t* arr, uint32_t len);

//Minimum number of steps required to convert string 1 to string 2 
// Three operations permitted: insert, delete, replace character
void editDistance(char *str1, char *str2); 

//Given an API function read4(char* buf), write wrapper function to read any number of 
//bytes specified from a file that internally managed by read4 API function. We don't
//know size of file

//Version 1: Works if read is called once 
unsigned int read(uint8_t* buf, unsigned int n);

//Version 2: If read is called multiple times, track internally what we've already
//read from read4 
unsigned int read(struct BufState* state, uint8_t* buf, unsigned int n);

//Similar question to: 
//https://www.geeksforgeeks.org/run-length-encoding/ 
//https://leetcode.com/problems/string-compression/
void runLengthEncoding(char *input, int len, char* encoded);

//Similar question is LeetCode:
//https://leetcode.com/problems/encode-and-decode-strings/solution/
void transferChunkedEncoding(char *input, int len, char* encoded);

//Huffman Coding 
//https://leetcode.com/discuss/interview-question/125263/construct-huffman-tree/124125 

//Similar but harder question:
//https://leetcode.com/discuss/interview-question/416316/google-onsite-software-engineer-huffman-coding-algorithm
void huffmanEncode(char *input, int len, char* encoded);
void huffmanDecode(char *input, int len, char* decoded);

//Encode and Decode TinyURL
//https://leetcode.com/problems/encode-and-decode-tinyurl/solution/ 
void encodeUrl(char *longUrl, char* encodedShortUrl);
void decodeTinyUrl(char *tinyUrl, char* decodedUrl);


//----------------------------------------------------------------------------------
//We have a large file stored somewhere. The network is very slow. Design an algorithm to efficiently transfer required bytes of data to a single PC on the network.
//Note: We know the portion of the file we want; eg: 10k - 20k
//https://leetcode.com/discuss/interview-question/system-design/632537/Design-an-algorithm-to-efficiently-transfer-required-bytes-of-data-to-a-single-PC-on-the-network.

//Should protocol run over TCP or UDP? 
//TCP - connection oriented (uses handshake protocol to establish connection) and reliable 
/*
- Delivery Acknowledgements 
- Re-transmission 
- Delays transmission when network is congested 
- Easy error detection 
- TCP rearranges packets in specific order (packets are related to one another)
- Header size is 20 bytes
- Does error checking but does error recovery 
*/
//UDP - connection-less and doesn't guarantee delivery of frames but less overhead so its fast to achieve higher bit rates for real-time streaming 
/* 
- Supports bandwidth intensive applications that can tolerate packet loss
- less delay
- can send bulk quantity of packets
- Possibility of data loss
- allows small transaction (DNS look up)
- Each packet is completely independent of another packet 
- Header size is 8 bytes 
- Does error checking but drops erroroneous packets 
*/
//Each chunk <4 bytes representing chunk len><chunk bytes><2 bytes for checksum, SHA hash>
//Length tells you size of chunk payload bytes plus includes fixed length of chunk checksum 
//Chunk bytes present a predefined chunk frame which has a sequence number, if sequence number is zero (chunk frame also has metadata about codec used, 
//video container format?)
//Client receives each chunk, computes hash to verify correctness, than decodes/decompresses chunk 
//Bit resolution of chunk data can depend on bandwidth, transfer rate can be adjusted along with bit resolution (size of chunk) 
// If download is interrupted, client should keep track of where it is in receiving chunks (cache received chunks that haven't been processed)
//Should resume interrupted download when network is back 
//Does the server have ability to buffer/cache the file or some parts before its sent? 

//------------------------------------------------------------------------
//For real-time video streaming: we want guaranteed low latency, and efficient transmissions with occassional data loss 
//We should be able to detect network bandwidth and based on bandwidth we adjust our transmission bit rate and perhaps our video frame resolution

//Push based protocols
//If we need to support both streaming and command/response between client and server than we may need a connection oriented protocol
//Client establishes connection with server, client requests video stream and server starts sending data, server also mantains a session to listen for 
//commands from the client (these protocols can work over UDP or TCP, and use RTP which is real time transport protocol)

// Raw video frame bytes --> H.264 encode (video frame) --> (Encoded frame + metadata) --> Chunked Frame: <size of chunk payload><chunk payload><SHA>
// Each chunk transmitted over UDP? 

//
// RTSP, RTP, UDP

//Client 
// DESCRIBE and SETUP header requests
// Initialize set up by sending commands to server as well as important info about the connection (ack by server) 
//- RTSP version clients supports, transport protocol to use for data flow, associated UDP or TCP port info 
//Server will return a stream ID for this session 

//PLAY request
//After negotiation of transport parameters is complete, client will issue PLAY command
//Server can begin sending RTP data stream on separate UDP port 

//TEARDOWN request 
//Client decides to close the stream, command sent along with session ID 

//EXAMPLE: RTSP using TCP, UDP based RTP delivery of stream, RTCP for command/control 

//Rtsp Server

//Create
//Add Session, Remove Session
//Push Frame 

//Can process OPTION, DESCRIBE, SETUP, PLAY, AND TEARDOWN requests
//Can send OPTIONS, DESCRIBE, ANNOUNCE, SETUP commands 

//Uses RtspConnection object which can be tied to a stream ID
//Can use TCPServer object to set up connection 

//Pull-based protocols 
//based on HTTP protocol and consists of communication between client and server where client is responsible for sending request to server and server 
//starts communication where client downloads video streaming, streaming speed depends on bandwidth of network 
//Common type of pull based protocol is progressive download, client sends request to server, and starts pulling media content as quickly as possible

// HTTP (HLS, MPEG-DASH, Adobe HTTP dynamic streaming)

//Example system: The goal is to record video from a network camera onto disk. The camera has an RTSP server that provides an H.264 encoded stream which 
//it sends via RTP to a player. I have successfully played the stream using VLC, but would like to customize the process.

/* 
Functional requirements
Move a large file across a slow network to a single PC
Target a specific range of the file (i.e. byte offsets)
Goal is to do this efficiently. How do you define efficiency? Ex. Using the least amount of bandwidth/retries, lowest latency?
Are there other clients that may want to download the same file? From the same local area network? From a different network?
Are there any considerations around fairness to other clients using the same network?
Do we trust the server serving the file? What if it is compromised?
Is there any sensitive data in the file?
Scale requirements
How large is the file? How large is the portion of the file we want? Is it so large that it doesn’t fit on a single PC?
What’s the simple, naive way?

Client initiates a request to the server with a file path and byte offset range to download. Server starts sending the file back. If the request times out, the client will start over again. What’s wrong here? It’s very wasteful for the client to restart the entire download, especially if the portion of the file we are trying to download is very large.
What’s a better way to approach the problem?

High level
Can we break down the file to be downloaded into smaller chunks to be transferred? If there is any network timeout, we only need to retry the chunk and the loss is at the chunk level.
The client machine will store individual chunks and be responsible for re-assembling the file at the end of the download.
Save network bandwidth by having the server compress each chunk before transmitting to client.
What network protocol to use for transferring the file? Prefer TCP which has already solved a number of problems such as reliability, flow congestion, etc.
Protocol Algorithm

Clients wants to download a specific portion of a file and constructs the following input parameter:
Network file path which can be used to uniquely identify the file and server hosting the file
Byte range offset into the file to be retrieved
Server is responsible for breaking the file down into chunks (say 256 KB). Server will return back a range of chunks to the client which need to be downloaded
For each chunk
Client checks if the chunk is already downloaded in its client side cache (persisted to disk to survive crashes/restarts)
Client sends request to the server with chunk to be retrieved
Note: This can be done in batches of chunks but general idea is the same.
Server will generate a checksum for each chunk, compress the chunk, and transmit the chunk + checksum (ex. SHA hash) to the client. Client will verify the SHA hash of the chunk on the client side.
When all chunks are downloaded, client will re-assemble the file and delete any cached files
Additional considerations

Client should re-use TCP connection to avoid TCP slow start overhead which will be amplified in slow network.
Algorithm can survive entire restart if the server were to crash and become unavailable for a long period of time. Client can resume from where it left off.
If it’s desirable for the client to verify the integrity of the downloaded file content with the entire file integrity, we can use hash tree technique where we have the root hash of the entire file. Client can request hashes of the branches which were not downloaded and then generate the root hash locally to see if it matches.
Other considerations

Are there other clients which are trying to download this file from other networks (which may not be slow)?
If so, we could have this file cached elsewhere (CDN, cache servers, etc) to speed up future downloads from other clients?
Do we trust the server which is serving the file?
If not, there could be a different trusted server which stores a directory of file paths + root hashes which can be used to verify the contents of the file.
Are we concerned with transferring the file securely over the network?
If so, we can consider using HTTPS to securely transfer the file chunks.
*/ 

//----------- Lyft Multi-stream problem
/*
Declare Stream class that can hold numbers.
it has operations add() read() and remove()
you have to add or read or remove given number of elements to Stream.

Multi Stream (There are infinite number of streams)
add or remove stream to multi stream.
declare only one operation read.
read from multi stream, when you are done reading the first stream, the pointer has to set automatically to next stream and so on, when you finished reading all chars say null
https://leetcode.com/problems/flatten-2d-vector/ 

//-------------- Google TCP Stream problem 
https://leetcode.com/discuss/interview-question/772987/Google-or-Phone-or-TcpStream
https://leetcode.com/discuss/interview-question/740927/Google-or-Online-Assesment-or-Read-Stream-of-bytes 
https://leetcode.com/discuss/interview-question/892726/TCP-Sender-Receiver 
https://aticleworld.com/socket-programming-in-c-using-tcpip/

Implement the below interface with the constraint that there's only a finite amount of memory available to the stream impementation

interface TcpStream {
  // Save a packet in the stream, at ‘offset’ from the stream beginning.
  void takePacket(int offset, byte[] data);
  // Read data from stream.
  // If the data at the current position is not yet available, return 0
  // Otherwise, read data into dest and return the number of bytes read
  int read(byte[] dest);
}


-------------------------- Entire interview (Expert level) - Qualcomm 
https://www.geeksforgeeks.org/qualcomm-interview-set-2/ 

Notable concept questions 
1) How is memory transferred in IPC?
2) Difference between library call and system call 
3) How the OS handles Page Faults?
4) Explain the layers of the OSI model with their brief explanation.

Coding questions: 
1) Implement strstr function optimal way
2) Convert singly linked list to BST 
3) Convert between Big and little endian 
4) Write program to implement memcpy on your own
5) Timer module code // you need to write code for the 
timer module which actually handles timeout functionality 
for all clients and execute handlers of client at timeout. 
(things they looked for are how you design a given problem, 
callback functions, function pointers,etc) 
6) Program to reverse singly linked list, detect loop in single linked list 

---------------- Lyft Self-driving SDE level 5 position 
Phone Interview Question (finding minimum number of <object>s to cover some total range)
There are houses numbered from 1 to 1000.
There are satellites positioned to cover the house broadcasting.
Given two arrays L and R, L[i] and R[i] represents the house range where L[i] < R[i].
At any time, i satellite will cover houses between L[i] and R[i].
Return minimum number of satellites to cover all houses or else return -1 if all houses are not covered.

//Same problems using different analogies (Array, Dynamic Programming, Greedy)
https://leetcode.com/problems/video-stitching/
https://leetcode.com/problems/minimum-number-of-taps-to-open-to-water-a-garden/

-------- Producer/Consumer Synchronization Problem (Bounded Buffer)
https://leetcode.com/discuss/interview-question/1001879/C%2B%2B-or-Producer-Consumer-Synchronization-Problem-or-Embedded-or-Operating-System

-------- Google Phone Screen (Product stream)

https://leetcode.com/discuss/interview-question/364396/
Design a data structure with get() and insert(int val) function for a stream of integers which can give you the product of last k terms from end.

Ex. k=3;
insert(4), insert(5), insert(10), insert(-1), get(), insert(3), get()
Output:- [NULL, NULL, NULL, NULL, -50, NULL, -30]

---- Google Phone Screen (Product of K Consecutive numbers)
https://leetcode.com/discuss/interview-question/336746/Google-or-Onsite-or-Product-of-K-consecutive-numbers 

*/

#ifdef __cplusplus	
}
#endif

#endif 
