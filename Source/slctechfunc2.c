#include"public.h"
#include"database.h"
#include"techslc.h"
#include"slctfunc.h"
#include"tsearch.h"
#include"control.h"

/*****************************************
slctechfunc2.c
COPYRIGHT:	weijingmin
FUNCTION:	T_select page 2
ABSTRACT:
		A.find button for light
		B.check option array
DATE:2019/10/29
******************************************/


/*********************************************
FUNCTION:T_stoselect2
DESCRIPTION����ҳ��ʾ
	MA, KDJ, MACD, RSI, VOL/OBV, BIAS, BOLL
INPUT:cinfo,u,page,opt[][6],sto_list
RETURN:��
***********************************************/
void T_stoselect2(Ctr* cinfo, USER* u, int* page, int opt[][6], int* sto_list)
{
	int i, j;
	int num;//��ť���
	clrmous(MouseX, MouseY);
	delay(100);
	cleardevice();
	draw_T_stoselect2();
	mainmenu_draw();
	control_judge(u);
	while (1)
	{
		if(!bioskey(1))
		{
			newmouse(&MouseX, &MouseY, &press);
			control_mouse(cinfo,u);
		}
		else if(bioskey(1))
			cinfo->key = bioskey(0);
		control_key(cinfo);
		if(control_menu(cinfo))
		{
			clrmous(MouseX,MouseY);
			mainmenu_draw();
			control_judge(u);
		//	setfillstyle(1,BLACK);
		//	bar(0,25,639,480);
			draw_T_stoselect1();
			submenu_draw(cinfo->itemnum);
			memset(opt,0,66*sizeof(int));
		}
		if(cinfo->func != 5 && cinfo->func != 10)
		{
			clrmous(MouseX,MouseY);
			delay(10);
			return;
		}
		
		if (MouseX > 0 && MouseX < 580 && MouseY> 58 && MouseY < 430)
		{
			if (mouse_press(24 + 90, 68, 24 + 100, 68 + 10) == 2
				|| mouse_press(24 + 90, 68 + 32, 24 + 100, 68 + 32 + 10) == 2
				|| mouse_press(144 + 90, 68, 144 + 100, 68 + 10) == 2
				|| mouse_press(144 + 90, 68 + 32, 144 + 100, 68 + 32 + 10) == 2)//KDJ
			{
				MouseS = 1;
				continue;
			}
			else if (mouse_press(344 + 90, 68, 344 + 100, 68 + 10) == 2
				|| mouse_press(344 + 90, 68 + 32, 344 + 100, 68 + 32 + 10) == 2
				|| mouse_press(464 + 90, 68, 464 + 100, 68 + 10) == 2
				|| mouse_press(464 + 90, 68 + 32, 464 + 100, 68 + 32 + 10) == 2)//MACD
			{
				MouseS = 1;
				continue;
			}
			else if (mouse_press(24 + 90, 208, 24 + 100, 208 + 10) == 2
				|| mouse_press(24 + 90, 208 + 32, 24 + 100, 208 + 32 + 10) == 2)//RSI
			{
				MouseS = 1;
				continue;
			}
			else if (mouse_press(344 + 90, 208, 344 + 100, 208 + 10) == 2
				|| mouse_press(344 + 90, 208 + 32, 344 + 100, 208 + 32 + 10) == 2)//VOL/OBV
			{
				MouseS = 1;
				continue;
			}
			else if (mouse_press(24 + 90, 348, 24 + 100, 348 + 10) == 2
				|| mouse_press(24 + 90, 348 + 32, 24 + 100, 348 + 32 + 10) == 2)//BIAS
			{
				MouseS = 1;
				continue;
			}
			else if (mouse_press(344 + 90, 348, 344 + 100, 348 + 10) == 2
				|| mouse_press(344 + 90, 348 + 32, 344 + 100, 348 + 32 + 10) == 2
				|| mouse_press(344 + 90, 348 + 64, 344 + 100, 348 + 64 + 10) == 2)//BOLL
			{
				MouseS = 1;
				continue;
			}
			else
			{
				MouseS = 0;
			}

			if (mouse_press(0, 58, 580, 430) == 1)
			{
				T_select2_check(opt);//���ڶ�ҳ�ĸ�Ԫ�ر���ǣ��ı�opt���鲢���б�Ƿ���
				continue;
			}
		}
		if (MouseX > 20 && MouseX < 80 && MouseY > 452 && MouseY < 479)
		{
			if (mouse_press(20, 452, 80, 479) == 2)//δ���
			{
				MouseS = 1;
				if (num == 0)//��ֹ���ظ�����
				{
					lightbutton_Tselect(2);
					num = 2;
				}
				continue;
				//��������
			}
			else if (mouse_press(20, 452, 80, 479) == 1)
			{
				MouseS = 0;
				lightbutton_Tselect(2);
				*page = 1;
				return;
			}
		}

		if (MouseX > 250 && MouseX < 290 && MouseY > 452 && MouseY < 479)
		{
			if (mouse_press(250, 452, 290, 479) == 2)//δ���
			{
				MouseS = 1;
				if (num == 0)//��ֹ���ظ�����
				{
					lightbutton_Tselect(4);
					num = 4;
				}
				continue;
				//��������
			}
			else if (mouse_press(250, 452, 290, 479) == 1)
			{
				MouseS = 0;
				lightbutton_Tselect(4);
				T_search(opt, sto_list, BLUE);
				*page = 3;//��ת�������ʾ����
				return;
			}
		}

		if (num != 0)
		{
			MouseS = 0;
			recoverbutton_Tselect(num);
			num = 0;
		}
		if (MouseS != 0)
		{
			MouseS = 0;
		}
	}
}

