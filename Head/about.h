#ifndef _ABOUT_H_
#define _ABOUT_H_

#include"control.h"
#include"database.h"


void About(Ctr* cinfo, USER* u);//�����Ϣ�ܿغ���
void About_show(void);//��ʾ������Ϣ
void Help_show(void);//��ʾ������Ϣ
void lightbutton_about(int x, int y, int x1, int y1, int color1, int color2);//About��ť����
void recoverbutton_about(int status);//About��ť�ָ�

#endif
