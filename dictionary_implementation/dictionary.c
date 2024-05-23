#define _CRT_SECURE_NO_WARNINGS
#include "dictionary.h"

Dictionary create()
{
	Dictionary emptyDict = (Dictionary)malloc(sizeof(Word));

	if (!emptyDict)
		return NULL;

	emptyDict->next = NULL;
	emptyDict->word = NULL;
	emptyDict->count = 0;

	return emptyDict;
}

Word* createNewWord(char* str)
{
	Word* newWord = (Word*)malloc(sizeof(Word));

	if (!newWord)
		return NULL;

	newWord->word = _strdup(str);
	newWord->count = 1;
	newWord->next = NULL;

	return newWord;
}

void add(Dictionary dict, char* str)
{	
	// skip dummy head
	Word* nextWord = dict->next;
	Word* newWord;

	while(nextWord)
	{
		if (strcmp(nextWord->word, str) == 0)
		{
			nextWord->count += 1;
			return;
		}
		else if (strcmp(nextWord->word, str) > 0)
		{
			newWord = createNewWord(str);
			newWord->next = nextWord;
			dict->next = newWord;
			return;
		}
		else
		{
			nextWord = nextWord->next;
			dict = dict->next;
		}
	}
	// putting new word to the end if dict->next(or nextWord) is NULL
	dict->next = createNewWord(str);
}

void print(Dictionary dict)
{
	Word* nextWord = dict->next;

	while (nextWord)
	{
		printf("'%s' se pojavljuje %d puta.\n", nextWord->word, nextWord->count);
		nextWord = nextWord->next;
	}
}

void destroy(Dictionary dict)
{
	Word* nextWord = dict->next;
	Word* temp;

	while (nextWord)
	{
		temp = nextWord;
		nextWord = nextWord->next;
		free(temp->word);
		free(temp);
	}

	free(dict);
}

int filter(Word* w)
{
	return w->count > 5 && w->count < 10 && strlen(w->word) > 3;
}

Dictionary filterDictionary(Dictionary indict, int(*filter)(Word* w))
{
	Word* nextWord = indict;
	Word* temp;

	while (nextWord->next)
	{
		if (!filter(nextWord->next))
		{
			temp = nextWord->next;
			nextWord->next = nextWord->next->next;

			free(temp->word);
			free(temp);
		}
		nextWord = nextWord->next;
	}
	return indict;
}

Word* findLongestWord(Dictionary dict)
{
	Word* currentWord = dict->next;
	Word* longestWord = currentWord;

	while (currentWord)
	{
		if (strlen(currentWord->word) > strlen(longestWord->word))
			longestWord = currentWord;
		currentWord = currentWord->next;
	}
	return longestWord;
}

int findTotalNumberOfWords(Dictionary dict)
{
	Word* currentWord = dict->next;

	int totalCount = 0;

	while (currentWord)
	{
		totalCount += currentWord->count;
		currentWord = currentWord->next;
	}

	return totalCount;
}

int findTotalNumberOfUniqueWords(Dictionary dict)
{
	Word* currentWord = dict->next;
	
	int totalCount = 0;

	while (currentWord)
	{
		totalCount++;
		currentWord = currentWord->next;
	}

	return totalCount;
}

Dictionary addToHead(Dictionary head, char* str)
{
	Word* newWord = (Word*)malloc(sizeof(Word));
	newWord->word = _strdup(str);
	newWord->count = 1;
	
	Word* firstWord = head->next;
	newWord->next = firstWord;
	head->next = newWord;

	return head;
}

Dictionary addToEnd(Dictionary dict, char* str)
{
	Dictionary dictCopy = dict;

	Word* newWord = (Word*)malloc(sizeof(Word));
	newWord->word = _strdup(str);
	newWord->count = 1;

	while (dictCopy->next)
		dictCopy = dictCopy->next;
	dictCopy->next = newWord;

	return dict;
}

Dictionary addBeforeSpecificElement(Dictionary dict, char* str, char* specificStr)
{
	Word* dictCopy = dict;
	Word* currentWord = dict->next;

	Word* newWord = (Word*)malloc(sizeof(Word));
	newWord->word = _strdup(str);
	newWord->count = 1;

	while (dictCopy)
	{
		if (strcmp(currentWord->word, specificStr) == 0)
		{
			newWord->next = currentWord;
			dictCopy->next = newWord;

			return dict;
		}
		dictCopy = dictCopy->next;
		currentWord = currentWord->next;
	}

	return dict;
}

