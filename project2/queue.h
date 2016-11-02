#define MAX_NUMBERS 100
#include <stdio.h>
typedef struct Queue {
	int lineNumbers[MAX_NUMBERS];
} Queue;

Queue * InitQueue();
int addToQueue(Queue * queue, int lineNumber);
void printLineNumbers(Queue * queue, FILE * fout);
int getNumber(Queue * queue, int i);
