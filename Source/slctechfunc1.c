#include"public.h"
#include"database.h"
#include"techslc.h"
#include"slctfunc.h"
#include"tsearch.h"
#include"control.h"

/*****************************************
slctechfunc1.c
COPYRIGHT:	weijingmin
FUNCTION:	T_select page 1
ABSTRACT:
		A.find button for light
		B.check option array
DATE:2019/10/29
******************************************/

/*********************************************
FUNCTION:T_stoselect1
DESCRIPTION����ҳ��ʾK����̬ѡ�ɣ�MA������̬ѡ��
INPUT:cinfo,u,page,opt[][6],sto_list
RETURN:��
***********************************************/
void T_stoselect1(Ctr* cinfo, USER* u, int* page, int opt[][6], int* sto_list)
{
	int i, j;
	int num;//��ť���
	int color = 0;//��¼���α�ŵİ�ť��ɫ
	int precolor = 0;//��¼�ϴα�ŵİ�ť��ɫ
	clrmous(MouseX, MouseY);
	delay(100);
	cleardevice();
	draw_T_stoselect1();
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
		//	setfillstyle(1,BLACK);
			//bar(0,25,639,480);
			mainmenu_draw();
			control_judge(u);
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

		if (MouseX > 35 && MouseX < 512 && MouseY> 320 && MouseY < 440)
		{
			if (mouse_press(45 + 17 * 4 + 7, 332 - 5, 45 + 17 * 4 + 17, 332 + 5) == 2)
			{
				MouseS = 1;
				continue;
			}
			else if (mouse_press(210 + 17 * 4 + 7, 332 - 5, 210 + 17 * 4 + 17, 332 + 5) == 2)
			{
				MouseS = 1;
				continue;
			}
			else if (mouse_press(45 + 17 * 4 + 7, 332 + 35, 45 + 17 * 4 + 17, 332 + 45) == 2)
			{
				MouseS = 1;
				continue;
			}
			else if (mouse_press(210 + 17 * 4 + 7, 332 + 35, 210 + 17 * 4 + 17, 332 + 45) == 2)
			{
				MouseS = 1;
				continue;
			}
			else if (mouse_press(45 + 17 * 4 + 7, 332 + 75, 45 + 17 * 4 + 17, 332 + 85) == 2)
			{
				MouseS = 1;
				continue;
			}
			else if (mouse_press(210 + 17 * 4 + 7, 332 + 75, 210 + 17 * 4 + 17, 332 + 85) == 2)
			{
				MouseS = 1;
				continue;
			}
			else
			{
				MouseS = 0;
			}

			if (mouse_press(35, 320, 512, 440) == 1)
			{
				MA_select1_check(&precolor, &color, opt);//����һҳ�ĸ�Ԫ�ر���ǣ��ı�opt���鲢���б�Ƿ���
				continue;
			}
		}


		if (MouseX > 35 && MouseX < 512 && MouseY> 68 && MouseY < 280)
		{
			if (mouse_press(35 + 17 * 5 + 4, 83, 35 + 17 * 5 + 14, 93) == 2
				|| mouse_press(35 + 17 * 5 + 4, 83 + 30, 35 + 17 * 5 + 14, 123) == 2
				|| mouse_press(35 + 17 * 5 + 4, 83 + 30 * 2, 35 + 17 * 5 + 14, 153) == 2)
			{
				MouseS = 1;
				continue;
			}
			else if (mouse_press(322 + 17 * 5 + 4, 83, 322 + 17 * 5 + 14, 93) == 2
				|| mouse_press(322 + 17 * 5 + 4, 83 + 30, 322 + 17 * 5 + 14, 123) == 2
				|| mouse_press(322 + 17 * 5 + 4, 83 + 30 * 2, 322 + 17 * 5 + 14, 153) == 2)
			{
				MouseS = 1;
				continue;
			}
			else if (mouse_press(35 + 17 * 5 + 4, 203, 35 + 17 * 5 + 14, 213) == 2
				|| mouse_press(35 + 17 * 5 + 4, 203 + 30, 35 + 17 * 5 + 14, 243) == 2
				|| mouse_press(35 + 17 * 5 + 4, 203 + 30 * 2, 35 + 17 * 5 + 14, 273) == 2)
			{
				MouseS = 1;
				continue;
			}
			else if (mouse_press(322 + 17 * 5 + 4, 203, 322 + 17 * 5 + 14, 213) == 2
				|| mouse_press(322 + 17 * 5 + 4, 203 + 30, 322 + 17 * 5 + 14, 243) == 2)
			{
				MouseS = 1;
				continue;
			}
			else
			{
				MouseS = 0;
			}

			if (mouse_press(35, 68, 512, 280) == 1)
			{
				T_select1_check(opt);//����һҳ�ĸ�Ԫ�ر���ǣ��ı�opt���鲢���б�Ƿ���
				continue;
			}
		}
		
		
		if (MouseX > 560 && MouseX < 620 && MouseY > 442 && MouseY < 479)
		{
			if (mouse_press(560, 442, 620, 479) == 2)//δ���
			{
				MouseS = 1;
				if (num == 0)//��ֹ���ظ�����
				{
					lightbutton_Tselect(1);
					num = 1;
				}
				continue;
				//��������
			}
			else if (mouse_press(560, 442, 620, 479) == 1)
			{
				MouseS = 0;
				lightbutton_Tselect(1);
				delay(100);
				*page = 2;
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
					lightbutton_Tselect(3);
					num = 3;
				}
				continue;
				//��������
			}
			else if (mouse_press(250, 452, 290, 479) == 1)
			{
				MouseS = 0;
				lightbutton_Tselect(3);
				T_search(opt, sto_list, RED);
				*page = 3;
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
FUNCTION:T_select1_check
DESCRIPTION��Ѱ�ұ�ǣ�
	���ǲ�����Ӧ��opt���鸳ֵ
INPUT:opt[][6]
RETURN:��
***********************************************/
void T_select1_check(int opt[][6])
{
	int x, y;//Ҫ�����İ�ť������
	int i;
	int color;
	int pre_x, pre_y;//��һ����������ť������
	int tech = 0, index = 0;//techΪ���ͺţ�indexΪ����ѡ��

	//Kline�����ͱ��
	find_Klinebutton(&tech, &index, &x, &y);//Ѱ���û�����Ŀ�
	if ((tech == 0) || ((tech != 0) && (index == 0)))//û�е�����ÿ�
	{
		return;
	}

	switch (tech)
	{
	case 1:
		color = WHITE;
		break;
	case 2:
		color = YELLOW;
		break;
	case 3:
		color = LIGHTRED;
		break;
	case 4:
		color = LIGHTBLUE;
		break;
	}
	for (i = 0; i < 4; i++)
	{
		if (opt[tech - 1][i] == 1)//��һ���ʹ����ѱ�ѡ����
		{
			if (i == index - 1)//�����û�Ŀǰ����İ�ť���ϴ�ѡ����һ�������һ��
			{
				find_lastbutton(tech, i, &pre_x, &pre_y);
				clrmous(MouseX, MouseY);
				setcolor(color);
				draw_element(pre_x, pre_y, 1, color);
				opt[tech - 1][i] = 0;
				return;
			}
			else//�����û�����һ���������İ�ť���ϴεĲ�һ��
			{
				find_lastbutton(tech, i, &pre_x, &pre_y);//Ѱ����һ�ε���İ�ť�����Ͻ�����
				clrmous(MouseX, MouseY);
				setcolor(color);
				draw_element(pre_x, pre_y, 1, color);//�ָ�֮ǰ�İ�ť
				opt[tech - 1][i] = 0;
			}
		}
	}
	opt[tech - 1][index - 1] = 1;
	x += 17 * 5 + 4;
	y = y + 30 * (index - 1);
	clrmous(MouseX, MouseY);
	setcolor(color);
	draw_element(x, y, 1, LIGHTGRAY);//������ǵİ�ť
	
	return;
}

/*********************************************
FUNCTION:MA_select1_check
DESCRIPTION��Ѱ��ma��ǣ�
	���ǲ�����Ӧ��opt���鸳ֵ
INPUT:precolor,color,opt[][6]
RETURN:��
***********************************************/
void MA_select1_check(int *precolor, int *color, int opt[][6])
{
	int x, y;//Ҫ�����İ�ť������
	int i, j;
	int pre_x, pre_y;//��һ����������ť������
	int tech = 0, index = 0;//techΪ���ͺţ�indexΪ����ѡ��

	//MA�����ͱ��
	find_MAbutton(&tech, &index, &x, &y);
	if ((tech != 5) || ((tech == 5) && (index == 0)))//û�е�����ÿ�
	{
		return;
	}
	*precolor = *color;
	switch (index)
	{
	case 1:
		*color = WHITE;
		break;
	case 2:
		*color = WHITE;
		break;
	case 3:
		*color = YELLOW;
		break;
	case 4:
		*color = YELLOW;
		break;
	case 5:
		*color = LIGHTMAGENTA;
		break;
	case 6:
		*color = LIGHTMAGENTA;
		break;
	}
	for (i = 0; i < 6; i++)
	{
		if (opt[tech - 1][i] == 1)//��һ���ʹ����ѱ�ѡ����
		{
			if (i == index - 1)//�����û�Ŀǰ����İ�ť���ϴ�ѡ����һ�������һ��
			{
				find_lastbutton(tech, i + 1, &pre_x, &pre_y);
				clrmous(MouseX, MouseY);
				draw_element(pre_x, pre_y, 2, *precolor);
				opt[tech - 1][i] = 0;
				return;
			}
			else//�����û�����һ���������İ�ť���ϴεĲ�һ��
			{
				find_lastbutton(tech, i + 1, &pre_x, &pre_y);//Ѱ����һ�ε���İ�ť�����Ͻ�����
				clrmous(MouseX, MouseY);
				draw_element(pre_x, pre_y, 2, *precolor);//�ָ�֮ǰ�İ�ť
				opt[tech - 1][i] = 0;
			}
		}
	}
	opt[tech - 1][index - 1] = 1;
	clrmous(MouseX, MouseY);
	draw_element(x, y, 2, LIGHTCYAN);//������ǵİ�ť

}

/*********************************************
FUNCTION:find_MAbutton
DESCRIPTION���ҵ�MA�е�ĳһ��ָ̬��
INPUT:tech,index,x,y
RETURN:��
***********************************************/
void find_MAbutton(int* tech, int* index, int* x, int* y)
{
	//techΪ���ͺţ�indexΪ����ѡ��,x��yΪĳһK�����͵����Ͻ�����
	if (mouse_press(35, 320, 512, 450) == 1)
	{
		delay(120);
		*tech = 5;//MAѡ��
		*x = 45;
		*y = 332;
	}

	if (mouse_press(*x + 17 * 4 + 7, *y - 5, *x + 17 * 4 + 17, *y + 5) == 1)
	{
		delay(120);
		*index = 1;//��ͷ����
		*x += 17 * 4 + 12;
		return;
	}
	else if (mouse_press(*x + 165 + 17 * 4 + 7, *y - 5, *x + 165 + 17 * 4 + 17, *y + 5) == 1)
	{
		delay(120);
		*index = 2;//��ͷ����
		*x += 165 + 17 * 4 + 12;
		return;
	}
	else if (mouse_press(*x + 17 * 4 + 7, *y + 35, *x + 17 * 4 + 17, *y + 45) == 1)
	{
		delay(120);
		*index = 3;//ճ��
		*x += 17 * 4 + 12;
		*y += 40;
		return;
	}
	else if (mouse_press(*x + 165 + 17 * 4 + 7, *y + 35, *x + 165 + 17 * 4 + 17, *y + 45) == 1)
	{
		delay(120);
		*index = 4;//��ɢ
		*x += 165 + 17 * 4 + 12;
		*y += 40;
		return;
	}
	else if (mouse_press(*x + 17 * 4 + 7, *y + 75, *x + 17 * 4 + 17, *y + 85) == 1)
	{
		delay(120);
		*index = 5;//��ͷ����
		*x += 17 * 4 + 12;
		*y += 80;
	}
	else if (mouse_press(*x + 165 + 17 * 4 + 7, *y + 75, *x + 165 + 17 * 4 + 17, *y + 85) == 1)
	{
		delay(120);
		*index = 6;//��ͷ����
		*x += 165 + 17 * 4 + 12;
		*y += 80;
		return;
	}
	
}

/*********************************************
FUNCTION:find_Klinebutton
DESCRIPTION���ҵ��Ƕ��ٸ�K����̬�е�ĳһָ��
INPUT:tech,index,x,y
RETURN:��
***********************************************/
void find_Klinebutton(int* tech, int* index, int* x, int* y)
{
	//techΪ���ͺţ�indexΪ����ѡ��,x��yΪĳһK�����͵����Ͻ�����
	if (mouse_press(35, 68, 225, 168) == 1)
	{
		delay(120);
		*tech = 1;//����K��
		*x = 35;
		*y = 83;
	}
	else if (mouse_press(322, 68, 512, 168) == 1)
	{
		delay(120);
		*tech = 2;//˫��K��
		*x = 322;
		*y = 83;
	}
	else if (mouse_press(35, 188, 225, 280) == 1)
	{
		delay(120);
		*tech = 3;//����K��
		*x = 35;
		*y = 203;
	}
	else if (mouse_press(322, 188, 512, 280) == 1)
	{
		delay(120);
		*tech = 4;//���K��
		*x = 322;
		*y = 203;
	}

	if (mouse_press(*x + 17 * 5 + 4, *y, *x + 17 * 5 + 14, *y + 10) == 1)
	{
		delay(120);
		*index = 1;//n��K���еĵ�һ����̬
	}
	else if (mouse_press(*x + 17 * 5 + 4, *y + 30, *x + 17 * 5 + 14, *y + 40) == 1)
	{
		delay(120);
		*index = 2;//n��K���еĵڶ�����̬
	}
	else if (mouse_press(*x + 17 * 5 + 4, *y + 60, *x + 17 * 5 + 14, *y + 70) == 1)
	{
		delay(120);
		*index = 3;//n��K���еĵ�������̬
	}
}

/*********************************************
FUNCTION:find_lastbutton
DESCRIPTION���ҵ���һ����ǵ�����
INPUT:tech,last,pre_x,pre_y
RETURN:��
***********************************************/
void find_lastbutton(int tech, int last, int* pre_x, int* pre_y)
{
	if (tech == 1 || tech == 3)
	{
		*pre_x = 35 + 17 * 5 + 4;
	}
	else if (tech == 2 || tech == 4)
	{
		*pre_x = 322 + 17 * 5 + 4;
	}
	if (tech == 1 || tech == 2)
	{
		*pre_y = 83 + last * 30;
	}
	else if (tech == 3 || tech == 4)
	{
		*pre_y = 203 + last * 30;
	}

	if (tech == 5)//MA
	{
		if (last % 2 == 0)//last=2,4,6
		{
			*pre_x = 210 + 17 * 4 + 12;
			if (last == 2)
			{
				*pre_y = 332;
			}
			else if (last == 4)
			{
				*pre_y = 332 + 40;
			}
			else if (last == 6)
			{
				*pre_y = 332 + 80;
			}
		}
		else if (last % 2 == 1)//last=1,3,5
		{
			*pre_x = 45 + 17 * 4 + 12;
			if (last == 1)
			{
				*pre_y = 332;
			}
			else if (last == 3)
			{
				*pre_y = 332 + 40;
			}
			else if (last == 5)
			{
				*pre_y = 332 + 80;
			}
		}
	}
}