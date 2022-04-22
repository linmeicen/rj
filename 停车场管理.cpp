#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<iostream>
using namespace std;
typedef struct SqStack {
	char a[6];//车牌号
	int top;
	int time[6];
}SqStack;
typedef struct SA {//临时停车场
	char a[6];
	int top;
	int base;
	int time[6];
}A;
typedef struct QNode {//过道
	int data;
	struct QNode* next;
}QNode, * Queueptr;
typedef struct {
	Queueptr front, rear;
}LinkQueue;
void chu(A& D) {
	D.top = 1;
	D.base = 0;
}
void push(A& D, char e) {
	D.top++;
	D.a[D.top] = e;
}
void pop(A& D, char& e) {
	if (D.base == D.top) {
		D.base++;
		e = D.a[D.base];
	}
}
void InitStack(SqStack& S) {//停车场容量“5”
	S.top = 0;
}
int StackEmpty(SqStack S) {
	if (S.top == 0)return 1;
	else
		return 0;
}
int InitQueue(LinkQueue& Q) {//候车区
	Q.front = Q.rear = new QNode;
	if (!Q.front)exit(-2);//储存分配失败
	Q.front->next = NULL;
	return 1;
}
int QueueEmpty(LinkQueue Q) {
	if (Q.front == Q.rear)return 1;
	else
		return 0;
}
int EnQueue(LinkQueue& Q, char e) {//入队
	Queueptr p = new QNode;
	if (!p)exit(-2);
	p->data = e;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
	return 1;
}
int DeQueue(LinkQueue& Q, char& e) {//出队
	if (QueueEmpty(Q))return 0;
	Queueptr p = Q.front->next;
	e = p->data;
	Q.front->next = p->next;
	if (Q.rear == p)Q.rear = Q.front;//只有一个结点
	delete p; p = NULL;
	return 1;
}
int Push0(SqStack& S, char e, int t) {
	S.top++;
	S.a[S.top] = e;
	S.time[S.top] = t;
	return 1;
}
int Push(SqStack& S, char e, LinkQueue& Q) {//入栈
	if (S.top == 5) {
		cout << "-----停车场已满，请在过道等候！！！" << endl;
		EnQueue(Q, e);
		return 1;
	}
	else {
		S.top++;
		S.a[S.top] = e;
		cout << "车辆入场时间是：";
		int t;
		cin >> t;
		S.time[S.top] = t;
		cout << "-----好的，该车已停在" << S.top << "号车位" << endl;
		return 1;
	}
}
int Pop(SqStack& S, char& e, LinkQueue& Q) {//出栈
	if (StackEmpty(S)) {
		cout << "-----停车场内已无车辆！！！" << endl;
		return 0;
	}
	else {//查找需要出场车辆!!!
		int x;
		A D;
		chu(D);
		x = S.top;
		while (S.a[x] != e) {
			x--;
			if (x == 0) {
				cout << " -----停车场内没有该辆车!!!" << endl;
				return 0;
			}
		}
		while (S.a[S.top] != e) {
			D.top++;
			D.a[D.top] = S.a[S.top];
			S.top--;
		}
		char t;
		t = S.a[S.top];
		cout << "现在时刻为：";
		int c;
		cin >> c;
		cout << "-----本次停车车牌号为 " << t << "的车辆停车费为：" << (c - S.time[S.top]) << endl;
		S.top--;
		while (D.top != 1) {
			S.top++;
			S.a[S.top] = D.a[D.top];
			D.top--;
		}
		if (!QueueEmpty(Q)) {
			char q;
			DeQueue(Q, q);
			Push0(S, q, c);
		}
		return 1;
	}
}
void copy(SqStack S) {
	int n = 1;
	cout << "车位号       车牌号    到达时间" << endl;
	while (S.top != 0) {
		cout << "   " << n << "           " << S.a[n] << "           " << S.time[n] << endl;
		S.top--; n++;
	}
}
int main() {
	cout << "                        停车场管理系统";
	SqStack S;
	InitStack(S);
	LinkQueue Q;
	InitQueue(Q);
	while (1) {
		cout << endl << "               *************主菜单*************" << endl;
		cout << "               | A.车辆进场        B.车辆出场 |" << endl << "               | C.显示信息        E.退出程序 |";
		cout << endl;
		cout << "               ********************************" << endl;
		cout << endl << "请输入您想要进行的操作: ";
		char ch;
		cin >> ch;
		if (ch == 'A') {
			cout << "请输入车辆信息：" << endl << "车牌号：";
			char x;
			cin >> x;
			if (Push(S, x, Q) == 0)
				EnQueue(Q, x);
		}
		if (ch == 'B') {
			cout << "请输入想要离场的车辆信息：" << endl << "车牌号：";
			char x;
			cin >> x;
			(Pop(S, x, Q));
		}
		if (ch == 'C') {
			if (StackEmpty(S))
				cout << "****抱歉！停车场内暂无车辆****";
			else
				copy(S);
		}
		if (ch == 'E') {
			cout << "------退出程序，谢谢使用------" << endl << endl << endl;
			break;

		}
	}
	return 0;
}