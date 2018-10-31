#include "pch.h"
#include <iostream>
#include <crtdbg.h>

using namespace std;

#define BLACK 0
#define RED 1

typedef struct TreeNode {
	int key;
	double val;
	int size;
	int color;
	TreeNode *p;
	TreeNode *left;
	TreeNode *right;
}TreeNode, *RBTree;

bool isRed(TreeNode *x) {
	if (x != NULL && x->color == RED) {
		return true;
	}
	return false;
}

int size(TreeNode *x) {
	if (x == NULL) {
		return 0;
	}
	else {
		return x->size;
	}
}

void LeftRotation(RBTree *t, TreeNode *x) {
	TreeNode *y = x->right;
	x->right = y->left;
	if (y->left != NULL) {
		y->left->p = x;
	}
	y->p = x->p;
	if (x->p == NULL) {
		*t = y;
	}
	else if (x == x->p->left) {
		x->p->left = y;
	}
	else if (x == x->p->right) {
		x->p->right = y;
	}
	y->left = x;
	x->p = y;
	y->size = x->size;
	x->size = size(x->left) + size(x->right) + 1;
}

void RightRotation(RBTree *t, TreeNode *x) {
	TreeNode *y = x->left;
	x->left = y->right;
	if (y->right != NULL) {
		y->right->p = x;
	}
	y->p = x->p;
	if (x->p == NULL) {
		*t = y;
	}
	else if (x == x->p->left) {
		x->p->left = y;
	}
	else if (x == x->p->right) {
		x->p->right = y;
	}
	y->right = x;
	x->p = y;
	y->size = x->size;
	x->size = size(x->left) + size(x->right) + 1;
}

void RBInsertFixup(RBTree *t, TreeNode *x) {
	TreeNode *y = NULL;
	while (isRed(x->p)) {
		y = x->p->p;
		if (x->p == y->left) {
			if (isRed(y->right)) {
				y->color = RED;
				x->p->color = BLACK;
				y->right->color = BLACK;
				x = y;
			}
			else {
				if (x == x->p->right) {
					x = x->p;
					LeftRotation(t, x);
				}
				RightRotation(t, y);
				x->p->color = BLACK;
				y->color = RED;
			}
		}
		else {
			if (isRed(y->left)) {
				y->color = RED;
				x->p->color = BLACK;
				y->left->color = BLACK;
				x = y;
			}
			else {
				if (x == x->p->left) {
					x = x->p;
					RightRotation(t, x);
				}
				LeftRotation(t, y);
				x->p->color = BLACK;
				y->color = RED;
			}
		}
	}
	(*t)->color = BLACK;
}

void RBInsert(RBTree *t, int key, double val) {
	TreeNode *p = NULL;
	TreeNode *x = *t;
	while (x != NULL) {
		p = x;
		if (key < x->key) {
			x->size++;
			x = x->left;
		}
		else if (key > x->key) {
			x->size++;
			x = x->right;
		}
		else {
			x->val = val;
			return;
		}
	}
	x = (TreeNode *)malloc(sizeof(TreeNode));
	x->key = key;
	x->val = val;
	x->color = RED;
	x->left = NULL;
	x->right = NULL;
	x->size = 1;
	x->p = p;
	if (p == NULL) {
		*t = x;
	}
	else if (key < p->key) {
		p->left = x;
	}
	else if (key > p->key) {
		p->right = x;
	}
	RBInsertFixup(t, x);

}

void printNode(TreeNode *n) {
	if (n != NULL) {
		printf("[key=%d,value=%f,color=%d]\n", n->key, n->val, n->color);
	}
}

void printInOrder(RBTree t) {
	if (t != NULL) {
		printInOrder(t->left);
		printNode(t);
		printInOrder(t->right);
	}
}

void printPreOrder(RBTree t) {
	if (t != NULL) {
		printNode(t);
		printPreOrder(t->left);
		printPreOrder(t->right);
	}
}

void FreeMemory(RBTree t) {
	if (t != NULL) {
		FreeMemory(t->left);
		FreeMemory(t->right);
		free(t);
	}
}

