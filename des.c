#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <signal.h>


#define SHIFT_1 1
#define SHIFT_2 2
//#define MAX_THREAD_PER_MACHINE 5
//#define MAX_KEY_COMBINATIONS 72057594037927935


#define MAX_THREAD_PER_MACHINE 5
#define MAX_KEY_COMBINATIONS 4294967296
//#define MAX_KEY_COMBINATIONS 70000



struct worker_inputs {
	int workerid;
	unsigned long long int start;
	unsigned long long int end;
}workerInput;

//#define POWER_VALUE (pow(2,56)-1/5)
#define DATA "Got Message from Pooja.  She found the Key working in des.c!"

//int plainText64Bit[64]={0,0,0,0,0,0,0,1,0,0,1,0,0,0,1,1,0,1,0,0,0,1,0,1,0,1,1,0,0,1,1,1,1,0,0,0,1,0,0,1,1,0,1,0,1,0,1,1,1,1,0,0,1,1,0,1,1,1,1,0,1,1,1,1};
//this is from online DES working int plainText64Bit[64] = {0,0,0,0,0,0,0,1,0,0,1,0,0,0,1,1,0,1,0,0,0,1,0,1,0,1,1,0,0,1,1,1,1,0,0,0,1,0,0,1,1,0,1,0,1,0,1,1,1,1,0,0,1,1,0,1,1,1,1,0,1,1,1,1};
//int cipher64Bit[64]=   {0,0,0,1,1,1,1,0,0,1,0,1,1,0,0,0,1,1,1,1,1,1,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,1,1,0,1,0,0,0,0,0,1,0,0,0,0,1,1,0,0,1,0,1,1,1};
//this is from online DES working int cipher64Bit[64] = {1,0,0,0,0,1,0,1,1,1,1,0,1,0,0,0,0,0,0,1,0,0,1,1,0,1,0,1,0,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,1,0,1,0,1,0,1,1,0,1,0,0,0,0,0,0,0,1,0,1};
//int cipher64Bit[64]=   {1,0,1,1,1,1,1,0,0,1,1,0,0,1,1,0,1,0,0,0,1,0,1,0,0,1,1,1,0,1,0,0,0,1,0,1,0,1,1,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,1,1,1,0,1};
//long long int powerValue = ((pow(2,56)-1)/10);

