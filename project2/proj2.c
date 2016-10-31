#include "list.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
Node * processFile(Node * firstNode, FILE *fin);
//int isIdentifier(char * word);
//int checkForComment(char * word);
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
	char * line = NULL;
	size_t len = 0;
	ssize_t read;
	int linePtr = 1;
	Node * nextNode;
	int firstNodeEmpty = 1;
	while((read = getline(&line, &len, fp)) != -1)
	{
		//New Line
		printf("new line\n");
		char * delim;
		char * newLine;
		
		//Remove new line from the end of line
		int length = strlen(line);
		if (line[length-1] == '\n'){
			printf("Line %d has a new line\n", linePtr);
			line[length-1] = '\0';
		}
		delim = strtok(line, " ");
		

		while (delim != NULL)
		{
		if(*delim == '\n')// || strcmp(delim, "\n"))
		{
			//Do nothing
		}
		else if(firstNodeEmpty)
		{
		//	printf("Creating First Node\n")
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
		}
		delim = strtok(NULL, " ");
		/*	if(isIdentifier(delim))
			{
				//Add this shit to the firstNode
				if(isEmpty(firstNode))
					firstNode = createNode(delim, linePtr);	
				else
				{
					Node * node = createNode(delim, linePtr);
					addNodeToList(firstNode, node);
				}
			}
			isComment = checkForComment(delim);			
		
		*/
		
		//delim is next word in stream
		//If this word is a comment, check if it ends in the beginning
		
/*
		char * letter = delim;
		if ((*letter) == '\0')\
		{
			//Word doesn't exist
			continue;
		} 
		if(*(letter + 1) == '\0')
		{
			//The word is just one letter
			if(	
			Node node = createNode(delim, linePtr);	
		}*/
		}
		linePtr++;
	}
	return firstNode;
}
/*
int isIdentifier(char * word)
{
	int returnVal = 0;
	char * letter = word;
	if(*letter == '/' && !(*endOfLine))
	{
		if(*(letter + 1) == '/')
		{
			//Comment
			*endOfLine = 1;
		}
		if(*(letter + 1) == '*')
		{
			*isComment = 1;;
		}
	}
	if(isdigit(letter))
		return 0;
}

int checkForComment(char * word)
{
	char * letter = word;//letter == first letter in word
	if(*letter == '/')
	{
		if(*(letter + 1) == '/')
		{
			//Comment
			return 1;
		}
	}
}
*/



















