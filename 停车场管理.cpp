#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<iostream>
using namespace std;
typedef struct SqStack {
	char a[6];//���ƺ�
	int top;
	int time[6];
}SqStack;
typedef struct SA {//��ʱͣ����
	char a[6];
	int top;
	int base;
	int time[6];
}A;
typedef struct QNode {//����
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
void InitStack(SqStack& S) {//ͣ����������5��
	S.top = 0;
}
int StackEmpty(SqStack S) {
	if (S.top == 0)return 1;
	else
		return 0;
}
int InitQueue(LinkQueue& Q) {//����
	Q.front = Q.rear = new QNode;
	if (!Q.front)exit(-2);//�������ʧ��
	Q.front->next = NULL;
	return 1;
}
int QueueEmpty(LinkQueue Q) {
	if (Q.front == Q.rear)return 1;
	else
		return 0;
}
int EnQueue(LinkQueue& Q, char e) {//���
	Queueptr p = new QNode;
	if (!p)exit(-2);
	p->data = e;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
	return 1;
}
int DeQueue(LinkQueue& Q, char& e) {//����
	if (QueueEmpty(Q))return 0;
	Queueptr p = Q.front->next;
	e = p->data;
	Q.front->next = p->next;
	if (Q.rear == p)Q.rear = Q.front;//ֻ��һ�����
	delete p; p = NULL;
	return 1;
}
int Push0(SqStack& S, char e, int t) {
	S.top++;
	S.a[S.top] = e;
	S.time[S.top] = t;
	return 1;
}
int Push(SqStack& S, char e, LinkQueue& Q) {//��ջ
	if (S.top == 5) {
		cout << "-----ͣ�������������ڹ����Ⱥ򣡣���" << endl;
		EnQueue(Q, e);
		return 1;
	}
	else {
		S.top++;
		S.a[S.top] = e;
		cout << "�����볡ʱ���ǣ�";
		int t;
		cin >> t;
		S.time[S.top] = t;
		cout << "-----�õģ��ó���ͣ��" << S.top << "�ų�λ" << endl;
		return 1;
	}
}
int Pop(SqStack& S, char& e, LinkQueue& Q) {//��ջ
	if (StackEmpty(S)) {
		cout << "-----ͣ���������޳���������" << endl;
		return 0;
	}
	else {//������Ҫ��������!!!
		int x;
		A D;
		chu(D);
		x = S.top;
		while (S.a[x] != e) {
			x--;
			if (x == 0) {
				cout << " -----ͣ������û�и�����!!!" << endl;
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
		cout << "����ʱ��Ϊ��";
		int c;
		cin >> c;
		cout << "-----����ͣ�����ƺ�Ϊ " << t << "�ĳ���ͣ����Ϊ��" << (c - S.time[S.top]) << endl;
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
	cout << "��λ��       ���ƺ�    ����ʱ��" << endl;
	while (S.top != 0) {
		cout << "   " << n << "           " << S.a[n] << "           " << S.time[n] << endl;
		S.top--; n++;
	}
}
int main() {
	cout << "                        ͣ��������ϵͳ";
	SqStack S;
	InitStack(S);
	LinkQueue Q;
	InitQueue(Q);
	while (1) {
		cout << endl << "               *************���˵�*************" << endl;
		cout << "               | A.��������        B.�������� |" << endl << "               | C.��ʾ��Ϣ        E.�˳����� |";
		cout << endl;
		cout << "               ********************************" << endl;
		cout << endl << "����������Ҫ���еĲ���: ";
		char ch;
		cin >> ch;
		if (ch == 'A') {
			cout << "�����복����Ϣ��" << endl << "���ƺţ�";
			char x;
			cin >> x;
			if (Push(S, x, Q) == 0)
				EnQueue(Q, x);
		}
		if (ch == 'B') {
			cout << "��������Ҫ�볡�ĳ�����Ϣ��" << endl << "���ƺţ�";
			char x;
			cin >> x;
			(Pop(S, x, Q));
		}
		if (ch == 'C') {
			if (StackEmpty(S))
				cout << "****��Ǹ��ͣ���������޳���****";
			else
				copy(S);
		}
		if (ch == 'E') {
			cout << "------�˳�����ллʹ��------" << endl << endl << endl;
			break;

		}
	}
	return 0;
}