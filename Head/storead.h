#ifndef _STODAYREAD_H_
#define _STODAYREAD_H_

#include"database.h"
#include"public.h"

//int check_database(int sto_number)//���ظ����ݿ�����ֵ
void sto_daybyday(int sto_number, long int start_date,long int days, STODAYCHAR* stk);//��ȡ��ָ��������ʼ�Ĺ�Ʊ��Ϣ
void sto_daybyday2float(int sto_num, long int No_date, long int read_days, STODAYFLOAT* info);//��������������Ϣת��Ϊ������
void turn_a2_f_t(STODAYCHAR* str, STODAYFLOAT* f);//�ܿ����������޸ĺ��� 
void turn_a2f(char* str, float* price);//��ÿ��ָ�궼ת��Ϊ������
void turn_a2i(char* str, int* y, int* m, int* d);//date�л���int


#endif