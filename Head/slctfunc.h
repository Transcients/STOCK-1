#ifndef _SLCTFUNC_H_
#define _SLCTFUNC_H_
#include"control.h"
#include"database.h"


void T_stoselect1(Ctr* cinfo, USER* u, int* page, int opt[][6], int* sto_list);//��ҳ��ʾK����̬ѡ�ɣ�MA������̬ѡ��
void T_select1_check(int opt[][6]);//Ѱ��kline��ǣ����ǲ�����Ӧ��opt���鸳ֵ
void MA_select1_check(int* precolor, int* color, int opt[][6]);//Ѱ��ma��ǣ����ǲ�����Ӧ��opt���鸳ֵ
void find_Klinebutton(int* tech, int* index, int* x, int* y);//�ҵ��Ƕ��ٸ�K����̬�е�ĳһָ��
void find_lastbutton(int tech, int last, int* pre_x, int* pre_y);//�ҵ���һ����ǵ�����
void find_MAbutton(int* tech, int* index, int* x, int* y);//�ҵ�MA�е�ĳһ��ָ̬��

void T_stoselect2(Ctr* cinfo, USER* u, int* page, int opt[][6], int* sto_list);//��ҳ��ʾMA, KDJ, MACD, RSI, VOL/OBV, BIAS, BOLL
void T_select2_check(int opt[][6]);//Ѱ�ұ�ǣ����ǲ�����Ӧ��opt���鸳ֵ
void find_button2(int tech, int last, int* pre_x, int* pre_y);//�ҵ���һ����ǵ�����������ǵ�����
void find_Kstobutton2(int* tech, int* index, int* x, int* y);//�ҵ����Ǹ����͵�ĳһָ��

int T_searchresult(Ctr* cinfo, USER* u, int* p_page, int* sto_list,int return_page);//��ʾ�������
void draw_T_result(void);//�������������
void show_searchsto(STODAYCHAR* info, int coordY, char* sto);//��ӡ�����Ĺ�Ʊ��Ϣ
void show_failpop(void);//û�ҵ���Ʊ�ķ��ص���

#endif