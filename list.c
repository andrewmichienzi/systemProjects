#include "list.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
/*
* 
*/
Node * InitNode()
{
	Node *node = malloc(sizeof(Node));
	int i;
	node->queue = InitQueue();
	strcpy(node->identifier, "");
	node->nextNode = NULL;
	node->isComment = 0;
	node->nextNodeIsComment = 0;
	return node;
}

Node * InitNodeWithArgs(int isComment)
{
	Node * node = InitNode();
	node->isComment = isComment;
	return node;
}

void addNodeToList(Node * node, Node * nodeToAdd)
{
	int nodeComp;
	if(!nodeCompare(node, nodeToAdd))
	{
	//	printf("nodeComp = %d\n", nodeComp);
		int lineNumber = getNumber(nodeToAdd->queue, 0);
		addToQueue(node->queue, lineNumber);
		return;
	}
	if(node->nextNode == NULL)
		node->nextNode = nodeToAdd;
	else
		addNodeToList(node->nextNode, nodeToAdd);
}

void printNodes(Node * node)
{	
	int i = 0;
	printf("%s:\t", node->identifier);
//	printf("Howdy\n");
	printLineNumbers(node->queue);
	printf("\n"); 
	if(node->nextNode != NULL)
		printNodes(node->nextNode);
}

Node * createNode(char word[], int lineNumber)
{
	Node * node = InitNode();
	strcpy(node->identifier, word);
	addToQueue(node->queue, lineNumber);
	return node;
}

/*Returns 1 if node exists, else it returns 0*/
int checkIfNodeExists(Node * node, Node * nodeToAdd)
{
	if(node->nextNode == NULL)
		return 1;
	if(nodeCompare(node, nodeToAdd))
		return 0;
	return checkIfNodeExists(node->nextNode, nodeToAdd);

	
}

/* Returns 1 if the identifiers are equal, else returns 0*/
int nodeCompare(Node * node1, Node * node2)
{
	return strcmp(node1->identifier, node2->identifier);
}

int isEmpty(Node * node)
{
	int num = getLineNumber(node->queue, 0);
	if(num == -1)
		return 1;
	else
		return 0;
}



