#include "bstree.h"

BSTree NewBSTree()
{
	BSTree newTree = (BSTree)malloc(sizeof(Node));
	if (newTree == NULL)
		return NULL;

	newTree->left = NULL;
	newTree->right = NULL;
	newTree->word = NULL;

	return newTree;
}

Node* NewNode(char* word)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL)
		return NULL;

	newNode->left = NULL;
	newNode->right = NULL;
	newNode->word = word;

	return newNode;
}

void AddNode(BSTree* bst, char* word)
{
	if ((*bst) == NULL || (*bst)->word == NULL)
	{
		Node* newNode = NewNode(word);
		*bst = newNode; 
		return;
	}

	if (strcmp((*bst)->word, word) == 0)
	{
		free(word);
		return;
	}

	else if (strcmp((*bst)->word, word) > 0)
		AddNode(&((*bst)->left), word);

	else // comp < 0
		AddNode(&((*bst)->right), word);
}

int BSTHeight(BSTree bst)
{
	if (bst == NULL)
		return 0;

	int leftHeight = BSTHeight(bst->left);
	int rightHeight = BSTHeight(bst->right);

	if (leftHeight > rightHeight)
		return (leftHeight + 1);
	else
		return (rightHeight + 1);
}

void PrintBSTree(BSTree bst)

{
	if (bst == NULL)
		return;

	PrintBSTree(bst->left);
	printf("%s\n", bst->word);
	PrintBSTree(bst->right);
}

void SaveBSTree(BSTree bst, FILE* fd)
{
	if (bst == NULL)
		return;

	fprintf(fd, "%s ", bst->word);

	SaveBSTree(bst->left, fd);
	SaveBSTree(bst->right, fd);
}

void DeleteBSTree(BSTree bst)
{
	if (bst == NULL)
		return;

	DeleteBSTree(bst->left);
	DeleteBSTree(bst->right);

	free(bst->word);
	free(bst);
}

int readWord(FILE* fp, char* buffer)
{
	int c;

	do
	{
		c = fgetc(fp);

		if (c == EOF)
			return 0;

	} while (!isalpha(c));

	do
	{
		*buffer = tolower(c);
		buffer++;

		c = fgetc(fp);

		if (c == 146)
			c = '\'';

	} while (isalpha(c) || c == '\'');
	*buffer = '\0';

	return 1;
}

BSTree LoadBSTree(FILE* fd)
{
	char buffer[1024];

	BSTree bst = NewBSTree();

	while (readWord(fd, buffer))
		AddNode(&bst, _strdup(buffer));

	return bst;
}