Dictionary addOnChosenIndex(Dictionary dict, char* str, int index)
{
	
	Word* newWord = (Word*)malloc(sizeof(Word));
	newWord->word = _strdup(str);
	newWord->count = 1;

	int counter = 1;
	Word* currentWord = dict->next;

	while (currentWord)
	{
		currentWord = currentWord->next;
		counter++;
		if (counter == index)
		{
			newWord->next = currentWord->next;
			currentWord->next = newWord;
			return dict;
		}
	}
	return NULL;
}

Dictionary removeFromHead(Dictionary dict)
{
	Word* currentWord = dict->next;
	dict->next = dict->next->next;
	free(currentWord->word);
	free(currentWord);
	return dict;
}

Dictionary removeFromEnd(Dictionary dict)
{
	Word* currentWord = dict;
	Word* temp = dict->next;

	while (temp->next)
	{
		currentWord = currentWord->next;
		temp = temp->next;
	}
	free(temp->word);
	free(temp);
	currentWord->next = NULL;

	return dict;
}

Dictionary removeChosenWord(Dictionary dict, char* str)
{
	Word* currentWord = dict;
	Word* temp = dict->next;
	while (currentWord)
	{
		if (strcmp(temp->word, str) == 0)
		{
			currentWord->next = currentWord->next->next;
			free(temp->word);
			free(temp);
			return dict;
		}
		currentWord = currentWord->next;
		temp = temp->next;
	}
	return dict;
}

Dictionary deleteLongestWord(Dictionary dict)
{

	Word* currentWord = dict->next;
	Word* temp = dict->next->next;
	Word* longestWord = currentWord;
	Word* beforeLongest = NULL;

	while (currentWord)
	{
		if (strlen(currentWord->next->word) > strlen(longestWord->word))
		{
			longestWord = currentWord->next;
			beforeLongest = currentWord;
		}
		currentWord = currentWord->next;
		temp = temp->next;
	}
	beforeLongest->next = beforeLongest->next->next;
	free(longestWord->word);
	free(longestWord);
	return dict;
}
// pogledaj ove dvi na papiru
Dictionary reverseDict(Dictionary dict)
{
	Word* previous = NULL;
	Word* current = dict->next;
	Word* next = NULL;

	while (current)
	{
		next = current->next;
		current->next = previous;
		previous = current;
		current = next;
	}

	dict->next = previous;
	return dict;
}
/*
kad nema dummy heada
*/
Dictionary reverseDict2(Dictionary dict)
{
	Word* reversed = NULL;
	while (dict)
	{
		Word* temp = dict;
		dict = dict->next;
		temp->next = reversed;
		reversed = temp;
	}
}

Dictionary deleteAllLongerThanTen(Dictionary dict)
{
	Word* currentWord = dict;
	Word* temp = dict->next;
	while (temp)
	{
		if (strlen(temp->word) > 10)
		{
			currentWord->next = currentWord->next->next;
			free(temp->word);
			free(temp);
		}
		currentWord = currentWord->next;
		temp = temp->next;
	}

	return dict;
}

Dictionary deleteLastTen(Dictionary dict)
{
	Word* temp = dict;
	Word* brisi;

	int counter = 0;
	int position = 0;

	while (temp)
	{
		temp = temp->next;
		counter++;
	}

	temp = dict;

	while (position != counter - 11)
	{
		position++;
		temp = temp->next;
	}

	temp = dict;

	while (temp->next)
	{
		brisi = temp->next;
		temp->next = temp->next->next;
		free(brisi->word);
		free(brisi);
	}
	return dict;
}

Dictionary addMoreElements(Dictionary dict, char* str)
{
	Word* temp1 = dict;
	Word* temp2 = dict->next;

	Word* newWord = (Word*)malloc(sizeof(Word));
	newWord->word = _strdup(str);
	newWord->count = 1;
	newWord->next = NULL;

	while (temp1)
	{
		if (strlen(temp2->word) > 10)
		{
			Word* newWord = (Word*)malloc(sizeof(Word));
			newWord->word = _strdup(str);
			newWord->count = 1;
			newWord->next = NULL;

			temp1->next = newWord;
			newWord->next = temp2;
		}
		temp1 = temp1->next;
		temp2 = temp2->next;
	}
	return dict;
}

