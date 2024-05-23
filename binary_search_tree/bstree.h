#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <ctype.h>

// cvor stabla sa pokazivacom na rijec i na djecu cvora
typedef struct Node {
	char* word;
	struct Node* left, * right;
} Node;

// Stablo odnosno pokazivac na korijen stabla
typedef Node* BSTree;

BSTree NewBSTree();

void AddNode(BSTree* bst, char* word);

int BSTHeight(BSTree bst);

void PrintBSTree(BSTree bst);

void SaveBSTree(BSTree bst, FILE* fd);

void DeleteBSTree(BSTree bst);

BSTree LoadBSTree(FILE* fd);