/*********************************************
FUNCTION:T_select2_check
DESCRIPTION��Ѱ�ұ�ǣ�
	���ǲ�����Ӧ��opt���鸳ֵ
INPUT:opt[][6]
RETURN:��
***********************************************/
void T_select2_check(int opt[][6])
{
	int x, y;//Ҫ�����İ�ť������
	int i;
	int color;
	int pre_x, pre_y;//��һ����������ť������
	int tech = 0, index = 0;//techΪ���ͺţ�indexΪ����ѡ��

	//�ڶ��漼����ĵ����ͱ��
	find_Kstobutton2(&tech, &index, &x, &y);//Ѱ���û�����Ŀ�
	if ((tech == 0) || ((tech != 0) && (index == 0)))//û�е�����ÿ�
	{
		return;
	}

	switch (tech)
	{
	case 6:
		color = RED;
		break;
	case 7:
		color = BLUE;
		break;
	case 8:
		color = BROWN;
		break;
	case 9:
		color = GREEN;
		break;
	case 10:
		color = LIGHTMAGENTA;
		break;
	case 11:
		color = LIGHTCYAN;
		break;
	}
	for (i = 0; i < 4; i++)
	{
		if (opt[tech - 1][i] == 1)//��һ���ʹ����ѱ�ѡ����
		{
			if (i == index - 1)//�����û�Ŀǰ����İ�ť���ϴ�ѡ����һ�������һ��
			{
				find_button2(tech, i + 1, &pre_x, &pre_y);
				clrmous(MouseX, MouseY);
				setcolor(WHITE);
				draw_element(pre_x, pre_y, 1, color);
				opt[tech - 1][i] = 0;
				return;
			}
			else//�����û�����һ���������İ�ť���ϴεĲ�һ��
			{
				find_button2(tech, i + 1, &pre_x, &pre_y);//Ѱ����һ�ε���İ�ť�����Ͻ�����
				clrmous(MouseX, MouseY);
				setcolor(WHITE);
				draw_element(pre_x, pre_y, 1, color);//�ָ�֮ǰ�İ�ť
				opt[tech - 1][i] = 0;
			}
		}
	}
	opt[tech - 1][index - 1] = 1;
	find_button2(tech, index, &x, &y);
	clrmous(MouseX, MouseY);
	setcolor(WHITE);
	draw_element(x, y, 1, LIGHTGRAY);//������ǵİ�ť

	return;
}


