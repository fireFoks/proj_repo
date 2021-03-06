//SDIZO I1 212A LAB03
//Krzysztof Oflus
//ok32746@zut.edu.pl
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#pragma warning(disable:4996)

struct Dictionary {
	int key;
	Dictionary *Left, *Right;
	char tab[10];
};

int counter = 0;

void initEmpty();
void addNewElement(Dictionary* &Root, int key);
void addRandom_X(Dictionary* &Root, int X);
void searchKey(Dictionary* &Root, int key);
void deleteKey(Dictionary* &Root, int key);
void preOrder(Dictionary* tmp);
void inOrder(Dictionary* tmp);
void postOrder(Dictionary* tmp);

int main() {

	int X, k1, k2, k3, k4;
	clock_t begin, end;
	double time_spent;
	srand((unsigned int)time(NULL));
	FILE* ftmp = fopen("inlab03.txt", "r");
	if (ftmp == NULL) {
		printf("File does not exist.");
		getchar();
		return -1;
	}

	fscanf(ftmp, "%d %d %d %d %d", &X, &k1, &k2, &k3, &k4);
	fclose(ftmp);

	struct Dictionary *Root = (Dictionary*)malloc(sizeof(Dictionary));
	Root = NULL;

	begin = clock();
	initEmpty();
	searchKey(Root, k1);
	addNewElement(Root, k1);
	addRandom_X(Root, X);
	inOrder(Root);
	printf("\nNodes inOrder -> %d\n", counter); counter = 0;
	preOrder(Root);
	printf("\nNodes preOrder -> %d\n", counter); counter = 0;
	addNewElement(Root, k2);
	inOrder(Root);
	printf("\nNodes inOrder -> %d\n", counter); counter = 0;
	addNewElement(Root, k3);
	addNewElement(Root, k4);
	deleteKey(Root, k1);
	preOrder(Root);
	printf("\nNodes preOrder -> %d\n", counter); counter = 0;
	searchKey(Root, k1);
	deleteKey(Root, k2);
	inOrder(Root);
	printf("\nNodes inOrder -> %d\n", counter); counter = 0;
	deleteKey(Root, k3);
	deleteKey(Root, k4);

	printf("\n%d %d %d %d %d \n", X, k1, k2, k3, k4);
	end = clock();

	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Time : %e \n", time_spent);

	getchar();
	return 0;
}

void initEmpty() {
	Dictionary *tmp;
	tmp = (Dictionary *)malloc(sizeof(Dictionary));
	tmp->Left = NULL;
	tmp->Right = NULL;
};

void addNewElement(Dictionary* &Root, int key) {
	Dictionary *tmp = NULL, *newNode = NULL, *parent = NULL;
	newNode = (Dictionary *)malloc(sizeof(Dictionary));
	newNode->Left = NULL;
	newNode->Right = NULL;
	newNode->key = key;
	itoa(key, newNode->tab,10);
	tmp = Root;

	if (Root == NULL) {
		Root = newNode;
	}
	else {
		while (tmp != NULL) {
			if (tmp->key == key)
				break;
			parent = tmp;
			if (tmp->key > key)
				tmp = tmp->Left;
			else
				tmp = tmp->Right;
		}
		if (parent->key > key)
			parent->Left = newNode;
		else
			parent->Right = newNode;
	}
};

void addRandom_X(Dictionary* &Root, int X) {
	int key, R_MIN = -10000, R_MAX = 20000;
	for (int i = 0; i < X; i++) {
		key = R_MIN +(rand() % R_MAX);
		addNewElement(Root, key);
	}
}

void searchKey(Dictionary* &Root, int key) {
	Dictionary *tmp;
	tmp = Root;
	int flag = 0;
	if (tmp == NULL) {
		printf("Can't find key %d, tree is empty!!!\n", key);
	}
	else {
		do {
			if (tmp->key == key) {
				flag = 1;
				break;
			}
			else if (tmp->key > key)
				tmp = tmp->Left;
			else
				tmp = tmp->Right;
		} while (tmp);
		if (flag == 1)
			printf("Found key -> %d\n", key);
		else
			printf("Key %d does not exist!!!\n", key);
	}
	
}

void deleteKey(Dictionary* &Root, int key) {
	Dictionary *tmp = NULL, *parent = NULL;
	Dictionary *child = NULL, *grandChild = NULL, *grandParent = NULL;
	tmp = Root;
	int flag = 0;
	
	if (tmp == NULL) {
		printf("Tree is empty, nothing to delete\n");
	}
	else if (tmp->key == key) {
		parent = tmp->Right;
		while (parent->Left != NULL) {
			tmp = parent;
			parent = parent->Left;
		} if (parent != tmp->Right) {
			tmp->Left = parent->Right;
			parent->Right = Root->Right;
		}
		parent->Left = Root->Left;
		Root = parent;
		flag = 1;
	}
	else {
		while ((tmp != NULL) && (tmp->key != key)) {
			parent = tmp;
			if (tmp->key < key) {
				tmp = tmp->Right;
			}
			else {
				tmp = tmp->Left;
			}
		}
		if ((tmp->Right == NULL) && (tmp->Left == NULL)) {
			if (tmp == Root)
				Root = NULL;
			if (parent->Right == tmp) {
				parent->Right = NULL;
				flag = 1;
			}
			else {
				parent->Left == NULL;
				flag = 1;
			}
		}
		if (tmp->Right == NULL) {
			if (parent->Right == tmp) {
				parent->Right = tmp->Left;
				flag = 1;
			}
			else {
				parent->Left = tmp->Left;
				flag = 1;
			}
		}
		if (tmp->Left == NULL) {
			if (parent->Right == tmp) {
				parent->Right = tmp->Right;
				flag = 1;
			}
			else {
				parent->Left = tmp->Right;
				flag = 1;
			}
		}
		if ((tmp->Right != NULL) && (tmp->Left != NULL)) {
			grandParent = tmp;
			child = tmp->Left;
			while (child->Right != NULL) {
				grandParent = child;
				child = child->Right;
			}
			if (child == tmp->Right) {
				if (parent->Right == tmp) {
					parent->Right = child;
					flag = 1;
				}
				else {
					parent->Left = child;
					flag = 1;
				}
			}
			if (child != tmp->Right) {
				grandChild = child->Right;
				if (grandParent->Right == child) {
					grandParent->Right = grandChild;
					flag = 1;
				}
				else {
					grandParent->Left = grandChild;
					flag = 1;
				}
				if (grandParent->Right != child)
					child->Left = tmp->Right;
				if (parent->Right == tmp) {
					parent->Right = child;
					flag = 1;
				}
				else {
					parent->Left = child;
					flag = 1;
				}
			}
		}
	}
	if (flag == 0)
		printf("Key %d that you want delete doesn't exist\n", key);
	else
		printf("Key %d Deleted\n", key);
}

void preOrder(Dictionary* tmp) {
	if (tmp != NULL) {
		counter++;
		
		printf("|%d| ", tmp->key);
		preOrder(tmp->Left);
		preOrder(tmp->Right);
	}
}

void inOrder(Dictionary* tmp) {
	if (tmp != NULL) {
		counter++;
		inOrder(tmp->Left);
		printf("|%d| ", tmp->key);
		inOrder(tmp->Right);
	}
}

void postOrder(Dictionary* tmp) {
	if (tmp != NULL) {
		counter++;
		postOrder(tmp->Left);
		postOrder(tmp->Right);
		printf("|%d| ", tmp->key);
	}
}