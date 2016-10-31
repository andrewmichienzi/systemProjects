
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
	printf("First Node Made\n");
	firstNode = processFile(firstNode, fin);	
	printf("First Node = %s\n", firstNode->identifier);
	printNodes(firstNode);
/*

	Node * firstNode = createNode("Donkey", 14);
	Node * nextNode = createNode("Donkey", 12);
	addNodeToList(firstNode, nextNode);
	nextNode = createNode("Jenga", 2);
	addNodeToList(firstNode, nextNode);
	nextNode = createNode("Fila", 156);
	addNodeToList(firstNode, nextNode);
	nextNode = createNode("Mikey", 42);
	addNodeToList(firstNode, nextNode);
	printNodes(firstNode);	
*/	
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
			
			//Is this word in a comment?
			
			char * c = delim;
			int i;
			int wordLength = strlen(delim);
			
			for(i = 0;i < (wordLength - 1); i++)
			{	
				if(*(c+i) == '/' && *(c+i+1) == '/')
				{
					printf("line comment\n");
					//Line Comment
					cArgs.lineComment = 1;
		
					if(i != 0)
					{
						delim[i] = '\0';
						//memcpy(delim, delim, i-2);
						printf("New delim = %s\n", delim);
						if(isIdentifier(delim))
						{
							firstNode = addIdentifier(firstNode, delim, linePtr);
						}
					}
					i = wordLength;
				}	
			}
			//printf("Out of Line Comment\n");
			//Check for line comment
			if(cArgs.lineComment || !isIdentifier(delim))
			{
				printf("Is line comment of is not identifier");
				delim = strtok(NULL, " ");
				continue;
			}
			//TODO: Check for block comments
			else
				firstNode = addIdentifier(firstNode, delim, linePtr);		

/*
			if(firstNodeEmpty)
			{
				//printf("Creating First Node\n")
				int length = strlen(delim);
				firstNode = createNode(delim, linePtr);
				firstNodeEmpty = 0;
				printf("First Node = %s\n", firstNode->identifier);
				printf("String Length = %d\n", length);
			}	
			else
			{
				//printf("Creating Node for %s\n", delim);
				nextNode = createNode(delim, linePtr);
				printf("Next Node = %s\n", nextNode->identifier);
				addNodeToList(firstNode, nextNode);
				printf("First Node = %s\n", firstNode->identifier);
				int length = strlen(delim);
			}*/
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



