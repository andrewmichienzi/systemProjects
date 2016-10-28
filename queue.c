#include "queue.h"
#include <stdlib.h>
#include <stdio.h>
Queue * InitQueue()
{
	Queue * queue = malloc(sizeof(Queue));
	int i;
	for(i = 0; i < MAX_NUMBERS; i++)
	{
		queue->lineNumbers[i] = -1;
	//	printf("queue->lineNumbers[%d] = %d\n", i, queue->lineNumbers[i]);
	}
	return queue;
}
/*
*Returns a 0 if the line exists, otherwise prints its new place in the queue
*/
int addToQueue(Queue * queue, int lineNumber)
{
	int i = 0;
	while(queue->lineNumbers[i] != -1)
	{
		if(queue->lineNumbers[i] == lineNumber)
		{
	//		printf("Line number already exists\n");
			return 0;
		}
		i++;
	}
	queue->lineNumbers[i] = lineNumber;
	return i;
}

void printLineNumbers(Queue * queue)
{
	printf("Hello there\n");
	int i = 0;
	while(queue->lineNumbers[i] != -1)
	{
		printf("%d \n", queue->lineNumbers[i]);
		i++;
	}
	printf("\n");
}

int getNumber(Queue * queue, int i)
{
	return queue->lineNumbers[i];
}
