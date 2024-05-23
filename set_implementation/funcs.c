#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


int* generiraj(int n)
{
	int* niz = (int*)malloc(sizeof(int) * n);
	niz[0] = rand() % 5;

	for (int i = 1; i < n; i++)
		niz[i] = niz[i - 1] + 1 + rand() % 5;

	return niz;
}

void shuffle(int* niz, int n)
{
	for (int i = 0; i < n; i++)
	{
		int j = (rand() * rand()) % n;
		int tmp = niz[i];
		niz[i] = niz[j];
		niz[j] = tmp;
	}
}

int compare(const void* a, const void* b)
{
	return(*(int*)a - *(int*)b);
}


int* presjek(int* skupA, int* skupB, int n)
{
	int* intersection = (int*)malloc(sizeof(int) * n);
	size_t k = 0;

	for (size_t i = 0; i < n; i++)
		for (size_t j = 0; j < n; j++)
			if (skupA[i] == skupB[j])
				intersection[k++] = skupA[i];

	intersection = realloc(intersection, k);

	return intersection;
}

int* presjek_jedan_sortiran(int* skupA, int* skupB, int n)
{
	qsort(skupB, n, sizeof(int), compare);

	int* intersectionOneSorted = (int*)malloc(sizeof(int) * n);
	int* num;
	size_t i, j;

	for (i = 0, j = 0; i < n; i++)
	{
		num = (int*)bsearch(&(skupA[i]), skupB, n, sizeof(int), compare);
		if (num != NULL && skupA[i] == *num)
			intersectionOneSorted[j++] = *num;
	}

	intersectionOneSorted = realloc(intersectionOneSorted, j);

	return intersectionOneSorted;
}

int* presjek_oba_sortirana(int* skupA, int* skupB, int n)
{
	qsort(skupA, n, sizeof(int), compare);
	qsort(skupB, n, sizeof(int), compare);

	int* intersectionBothSorted = (int*)malloc(sizeof(int) * n);
	size_t i = 0, j = 0, k = 0;

	while (i < n && j < n)
	{
		if (skupA[i] < skupB[j])
			i++;
		else if (skupA[i] > skupB[j])
			j++;
		else
		{
			intersectionBothSorted[k++] = skupA[i];
			i++;
			j++;
		}
	}
		

	intersectionBothSorted = realloc(intersectionBothSorted, j);

	return intersectionBothSorted;
}