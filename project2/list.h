#include "queue.h"
#define SIZE 100
typedef struct Node {
	Queue * queue;
	char identifier[SIZE];
	struct Node * nextNode;
	int isComment;
	int nextNodeIsComment;
} Node;
Node * InitNode();
Node * InitNodeWithArgs(int isComment);
void addNodeToList(Node * node, Node * nodeToAdd);
void printNodes(Node * node);
Node * createNode(char word[], int lineNumber);
int checkIfNodeExists(Node * node, Node * nodeToAdd);
int isEmpty(Node * node);