TreeNode *TreeMininum(RBTree t) {
	TreeNode *p = NULL;
	while (t != NULL) {
		p = t;
		t = t->left;
	}
	return p;
}

void TreeTransplant(RBTree *t, TreeNode *x, TreeNode *y) {
	if (y != NULL) {
		y->p = x->p;
	}
	if (x->p == NULL) {
		*t = y;
	}
	else if (x == x->p->left) {
		x->p->left = y;
	}
	else if (x == x->p->right) {
		x->p->right = y;
	}
}

void RBDeleteFixup(RBTree *t, TreeNode *x, TreeNode *p) {
	TreeNode *y = NULL;
	while (x != *t && !isRed(x)) {
		if (x == p->left) {
			y = p->right;
			if (y->color == RED) {
				p->color = RED;
				y->color = BLACK;
				LeftRotation(t, p);
				y = p->right;
			}
			if (!isRed(y->left) && !isRed(y->right)) {
				y->color = RED;
				x = p;
				p = p->p;
			}
			else {
				if (isRed(y->left)) {
					y->left->color = BLACK;
					y->color = RED;
					RightRotation(t, y);
					y = p->right;
				}
				y->right->color = BLACK;
				y->color = p->color;
				p->color = BLACK;
				LeftRotation(t, p);
				x = *t;
			}
		}
		else {
			y = p->left;
			if (y->color == RED) {
				p->color = RED;
				y->color = BLACK;
				RightRotation(t, p);
				y = p->left;
			}
			if (!isRed(y->left) && !isRed(y->right)) {
				y->color = RED;
				x = p;
				p = p->p;
			}
			else {
				if (isRed(y->right)) {
					y->right->color = BLACK;
					y->color = RED;
					LeftRotation(t, y);
					y = p->left;
				}
				y->left->color = BLACK;
				y->color = p->color;
				p->color = BLACK;
				RightRotation(t, p);
				x = *t;
			}
		}
	}
	x->color = BLACK;
}

void RBDelete(RBTree *t, int key) {
	TreeNode *x = *t;
	while (x != NULL) {
		if (key < x->key) {
			x->size--;
			x = x->left;
		}
		else if (key > x->key) {
			x->size--;
			x = x->right;
		}
		else {
			TreeNode *z = NULL;//记录删除或移动节点的孩子
			TreeNode *p = NULL;//记录删除或移动后z的父亲节点，由于z可能为NULL，所以需单独记录
			int color = 0;//记录删除或者内部移动节点的颜色
			if (x->left == NULL) {
				p = x->p;
				z = x->right;
				color = x->color;
				TreeTransplant(t, x, x->right);
			}
			else if (x->right == NULL) {
				p = x->p;
				z = x->left;
				color = x->color;
				TreeTransplant(t, x, x->left);
			}
			else {
				TreeNode *y = TreeMininum(x->right);
				z = y->right;
				color = y->color;
				if (y->p == x) {
					//y是x的孩子节点
					p = y;
				}
				else {
					p = y->p;
					TreeTransplant(t, y, y->right);
					y->right = x->right;
					x->right->p = y;
				}
				TreeTransplant(t, x, y);
				y->left = x->left;
				x->left->p = y;
				y->color = x->color;
			}
			if (*t != NULL && color == BLACK) {
				RBDeleteFixup(t, z, p);
			}
			free(x);
			break;
		}
	}
}

TreeNode *find(RBTree t, int rank) {
	TreeNode *p = t;
	int r = size(p->left) + 1;
	while (p != NULL) {
		r = size(p->left) + 1;
		if (rank < r) {
			p = p->left;
		}
		else if (rank > r) {
			rank -= r;
			p = p->right;
		}
		else {
			break;
		}
	}
	return p;
}

int getRank(RBTree t, int key) {
	TreeNode *p = t;
	int r = 0;
	while (p != NULL) {
		if (key < p->key) {
			p = p->left;
		}
		else if (key > p->key) {
			r += size(p->left) + 1;
			p = p->right;
		}
		else {
			r += size(p->left) + 1;
			break;
		}
	}
	return r;
}
