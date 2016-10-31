#define MAX_NUMBERS 100
typedef struct Queue {
	int lineNumbers[MAX_NUMBERS];
} Queue;

Queue * InitQueue();
int addToQueue(Queue * queue, int lineNumber);
void printLineNumbers(Queue * queue);
int getNumber(Queue * queue, int i);