//Chetan's input plain text.
//int plainText64Bit[64] = {1,0,0,0,0,1,0,1,1,1,1,0,1,0,0,0,0,0,0,1,0,0,1,1,0,1,0,1,0,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,1,0,1,0,1,0,1,1,0,1,0,0,0,0,0,0,0,1,0,1};
//H plaintext
int plainText64Bit[64] = {1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
//Chetan's input cipher 1.
//int cipher64Bit[64] = {0,0,0,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,0,1,0,1,1,0,0,0,1,0,1,0,1,1,1,0,1,1,0,0,0,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,1};
//Chetan's input cipher 2.
//int cipher64Bit[64] = {1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,0,0,1,0,0,0,1,1,1,0,1,0,1,1,0,0,0,1,1,0,0,1,0,0,0,1,1,1,0,1,0,0,1,0,1,1,0,1,1,1,0,0,1,0,0,1};
//cipher for H
//int cipher64Bit[64] = {0,0,1,1,1,0,0,0,0,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,0,1,0,1,0,0,0,1,0,1,1,1,1,1,0,1,0,1,1,0,1,0,1,0,0,1,0,1,1,1,1,0,1,0,0,0,1,0,0,1};
//Chetan's input cipher 3.
//int cipher64Bit[64] = {1,1,0,1,1,0,1,0,0,0,1,1,0,1,1,1,1,1,0,0,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,1,1,0,1,1,1,0,1,0,1,0,1};
//small cipher
int cipher64Bit[64] = {1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,1,1,0,1,1,0,0,1,0,1,1,1,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,1,1,1,0,0,0,1,1,0,0,1,1};
char masterIPAddress[16];
char masterFoundKey[512];
char clientFoundKey[1024];

int mysock;
int sock;
int isMaster = 0;
int maxNumberOfComputers = 0;

char clientIPAddress[7][16];

int messageSender(char ipAddress[16],char* message);

void signal_callback_handler(int signum)
{
	printf("Caught signal %d\n",signum);
	// Cleanup and close up stuff here

	close(mysock);
	close(sock);

	if(isMaster != 1)
	{
		remove("start");
	}
	system("killall des");

	// Terminate program
	exit(signum);
}

//conversion of 64 bit key to 56 bit by using pc1
void permutationChoice1(int key64Bit[], int permutationChoiceMatrix1[], int output56Bit[])
{
	int i=0;
	for(i=0;i<56;i++)
	{
		output56Bit[i]=key64Bit[permutationChoiceMatrix1[i]-1];

	}
}

//Divide 56 bit key into 2 parts left and right each of 28 bits.
void divide56To28(int input[], int output1[], int output2[])
{
	int i=0,j=0;
	for(i=0;i<56;i++)
	{
		if(i<28)
		{
			output1[i]=input[i];
		}

		if(i>=28)
		{
			output2[j]=input[i];
			j++;
		}
	}
}

//Applying initial permutation to the PT
void InitialPermutation(int initialPermutationMatrix[], int plainText64Bit[], int output64Bit[])
{
	int i=0;
	for(i=0;i<64;i++)
	{
		output64Bit[i]=plainText64Bit[initialPermutationMatrix[i]-1];
	}
}

//Dividing IP output 64 bit into 2 parts left and right each of 32 bits. This is left part.
void divide64To32(int input[], int output1[], int output2[])
{
	int i=0,j=0;
	for(i=0;i<64;i++)
	{
		if(i<32)
		{
			output1[i]=input[i];
		}

		if(i>=32)
		{
			output2[j]=input[i];
			j++;
		}
	}
}

//56 bits(each of 28 bits)keys are getting converted to 28 bits keys by using left shift
void leftShift28(int input[], int output[], int mode)
{
	if (mode == SHIFT_1)
	{
		int j;
		int m=1;
		for(j=0;j<28;j++)
		{
			output[j]=input[m];
			m++;
		}
		output[27]=input[0];
	}
	if (mode == SHIFT_2)
	{
		int j;
		int m=2;
		for(j=0;j<28;j++)
		{
			output[j]=input[m];
			m++;

		}
		output[26]=input[0];
		output[27]=input[1];
	}
}

//Concatenation function 56 bits
void concatenate28To56(int input1[], int input2[], int output[])
{
	int i=0;
	int j=0;
	for(i=0; i<56; i++)
	{
		if(i<28)
		{
			// for the leftside i,e 1st 28 bits
			output[i]=input1[i];
		}
		if(i>=28)
		{
			// for the rightside i,e next 28 bits
			output[i]=input2[j];
			j++;
		}
	}
}

//PC2 function
void permutedChoice2(int permutedChoiceMatrix2[], int key56bit[], int output48bitkey[])
{
	int i=0;
	for(i=0;i<48;i++)
	{
		// converting 56 bit key into 48 bit key using matrix pc2
		output48bitkey[i]=key56bit[permutedChoiceMatrix2[i]-1];
	}
}

//eBit Selection function
void eBitSelection(int eBitSelectionMatrix[], int Rn32bit[], int output48bit[])
{
	int i=0;
	for(i=0;i<48;i++)
	{
		output48bit[i]=Rn32bit[eBitSelectionMatrix[i]-1];
	}
}

//XOR 48 bit function
void XOR48bit(int input1[], int input2[], int output[])
{
	int i=0;
	for(i=0;i<48;i++)
	{
		output[i]=input1[i]^input2[i];
	}
}

//SBOX selection function
void sBoxSelection(int sBox1[][16],int sBox2[][16],int sBox3[][16],int sBox4[][16],int sBox5[][16],int sBox6[][16],int sBox7[][16],int sBox8[][16],int f48bit[],int output32bit[])
{

	int sRow=0;
	int sColumn=0;
	int sDecimal=0;
	int i=0;
	int count=0;
	int index=0;

	for(i=0;i<8;i++)
	{
		count=i*6;
		sRow=(f48bit[count]*2)+(f48bit[count+5]*1);
		sColumn=(f48bit[count+1]*8)+(f48bit[count+2]*4)+(f48bit[count+3]*2)+(f48bit[count+4]*1);

		if(i==0)
			sDecimal=sBox1[sRow][sColumn];
		else if(i==1)
			sDecimal=sBox2[sRow][sColumn];
		else if(i==2)
			sDecimal=sBox3[sRow][sColumn];
		else if(i==3)
			sDecimal=sBox4[sRow][sColumn];
		else if(i==4)
			sDecimal=sBox5[sRow][sColumn];
		else if(i==5)
			sDecimal=sBox6[sRow][sColumn];
		else if(i==6)
			sDecimal=sBox7[sRow][sColumn];
		else if(i==7)
			sDecimal=sBox8[sRow][sColumn];

		index=i*4;
		output32bit[index+3]=sDecimal & 1;
		sDecimal=sDecimal>>1;
		output32bit[index+2]=sDecimal & 1;
		sDecimal=sDecimal>>1;
		output32bit[index+1]=sDecimal & 1;
		sDecimal=sDecimal>>1;
		output32bit[index+0]=sDecimal & 1;
	}

}

//permutation function
void functionPermutationSelection(int perMatrix[],int sBox32[],int output32bit[])
{
	int i = 0;
	for(i=0;i<32;i++)
	{
		output32bit[i]=sBox32[perMatrix[i]-1];

	}

}

//XOR 32 bit function
void XOR32bit(int input1[],int input2[],int output[])
{
	int i = 0;
	for(i=0;i<32;i++)
	{
		output[i]=input1[i]^input2[i];
	}

}

//Right part function for plain text
void rightN(int leftNminus1[],int permutationSelection[],int output32bit[])
{
	XOR32bit(leftNminus1,permutationSelection,output32bit);

}

//Concatenation function 64 bits
void concatenate32To64(int input1[], int input2[], int output[])
{
	int i=0;
	int j=0;
	for(i=0; i<64; i++)
	{
		if(i<32)
		{
			// for the leftside i,e 1st 32 bits
			output[i]=input1[i];
		}
		if(i>=32)
		{
			// for the rightside i,e next 32 bits
			output[i]=input2[j];
			j++;
		}
	}
}

//Applying inverse permutation
void inverseInitialPermutation(int inverseInitialPermutationMatrix[], int input64Bit[], int output64Bit[])
{
	int i=0;
	for(i=0;i<64;i++)
	{
		output64Bit[i]=input64Bit[inverseInitialPermutationMatrix[i]-1];
	}
}

//Print Array function
void printArray(int array[],int sizeOfArray,char nameOfArray[])
{
	int i = 0;

	printf("\n");
	printf("%s :", nameOfArray);
	for(i = 0;i < sizeOfArray;i++)
	{
		printf("%d", array[i]);
	}
	printf("\n");
}

//Encryption Function
int encryption(int plainText64Bit[],int pc1Output56BitKey[],int cipher64Bit[])
{
	int iteration = 0;
	//int plainText64Bit[64]={0,0,0,0,0,0,0,1,0,0,1,0,0,0,1,1,0,1,0,0,0,1,0,1,0,1,1,0,0,1,1,1,1,0,0,0,1,0,0,1,1,0,1,0,1,0,1,1,1,1,0,0,1,1,0,1,1,1,1,0,1,1,1,1};
	//original int key64Bit[64]={0,0,0,1,0,0,1,1,0,0,1,1,0,1,0,0,0,1,0,1,0,1,1,1,0,1,1,1,1,0,0,1,1,0,0,1,1,0,1,1,1,0,1,1,1,1,0,0,1,1,0,1,1,1,1,1,1,1,1,1,0,0,0,1};
	//testing
	//int key64Bit[64] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0};
	//int permutationChoiceMatrix1[56]={57,49,41,33,25,17,9,1,58,50,42,34,26,18,10,2,59,51,43,35,27,19,11,3,60,52,44,36,63,55,47,39,31,23,15,7,62,54,46,38,30,22,14,6,61,53,45,37,29,21,13,5,28,20,12,4};
	int permutationChoiceMatrix2[48]={14,17,11,24,1,5,3,28,
			15,6,21,10,23,19,12,4,
			26,8,16,7,27,20,13,2,
			41,52,31,37,47,55,30,40,
			51,45,33,48,44,49,39,56,
			34,53,46,42,50,36,29,32};
	//int pc1Output56BitKey[56];
	int ipOutput64Bit[64];
	int leftKey28Bit[28];
	int rightKey28Bit[28];
	int shiftedLeftKey28Bit[28],shiftedRightKey28Bit[28],key56Bit[56],key48Bit[48];
	int initialPermutationMatrix[64]={58,50,42,34,26,18,10,2,
			60,52,44,36,28,20,12,4,
			62,54,46,38,30,22,14,6,
			64,56,48,40,32,24,16,8,
			57,49,41,33,25,17,9,1,
			59,51,43,35,27,19,11,3,
			61,53,45,37,29,21,13,5,
			63,55,47,39,31,23,15,7};

	int leftN32Bit[32],rightN32Bit[32];


	int inverseInitialPermutationMatrix[64]={40, 8 ,48, 16, 56, 24, 64, 32,
			39, 7, 47, 15, 55, 23, 63, 31,
			38, 6, 46, 14, 54, 22, 62, 30,
			37 ,5 ,45, 13, 53, 21, 61, 29,
			36, 4, 44, 12, 52, 20, 60, 28,
			35, 3, 43, 11, 51, 19, 59, 27,
			34, 2 ,42, 10, 50, 18, 58, 26,
			33, 1 ,41, 9 ,49, 17, 57, 25};
	int eBitSelectionMatrix[48]={32,1,2,3,4,5,
			4,5,6,7,8,9,
			8,9,10,11,12,13,
			12,13,14,15,16,17,
			16,17,18,19,20,21,
			20,21,22,23,24,25,
			24,25,26,27,28,29,
			28,29,30,31,32,1};
	int rightN48Bit[48],xorOutput48bit[48],sBoxOutput32bit[32];

	int sBox1[4][16]={
			{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
			{0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
			{4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
			{15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}};

	int sBox2[4][16]={
			{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
			{3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
			{0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
			{13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}};

	int sBox3[4][16]={
			{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
			{13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
			{13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
			{1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}};

	int sBox4[4][16]={
			{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
			{13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
			{10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
			{3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}};

	int sBox5[4][16]={
			{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
			{14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
			{4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
			{11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}};

	int sBox6[4][16]={
			{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
			{10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
			{9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
			{4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}};

	int sBox7[4][16]={
			{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
			{13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
			{1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
			{6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}};

	int sBox8[4][16]={
			{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
			{1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
			{7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
			{2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}};

	int perMatrix[32]={16 ,  7,  20,  21,
			29,  12,  28,  17,
			1 , 15,  23,  26,
			5 , 18 , 31,  10,
			2 ,  8 , 24,  14,
			32 , 27  , 3 ,  9,
			19 , 13 , 30  , 6,
			22 , 11,   4 , 25};

	int perMatrixOutput32bit[32];
	int rightNOutput32bit[32];
	int siftMode[16]={SHIFT_1,SHIFT_1, SHIFT_2, SHIFT_2, SHIFT_2, SHIFT_2, SHIFT_2,
			SHIFT_2, SHIFT_1, SHIFT_2, SHIFT_2, SHIFT_2, SHIFT_2, SHIFT_2, SHIFT_2, SHIFT_1};
	//int cipher[64];
	int output64Bit[64];
	int x=0,y=0;


	//printArray(plainText64Bit, 64, "plainText64");
	//printArray(key64Bit, 64, "key64Bit");

	//STEP 1
	//permutationChoice1(key64Bit,permutationChoiceMatrix1,pc1Output56BitKey);
	//printArray(pc1Output56BitKey, 56, "permutationChoice1");

	//STEP 2
	InitialPermutation( initialPermutationMatrix, plainText64Bit,ipOutput64Bit);
	//printArray(ipOutput64Bit, 64, "ipOutput64Bit");

	//STEP 3
	divide64To32(ipOutput64Bit,leftN32Bit,rightN32Bit);
	//printArray(leftN32Bit, 32, "leftN32Bit");
	//printArray(rightN32Bit, 32, "rightN32Bit");


	for(iteration= 0; iteration<16;iteration++)
	{
		//printf("\n Iteration : %d",iteration+1);

		//STEP 4 A
		divide56To28( pc1Output56BitKey,leftKey28Bit,rightKey28Bit);
		//printArray(leftKey28Bit, 28, "leftKey28Bit");
		//printArray(rightKey28Bit, 28, "rightKey28Bit");

		//STEP 4 B1
		leftShift28(leftKey28Bit,shiftedLeftKey28Bit,siftMode[iteration]);
		//printArray(shiftedLeftKey28Bit, 28, "shiftedLeftKey28Bit");

		//STEP 4 B2
		leftShift28(rightKey28Bit,shiftedRightKey28Bit,siftMode[iteration]);
		//printArray(shiftedRightKey28Bit, 28, "shiftedRightKey28Bit");

		//STEP 4 C
		concatenate28To56(shiftedLeftKey28Bit, shiftedRightKey28Bit, key56Bit);
		//printArray(key56Bit, 56, "key56Bit");

		for(y=0;y<56;y++)
		{
			pc1Output56BitKey[y]=key56Bit[y];
		}

		//STEP 4 D
		permutedChoice2( permutationChoiceMatrix2,  key56Bit,  key48Bit);
		//printArray(key48Bit, 48, "key48Bit");

		//STEP 4 E
		eBitSelection( eBitSelectionMatrix,  rightN32Bit,  rightN48Bit);
		//printArray(rightN48Bit, 48, "rightN48Bit");

		//STEP 4 F
		XOR48bit(rightN48Bit, key48Bit, xorOutput48bit);
		//printArray(xorOutput48bit, 48, "xorOutput48bit");

		//STEP 4 G
		sBoxSelection( sBox1, sBox2, sBox3, sBox4,
				sBox5, sBox6, sBox7, sBox8, xorOutput48bit, sBoxOutput32bit);
		//printArray(sBoxOutput32bit, 32, "sBoxOutput32bit");

		//STEP 4 H
		functionPermutationSelection( perMatrix, sBoxOutput32bit, perMatrixOutput32bit);
		//printArray(perMatrixOutput32bit, 32, "perMatrixOutput32bit");

		//STEP 4 I
		rightN( leftN32Bit, perMatrixOutput32bit, rightNOutput32bit);
		//printArray(rightNOutput32bit, 32, "rightNOutput32bit");

		if(iteration<=14)
		{
			//STEP 4 J
			for(x=0;x<32;x++)
			{
				leftN32Bit[x]=rightN32Bit[x];
			}
			//printArray(leftN32Bit, 32, "leftN32Bit");

			//STEP 4 K
			for(x=0;x<32;x++)
			{
				rightN32Bit[x]=rightNOutput32bit[x];
			}
			//printArray(rightN32Bit, 32, "rightN32Bit");
		}
		else{
			for(x=0;x<32;x++)
			{
				leftN32Bit[x]=rightNOutput32bit[x];
			}
			//printArray(leftN32Bit, 32, "leftN32Bit");

		}
	}

	//STEP 5
	concatenate32To64(leftN32Bit, rightN32Bit, output64Bit);
	//printArray(output64Bit,64, "output64Bit");

	//STEP 6
	inverseInitialPermutation(inverseInitialPermutationMatrix,output64Bit, cipher64Bit);
	//printArray(cipher64Bit,64, "cipher64Bit");

	return 0;
}

//Decryption Function
int decryption(int cipher64Bit[], int pc1Output56BitKey[], int plainText[])
{
	int iteration = 0;
	int	ipOutput64Bit[64];
	int permutationChoiceMatrix2[48]={14,17,11,24,1,5,3,28,
			15,6,21,10,23,19,12,4,
			26,8,16,7,27,20,13,2,
			41,52,31,37,47,55,30,40,
			51,45,33,48,44,49,39,56,
			34,53,46,42,50,36,29,32};
	int leftKey28Bit[28];
	int rightKey28Bit[28];
	int shiftedLeftKey28Bit[28],shiftedRightKey28Bit[28],key56Bit[56],key48Bit[48];
	int initialPermutationMatrix[64]={58,50,42,34,26,18,10,2,
			60,52,44,36,28,20,12,4,
			62,54,46,38,30,22,14,6,
			64,56,48,40,32,24,16,8,
			57,49,41,33,25,17,9,1,
			59,51,43,35,27,19,11,3,
			61,53,45,37,29,21,13,5,
			63,55,47,39,31,23,15,7};

	int leftN32Bit[32],rightN32Bit[32];

	int inverseInitialPermutationMatrix[64]={40, 8 ,48, 16, 56, 24, 64, 32,
			39, 7, 47, 15, 55, 23, 63, 31,
			38, 6, 46, 14, 54, 22, 62, 30,
			37 ,5 ,45, 13, 53, 21, 61, 29,
			36, 4, 44, 12, 52, 20, 60, 28,
			35, 3, 43, 11, 51, 19, 59, 27,
			34, 2 ,42, 10, 50, 18, 58, 26,
			33, 1 ,41, 9 ,49, 17, 57, 25};
	int eBitSelectionMatrix[48]={32,1,2,3,4,5,
			4,5,6,7,8,9,
			8,9,10,11,12,13,
			12,13,14,15,16,17,
			16,17,18,19,20,21,
			20,21,22,23,24,25,
			24,25,26,27,28,29,
			28,29,30,31,32,1};
	int rightN48Bit[48],xorOutput48bit[48],sBoxOutput32bit[32];

	int sBox1[4][16]={
			{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
			{0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
			{4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
			{15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}};

	int sBox2[4][16]={
			{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
			{3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
			{0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
			{13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}};

	int sBox3[4][16]={
			{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
			{13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
			{13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
			{1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}};

	int sBox4[4][16]={
			{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
			{13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
			{10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
			{3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}};

	int sBox5[4][16]={
			{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
			{14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
			{4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
			{11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}};

	int sBox6[4][16]={
			{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
			{10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
			{9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
			{4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}};

	int sBox7[4][16]={
			{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
			{13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
			{1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
			{6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}};

	int sBox8[4][16]={
			{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
			{1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
			{7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
			{2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}};

	int perMatrix[32]={16 ,  7,  20,  21,
			29,  12,  28,  17,
			1 , 15,  23,  26,
			5 , 18 , 31,  10,
			2 ,  8 , 24,  14,
			32 , 27  , 3 ,  9,
			19 , 13 , 30  , 6,
			22 , 11,   4 , 25};

	int perMatrixOutput32bit[32];
	int rightNOutput32bit[32];
	int siftMode[16]={SHIFT_1,SHIFT_1, SHIFT_2, SHIFT_2, SHIFT_2, SHIFT_2, SHIFT_2,
			SHIFT_2, SHIFT_1, SHIFT_2, SHIFT_2, SHIFT_2, SHIFT_2, SHIFT_2, SHIFT_2, SHIFT_1};
	int output64Bit[64];
	int x=0,y=0,z=0;
	int key[16][48];
	int keyIndex;


	//printArray(cipher, 64, "cipher");
	//printArray(key64Bit, 64, "key64Bit");



	//***********DECRYPTION IMPLEMENTATION STARTS FROM HERE*************//


	//16 keys calculation
	for(iteration= 0; iteration<16;iteration++)
	{
		//printf("\n Key : %d",iteration+1);

		//STEP 1 A
		divide56To28( pc1Output56BitKey,leftKey28Bit,rightKey28Bit);
		//printArray(leftKey28Bit, 28, "leftKey28Bit");
		//printArray(rightKey28Bit, 28, "rightKey28Bit");

		//STEP 1 B1
		leftShift28(leftKey28Bit,shiftedLeftKey28Bit,siftMode[iteration]);
		//printArray(shiftedLeftKey28Bit, 28, "shiftedLeftKey28Bit");

		//STEP 1 B2
		leftShift28(rightKey28Bit,shiftedRightKey28Bit,siftMode[iteration]);
		//printArray(shiftedRightKey28Bit, 28, "shiftedRightKey28Bit");

		//STEP 1 C
		concatenate28To56(shiftedLeftKey28Bit, shiftedRightKey28Bit, key56Bit);
		//printArray(key56Bit, 56, "key56Bit");

		for(y=0;y<56;y++)
		{
			pc1Output56BitKey[y]=key56Bit[y];
		}

		//STEP 1 D
		permutedChoice2( permutationChoiceMatrix2,  key56Bit,  key48Bit);
		//printArray(key48Bit, 48, "key48Bit");

		for(z=0;z<48;z++)
		{
			key[iteration][z] = key48Bit[z];
		}

	}

	//STEP 2
	InitialPermutation(initialPermutationMatrix,cipher64Bit, ipOutput64Bit);
	//printArray(ipOutput64Bit,64, "ipOutput64Bit");

	//STEP 3
	divide64To32(ipOutput64Bit,leftN32Bit,rightN32Bit);
	//printArray(leftN32Bit, 32, "leftN32Bit");
	//printArray(rightN32Bit, 32, "rightN32Bit");

	for(iteration= 0,keyIndex=15; iteration<16;iteration++,keyIndex--)
	{
		//printf("\n Iteration : %d",iteration+1);

		//STEP 4 E
		eBitSelection( eBitSelectionMatrix,  rightN32Bit,  rightN48Bit);
		//printArray(rightN48Bit, 48, "rightN48Bit");

		//STEP 4 F
		XOR48bit(rightN48Bit, key[keyIndex], xorOutput48bit);
		//printArray(xorOutput48bit, 48, "xorOutput48bit");

		//STEP 4 G
		sBoxSelection( sBox1, sBox2, sBox3, sBox4,
				sBox5, sBox6, sBox7, sBox8, xorOutput48bit, sBoxOutput32bit);
		//printArray(sBoxOutput32bit, 32, "sBoxOutput32bit");

		//STEP 4 H
		functionPermutationSelection( perMatrix, sBoxOutput32bit, perMatrixOutput32bit);
		//printArray(perMatrixOutput32bit, 32, "perMatrixOutput32bit");

		//STEP 4 I
		rightN( leftN32Bit, perMatrixOutput32bit, rightNOutput32bit);
		//printArray(rightNOutput32bit, 32, "rightNOutput32bit");



		if(iteration<=14)
		{
			//STEP 4 J
			for(x=0;x<32;x++)
			{
				leftN32Bit[x]=rightN32Bit[x];
			}
			//printArray(leftN32Bit, 32, "leftN32Bit");

			//STEP 4 K
			for(x=0;x<32;x++)
			{
				rightN32Bit[x]=rightNOutput32bit[x];
			}
			//printArray(rightN32Bit, 32, "rightN32Bit");
		}
		else
		{
			for(x=0;x<32;x++)
			{
				leftN32Bit[x]=rightNOutput32bit[x];
			}
			//printArray(leftN32Bit, 32, "leftN32Bit");

		}

	}

	//STEP 5
	concatenate32To64(leftN32Bit, rightN32Bit, output64Bit);
	//printArray(output64Bit,64, "output64Bit");

	//STEP 6
	inverseInitialPermutation(inverseInitialPermutationMatrix,output64Bit, plainText);
	//printArray(plainText,64, "plainText");


	return 0;

}

//Brute Force Function
int bruteForce(int plainText64Bit[],int cipher64Bit[],unsigned long long int start,unsigned long long int end, int output56BitKey[], int worker_id) {
	int resultCipher64Bit[64];
	unsigned long long int i=0;
//	int shouldBeKey[56]=
//	//{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0};
//	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
//	//{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	time_t start_t, end_t;
	double diff_t;
	time(&start_t);
	for(i=start;i< end;i++ )
	{

		long long int a=1,j;
		int key[56];
		for(j=0;j<56;j++)
		{
			if((i&a)>0)
				key[55-j]=1;
			else
				key[55-j]=0;
			//printf("\ni&a : %ll \n",i&a);
			a=a<<1;
		}

		if(i%100000 == 0)
		{	printf("\nWorker %d and value of i is %llu\n",worker_id,i);
					printArray(key,56, "keyCombination");
		}
		encryption(plainText64Bit,key,resultCipher64Bit);
		if(!(memcmp(cipher64Bit, resultCipher64Bit, 64 * sizeof(int))))
		{
			time(&end_t);
			diff_t = difftime(end_t, start_t);
			int k=0;
			printf("\nKey Found!!! by worker_id : %d\n",worker_id);
			for(k=0; k<56;k++)
			{
				output56BitKey[k] = key[k];
			}
			printArray(output56BitKey,56, "key FOUND");


			system("rm key.txt");
			system("touch key.txt");
			FILE *f = fopen("key.txt", "w");
			if (f == NULL)
			{
			    printf("Error opening file!\n");
			    exit(1);
			}

			fprintf(f, "Key : %d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d by Worker : %d Time took : %le\n"
					,output56BitKey[0],output56BitKey[1],output56BitKey[2],output56BitKey[3],output56BitKey[4],
					output56BitKey[5],output56BitKey[6],output56BitKey[7],output56BitKey[8],output56BitKey[9],
					output56BitKey[10],output56BitKey[11],output56BitKey[12],output56BitKey[13],output56BitKey[14],
					output56BitKey[15],output56BitKey[16],output56BitKey[17],output56BitKey[18],output56BitKey[19],
					output56BitKey[20],output56BitKey[21],output56BitKey[22],output56BitKey[23],output56BitKey[24],
					output56BitKey[25],output56BitKey[26],output56BitKey[27],output56BitKey[28],output56BitKey[29],
					output56BitKey[30],output56BitKey[31],output56BitKey[32],output56BitKey[33],output56BitKey[34],
					output56BitKey[35],output56BitKey[36],output56BitKey[37],output56BitKey[38],output56BitKey[39],
					output56BitKey[40],output56BitKey[41],output56BitKey[42],output56BitKey[43],output56BitKey[44],
					output56BitKey[45],output56BitKey[46],output56BitKey[47],output56BitKey[48],output56BitKey[49],
					output56BitKey[50],output56BitKey[51],output56BitKey[52],output56BitKey[53],output56BitKey[54],
					output56BitKey[55],worker_id,diff_t);

			fclose(f);

			return (1);
		}
//		else if(!(memcmp(key, shouldBeKey, 56 * sizeof(int))))
//		{
//			printf("\n This should have been found. Something wrong!!! \n");
//		}
	}
	return (0);
}

int test_bruteForce()
{

	/*int plainText64Bit[64]={1,0,0,0,0,1,0,1,1,1,1,0,1,0,0,0,0,0,0,1,0,0,1,1,0,1,0,1,0,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,1,0,1,0,1,0,1,1,0,1,0,0,0,0,0,0,0,1,0,1};
	int output56BitKey[56];
	long long int start=0;
	long long int end= pow(2,56);
	//small test
	int cipher64Bit[64]={1,1,1,1,1,1,0,0,1,0,1,1,0,1,0,1,0,0,1,0,1,0,0,0,1,1,1,0,0,1,1,1,0,0,1,0,0,1,0,0,0,1,1,0,0,0,0,1,0,0,0,1,0,1,0,0,0,1,1,0,1,0,0,0};

	bruteForce(plainText64Bit,cipher64Bit,start,end, output56BitKey,1);
	printArray(output56BitKey,56, "output56BitKey");*/
	return 0;
}

int test_encryption()
{
	int plainText64Bit[64]={0,0,0,0,0,0,0,1,0,0,1,0,0,0,1,1,0,1,0,0,0,1,0,1,0,1,1,0,0,1,1,1,1,0,0,0,1,0,0,1,1,0,1,0,1,0,1,1,1,1,0,0,1,1,0,1,1,1,1,0,1,1,1,1};
	int pc1Output56BitKey[56]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0};
	int cipher64Bit[64];
	encryption(plainText64Bit,pc1Output56BitKey,cipher64Bit);
	printArray(plainText64Bit,56, "plainText64Bit");
	printArray(pc1Output56BitKey,56, "pc1Output56BitKey");
	printArray(cipher64Bit,56, "cipher64Bit");

	return 0;
}

void* messageReceiver(void *arg)
{
	// Variable
	struct sockaddr_in server;

	char buffer[1024];
	int rval;

	//Step 1 : Create socket
	sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock<0)
	{
		perror("\nFailed to create socket\n");
		exit(errno);
	}

	bzero(&server, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(5000);

	//call bind.
	if(bind(sock,(struct sockaddr *)&server,sizeof(server)) !=0)
	{
		perror("\nBind failed\n");//if the bind is 0 it will never come to this line.
		exit(1);
	}

	//listen
	if(listen(sock,100) != 0){
		perror("socket--listen");
		exit(errno);
	}

	//accept
	do
	{
		mysock = accept(sock,(struct sockaddr *) 0, 0);
		if(mysock == -1)
			perror("\nAccept failed\n");
		else
		{
			int total_size= 0;
			memset(buffer ,0 , 1024);
			if((rval =  recv(mysock , buffer , 1024 , 0) ) < 0)
			{
				break;
			}
			else
			{
				total_size += rval;
			}

			if(rval == 0)
			{
				printf("\nEnding connection\n");
			}
			else
			{
				printf("\nMSG : %s\n",buffer);

				/*if(memcmp ( buffer, "CLIENT OK TO START", 17)==0)
				{
					printf("Client Sent ok to start!! ");
					system("touch clientOkToStart");
				}*/
				if(memcmp ( buffer, "MASTER IPADDRESS", 15)==0)
				{
					//This is message 1.  Message from Master sending its IP Address.
					//String operation on message to assign it to masterIPAddress.
					int i=0,j=0;

					for(i=0,j=17; ;i++,j++)
					{
						if(buffer[j]!='\0')
						{
							masterIPAddress[i] = buffer[j];
						}
						else
						{
							masterIPAddress[i] = '\0';
							break;
						}
					}
					printf("\n MASTER's IPADDRESS : %s",masterIPAddress);
				}
				if(memcmp ( buffer, "MASTER - START", 14)==0)
				{
					//This is message 2.  Message from Master to start.
					//Create a file to start.
					system("touch start");

				}
				if(memcmp ( buffer, "MASTER - STOP", 13)==0)
				{
					//This is message 3.  Message from Master to stop.
					printf("\nReceived Stop from Master Exiting....\n");
					exit(0);
				}
				if(memcmp ( buffer, "MASTER - IFOUNDIT", 17)==0)
				{
					//This is message 4.  Message from Master I found it.
					int i=0,j=0;

					for(i=0,j=19;;i++,j++)
					{
						if(buffer[j]!='\0')
						{
							masterFoundKey[i] = buffer[j];
						}
						else
						{
							masterFoundKey[i] = '\0';
							break;
						}
					}
					printf("\n\n\n\n Master  found the key : %s \n\n\n\n;",masterFoundKey);
				}
				if(memcmp ( buffer, "CLIENT - IFOUNDIT", 17)==0)
				{
					//This is message 5.  Message from Client to Master that I found it.
					int i=0,j=0;

					for(i=0,j=18;;i++,j++)
					{
						if(buffer[j]!='\0')
						{
							clientFoundKey[i] = buffer[j];

						}
						else
						{
							clientFoundKey[i] = '\0';
							break;
						}
					}
					printf("\n\n\n\n Client found the key : %s \n\n\n\n;",clientFoundKey);


					char keyMessage[1024];
					memset(keyMessage,0x0,(sizeof(char))*1024);


					//If there are more than 2 computers, Server has to send the what
					//client found and send stop to the others clients.
					if(maxNumberOfComputers > 2 && isMaster == 1)
					{
						char ipAddress[16];
						//char* message="MASTER - CLIENTFOUNDIT";
						char message[1024];
						memset(message,0x0,(sizeof(char))*1024);

						strcpy(message,"MASTER - CLIENTFOUNDIT ");

						strcat(message,clientFoundKey);

						memset(ipAddress,'\0',sizeof(ipAddress));
						strcpy(ipAddress, clientIPAddress[1]);
						messageSender(ipAddress, message);

						memset(ipAddress,'\0',sizeof(ipAddress));
						strcpy(ipAddress, clientIPAddress[2]);
						messageSender(ipAddress, message);

						memset(ipAddress,'\0',sizeof(ipAddress));
						strcpy(ipAddress, clientIPAddress[3]);
						messageSender(ipAddress, message);

						memset(ipAddress,'\0',sizeof(ipAddress));
						strcpy(ipAddress, clientIPAddress[4]);
						messageSender(ipAddress, message);

						memset(ipAddress,'\0',sizeof(ipAddress));
						strcpy(ipAddress, clientIPAddress[5]);
						messageSender(ipAddress, message);

						memset(ipAddress,'\0',sizeof(ipAddress));
						strcpy(ipAddress, clientIPAddress[6]);
						messageSender(ipAddress, message);


						//message="MASTER - STOP";
						memset(message,0x0,(sizeof(char))*1024);
						strcpy(message,"MASTER - STOP");


						memset(ipAddress,'\0',sizeof(ipAddress));
						strcpy(ipAddress, clientIPAddress[1]);
						messageSender(ipAddress, message);

						memset(ipAddress,'\0',sizeof(ipAddress));
						strcpy(ipAddress, clientIPAddress[2]);
						messageSender(ipAddress, message);

						memset(ipAddress,'\0',sizeof(ipAddress));
						strcpy(ipAddress, clientIPAddress[3]);
						messageSender(ipAddress, message);

						memset(ipAddress,'\0',sizeof(ipAddress));
						strcpy(ipAddress, clientIPAddress[4]);
						messageSender(ipAddress, message);

						memset(ipAddress,'\0',sizeof(ipAddress));
						strcpy(ipAddress, clientIPAddress[5]);
						messageSender(ipAddress, message);

						memset(ipAddress,'\0',sizeof(ipAddress));
						strcpy(ipAddress, clientIPAddress[6]);
						messageSender(ipAddress, message);

						exit(0);
					}
					exit(0);
				}
				if(memcmp ( buffer, "MASTER - CLIENTFOUNDIT", 22)==0)
				{
					//This is message 5.  Message from Client to Master that I found it.
					printf("\n\n\n\n One of the Clients found the key : %s \n\n\n\n;",clientFoundKey);
				}

			}

			printf("Got the message (rval = %d)\n",rval);
			//Close data connection
			close(mysock);
		}
	}
	while(1); // do while loop end

	//close socket
	close(sock);
	return(0);
}

//not working.
int messageSender(char ipAddress[16],char* message)
{
	int sock;
	struct sockaddr_in server;
	struct hostent *hp;

	//send message to the server.
	sock = socket(AF_INET,SOCK_STREAM, 0);
	if(sock <0)
	{
		perror("socket failed");
		return(1);
	}
	server.sin_family = AF_INET;

	hp = gethostbyname(ipAddress);
	if(hp == 0)
	{
		perror("gethostbyname failed");
		close(sock);
		return(1);
	}

	memcpy(&server.sin_addr, hp->h_addr, hp->h_length);
	server.sin_port = htons(5000);

	if(connect(sock, (struct sockaddr *) &server, sizeof(server)) < 0)
	{
		perror("connect failed");
		close(sock);
		return(1);
	}

	if(send(sock, message, strlen(message), 0 )<0)
	{
		perror("send failed");
		close(sock);
		return(1);
	}
	printf("\n********************************>Sent %s*******\n",message);
	close(sock);

	return (0);
}


void* workerX(void *arg)
{
	int output56BitKey[56];
	int result = 0;
	struct worker_inputs *input=arg;
	printf("\n Worker : %d\n",input->workerid);
	//printf("\n start : %d\n",input->start);
	//printf("\n end : %d\n",input->end);

	result = bruteForce(plainText64Bit,cipher64Bit, input->start,input->end,output56BitKey,input->workerid);

	if(result == 1)
	{
		printf("\n---------- Worker %d found the key--------------->\n",input->workerid);
		printArray(output56BitKey,56,"KEY FOUND");

		if(isMaster == 1)
		{
			//MASTER - IFOUNDIT
			char ipAddress[16];
			char* message="MASTER - IFOUNDIT";

			memset(ipAddress,'\0',sizeof(ipAddress));
			strcpy(ipAddress, clientIPAddress[1]);
			messageSender(ipAddress, message);

			memset(ipAddress,'\0',sizeof(ipAddress));
			strcpy(ipAddress, clientIPAddress[2]);
			messageSender(ipAddress, message);

			memset(ipAddress,'\0',sizeof(ipAddress));
			strcpy(ipAddress, clientIPAddress[3]);
			messageSender(ipAddress, message);

			memset(ipAddress,'\0',sizeof(ipAddress));
			strcpy(ipAddress, clientIPAddress[4]);
			messageSender(ipAddress, message);

			memset(ipAddress,'\0',sizeof(ipAddress));
			strcpy(ipAddress, clientIPAddress[5]);
			messageSender(ipAddress, message);

			memset(ipAddress,'\0',sizeof(ipAddress));
			strcpy(ipAddress, clientIPAddress[6]);
			messageSender(ipAddress, message);



			//MASTER - STOP
			message="MASTER - STOP";

			memset(ipAddress,'\0',sizeof(ipAddress));
			strcpy(ipAddress, clientIPAddress[1]);
			messageSender(ipAddress, message);

			memset(ipAddress,'\0',sizeof(ipAddress));
			strcpy(ipAddress, clientIPAddress[2]);
			messageSender(ipAddress, message);

			memset(ipAddress,'\0',sizeof(ipAddress));
			strcpy(ipAddress, clientIPAddress[3]);
			messageSender(ipAddress, message);

			memset(ipAddress,'\0',sizeof(ipAddress));
			strcpy(ipAddress, clientIPAddress[4]);
			messageSender(ipAddress, message);

			memset(ipAddress,'\0',sizeof(ipAddress));
			strcpy(ipAddress, clientIPAddress[5]);
			messageSender(ipAddress, message);

			memset(ipAddress,'\0',sizeof(ipAddress));
			strcpy(ipAddress, clientIPAddress[6]);
			messageSender(ipAddress, message);

			exit(0);
		}
		else
		{
			char message[1024];
			char array[57];
			char workerName[56];
			//int g=0,h=0;

			memset(message,0x0,(sizeof(char)*1024));
			memset(workerName,0x0,(sizeof(char)*56));
			memset(array,0x0,(sizeof(char)*57));

			strcpy(message,"CLIENT - IFOUNDIT Key : ");
//			//24 char filled.
//			for(g=24,h=0;h<56;g++,h++)
//			{
//				message[g] = output56BitKey[h];
//			}
			sprintf(array,"%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d"
					,output56BitKey[0],output56BitKey[1],output56BitKey[2],output56BitKey[3],output56BitKey[4],
					output56BitKey[5],output56BitKey[6],output56BitKey[7],output56BitKey[8],output56BitKey[9],
					output56BitKey[10],output56BitKey[11],output56BitKey[12],output56BitKey[13],output56BitKey[14],
					output56BitKey[15],output56BitKey[16],output56BitKey[17],output56BitKey[18],output56BitKey[19],
					output56BitKey[20],output56BitKey[21],output56BitKey[22],output56BitKey[23],output56BitKey[24],
					output56BitKey[25],output56BitKey[26],output56BitKey[27],output56BitKey[28],output56BitKey[29],
					output56BitKey[30],output56BitKey[31],output56BitKey[32],output56BitKey[33],output56BitKey[34],
					output56BitKey[35],output56BitKey[36],output56BitKey[37],output56BitKey[38],output56BitKey[39],
					output56BitKey[40],output56BitKey[41],output56BitKey[42],output56BitKey[43],output56BitKey[44],
					output56BitKey[45],output56BitKey[46],output56BitKey[47],output56BitKey[48],output56BitKey[49],
					output56BitKey[50],output56BitKey[51],output56BitKey[52],output56BitKey[53],output56BitKey[54],
					output56BitKey[55]);
			sprintf(workerName, " by Worker %d", input->workerid);

			strcat(message,array);

			strcat(message,workerName);

			printf("\n Send message to the Master that I found the key.\n");
			printf("\n Send the message to Master IP : %s \n",masterIPAddress);
			printf("\n Send the message : %s \n",message);
			messageSender(masterIPAddress, message);
			printf("\n Returned from messageSender\n");
		}
	}

	while(1)
	{
		//printf("\nWorker %d done brute forcing. Idling.\n",input->workerid);
		sleep(1);
	}

	return (0);
}



//***********MAIN STARTS FROM HERE*************//
int main_testServer()
{
	int err;
	pthread_t server1;
	err = pthread_create(&server1,NULL,&messageReceiver,NULL);
	if (err != 0)
		printf("\nError Creating Server Thread!");
	else
		printf("\n Server Thread Created!");
	while(1)
	{

	}
	return (0);
}
//int main_test_sender()
//{
//	signal(SIGINT, signal_callback_handler);
//
//	char ipAddress[16];
//
//	char* message="MASTER IPADDRESS 192.168.0.14";
//
//	memset(ipAddress,'\0',sizeof(ipAddress));
//	strcpy(ipAddress,"192.168.0.15");
//
//	messageSender(ipAddress, message);
//
//	return(0);
//}
int main(int argc, char *argv[])
{
	//local variables to the main method
	int computer_id=1;
	// = "192.168.0.15";

	int count = 0,inputj = 0;
	if (argc > 1 || argc < 10)
	{
		for (count = 1; count < argc; count++)
		{
			printf("argv[%d] = %s\n", count, argv[count]);
			if(count == 1)
			{
				isMaster = atoi(argv[count]);
			}
			if(count == 2)
			{
				computer_id = atoi(argv[count]);
			}
			if(count == 3)
			{
				maxNumberOfComputers = atoi(argv[count]);
			}
			if(isMaster == 1 && count > 3 && count <= 3+maxNumberOfComputers)
			{
				strcpy(clientIPAddress[inputj],argv[count]);
				inputj++;
			}
		}
	}
	else
	{
		printf("The command had no other arguments.\n");
	}

	int err=0,i=0,j=0;

	//be prep for any kind of signal.
	signal(SIGABRT, signal_callback_handler);
	signal(SIGFPE, signal_callback_handler);
	signal(SIGILL, signal_callback_handler);
	signal(SIGINT, signal_callback_handler);
	signal(SIGSEGV, signal_callback_handler);
	signal(SIGTERM, signal_callback_handler);

	//clientIPAddress[0] = "192.168.0.15";

	int threadStartIndex = ((MAX_THREAD_PER_MACHINE*computer_id)-MAX_THREAD_PER_MACHINE)+1;
	int threadEndIndex = (MAX_THREAD_PER_MACHINE*computer_id);

	//printf("\n threadStartIndex : %d\n",threadStartIndex);
	//printf("\n threadEndIndex : %d\n",threadEndIndex);

	char message[1024];

	unsigned long long int maximumIterations = MAX_KEY_COMBINATIONS;
	unsigned int noOfThreads = maxNumberOfComputers * MAX_THREAD_PER_MACHINE;
	unsigned long long int remainder=0;
	unsigned long long int noOfIterationsEachThread=0;

	//	char ipAddress2[16] = "192.168.0.15";
	//	char ipAddress3[16] = "192.168.0.15";
	//	char ipAddress4[16] = "192.168.0.15";

	//We need to make sure that Receivers are running for all Server and Clients.
	//Starting the receiver thread
	pthread_t messageReceiver1;
	err = pthread_create(&messageReceiver1,NULL,&messageReceiver,NULL);
	if (err != 0)
	{
		printf("\nError Creating Receiver Thread!");
		exit(0);
	}
	else
	{
		printf("\n Receiver Thread Created!");
	}

//	if(isMaster == 1)
//	{
//		system("sshpass -p shweta ssh shweta@192.168.0.15 '/home/shweta/workspaceDES/Test2DES/Debug/Test2DES' &");
//		system("ssh -i /home/pooja/Desktop/amazon_ec2_keys/AboFaris.pem ubuntu@52.25.7.51 '/home/ubuntu/Test2DES' &");
//		system("ssh -i /home/pooja/Desktop/amazon_ec2_keys/AboFaris.pem ubuntu@52.26.166.209 '/home/ubuntu/Test2DES' &");
//		system("ssh -i /home/pooja/Desktop/amazon_ec2_keys/AboFaris.pem ubuntu@52.25.254.10 '/home/ubuntu/Test2DES' &");
//		system("ssh -i /home/pooja/Desktop/amazon_ec2_keys/AboFaris.pem ubuntu@52.27.206.53 '/home/ubuntu/Test2DES' &");
//		system("ssh -i /home/pooja/Desktop/amazon_ec2_keys/AboFaris.pem ubuntu@52.26.253.60 '/home/ubuntu/Test2DES' &");
//
//	}

	if(isMaster)
	{
		printf("\nSleeping 10 Seconds to see if we can invoke. \n");
		sleep(10);
	}

	//If I am Master, send message to the other clients saying I am the Master.
	if(isMaster == 1)
	{
		strcpy(message,"MASTER IPADDRESS ");
		strcat(message, clientIPAddress[0]);

		//for(k=1;k<maxNumberOfComputers;k++)
		//{
			messageSender(clientIPAddress[1], message);
			messageSender(clientIPAddress[2], message);
			messageSender(clientIPAddress[3], message);
			messageSender(clientIPAddress[4], message);
			messageSender(clientIPAddress[5], message);
			messageSender(clientIPAddress[6], message);
		//}

		//sleeping for 5 seconds before sending the next message.
		sleep(5);

		memset(message, 0x0,sizeof(char)*1024);
		strcpy(message, "MASTER - START");

		//for(k=1;k<maxNumberOfComputers;k++)
		//{
		messageSender(clientIPAddress[1], message);
		messageSender(clientIPAddress[2], message);
		messageSender(clientIPAddress[3], message);
		messageSender(clientIPAddress[4], message);
		messageSender(clientIPAddress[5], message);
		messageSender(clientIPAddress[6], message);
		//}

	}

	if(isMaster != 1){
		while(1)
		{
			//if start file exist delete it and break.  else keep on rocking!.
			//start file will be created when Client's receiver receives MASTER - START message.
			if(access("start", F_OK) != -1){
				remove("start");
				break;
			}
		}
	}

	remainder =  (maximumIterations % noOfThreads);
	noOfIterationsEachThread = (maximumIterations/noOfThreads);

	//printf(" remainder in main : %llu\n",remainder);
	//printf(" noOfIterationsEachThread in main : %llu\n",noOfIterationsEachThread);

	pthread_t workerX_thread[5];
	struct worker_inputs worker[5];

	for(j=0,i=threadStartIndex;i<=threadEndIndex;i++,j++)
	{
		worker[j].workerid = i;
		worker[j].start = ((i-1)*noOfIterationsEachThread)+268435456;
		worker[j].end = worker[j].start + noOfIterationsEachThread;

		//printf(" worker[j].workerid in main : %d\n",worker[j].workerid);
		//printf(" worker[j].start in main : %llu\n",worker[j].start);
		//printf(" worker[j].end in main : %llu\n",worker[j].end);


		err = pthread_create(&workerX_thread[j],NULL,&workerX,&worker[j]);
		if (err != 0)
			printf("\nError Creating Worker %d Thread!",worker[j].workerid);
		else
			printf("\n Worker %d Thread Created!",worker[j].workerid);

	}

	if(remainder > 0 && computer_id == maxNumberOfComputers){
		// start one more worker with no. of iterations equal to the value of remainder.
		struct worker_inputs extraWorker;
		pthread_t extra_workerX_thread;

		extraWorker.workerid = threadEndIndex + 1;
		//printf("10th worker end index in main : %llu\n",worker[MAX_THREAD_PER_MACHINE - 1].end);
		extraWorker.start = worker[MAX_THREAD_PER_MACHINE - 1].end;
		extraWorker.end = extraWorker.start + remainder;

		//printf("\n Extra worker id in main : %d\n",extraWorker.workerid);
		//printf(" Extra worker start in main : %llu\n",extraWorker.start);
		//printf(" Extra worker end in main : %llu\n",extraWorker.end);

		err = pthread_create(&extra_workerX_thread,NULL,&workerX,&extraWorker);
		if (err != 0)
			printf("\nError Creating Worker %d Thread!",worker[j].workerid);
		else
			printf("\n Worker %d Thread Created!",worker[j].workerid);

	}
	printf("\nDONE.");

	while(1)
	{

	}
}

