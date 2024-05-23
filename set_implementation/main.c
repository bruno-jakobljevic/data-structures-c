#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funcs.h"
#define N 3000000

int main()
{
	int* setA = NULL;
	int* setB = NULL;
	int* setC = NULL;

	clock_t start;
	clock_t stop;

	for (size_t i = 100000, j = 1; i <= N; i += 300000)
	{
		printf("%zu. ITERACIJA (%lu elemenata):\n", j++, i);
		/*
		//prvi

		setA = generiraj(i);
		shuffle(setA, i);
		setB = generiraj(i);
		shuffle(setB, i);

		start = clock();
		setC = presjek(setA, setB, i);
		stop = clock();

		printf("Prvi zadatak se izvrsio u: %f s\n", (float)(stop - start) / CLOCKS_PER_SEC);

		free(setA);
		free(setB);
		free(setC);
		setA = NULL;
		setB = NULL;
		setC = NULL;
		*/
		//drugi

		setA = generiraj(i);
		shuffle(setA, i);
		setB = generiraj(i);
		shuffle(setB, i);

		start = clock();
		setC = presjek_jedan_sortiran(setA, setB, i);
		stop = clock();

		printf("Drugi zadatak se izvrsio u: %f s\n", (float)(stop - start) / CLOCKS_PER_SEC);

		free(setA);
		free(setB);
		free(setC);
		setA = NULL;
		setB = NULL;
		setC = NULL;

		//treci

		setA = generiraj(i);
		shuffle(setA, i);
		setB = generiraj(i);
		shuffle(setB, i);

		start = clock();
		setC = presjek_oba_sortirana(setA, setB, i);
		stop = clock();

		printf("Treci zadatak se izvrsio u: %f s\n", (float)(stop - start) / CLOCKS_PER_SEC);

		free(setA);
		free(setB);
		free(setC);
		setA = NULL;
		setB = NULL;
		setC = NULL;
	}

	return 0;
}