
#include "list.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
struct CommentArgs{
	int lineComment;
	int blockComment;
};
Node * processFile(Node * firstNode, FILE *fin);
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
	Node * firstNode = InitNode();	
	firstNode = processFile(firstNode, fin);	
	fout = fopen(argv[2], "w");
	printNodes(firstNode, fout);
	
	return 0;	
}

Node * processFile(Node * firstNode, FILE *fp)
{
	struct CommentArgs cArgs = {0, 0};
	char * line = NULL;
	size_t len = 0;
	ssize_t read;
	int linePtr = 1;
	int firstNodeEmpty = 1;
	while((read = getline(&line, &len, fp)) != -1)
	{
		//New Line
		char * delim;
		
		//Remove new line from the end of line
		int length = strlen(line);
		if (line[length-1] == '\n'){
			line[length-1] = '\0';
		}
		
		removeSpecials(line);
		delim = strtok(line, " ");
		

		while (delim != NULL)
		{

			if(*delim == '\n')
			{
				//delim just a new line
				delim = strtok(NULL, " ");
				continue;	
			}
			
			char * c = delim;
			int i;
			int wordLength = strlen(delim);

		
/****** --------------------------------------Checking for Comments-------------------------------------- ****/	
			for(i = 0;i < (wordLength - 1); i++)
			{	
				if(cArgs.blockComment)
				{
					//look for ending block comment
					if(*(c+i) == '*' && *(c+i+1) == '/')
					{
						printf("In block comment\n");
						cArgs.blockComment = 0;
						if((i+2) != wordLength) //block comment is NOT at the end of the word
						{
							delim = (delim + i + 2);
						}
						else
						{
							delim = strtok(NULL, " ");
						} 
						c = delim;
						i=0;
						if(delim == NULL){
							wordLength = -1;
							continue;
						}
						else
							wordLength = strlen(delim);	
					}	
				}

				if(!cArgs.blockComment)
				{
					if(*(c+i) == '/' && *(c+i+1) == '/')
					{
						//Line Comment
						cArgs.lineComment = 1;
			
						if(i != 0)
						{
							delim[i] = '\0';
							if(isIdentifier(delim))
							{
								firstNode = addIdentifier(firstNode, delim, linePtr);
							}
						}
						i = wordLength;
					}
					else
					{
						//Check for start of block comment
						if(*(c+i) == '/' && *(c+i+1) == '*')
						{
							printf("Block comment\n");
							cArgs.blockComment = 1;
							if(i != 0)
							{
								char * tempWord = delim;
								tempWord[i]='\0';
								printf("\n\nnew tempWord == %s\n\n", tempWord);
								if(isIdentifier(tempWord))
								{
									firstNode = addIdentifier(firstNode, tempWord, linePtr);
								}
							}
						}
					}
				}	
			}

/*-----------------------END Checking for Comments----------------------------------------*****/



			//Check for line comment
			if(cArgs.lineComment || !isIdentifier(delim) || cArgs.blockComment)
			{
				delim = strtok(NULL, " ");
				continue;
			}
			else
				firstNode = addIdentifier(firstNode, delim, linePtr);		

			delim = strtok(NULL, " ");
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
		if(*c == specials[i])
			return 1;
	}
	return 0;
}

void removeSpecials(char * line)
{
	int specialLen = 14;
	char specials[14] = {'.', '"', '<', '>', '#', '=', '+', '-', ';', '(', ')', '!', '|', '&'};
	char * c = line;
	int len = strlen(line);
	int i;
	for(i = 0; i < len; i++)
	{
		if(isInArray(c, specials, specialLen))
		{
			*(line + i) = ' ';
		}
	} 
}

