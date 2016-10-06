#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char alphaBack[26] = {'Z', 'Y', 'X', 'W', 'V', 'U', 'T', 'S', 'R' ,'Q' , 'P', 'O', 'N', 'M', 'L', 'K', 'J', 'I', 'H', 'G', 'F', 'E', 'D', 'C', 'B', 'A'};

char * removeDuplicates(char word[]);
char* addAlpha(char * word, int * length);
void initializeEncryptArray(char key[], char encrypt[]);
int targetFound(char charArray[], int num, char target);
void processInput(FILE *fin, FILE *fout, char substitute[]);
void initalizeDecryptArray(char encrypt[], char decrypt[]);
int isInAlphabet(int c);
char encrypt[26];
/*
 * This code uses a cipher to perform encryption and decryption on a file and outputs results to another file
 */
int main(int argc, char* argv[])
{  
	int choice;
	char ch;
	FILE *fin, *fout;
	char * key;
	if (argc != 5)
	{
		printf ("Usage: cipher option key infile, outfile\n");
		printf ("Option 1 for encryption and 2 for decryption\n");
		exit(1);
	}
	int option = atoi(argv[1]);
    	fin = fopen(argv[3], "r");
	fout = fopen(argv[4], "w");
	printf("Creating key and removing duplicates from key\n");
	key = removeDuplicates(argv[2]);
	printf("Initializing encrypt array\n");
	initializeEncryptArray(key, alphaBack);
	printf("Encrypt Array: %s\n",encrypt);		
	if(option == 1){
		processInput(fin, fout, encrypt);	
	}else
	{
		printf("Initializing decrypt array\n");
		char decrypt[26];
		initalizeDecryptArray(encrypt, decrypt);
		printf("Decrypt Array: %s\n",decrypt);		
		printf("Processing output\n");
		processInput(fin, fout, decrypt);
	}
	return(0);
}

// remove duplicate characters in array word and return the result string
char * removeDuplicates(char word[]){
	int length = strlen(word);
	char * temp = &word[0];
	int i, j;
	for(i = 0; i < length; i++)
	{
		if(isalpha(word[i]) && islower(word[i]))
			word[i] = toupper(word[i]);
	}
	for(i = 0; i < length; i++)
	{
		for(j = i+1; j < length; j++)
		{
			while((*(temp + i)) == (*(temp + j)))
			{
				int del = j;
				memmove((&word[del]), (&word[del + 1]), length - del);
				length--;
			}
		}
	}
	return (word);
}

// initialize the encrypt array with appropriate cipher letters according to the given key
void initializeEncryptArray(char key[], char encrypt2[])
{
	int length = strlen(key) + strlen(encrypt2);
	int keyLength = strlen(key);
	char encTemp[length];
	memcpy(&encTemp[0], key, keyLength);
	memcpy(&encTemp[keyLength], encrypt2, strlen(encrypt2));
	char *temp = removeDuplicates(encTemp);
	memcpy(encrypt, temp, 26);
}

// process data from the input file and write the result to the output file
// pass the encrypt array to parameter substitute if encryption is intended
// pass the decrypt array to parameter substitute if decryption is intended
void processInput(FILE *fin, FILE *fout, char substitute[])
{
   
	char ch; 
    	if (fin ==  NULL || fout == NULL) 
	{
		printf("File could not be opened\n");
		exit(1);
	}
	
	
	int i;
	while ( fscanf(fin, "%c", &ch) != EOF )
	{
		char c = ch;
		i = targetFound(substitute, 26, c);	
		if(i != 0)
			c = (char)i;
			
		fprintf(fout, "%c", c);
	}

	fclose(fin);
	fclose(fout);


}

// search the first num characters in array charArray for character target
// return a non-zero integer if found, otherwise, return 0
int targetFound(char charArray[], int num, char charTarget)
{
	int c = (int) charTarget;
	if(!isInAlphabet(c))
		return 0;

	int temp =(int) toupper(c);
		temp = (int)charArray[temp-65];
		if(isupper(charTarget))
			return temp;
		else
			return temp+32;	
	return 0;
}

// Checks for special characters. Returns 0 if not in alphabet
int isInAlphabet(int c)
{
	if(c >= 65 && c <= 90)
		return 1;
	if(c >=97 && c <=122)
		return 1;
	return 0;
}

// initialize the decrypt array with appropriate substitute letters based on the encrypt array
void initalizeDecryptArray(char encrypt[], char decrypt[])
{
	int i;
	int temp;
	for(i = 0; i < 26; i++)
	{
		temp = (char) encrypt[i];
		temp = temp - 65;
		decrypt[temp] = (char)(i+65);
	}
}




