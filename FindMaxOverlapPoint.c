//《算法导论》14-1
//未使用红黑树，也可以使用红黑树


#include <iostream>
#include <time.h>
#include <crtdbg.h>

using namespace std;
//核心想法 arg(a[x])max(sum(a[i].pos))
#define LEFT 1
#define RIGHT -1

struct Node {
	int val;
	int pos;
	int comVal;
};

int partation(Node *a, int start, int end) {
	int p = start - 1;
	int q = end + 1;
	int r = rand() % (end - start + 1);
	swap(a[start], a[r + start]);
	Node key = a[start];
	while (true) {
		do {
			p++;
		} while (compare(a[p], key) < 0);
		do {
			q--;
		} while (compare(a[q], key) > 0);
		if (p < q) {
			swap(a[p], a[q]);
		}
		else {
			return q;
		}
	}
}

void quickSort(Node *a, int start, int end) {
	int cnt = 0;
	if (start < end) {
		int p = partation(a, start, end);
		quickSort(a, start, p);
		quickSort(a, p + 1, end);
	}
}

void printNode(Node *a) {
	if (a != NULL) {
		printf("val=%d,comVal=%d,pos=%d\n", a->val, a->comVal, a->pos);
	}
}

Node *findMaxOverlapPoint(Node *a,int start,int end) {
	int max = 0;
	int sum = 0;
	Node *m = NULL;
	for (int i = start; i <= end; ++i) {
		sum += a[i].pos;
		if (sum > max) {
			max = sum;
			m = &a[i];
		}
	}
	return m;
}

int main()
{
	srand((unsigned)time(NULL));
	int data[][2] = { {0,3},{6,8},{6,10},{15,23},{16,21}, {25,30},{17,19},{26,26},{20,20} };
	int n = sizeof(data) / sizeof(data[0]);
	Node *nodes = (Node *)malloc(sizeof(Node)*n * 2);
	for (int i = 0; i < n; i++) {
		nodes[i * 2].val = data[i][0];
		nodes[i * 2].comVal = data[i][1];
		nodes[i * 2].pos = LEFT;
		nodes[i * 2 + 1].val = data[i][1];
		nodes[i * 2 + 1].comVal = data[i][0];
		nodes[i * 2 + 1].pos = RIGHT;
	}
	quickSort(nodes, 0, n * 2 - 1);
	Node *p = findMaxOverlapPoint(nodes, 0, 2 * n - 1);
	if (p != NULL) {
		cout << "最大重叠点：\t";
		printNode(p);
	}
	else {
		cout << "没有重叠点！" << endl;
	}
	free(nodes);
	_CrtCheckMemory();
}
