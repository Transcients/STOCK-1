#ifndef _PERSON_H_
#define _PERSON_H_
#include"control.h"
#include"database.h"

void personinfo(Ctr* cinfo, USER* u);//�ʲ����ƺ���
void draw_ownmenu(void);//������
void hold_draw(void);
void lightbutton_person(int x1, int y1, int x2, int y2, int color, int button);//��ť����
void recoverbutton_person(int button);//��ť�ָ�


#endif
