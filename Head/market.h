#ifndef _MARKET_H_
#define _MARKET_H_


#define MAXMARKETSIZE 8
#include"public.h"
#include"control.h"
#include"database.h"


typedef struct
{
	int number;
	char code[7];//��Ʊ����
	char name[10];//��Ʊ����
}Stoname;


typedef struct				   //��Ʊ�б�Kline���нṹ
{
	Stoname base[MAXMARKETSIZE];
	int front;				   //front��Ϊ��Ļ�϶�
	int rear;				   //rear��Ϊ��Ļ�¶�
	int flag;
}MarketQueue;//���ڹ�Ʊ���ҵĶ���

void sto_market(Ctr* cinfo, USER* u, int sto_num, char* sto_name);//Ҫ��ȡ��ĳֻ��Ʊ�ı��,�����ӻ������������
void put_marketqueue(int* pos);
void draw_market(void);
void klinequeue(MarketQueue* Q);
void input_klinequeue(MarketQueue* Q, int k);
int en_klinequeue(MarketQueue* q, FILE* fp1, int line, int prelen);
void destroy_klinequeue(MarketQueue* q);
int count_klinequeue(int k);
int countline_kline(FILE* fp1, int prelen);
void lightbutton_market(int x, int y, int x1, int y1, int color, int flag);
void recoverbutton_market(int num);

#endif