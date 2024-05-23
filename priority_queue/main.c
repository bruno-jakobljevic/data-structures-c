#include "priorityQ.h"

int main()
{
	prioQ* q = createPrioQ();

	addNum(q, 11);
	addNum(q, 23);
	addNum(q, 34);

	printQ(q);

	removePrio(q);
	printQ(q);
	
	addNum(q, 99);
	addNum(q, 100);
	printQ(q);

	removePrio(q);
	printQ(q);

	q->index = NULL;
	free(q->el);
	free(q);

	return 0;
}