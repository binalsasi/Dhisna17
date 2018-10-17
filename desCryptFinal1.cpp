/*
*	An encryption program that encrypts data using the DES algorithm
*	Author : Binal S
*	Date   : 21 - 09 - 2016
*	Reference : "The DES Algorithm Illustrated", J.Orlin Grabbe
*		http://page.math.tu-berlin.de/~kant/teaching/hess/krypto-ws2006/des.htm
*/

#include<stdio.h> 

//	The Tables (yes, They were manually entered. :) )
const int eTable[48] = {32,1,2,3,4,5,4,5,6,7,8,9,8,9,10,11,12,13,12,13,14,15,16,17,16,17,18,19,20,21,20,21,22,23,24,25,24,25,26,27,28,29,28,29,30,31,32,1};

const unsigned int S[8][4][16]={14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13,  15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9,  10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12,  7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14,  2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3,  12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8,9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13,  4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1,13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6,1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12,  13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11};

const unsigned int P[32] = {16,7,20,21,29,12,28,17,1,15,23,26,5,18,31,10,2,8,24,14,32,27,3,9,19,13,30,6,22,11,4,25};

const int pc1[56] = {57,49,41,33,25,17,9,1,58,50,42,34,26,18,10,2,59,51,43,35,27,19,11,3,60,52,44,36,63,55,47,39,31,23,15,7,62,54,46,38,30,22,14,6,61,53,45,37,29,21,13,5,28,20,12,4};

const int pc2[48] = {14,17,11,24,1,5,3,28,15,6,21,10,23,19,12,4,26,8,16,7,27,20,13,2,41,52,31,37,47,55,30,40,51,45,33,48,44,49,39,56,34,53,46,42,50,36,29,32};

const unsigned int shifts[16] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};

const int ip[64] = { 58,50,42,34,26,18,10,2,60,52,44,36,28,20,12,4,62,54,46,38,30,22,14,6,64,56,48,40,32,24,16,8,57,49,41,33,25,17,9,1,59,51,43,35,27,19,11,3,61,53,45,37,29,21,13,5,63,55,47,39,31,23,15,7};
	
unsigned long ebits(unsigned int R);
unsigned int f(unsigned int R, unsigned long k);

