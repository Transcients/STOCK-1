#include"public.h"
#include"person.h"
#include"traverse.h"
#include"trade.h"
#include"transfer.h"


/**************************************************
person.c
COPYRIGHT: dengshumin
FUNCTION:  person information
ABSTRACT:
		A.person information, hold and asset
		B.button lightning and recovering
DATE: 2019/11/3
***************************************************/


/*********************************************
FUNCTION: personinfo
DESCRIPTION: ������Ϣ�������ֲ����ʲ�
INPUT: cinfo,u
RETURN: ��
*********************************************/
void personinfo(Ctr* cinfo,USER* u)
{
	int num = 0;
	int page = 1;
	int sum_page = 0;
	float stk_balance = 0;              //���ڻ�ȡ���
	clrmous(MouseX, MouseY);
	memset(cinfo,0,sizeof(Ctr));
	cinfo->func = 6;                    //��6��Ǹ��˽���
	delay(10);
	cleardevice();
	mainmenu_draw();
	control_judge(u);
	draw_ownmenu();
	get_balance1(u, &stk_balance);
	get_asset(u);
	sum_page = get_hold(u, 1);          //�����ҳ��
	while (1)
	{
		if(strlen(u->user) == 0 || strlen(u->bankcard) == 0)
			cinfo->func = 0;
		if(!bioskey(1))
		{
			newmouse(&MouseX, &MouseY, &press);
			control_mouse(cinfo,u);
		}
		else if(bioskey(1))
		{
			cinfo->key = bioskey(0);
		}
		if(sum_page != 0)
		{
			if(cinfo->key == DOWN)
			{
				hold_draw();
				page = (page + 1) % sum_page;
				if(page == 0)           //��0ҳ������
					page = sum_page;
				get_hold(u,page);
				cinfo->key = 0;
				continue;
			}
			if(cinfo->key == UP)
			{
				hold_draw();
				page = (page - 1) % sum_page;
				if (page == 0)
					page = sum_page;
				get_hold(u,page);
				cinfo->key = 0;
				continue;
			}
		}
		control_key(cinfo);
		if(control_menu(cinfo))
		{
			cleardevice();
			mainmenu_draw();
			control_judge(u);
			draw_ownmenu();
			get_hold(u, page);
			submenu_draw(cinfo->itemnum);
			get_asset(u);
			continue;
		}
		if(cinfo->func != 6 && cinfo->func != 14)
		{
			clrmous(MouseX,MouseY);
			delay(10);
			return;
		}
		if (MouseX > 324 && MouseX < 620 && MouseY > 30 && MouseY < 150)//ת��
		{
			if (mouse_press(324, 30, 620, 150) == 2 && cinfo-> itemnum == 0)//δ���
			{
				MouseS = 1;
				if (num == 0)//��ֹ���ظ�����
				{
					lightbutton_person(320, 30, 620, 150, LIGHTGREEN, 1);
					num = 1;
				}
				continue;
				//��������
			}
			
			if (mouse_press(324, 30, 620, 150) == 1 )//&& cinfo->itemnum == 0)
			{
				MouseS = 0;
				lightbutton_person(320, 30, 620, 150, LIGHTGREEN, 1);
				transfer_money(u);					//��ת��ת��
				clrmous(MouseX, MouseY);   			//��ת�˻���
				cleardevice();
				delay(50);
				mainmenu_draw();
				control_judge(u);
				draw_ownmenu();
				get_balance1(u, &stk_balance);   
				get_asset(u);
				get_hold(u, page);					//������ʾ��Ϣ
				continue;
			}
		}

		if (MouseX > 20 && MouseX < 316 && MouseY > 30 && MouseY < 150)
		{//��ʷ�ɽ�
			if (mouse_press(20, 30, 316, 150) == 2 && cinfo-> itemnum == 0)//δ���
			{
				MouseS = 1;
				if (num == 0)						//��ֹ���ظ�����
				{
					lightbutton_person(20, 30, 320, 150, LIGHTGREEN, 2);
					num = 2;
				}
				continue;

				//��������
			}
			else if (mouse_press(20, 30, 316, 150) == 1 && cinfo->itemnum == 0)
			{
				MouseS = 0;
				lightbutton_person(20, 30, 320, 150, LIGHTGREEN, 2);
				trade(cinfo, u, 2, 0);		//��ת����ʷ�ɽ�
				cinfo->itemnum = 0;
				cinfo->itemnum_last = 0;
				if(cinfo->func != 4 && cinfo->func != 8)
				{
					clrmous(MouseX,MouseY);
					delay(10);
					return;
				}
				else
				{
					cleardevice();
					mainmenu_draw();
					control_judge(u);
					draw_ownmenu();
					get_hold(u, page);
					get_asset(u);
					continue;
				}
			}
		}

		if (num != 0)
		{
			MouseS = 0;
			recoverbutton_person(num);
			num = 0;
		}
		if (MouseS != 0)
		{
			MouseS = 0;
		}
	}
}

