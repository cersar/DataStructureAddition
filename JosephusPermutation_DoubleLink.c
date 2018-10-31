// 《算法导论》14-2.a 约瑟夫斯排列，双向链表法(m为常数时，O(n))

#include "pch.h"
#include <iostream>
#include <crtdbg.h>

using namespace std;

typedef struct Node {
	int val;
	Node *next;
	Node *prev;
}*DoubleLinkedList;

void ListInsert(DoubleLinkedList *l,int val) {
	Node *p = (Node *)malloc(sizeof(Node));
	p->val = val;
	if (*l == NULL) {
		p->prev = p;
		p->next = p;
	}
	else {
		p->prev = (*l)->prev;
		(*l)->prev->next = p;
		(*l)->prev = p;
		p->next = *l;
	}
	*l = p;
}

void ListDelete(DoubleLinkedList *l,Node *p) {
	if (p == *l) {
		if (p->next != p) {
			(*l) = p->next;
		}
		else {
			(*l) = NULL;
		}
		
	}
	p->prev->next = p->next;
	p->next->prev = p->prev;
	free(p);
}

void printNode(Node *p) {
	if (p != NULL) {
		printf("val=%d\n", p->val);
	}
}

void printList(DoubleLinkedList l) {
	if (l != NULL) {
		Node *p = l;
		do {
			printNode(p);
			p = p->next;
		} while (p != l);
	}
}

void FreeMemory(DoubleLinkedList *l) {
	if (*l != NULL) {
		Node *p = *l, *tmp = NULL;
		do{
			tmp = p->next;
			free(p);
			p = tmp;
		} while (p != *l);
		*l = NULL;
	}
	
}

void JosephusPermutation(DoubleLinkedList *l, int start, int m) {
	int cnt = 1;
	Node *p = *l, *tmp = NULL;
	for (int i = 1; i < start; ++i) {
		p = p->next;
	}
	while (*l != NULL) {
		if (cnt == m) {
			cnt = 1;
			tmp = p->next;
			printNode(p);
			ListDelete(l, p);
			p = tmp;
		}
		else {
			p = p->next;
			cnt++;
		}
	}
}


int main()
{
	DoubleLinkedList l = NULL;
	int n = 7, m = 3, start = 2;
	for (int i = 7; i >= 1; i--) {
		ListInsert(&l, i);
	}
	Node *p = l,*tmp=NULL;
	
	JosephusPermutation(&l, start, m);
	FreeMemory(&l);
	_CrtCheckMemory();
}