Dictionary newDictLongerThanTen(Dictionary dict)
{
	Dictionary dict2 = create();
	Word* temp2 = dict2;
	Word* temp = dict;
	Word* del = NULL;

	while (temp->next)
	{
		if (strlen(temp->next->word) > 10)
		{
			Word* newWord = (Word*)malloc(sizeof(Word));
			newWord->word = _strdup(temp->next->word);
			newWord->count = 1;
			newWord->next = NULL;

			temp2->next = newWord;
			temp2 = temp2->next;
			del = temp->next;
			temp->next = temp->next->next;
			free(del->word);
			free(del);
		}
		temp = temp->next;
	}
	return dict2;
}

Dictionary switchFirstSecond(Dictionary dict)
{
	Word* temp1 = dict->next;
	Word* temp2 = dict->next->next;

	temp1->next = temp2->next;
	temp2->next = temp1;
	dict->next = temp2;

	return dict;
}

Dictionary switchLastFirst(Dictionary dict)
{
	Word* last = dict->next;
	Word* beforeLast = dict;

	while (last->next)
	{
		last = last->next;
		beforeLast = beforeLast->next;
	}

	last->next = dict->next;
	dict->next = last;
	beforeLast->next = NULL;

	return dict;
}

Dictionary switchLastSecondLast(Dictionary dict)
{
	Word* temp1 = dict->next;
	Word* temp2 = dict;
	Word* temp3;

	while (temp1->next->next)
	{
		temp1 = temp1->next; //predzadnji
		temp2 = temp2->next; //pretpredzadnji
	}
	temp2->next = temp1->next;
	temp2->next->next = temp1;
	temp1->next = NULL;

	return dict;
}

Dictionary switchSecondFourth(Dictionary dict)
{
	Word* temp1 = dict->next;
	Word* temp2 = temp1->next;
	Word* temp3 = temp1->next->next;
	Word* temp4 = temp1->next->next->next;
	

	Word* tempTemp = temp4->next;
	temp1->next = temp4;
	temp4->next = temp3;
	temp3->next = temp2;
	temp2->next = tempTemp;

	return dict;
}


Dictionary copyWords(Dictionary dict)
{
	Dictionary newDict = create();
	Word* newDictCpy = newDict;
	
	Word* currentWord = dict->next;

	while (currentWord)
	{
		if (strlen(currentWord->word) > 10)
		{
			Word* newWord = (Word*)malloc(sizeof(Word));
			newWord->word = _strdup(currentWord->word);
			newWord->count = 1;
			newWord->next = NULL;

			newDictCpy->next = newWord;
			newDictCpy = newDictCpy->next;
		}
		currentWord = currentWord->next;
	}

	return newDict;
}

char** copyWordsToArr(Dictionary dict)
{
	int counter = 0;
	Word* currentWord = dict->next;
	
	while (currentWord)
	{
		currentWord = currentWord->next;
		counter++;
	}
	char** arrayOfStrings = (char**)malloc(sizeof(char*) * counter);

	for (int i = 0; i < counter; i++)
		arrayOfStrings[i] = (char*)malloc(sizeof(char) * 30);

	currentWord = dict->next;

	for (int i = 0; i < counter; i++)
	{
		arrayOfStrings[i] = _strdup(currentWord->word);
		currentWord = currentWord->next;
	}

	return arrayOfStrings;
}


Dictionary addFromArray(Dictionary dict, char** arr)
{
	Word* currentWord = dict->next;

	while (currentWord)
		currentWord = currentWord->next;

	char** arrCpy = arr;
	int counter = 0;

	while (*arrCpy != NULL)
	{
		*arrCpy = arrCpy[counter];
		counter++;
	}

	for (int i = 0; i < counter; i++)
	{
		currentWord = createNewWord(*arr);
		currentWord = currentWord->next;
	}

	currentWord->next = NULL;

	return dict;
}

Dictionary addStringSecondLast(Dictionary dict, char* str)
{
	Word* currentWord = dict;
	Word* nextWord = dict->next;

	while (nextWord->next != NULL)
	{
		currentWord = currentWord->next;
		nextWord = nextWord->next;
	}

	Word* newWord = (Word*)malloc(sizeof(Word));

	newWord->word = _strdup(str);
	newWord->count = 1;

	newWord->next = nextWord;
	currentWord->next = newWord;

	return dict;
}

char* returnSecondLastWord(Dictionary dict)
{
	Word* currentWord = dict;

	while (currentWord->next->next != NULL)
		currentWord = currentWord->next;
	
	return currentWord->word;
}