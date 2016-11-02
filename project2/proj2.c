
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

int main(int argc, char* argv[])
{
	FILE *fin, *fout;
	if(argc != 3)
		exit(1);

	fin = fopen(argv[1], "r");
	Node * firstNode = InitNode();	
//	printf("First Node Made\n");
	firstNode = processFile(firstNode, fin);	
//	printf("First Node = %s\n", firstNode->identifier);
	printNodes(firstNode);
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
		//printf("new line\n");
		char * delim;
		
		//Remove new line from the end of line
		int length = strlen(line);
		if (line[length-1] == '\n'){
			//printf("Line %d has a new line\n", linePtr);
			line[length-1] = '\0';
		}
		delim = strtok(line, " ");
		

		while (delim != NULL)
		{

			if(*delim == '\n')// || strcmp(delim, "\n"))
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
					printf("%c and %c\n", *(c+i), *(c+i+1));
					if(*(c+i) == '*' && *(c+i+1) == '/')
					{
						printf("In block comment\n");
						cArgs.blockComment = 0;
						if((i+2) != wordLength) //block comment is NOT at the end of the word
						{
							delim = (delim + i + 2);
							printf("\n\nnew delim == %s %c\n\n", delim, delim[0]);
						}
						else
						{
							printf("Hey derr\n");
							delim = strtok(NULL, " ");
//							printf("Hello\n\n");
						} 
//						printf("Yo\n\n");
						c = delim;
						i=0;
//						printf("Yo\n\n");
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
//						printf("line comment\n");
						//Line Comment
						cArgs.lineComment = 1;
			
						if(i != 0)
						{
							delim[i] = '\0';
//							printf("New delim = %s\n", delim);
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
								//delim = (delim + i + 2);
								//wordLength = strlen(delim);
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



//			printf("Out of Line Comment\n");
			//Check for line comment
			if(cArgs.lineComment || !isIdentifier(delim) || cArgs.blockComment)
			{
//				printf("Is line comment or is not identifier");
				delim = strtok(NULL, " ");
				continue;
			}
			//TODO: Check for block comments
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
	//printf("isIdentifier()\n");
	if(delim == NULL)
		return 0;
	char * c = delim;
	if(isdigit(*c))
		return 0;
	return 1;
}

Node * addIdentifier(Node * firstNode, char * delim, int linePtr)
{
	//printf("Howdy\n");
	Node * nextNode;
	if(isEmpty(firstNode))
	{
		//printf("Creating First Node\n")
		int length = strlen(delim);
		firstNode = createNode(delim, linePtr);
		//printf("First Node = %s\n", firstNode->identifier);
		//printf("String Length = %d\n", length);
	}	
	else
	{
		//printf("Creating Node for %s\n", delim);
		nextNode = createNode(delim, linePtr);
		//printf("Next Node = %s\n", nextNode->identifier);
		addNodeToList(firstNode, nextNode);
	}
	return firstNode;
}