int main(){
	int i,j;

	unsigned char Mo[1024] = {0}, M[8] = {0}, K[8]= {0};
	unsigned long C[10] = {0}, kp = 0;

/*	Test Case
	unsigned char M[8] = { 0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef}, K[8] = {0x13,0x34,0x57,0x79,0x9b,0xbc,0xdf,0xf1 };
*/

	printf("\nMessage [Max : 1024]: ");         scanf("%s", Mo);
	printf("Key [8 characters only] : ");       scanf("%s", K);

//	STEP 1
//	applying permutation using table pc1
	for(i = 0; i < 56; i++){
			kp = kp | ((((unsigned long)(K[(pc1[i]/8)])) & (unsigned long)(0x100>>(pc1[i]%8)))<<(55+(pc1[i]%8)-i));
	}
	kp =  kp>>8;

//	splitting it into 2 28bit values
	unsigned int c[17]= {0}, d[17]={0};
	c[0] = kp >> 28;
	d[0] = kp & 0xfffffffUL;

//	temporary variables for generating 16 subkeys
	unsigned long k[16] = {0};

//	generating the 16 permutations for subkeys and concatenating them
	for(i=1;i<17;i++){
		c[i] = c[i-1] << shifts[i-1];
		c[i] = c[i] | ((c[i] & 0x30000000)>>28);
		c[i] = c[i] & 0xfffffff;

		d[i] = d[i-1] << shifts[i-1];
		d[i] = d[i] | ((d[i] & 0x30000000)>>28);
		d[i] = d[i] & 0xfffffff;

		k[i-1] = (unsigned long)d[i];
		k[i-1] = k[i-1] << 8;
		k[i-1] = k[i-1] | (((unsigned long) c[i])<<36);
	}

	unsigned long subkeys[16] = {0};

//	generating the 16 subkeys through permutation looking up table PC2
	for(j = 0; j<16; j++){
		for(i = 0; i<48; i++){
			subkeys[j] = subkeys[j] | (((k[j] & ( 0x8000000000000000UL >> (pc2[i]-1)))<<(pc2[i]-1))>>i);
		}
	}
	
//	checking if size of M is an integral value of 8 (i.e. whether it consists of n* 64bit blocks)
//	if non integral, 0s are padded
	int size = 0, n;
	for(;Mo[size+1] != '\0'; size++);
	if(size%8!=0){
		n = size/8 + 1;
		for(i = size + 1; i< n*8; i++)
			Mo[i] = 0;
		if(i<1024)
			Mo[i] = '\0';
	}
	else
		n = size/8;

//	encrypting one 64 bit block at a time
	for(j=0; j<n; j++){
		int k;
		for(i=j*8,k=0 ; k<8; i++,k++){
			M[k] = Mo[i];
		}


//		STEP 2
		unsigned long m = 0;

//		creating a permutation of Message (or 8 bytes of it) looking up the IP table
//		the values in the IP table is the bit number which should be moved to a new position which is that value's index
		for(i=0;i<64;i++){
			m = m | (((((unsigned long)(M[((ip[i]-1)/8)])) & (unsigned long)(0x80 >> ((ip[i]-1)%8)))<<(56+(ip[i]-1)%8))>>i);
		}
	
//		splitting it into 2 32 bit parts
		unsigned int L0 = 0, LN = 0, R0 = 0, RN = 0,t = 0;
		L0 = m >> 32;
		R0 = m & 0xffffffffUL;
	
//		encrypting them repeatedly
		for(i=0; i<16; i++){
			LN = R0;
			t = f(R0,subkeys[i]);
			RN = L0 ^ t;
			L0 = LN; R0 = RN; 
		}

//		concatenating them as  m = R0 + L0
		m = 0;
		m = (unsigned long)L0;
		m = m | ((unsigned long) R0 << 32);

//		final permutation of the 8 bytes of M. using IP inverse.
//		moving the bits from 0 - 64 to the corresponding values in IP table
		kp=0;
		for(i = 0; i<64; i++){
			if(i> ip[i]){
				kp = kp | ((m & (0x8000000000000000 >> i))<<(i - ip[i] +1));
			}
			else{
				kp = kp | ((m & (0x8000000000000000 >> i))>>(ip[i]-1-i));
			}
		}

		C[j] = kp;
	}

	printf("\nCipherText (in Hex) : ");
	for(i=0;i<n;i++)
		printf("%lx",C[i]);
	printf("\n");	
	return 0;
}

//	Expanding the 32 bit Right part of M, to a 48 bit value using the e bit selection table
unsigned long ebits(unsigned int R){
	int i = 0;
	unsigned long eR = 0;

	for(i = 0; i< 47; i++){
	  eR = eR | (((unsigned long)R & (0x1<<(32 - eTable[i])))<<(31+eTable[i] -i));
	}
	eR = eR | (((unsigned long)R & (0x1<<(32 - eTable[i])))>>15);
	
	return eR;

}

//	the function which converts a 48 bit value to a 32 bit value
unsigned int f(unsigned int r, unsigned long k){
	unsigned long eR = ebits(r);
	unsigned long B = k ^ eR;
	B = B>>16;
	int i;
	unsigned int temp = 0, row = 0, col = 0;
	unsigned int result = 0;
	
	for(i = 0; i<48; i+=6){
		temp =0 | (B >> ((7-(i/6))*6)) & 0xffffff;
		row = 0 | ((temp & 0x20)>>4) | (temp&1);
		col = 0 | ((temp & 0x1e) >> 1);
	
		result = result | ((S[i/6][row][col])<<((7-i/6)*4));
	}

	temp = 0;
	
	for(i = 0; i<32;i++){
		temp = temp | (((result & (0x80000000 >> (P[i] -1)))<<(P[i]-1))>>i);
	}

	return temp;
}
