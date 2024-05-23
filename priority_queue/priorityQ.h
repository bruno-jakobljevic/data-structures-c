#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	void* data;
	int prio;

}Num;

typedef struct
{
	int index;
	Num* el;

}prioQ;

prioQ* createPrioQ();

void addNum(prioQ* q, int num);
void removePrio(prioQ* q);

void fixToTop(prioQ* q, int childIndex);
void fixToBottom(prioQ* q, int parentIndex);

void printQ(prioQ* q);