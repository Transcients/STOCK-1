#ifndef _QSEARCH_H_
#define _QSEARCH_H_

#include"database.h"
#include"control.h"

//���������ӡ��ϣ���Ҷ�Ӧ�Ĺ�Ʊ��
void output_stoname(char* name);

//��ϣ˳����ң�sto_num�ؼ���ȫƥ��
void search_name(int sto_num, char* search_name);

//�ı���ʾ�Ĺ�Ʊ
void change_sto(int* sto_num, int* pos, int No_date, STODAYFLOAT info[], UPLINE* upinfo, DOWNLINE* downinfo, float* max, float* min);

//������������sto_No��ÿһҳ��ֵ
void queueup(int* sto, int* sto_No, int queuesize);

//������������sto_No��ÿһҳ��ֵ
void queuedown(int* sto, int* sto_No, int queuesize);

//������ǣ���������������ת
int queuesearch(int* sto_No, int* pre_k, int* k);

#endif
