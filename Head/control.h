#ifndef _CONTROL_H_
#define _CONTROL_H_
#include"database.h"

typedef struct controlinfo
{
	short int ord;         //�Ӳ˵���
	short int ord_last;    //�Ӳ˵�_last
	short int itemnum;     //���˵���
	short int itemnum_last;//��ֹ�ظ�ˢ��
	short int func;        //���ܺ�����  0���8���顢9�����桢10�����桢11����ѡ�ɡ�12���ס�13���ɡ�14���ˡ�15����
	int key;               //����
} Ctr;


void control_main(int* func,USER* u);
void control_mouse(Ctr* cinfo,USER* u);
void control_key(Ctr* cinfo);
int control_func(Ctr* cinfo, USER* u, int* sto_list, int* page);
int control_menu(Ctr* cinfo);
void submenu_draw(short int n);
void mainmenu_draw(void);
void lightbutton_menu(short int ord);
void recoverbutton_menu(short int ord_last);
void draw_stoqueue(void);
void control_judge(USER* u);
void cpop(int i);


#endif