/****************************************
FUNCTION: lightbutton_person
DESCRIPTION: ���˽������
INPUT: x1,y1,x2,y2,color,button
RETURN: ��
*****************************************/
void lightbutton_person(int x1, int y1, int x2, int y2,int color,int button)
{
	clrmous(MouseX, MouseY);
	delay(10);
	setfillstyle(SOLID_FILL, color);
	bar(x1, y1, x2, y2);
	switch (button)
	{
	case 1:
		setcolor(WHITE);
		setlinestyle(SOLID_LINE, 0, 3);
		rectangle(440, 25 + 30, 490, 25 + 60);
		line(440, 25 + 40, 490, 25 + 40);
		setlinestyle(SOLID_LINE, 0, 2);
		circle(465, 74, 5);
		puthz(450, 95, "ת��", 16, 20, WHITE);
		break;
	case 2:
		
		setcolor(WHITE);
		setlinestyle(SOLID_LINE, 0, 3);
		line(130, 55, 147, 55);
		line(163, 55, 180, 55);
		line(130, 85, 147, 85);
		line(163, 85, 180, 85);
		line(130, 55, 130, 65);
		line(130, 75, 130, 85);
		line(180, 55, 180, 65);
		line(180, 75, 180, 85);
		settextstyle(2, HORIZ_DIR, 9);
		outtextxy(137, 52, "+");
		outtextxy(163, 52, "-");
		puthz(120, 95, "��ʷ�ɽ�", 16, 20, WHITE);
		break;
	}
}

/******************************************
FUNCTION: recoverbutton_person
DESCRIPTION: �ָ�����
INPUT: button
RETURN: ��
*******************************************/
void recoverbutton_person(int button)
{
	clrmous(MouseX, MouseY);
	delay(10);
	switch (button)
	{
	case 1:
		setfillstyle(SOLID_FILL, GREEN);
		bar(320, 30, 620, 150);
		setcolor(WHITE);
		setlinestyle(SOLID_LINE, 0, 3);
		rectangle(440, 25 + 30, 490, 25 + 60);
		line(440, 25 + 40, 490, 25 + 40);
		setlinestyle(SOLID_LINE, 0, 2);
		circle(465, 74, 5);
		puthz(450, 95, "ת��", 16, 20, WHITE);
		break;
	case 2:
		setfillstyle(SOLID_FILL, GREEN);
		bar(20, 30, 320, 150);
		setcolor(WHITE);
		setlinestyle(SOLID_LINE, 0, 3);
		line(130, 55, 147, 55);
		line(163, 55, 180, 55);
		line(130, 85, 147, 85);
		line(163, 85, 180, 85);
		line(130, 55, 130, 65);
		line(130, 75, 130, 85);
		line(180, 55, 180, 65);
		line(180, 75, 180, 85);
		settextstyle(2, HORIZ_DIR, 9);
		outtextxy(137, 52, "+");
		outtextxy(163, 52, "-");
		puthz(120, 95, "��ʷ�ɽ�", 16, 20, WHITE);
		break;
	}
}


