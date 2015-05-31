#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define S11 7
#define S12 12
#define S13 17
#define S14 22

#define S21 5
#define S22 9
#define S23 14
#define S24 20

#define S31 4
#define S32 11
#define S33 16
#define S34 23

#define S41 6
#define S42 10
#define S43 15
#define S44 21


#define MAGIC_NUMBER_AA 0x67452301L
#define MAGIC_NUMBER_BB 0xEFCDAB89L
#define MAGIC_NUMBER_CC 0x98BADCFEL
#define MAGIC_NUMBER_DD 0x10325476L

#define F(x, y, z)  (((x) & (y))|((~x) & (z)))
#define G(x, y, z)  (((x) & (z))|((y) & (~z)))
#define H(x, y, z)  ((x) ^ (y) ^ (z))
#define I(x, y, z)  ((y) ^ (x) | (~z))

#define II(a, b, c, d, m, s, t) \
	(a = (b)+((a + I(b, c, d) + m + t) << s))

#define FF(a, b, c, d, m, s, t) \
	(a = (b)+((a + F(b, c, d) + m + t) << s))

#define GG(a, b, c, d, m, s, t) \
	(a = (b)+((a + G(b, c, d) + m + t) << s))

#define HH(a, b, c, d, m, s, t) \
	(a = (b)+((a + H(b, c, d) + m + t) << s))




#define changeToUnsignedInteger(a, b, c, d)  (((a)<<24) | ((b) << 16) | ((c) << 8) | (d))




int K[64] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,


	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,


	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,


	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391,
};


char hexCharacter[] = {
	'0', '1', '2', '3',
	'4', '5', '6', '7',
	'8', '9', 'A', 'B',
	'C', 'D', 'E', 'F'
};

void transformIntegerToHex(int decimal, char result[4]){
	int index = (decimal & 0xFF000000);
	result[0] = hexCharacter[index];
	index = (decimal & 0xFF0000);
	result[1] = hexCharacter[index];
	index = (decimal & 0xFF00);
	result[2] = hexCharacter[index];
	index = (decimal & 0xFF);
	result[3] = hexCharacter[index];

}

void changeBlockToAarray(const char* block, int* array){
	int len = strlen(block);
	if (len != 64)return;
	int i = 0, j = 0;
	for (i = 0, j = 0; i< 64; i += 4, j++){
		array[j] = changeToUnsignedInteger(block[i], block[i + 1], block[i + 2], block[i + 3]);
	}
}

void dumpBlock(const char* block){
	int length = strlen(block);
	printf("length = %d\n", length);
	int i = 0;
	for (i = 0; i < length; i++){
		printf("%x", block[i]);
		if (!((i + 1) % 4)){
			if (!((i + 1) % 16))
				printf("\n");
			else
				printf("\t");
		}
	}
}