/*********************************************
FUNCTION:find_button2
DESCRIPTION���ҵ���һ����ǵ�����
INPUT:tech,last,pre_x,pre_y
RETURN:��
***********************************************/
void find_button2(int tech, int last, int* pre_x, int* pre_y)
{//lastΪ1,2,3,4,�ֱ��Ӧindex1,2,3,4
	if (tech == 6 || tech == 8 || tech == 10)//KDJ,RSI,BIAS
	{
		if (last <= 2)//index1,2
		{
			*pre_x = 24 + 90;
		}
		else if (last >= 3 && tech == 6)//index3,4
		{
			*pre_x = 144 + 90;
		}
	}
	else if (tech == 7 || tech == 9 || tech == 11)//MACD,OBV,BOLL
	{
		if (last <= 2)//index1,2
		{
			*pre_x = 344 + 90;
		}
		else if (last >= 3 && tech == 7)//index3,4
		{
			*pre_x = 464 + 90;
		}
		
		if (last >= 3 && tech == 11)//BOLL index1
		{
			*pre_x = 344 + 90;
		}
	}


	if (tech == 6 || tech == 7)
	{//lastΪ1,2,3,4,�ֱ��Ӧindex1,2,3,4
		if (last % 2 == 1)//index1,3
		{
			*pre_y = 68;
		}
		else if (last % 2 == 0)//index2,4
		{
			*pre_y = 68 + 32;
		}
	}
	else if (tech == 8 || tech == 9)
	{
		if (last % 2 == 1)//index1
		{
			*pre_y = 208;
		}
		else if (last % 2 == 0)//index2
		{
			*pre_y = 208 + 32;
		}
	}
	else if (tech == 10 || tech == 11)
	{
		if (last == 1)//index1
		{
			*pre_y = 348;
		}
		else if (last == 2)//index2
		{
			*pre_y = 348 + 32;
		}
		
		if (last == 3 && tech == 11)//BOLL index3
		{
			*pre_y = 348 + 64;
		}
	}

}

/*********************************************
FUNCTION:find_Kstobutton2
DESCRIPTION���ҵ����Ǹ����͵�ĳһָ��
INPUT:tech,index,x,y
RETURN:��
***********************************************/
void find_Kstobutton2(int* tech, int* index, int* x, int* y)
{
	//techΪ���ͺţ�indexΪ����ѡ��,x��yΪĳһK�����͵����Ͻ�����
	if (mouse_press(24, 68, 260, 120) == 1)
	{
		delay(120);
		*tech = 6;//KDJ
		*x = 24;
		*y = 68;
	}
	else if (mouse_press(344, 68, 580, 120) == 1)
	{
		delay(120);
		*tech = 7;//MACD
		*x = 344;
		*y = 68;
	}
	else if (mouse_press(24, 208, 260, 260) == 1)
	{
		delay(120);
		*tech = 8;//RSI
		*x = 24;
		*y = 208;
	}
	else if (mouse_press(344, 208, 580, 260) == 1)
	{
		delay(120);
		*tech = 9;//VOL/OBV
		*x = 344;
		*y = 208;
	}
	else if (mouse_press(24, 348, 260, 400) == 1)
	{
		delay(120);
		*tech = 10;//BIAS
		*x = 24;
		*y = 348;
	}
	else if (mouse_press(344, 348, 580, 430) == 1)
	{
		delay(120);
		*tech = 11;//BOLL
		*x = 344;
		*y = 348;
	}

	if (mouse_press(*x + 90, *y, *x + 100, *y + 10) == 1)
	{
		delay(120);
		*index = 1;//���м�����ĵ�һ����̬
	}
	else if (mouse_press(*x + 90, *y + 32, *x + 100, *y + 32 + 10) == 1)
	{
		delay(120);
		*index = 2;//���м�����ĵڶ�����̬
	}
	else if ((mouse_press(*x + 120 + 90, *y, *x + 120 + 100, *y + 10) == 1) && ((*tech == 6) || (*tech == 7)))
	{
		delay(120);
		*index = 3;//MACD,KDJ��������̬
	}
	else if ((mouse_press(*x + 90, *y + 64, *x + 100, *y + 64 + 10) == 1) && (*tech == 11))
	{
		delay(120);
		*index = 3;//BOLL��������̬
	}
	else if (mouse_press(*x + 120 + 90, *y + 32, *x + 120 + 100, *y + 32 + 10) == 1 && ((*tech == 6) || (*tech == 7)))
	{
		delay(120);
		*index = 4;//MACD,KDJ��������̬
	}
}