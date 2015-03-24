#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef unsigned int UINT;

struct node {
	struct node* next[2];
	void* value;
};

struct queue {
	struct node* head;
	struct node* tail;
};

struct tree {
	struct node* head;
};

typedef struct node* Node;
typedef struct queue* Queue;
typedef struct tree* Tree;

Node CreateNode(void* v) {
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
void NodeSetChild(Node dst, Node src, int i) {
	dst->next[i] = src;
}
void NodePrint(Node src, int depth) {
	int i;
	for (i = 0; i<depth; i++)
		printf("   ");
	printf("%d\n", src->value);
	for (i=0; i<2; i++)
		if (src->next[i])
			NodePrint(src->next[i], depth + (1 - i));
}
void DestroyNode(Node nptr,int mx) {
	int i = 0;
	for (;i < mx;i++)
		if (nptr->next[i])
			DestroyNode(nptr->next[i], mx);
	free(nptr);
}
void KillNode(Node nptr) {
	free(nptr);
}

Queue CreateQueue(void) {
	Queue qptr = (Queue)malloc(sizeof(queue));
	qptr->head = NULL;
	qptr->tail = NULL;
	return qptr;
}
void Enqueue(Queue qptr, void* i) {
	Node src = CreateNode(i);
	if (qptr->head)
		NodeSetChild(qptr->head, src, 0);
	qptr->head = src;
	if (!qptr->tail)
		qptr->tail = src;
}
void* Dequeue(Queue qptr) {
	void* r;
	Node dst;
	if (!qptr->tail)
		return 0;
	dst = qptr->tail;
	r = dst->value;
	qptr->tail = dst->next[0];
	if (qptr->tail == qptr->head)
		qptr->head = NULL;
	KillNode(dst);
	return r;
}
int QueueEmpty(Queue qptr) {
	return qptr->tail == NULL;
}
void QueueClear(Queue qptr) {
	if (qptr->tail)
		DestroyNode(qptr->tail, 1);
}
void DestroyQueue(Queue qptr) {
	QueueClear(qptr);
	free(qptr);
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
void TreePrintWithQueue(Tree tptr) {
	Queue qptr;
	if (!tptr->head)
		return;
	qptr = CreateQueue();
	Enqueue(qptr, tptr->head);
	Enqueue(qptr, (void*)0);
	while (!QueueEmpty(qptr)) {
		int i;
		Node src = (Node)Dequeue(qptr);
		int depth = (int)Dequeue(qptr);
			for (i = 0; i<depth; i++)
				printf("   ");
			printf("%d\n", src->value);
			for (i = 0; i < 2; i++) {
				if (src->next[i]) {
					Enqueue(qptr, src->next[i]);
					Enqueue(qptr, (void*)(depth + 1));
				}
			}
	}
	DestroyQueue(qptr);
}
void TreeClear(Tree tptr) {
	if (tptr->head)
		DestroyNode(tptr->head, 2);
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
		Node bnd = CreateNode((void*)(rand() % 101));
		TreeInsertNode(btr, bnd);
	}
	TreePrint(btr);
	TreePrintWithQueue(btr);
	DestroyTree(btr);
}