void transform(const char* block, int result[4]){

	int a = result[0] = MAGIC_NUMBER_AA;
	int b = result[1] = MAGIC_NUMBER_BB;
	int c = result[2] = MAGIC_NUMBER_CC;
	int d = result[3] = MAGIC_NUMBER_DD;


	int Marray[16] = { 0 };
	changeBlockToAarray(block, Marray);

	FF(a, b, c, d, Marray[0], S11, K[0]);
	FF(d, a, b, c, Marray[1], S12, K[1]);
	FF(c, d, a, b, Marray[2], S13, K[2]);
	FF(b, c, d, a, Marray[3], S14, K[3]);
	FF(a, b, c, d, Marray[4], S11, K[4]);
	FF(d, a, b, c, Marray[5], S12, K[5]);
	FF(c, d, a, b, Marray[6], S13, K[6]);
	FF(b, c, d, a, Marray[7], S14, K[7]);
	FF(a, b, c, d, Marray[8], S11, K[8]);
	FF(d, a, b, c, Marray[9], S12, K[9]);
	FF(c, d, a, b, Marray[10], S13, K[10]);
	FF(b, c, d, a, Marray[11], S14, K[11]);
	FF(a, b, c, d, Marray[12], S11, K[12]);
	FF(d, a, b, c, Marray[13], S12, K[13]);
	FF(c, d, a, b, Marray[14], S13, K[14]);
	FF(b, c, d, a, Marray[15], S14, K[15]);


	GG(a, b, c, d, Marray[0], S21, K[16]);
	GG(d, a, b, c, Marray[1], S22, K[17]);
	GG(c, d, a, b, Marray[2], S23, K[18]);
	GG(b, c, d, a, Marray[3], S24, K[19]);
	GG(a, b, c, d, Marray[4], S21, K[20]);
	GG(d, a, b, c, Marray[5], S22, K[21]);
	GG(c, d, a, b, Marray[6], S23, K[22]);
	GG(b, c, d, a, Marray[7], S24, K[23]);
	GG(a, b, c, d, Marray[8], S21, K[24]);
	GG(d, a, b, c, Marray[9], S22, K[25]);
	GG(c, d, a, b, Marray[10], S23, K[26]);
	GG(b, c, d, a, Marray[11], S24, K[27]);
	GG(a, b, c, d, Marray[12], S21, K[28]);
	GG(d, a, b, c, Marray[13], S22, K[29]);
	GG(c, d, a, b, Marray[14], S23, K[30]);
	GG(b, c, d, a, Marray[15], S24, K[31]);


	HH(a, b, c, d, Marray[0], S31, K[32]);
	HH(d, a, b, c, Marray[1], S32, K[33]);
	HH(c, d, a, b, Marray[2], S33, K[34]);
	HH(b, c, d, a, Marray[3], S34, K[35]);
	HH(a, b, c, d, Marray[4], S31, K[36]);
	HH(d, a, b, c, Marray[5], S32, K[37]);
	HH(c, d, a, b, Marray[6], S33, K[38]);
	HH(b, c, d, a, Marray[7], S34, K[39]);
	HH(a, b, c, d, Marray[8], S31, K[40]);
	HH(d, a, b, c, Marray[9], S32, K[41]);
	HH(c, d, a, b, Marray[10], S33, K[42]);
	HH(b, c, d, a, Marray[11], S34, K[43]);
	HH(a, b, c, d, Marray[12], S31, K[44]);
	HH(d, a, b, c, Marray[13], S32, K[45]);
	HH(c, d, a, b, Marray[14], S33, K[46]);
	HH(b, c, d, a, Marray[15], S34, K[47]);

	II(a, b, c, d, Marray[0], S41, K[48]);
	II(d, a, b, c, Marray[1], S42, K[49]);
	II(c, d, a, b, Marray[2], S43, K[50]);
	II(b, c, d, a, Marray[3], S44, K[51]);
	II(a, b, c, d, Marray[4], S41, K[52]);
	II(d, a, b, c, Marray[5], S42, K[53]);
	II(c, d, a, b, Marray[6], S43, K[54]);
	II(b, c, d, a, Marray[7], S44, K[55]);
	II(a, b, c, d, Marray[8], S41, K[56]);
	II(d, a, b, c, Marray[9], S42, K[57]);
	II(c, d, a, b, Marray[10], S43, K[58]);
	II(b, c, d, a, Marray[11], S44, K[59]);
	II(a, b, c, d, Marray[12], S41, K[60]);
	II(d, a, b, c, Marray[13], S42, K[61]);
	II(c, d, a, b, Marray[14], S43, K[62]);
	II(b, c, d, a, Marray[15], S44, K[63]);


	result[0] += a;
	result[1] += b;
	result[2] += c;
	result[3] += d;
}


void fillLengthInfo(char lengthInfo[8], int length){
	int location = 0;
	while (length){
		int temp = length % 10;
		length = (int)(length - temp) / 10;
		lengthInfo[7 - location] = (char)(temp);
//		printf("%x\n", lengthInfo[63 - location]);
		location++;
	}
}

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {

	int result[4] = { 0 };
	char* testString = "adminadminadmin";
	int length = strlen(testString);
	char lengthInfo[8] = { '\0' };
	fillLengthInfo(lengthInfo, length);


	/*
	printf("Dump all lengthInfo:\n");
	int stepI = 0;
	for (stepI = 0; stepI < 8; stepI++)
		printf("%x", lengthInfo[stepI]);
	printf("\n");
	printf("length = %d\n", length);
	*/
	
	int needPaddingZeros = abs(512 - (length + 64) % 512);
	printf("needPaddingZeros = %d\n", needPaddingZeros);
	
	char* block = (char*)malloc(64 + 1);
	memset(block, '0', 64);
	block[64] = '\0';


	memcpy(block, testString, length);
	block[(int)length] = 1;
	memcpy(block + 56 , lengthInfo, 8);
	dumpBlock(block);



	transform(block, result);
	printf("\n%x%x%x%x\n", result[0], result[1], result[2], result[3]);

	free(block);
	block = NULL;
	
	return 0;
}
