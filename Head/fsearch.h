#ifndef _FSEARCH_H_
#define _FSEARCH_H_

#include"database.h"

void F_search(int* count, int opt[][2], int* sto_list);//��ȡ�ļ�
int fundsearch(int* count, int opt[][2], FUND* s);//���������
void refresh_progress2(int progress, int color);//���½�����

#endif