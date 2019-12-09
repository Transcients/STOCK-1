#ifndef _QUEUE_H_
#define _QUEUE_H_

#define MAXQSIZE 20
#include"control.h"
#include"database.h"

typedef struct				   //��Ʊ�б�ӽṹ
{
	Stodata* base;
	int front;				   //front��Ϊ��Ļ�϶�
	int rear;				   //rear��Ϊ��Ļ�¶�
	int flag;
}StoQueue;//��Ʊ��Ϣ�Ķ���  

void draw_stoqueue(void);//����Ʊ����

void stock_queue(Ctr* cinfo,USER* u);//���ù�Ʊ����

void initqueue(StoQueue* Q);//�����Ź�Ʊ��Ϣ�Ķ���

int enqueue(StoQueue* q, FILE* fp1, int line, int prelen);//��ͷ���β���Ԫ�أ����·�ҳ��ͷָ�븳ֵ�����Ϸ�ҳ��βָ�븳ֵ

void destroyqueue(StoQueue* q);//���ٶ���

void inputqueue(StoQueue* Q,int k);//���и�ֵ��kΪ�ļ���ʼλ��

int countqueue(int k);//��ÿһҳ�ж೤

int countline(FILE* fp1, int prelen);//��ÿ���ж೤

#endif
