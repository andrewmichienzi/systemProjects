
#include "list.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
struct CommentArgs{
	int lineComment;
	int blockComment;
};
Node * processFile(FILE *fin);
int isIdentifier(char * delim);
Node * addIdentifier(Node * firstNode, char * delim, int linePtr);
void removeSpecials(char * line);
int isInArray(char * c, char specials[], int specialLen);

int main(int argc, char* argv[])
{
	FILE *fin, *fout;
	if(argc != 3)
		exit(1);

	fin = fopen(argv[1], "r");
	Node * firstNode;
	firstNode = processFile(fin);	
	fout = fopen(argv[2], "w");
	printNodes(firstNode, fout);
	
	return 0;	
}

/*
 *	Finds all valid identifiers in a file 
 */
Node * processFile(FILE *fp)
{
	Node * firstNode = InitNode();
	struct CommentArgs cArgs = {0, 0};
	char * line = NULL;
	size_t len = 0;
	ssize_t read;
	int linePtr = 1;
	while((read = getline(&line, &len, fp)) != -1)		//Goes through each line in the file
	{
		char * delim;
		int length = strlen(line);
		if (line[length-1] == '\n'){			//Remove new line from the end of line
			line[length-1] = '\0';
		}
		
		removeSpecials(line);				//Remove all specials from the line 
		delim = strtok(line, " ");			//Starts word pointer at beginning of the line
		

		while (delim != NULL)				//While there are still words in the line
		{

			if(*delim == '\n') 			//if delim is just a new line
			{	
				delim = strtok(NULL, " "); 	//next word
				continue; 			//Start the while loop over
			}
								
			char * c = delim;
			int i;
			int wordLength = strlen(delim);

		
/****** --------------------------------------Checking for Comments-------------------------------------- ****/

	
			for(i = 0;i < (wordLength - 1); i++) 				//for each character in the word
			{	
				if(cArgs.blockComment)					//if we are inside of a block comment
				{
					if(*(c+i) == '*' && *(c+i+1) == '/')		//if there is an ending block comment
					{
						cArgs.blockComment = 0;			//We are not in a block comment anymore
						if((i+2) != wordLength) 		//if block comment is NOT at the end of the word
						{
							delim = (delim + i + 2);	//Start the word after the block comment	
						}
						else					//If block comment IS at the end of the word
						{
							delim = strtok(NULL, " ");	//Next word
						} 
						if(delim == NULL){			//If it's the end of the file
							wordLength = -1;		//Skip over for loop completely		
							continue;			//Takes care of seg faults
						}
						else
							wordLength = strlen(delim);	//update word Length since we have 
						
						c = delim;				//starting the character at the beginning of the new word
						i=0;					//starting the cursor at the beginning
					}	
				}

				if(!cArgs.blockComment)					//If we are not in a block comment
				{
					if(*(c+i) == '/' && *(c+i+1) == '/')		//If we are at the start of a line comment
					{
						cArgs.lineComment = 1;			
			
						if(i != 0)				//If the line comment isn't at the beginning of the word
						{
							delim[i] = '\0';		//Defining the end of the word before the line comment begins
							if(isIdentifier(delim))		//Check if new word is an identifier
							{
								firstNode = addIdentifier(firstNode, delim, linePtr);
											//add new word to the list
							}
						}
						i = wordLength;				//get out of the for loop and disregard rest of word
					}
					else						//Not a line comment
					{	
						if(*(c+i) == '/' && *(c+i+1) == '*')	//if we point to the start of a block comment
						{
							cArgs.blockComment = 1;		//Currently in a block comment
							if(i != 0)			//If we are not at the beginning of the word
							{
								char * tempWord = delim;
								tempWord[i]='\0';	//Checking if word before the comment block is an identifier
								if(isIdentifier(tempWord))
								{
									firstNode = addIdentifier(firstNode, tempWord, linePtr);
											//Add identifier before comment to list
								}
							}
						}
					}
				}	
			}

/*-----------------------END Checking for Comments----------------------------------------*****/

			if(!cArgs.lineComment && !cArgs.blockComment && isIdentifier(delim))	//If we are an identifier and not in a comment		
				firstNode = addIdentifier(firstNode, delim, linePtr);		//add word to the list	
										
			delim = strtok(NULL, " ");						//Next word
		}
		linePtr++;
		cArgs.lineComment = 0;
	}
	return firstNode;
}

int isIdentifier(char * delim)
{
	if(delim == NULL)
		return 0;
	char * c = delim;
	if(isdigit(*c))
		return 0;
	return 1;
}

Node * addIdentifier(Node * firstNode, char * delim, int linePtr)
{
	Node * nextNode;
	if(isEmpty(firstNode))
	{
		int length = strlen(delim);
		firstNode = createNode(delim, linePtr);
	}	
	else
	{
		nextNode = createNode(delim, linePtr);
		addNodeToList(firstNode, nextNode);
	}
	return firstNode;
}

int isInArray(char * c, char specials[], int specialLen)
{
	int i;
	for(i = 0; i < specialLen; i++)
	{
		printf("%c vs %c\n", *c, specials[i]);	
		if(*c == specials[i])
			return 1;
	}
	return 0;
}

void removeSpecials(char * line)
{
	int specialLen = 15;
	char specials[15] = {''.', '"', '<', '>', '#', '=', '+', '-', ';', '(', ')', '!', '|', '&'};
	char * c = line;
	int len = strlen(line);
	int i;
	for(i = 0; i < len; i++)
	{
		if(isInArray(c, specials, specialLen))
		{
		printf("hey\n");
			*(line + i) = ' ';
		}
	} 
}

