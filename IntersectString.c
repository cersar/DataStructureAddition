#include "pch.h"
#include <iostream>
#include <crtdbg.h>

using namespace std;
#define LEFT 0
#define RIGHT 1

struct LineNode {
	double angle;
	int ind;
	double position;
};

int main()
{
	double data[][2] = { {0.3,0.4},{0.1,0.5},{0.2,0.7},{0.6,0.9} };
	int lineNum = sizeof(data) / sizeof(data[0]);
	double **x = (double **)malloc(sizeof(double *) * lineNum);
	for (int i = 0; i < lineNum; ++i) {
		x[i] = (double *)malloc(sizeof(double) * 2);
		for (int j = 0; j < 2; ++j) {
			x[i][j]=data[i][j];
		}
	}

	quickSort(x, 0, lineNum -1);
	for (int i = 0; i < lineNum; ++i) {
		for (int j = 0; j < 2; ++j) {
			cout << x[i][j] << "\t" ;
		}
		cout << endl;
	}
	LineNode *nodes = (LineNode *)malloc(sizeof(LineNode)*lineNum * 2);
	for (int i = 0; i < lineNum; ++i) {
		nodes[2 * i].angle = x[i][0];
		nodes[2 * i + 1].angle = x[i][1];
		nodes[2 * i].position = LEFT;
		nodes[2 * i + 1].position = RIGHT;
		nodes[2 * i].ind = i;
		nodes[2 * i + 1].ind = i;
	}
	quickSort(nodes, 0, lineNum * 2 - 1);
	for (int i = 0; i < lineNum * 2; ++i) {
		cout << nodes[i].angle << "\t" << nodes[i].ind << "\t" << nodes[i].position<<endl;
	}
	RBTree t=NULL;
	int cnt = 0;
	for (int i = 0; i < lineNum * 2; ++i) {
		if (nodes[i].position == RIGHT) {
			cnt += (t->size-getRank(t, nodes[i].ind));
			RBDelete(&t, nodes[i].ind);
			printInOrder(t);
		}
		else {
			RBInsert(&t, nodes[i].ind, nodes[i].angle);
		}
	}
	printInOrder(t);
	cout << "相交弦数：" << cnt << endl;
	FreeMemory(t);
	free(x);
	free(nodes);
	_CrtCheckMemory();
}
