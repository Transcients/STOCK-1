#ifndef _TECHSELECT_H_
#define _TECHSELECT_H_
#include"control.h"
#include"database.h"


int technical_control(Ctr* cinfo, USER* u, int* sto_list, int* page);//��ҳѡ�ɵ��ܿغ���
void lightbutton_Tselect(int num);//��ť����
void recoverbutton_Tselect(int num);//�ָ�����
void draw_T_stoselect1(void);
void draw_T_stoselect2(void);
void draw_element(int x, int y, int state, int color);

#endif