/*****************************************
FUNCTION: draw_ownmenu
DESCRIPTION: �����˲˵�
INPUT: void
RETURN: ��
******************************************/
void draw_ownmenu(void)
{
	int i;

	setbkcolor(WHITE);
	setfillstyle(SOLID_FILL, GREEN);
	bar(20, 30, 620, 150);
	settextjustify(LEFT_TEXT, TOP_TEXT);
	settextstyle(2, HORIZ_DIR, 6);
	setlinestyle(SOLID_LINE, 0, 1);

	setcolor(LIGHTGRAY);
	line(100, 190, 550, 190);
	puthz(100, 170, "�˺�", 16, 17, DARKGRAY);
	setcolor(DARKGRAY);
	rectangle(50, 165, 75, 190);
	setcolor(GREEN);
	setfillstyle(1, GREEN);
	circle(63, 176 - 2, 6);
	sector(63, 176, 230, 310, 12, 12);
	fillellipse(63, 176  - 2, 6, 6);//����¼С��
	outtextxy(140, 170, ":");

	
	setcolor(LIGHTGRAY);
	line(100, 230, 550, 230);
	puthz(100, 210, "����", 16, 17, DARKGRAY);
	setcolor(DARKGRAY);
	rectangle(50, 205, 75, 230);
	rectangle(53, 210, 72, 225);
	setfillstyle(1, DARKGRAY);
	bar(53, 213, 72, 219);//�����п�
	outtextxy(140, 210, ":");

	
	setcolor(LIGHTGRAY);
	line(100, 270, 550, 270);
	puthz(100, 250, "���", 16, 17, DARKGRAY);
	setcolor(DARKGRAY);
	rectangle(50, 245, 75, 270);
	setcolor(RED);
	puthz(55, 250, "��", 16, 17, RED);//��Ǯ
	outtextxy(140, 250, ":");


	setcolor(WHITE);
	setlinestyle(SOLID_LINE, 0, 3);
	rectangle(440, 25 + 30, 490, 25 + 60);
	line(440, 25 + 40, 490, 25 + 40);
	setlinestyle(SOLID_LINE, 0, 2);
	circle(465, 74, 5);
	puthz(450, 95, "ת��", 16, 20, WHITE);


	setcolor(WHITE);
	setlinestyle(SOLID_LINE, 0, 3);
	line(130, 55, 147, 55);
	line(163, 55, 180, 55);
	line(130, 85, 147, 85);
	line(163, 85, 180, 85);
	line(130, 55, 130, 65);
	line(130, 75, 130, 85);
	line(180, 55, 180, 65);
	line(180, 75, 180, 85);
	settextstyle(2, HORIZ_DIR, 9);
	outtextxy(137, 52, "+");
	outtextxy(163, 52, "-");
	puthz(120, 95, "��ʷ�ɽ�", 16, 20, WHITE);
	
	hold_draw();
/*	setcolor(LIGHTGRAY);
	setlinestyle(SOLID_LINE, 0, 1);
	for (i = 0; i < 7; i++)
	{
		line(50 + 90 * i, 297, 50 + 90 * i, 477);
	}
	for (i = 0; i < 10; i++)
	{
		line(50, 297 + 20 * i, 590, 297 + 20 * i);
	}
	puthz(75, 299, "����", 16, 20, RED);
	puthz(165, 299, "����", 16, 20, GREEN);
	puthz(255, 299, "����", 16, 20, BLUE);
	//puthz(245, 299, "�ɽ���", 16, 20, BLUE);
	puthz(335, 299, "�ֹ���", 16, 20, LIGHTMAGENTA);
	//puthz(335, 299, "�ɽ���", 16, 20, LIGHTMAGENTA);
	puthz(425, 299, "�ɱ���", 16, 20, LIGHTBLUE);
	//puthz(435, 299, "״̬", 16, 20, LIGHTBLUE);
	puthz(510, 299, "�ֲ�����", 16, 20, DARKGRAY);*/

	setcolor(DARKGRAY);
	rectangle(612, 297, 622, 477);
	line(612, 307, 622, 307);
	line(612, 467, 622, 467);

	line(613, 305, 621, 305);
	line(613, 305, 617, 300);
	line(617, 300, 621, 305);
	line(613, 469, 621, 469);
	line(613, 469, 617, 474);
	line(617, 474, 621, 469);
	
	setfillstyle(SOLID_FILL, DARKGRAY);
	floodfill(617, 302, DARKGRAY);
	floodfill(617, 471, DARKGRAY);
}

/****************************************
FUNCTION: hold_draw
DESCRIPTION: ���Ƴֲ���Ϣ
INPUT: void
RETURN: ��
****************************************/
void hold_draw()
{
	int i;
	setfillstyle(1,WHITE);
	bar(50, 297, 590, 487);
	setcolor(LIGHTGRAY);
	setlinestyle(SOLID_LINE, 0, 1);
	for (i = 0; i < 7; i++)
	{
		line(50 + 90 * i, 297, 50 + 90 * i, 477);
	}
	for (i = 0; i < 10; i++)
	{
		line(50, 297 + 20 * i, 590, 297 + 20 * i);
	}
	puthz(75, 299, "����", 16, 20, RED);
	puthz(165, 299, "����", 16, 20, GREEN);
	puthz(255, 299, "����", 16, 20, BLUE);
	//puthz(245, 299, "�ɽ���", 16, 20, BLUE);
	puthz(335, 299, "�ֹ���", 16, 20, LIGHTMAGENTA);
	//puthz(335, 299, "�ɽ���", 16, 20, LIGHTMAGENTA);
	puthz(425, 299, "�ɱ���", 16, 20, LIGHTBLUE);
	//puthz(435, 299, "״̬", 16, 20, LIGHTBLUE);
	puthz(510, 299, "�ֲ�����", 16, 20, DARKGRAY);
}