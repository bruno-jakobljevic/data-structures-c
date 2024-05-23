#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Word {
	char* word; // rijec
	int count; // broj pojavljivanja rijeci
	struct Word* next;
} Word;

typedef Word* Dictionary;

// kreaira novi prazni rjecnik
Dictionary create();

// dodaje rijec ili uvecava broj pojavljivanja rijeci u rjecniku
// rijeci se dodaju u abecednom redu
void add(Dictionary dict, char* str);

// ispisuje sve rijeci i broj pojavljivanja svake rijeci
void print(Dictionary dict);

// brise cijeli rjecnik
void destroy(Dictionary dict);

// filtriranje liste
int filter(Word* w);
Dictionary filterDictionary(Dictionary indict, int(*filter)(Word* w));

Word* findLongestWord(Dictionary dict);
int findTotalNumberOfWords(Dictionary dict);
Dictionary addToHead(Dictionary head, char* str);
Dictionary addToEnd(Dictionary dict, char* str);
Dictionary reverseDict(Dictionary dict);
Dictionary switchLastSecondLast(Dictionary dict);
Dictionary switchSecondFourth(Dictionary dict);
Dictionary copyWords(Dictionary dict);