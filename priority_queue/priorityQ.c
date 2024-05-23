#include "priorityQ.h"
#define N 10000

prioQ* createPrioQ()
{
	prioQ* q = (prioQ*)malloc(sizeof(prioQ));

	if (q == NULL)
		return NULL;

	q->el = (Num*)malloc(sizeof(Num) * N);
	q->index = 0;
	return q;
}

void addNum(prioQ* q, int num)
{
	q->el[q->index].prio = num;
	q->index += 1;
	fixToTop(q, q->index);
}

void removePrio(prioQ* q)
{
	q->el[0] = q->el[q->index - 1];
	q->index -= 1;
	fixToBottom(q, 0);
}

void fixToTop(prioQ* q, int childIndex)
{
	if (childIndex == 0)
		return;

	int parentIndex = (childIndex - 1) / 2;

	if (q->el[parentIndex].prio < q->el[childIndex].prio)
	{
		int temp = q->el[parentIndex].prio;
		q->el[parentIndex].prio = q->el[childIndex].prio;
		q->el[childIndex].prio = temp;
		fixToTop(q, parentIndex);
	}
}

void fixToBottom(prioQ* q, int parentIndex)
{
	int leftChild = 2 * parentIndex + 1;
	int rightChild = 2 * parentIndex + 2;

	if (leftChild >= q->index && rightChild >= q->index)
		return;

	else if (leftChild < q->index && rightChild >= q->index)
	{
		if (q->el[parentIndex].prio < q->el[leftChild].prio)
		{
			int temp = q->el[parentIndex].prio;
			q->el[parentIndex].prio = q->el[leftChild].prio;
			q->el[leftChild].prio = temp;
		}
		else
			return;
	}

	else // ako je roditelj manji od livog ili od desnog
	{
		if (q->el[leftChild].prio < q->el[rightChild].prio)
		{
			int temp = q->el[parentIndex].prio;
			q->el[parentIndex].prio = q->el[rightChild].prio;
			q->el[rightChild].prio = temp;
			fixToBottom(q, rightChild);
		}
		else
		{
			int temp = q->el[parentIndex].prio;
			q->el[parentIndex].prio = q->el[leftChild].prio;
			q->el[leftChild].prio = temp;
			fixToBottom(q, leftChild);
		}
	}
}

void printQ(prioQ* q)
{
	for (int i = 0; i < q->index; i++)
		printf("%d ", q->el[i].prio);
	printf("\n");
}