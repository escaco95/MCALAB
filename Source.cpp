#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef unsigned int UINT;

struct node {
	struct node* next[2];
	int value;
};

struct tree {
	struct node* head;
};

typedef struct node* Node;
typedef struct tree* Tree;

Node CreateNode(int v) {
	Node nptr = (Node)malloc(sizeof(node));
	nptr->value = v;
	nptr->next[0] = NULL;
	nptr->next[1] = NULL;
	return nptr;
}
void NodeInsertNode(Node dst, Node src) {
	int i = src->value >= dst->value;
	if (dst->next[i])
		NodeInsertNode(dst->next[i], src);
	else
		dst->next[i] = src;
}
void NodePrint(Node src, int depth) {
	int i;
	for (i=0; i<depth; i++)
		printf("   ");
	printf("%d\n", src->value);
	for (i=0; i<2; i++)
		if (src->next[i])
			NodePrint(src->next[i], depth + (1 - i));
}
void DestroyNode(Node nptr) {
	int i = 0;
	for (;i < 2;i++)
		if (nptr->next[i])
			DestroyNode(nptr->next[i]);
}

Tree CreateTree(void) {
	Tree tptr = (Tree)malloc(sizeof(tree));
	tptr->head = NULL;
	return tptr;
}
void TreeInsertNode(Tree tptr, Node nptr) {
	if (tptr->head == NULL) {
		tptr->head = nptr;
		return;
	}
	NodeInsertNode(tptr->head, nptr);
}
void TreePrint(Tree tptr) {
	if (tptr->head)
		NodePrint(tptr->head, 0);
}
void TreeClear(Tree tptr) {
	if (tptr->head)
		DestroyNode(tptr->head);
}
void DestroyTree(Tree tptr) {
	TreeClear(tptr);
	free(tptr);
}

int main(void) {
	int i = 0;
	Tree btr = CreateTree();
	srand((UINT)time(NULL));
	for (; i < 100; i++) {
		Node bnd = CreateNode(rand() % 101);
		TreeInsertNode(btr, bnd);
	}
	TreePrint(btr);
	DestroyTree(btr);
}