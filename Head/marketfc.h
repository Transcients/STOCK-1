#ifndef _MARKETFUNC_H_
#define _MARKETFUNC_H_

#include"database.h"

//�ı���ʾ��Ϣ������
void change_datadate(int sto_num, long int* No_date, STODAYFLOAT info[], UPLINE* upinfo, DOWNLINE* downinfo, float* max, float* min, int read_way, int LR);

//�����׼��,daysΪ20.0
float std_deviation(STODAYFLOAT* info, int days, int date);


//Ѱ�һ���ͼ�ı߽纯��
void get_border(STODAYFLOAT* info, float* max, float* min, int read_days);


//��ָ��λ�û�������
void draw_float(float flt, int x, int y, int bits, int color);

//Ѱ�һ���ͼ�ı߽纯��
void get_viceborder(DOWNLINE* vice, float* max, float* min);



//����ƶ�����ʾ����
void mouse_datashow(STODAYFLOAT* info, UPLINE upinfo, DOWNLINE downinfo, int* p_preday, int* p_day, int state, int colorstate);

#endif

