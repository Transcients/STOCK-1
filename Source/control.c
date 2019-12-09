#include"public.h"
#include"control.h"
#include"open.h"
#include"queue.h"
#include"trade.h"
#include"market.h"
#include"qsearch.h"
#include"traverse.h"
#include"techslc.h"
#include"person.h"
#include"about.h"

/*****************************************
control.c
COPYRIGHT:	dengshumin
FUNCTION:	control mouse,key,and func
ABSTRACT:
		A.control and invoke function
		B.button lightning and recovering
		C.menu and submenu
DATE:2019/10/1
******************************************/



/******************************************
FUNCTION:control_main
DESCRIPTION:��������������������������̵Ŀ���
INPUT:*func,u
RETURN:��
******************************************/
void control_main(int* func,USER* u)       //uΪ�û���Ϣָ��
{
	int i = 0, j = 0, k = 0, pre_k = 1;
	int page = 0;
	int minute;
	StoQueue* Q = NULL;
	struct tm *tp = NULL;
	Ctr cinfo;
	int pos[10] = {0};   				//���ÿһҳ��ʼ�ֽڵ�����
	int sto_No[20] = { 0 };				//��Ź�Ʊ��ŵ����飬�������������ܻ���
	int sto_list[200] = { 0 };
	int sto = 1;						//��������Ʊ������鸳ֵ�ı���
	int sto_num = 0;					//������ϣ����������
	char name[20] = { '\0' };			//������ϣ����������

	pos[0] = 0;
	memset(&cinfo,0,sizeof(Ctr));  		//��ʼ��������Ϣ
	for (i = 1; i < 10; i++)
	{
		pos[i] = countqueue(pos[i-1]);//�ݹ飬��ÿҳ���ļ��п�ʼ��λ��
	}
	if ((Q = (StoQueue*)malloc(sizeof(StoQueue))) == NULL)
	{
		printf("memoryallocation runs wrong in control.c");
		delay(3000);
		exit(1);
	}
	clrmous(MouseX, MouseY);
	delay(100);
	cleardevice();
	draw_stoqueue();
	mainmenu_draw();
	control_judge(u);
	get_time(tp, &minute, 1);
	initqueue(Q);//��ʼ������ļ�ָ��λ��
	for (j = 0; j < 20; j++)
	{
		sto_No[j] = sto;//����ֵ1-20
		sto++;
	}
	i = 0;//��ʼ��ҳ��
	if(strlen(u->user) != 0)
		update_hold_day(tp,u);              //���³ֹ�����
	while(1)
	{
		//tp->tm_
		if(!bioskey(1))
		{
			newmouse(&MouseX,&MouseY,&press);
			control_mouse(&cinfo,u);
		}
		else if(bioskey(1))
		{
			cinfo.key = bioskey(0);
			if (cinfo.key == DOWN)
			{
				queuedown(&sto, sto_No, 20);	//������������sto_No��ÿһҳ��ֵ
				i=(i+1) % 10;					//�������һ�棬��ת����һ��
				clrmous(MouseX,MouseY);
				cleardevice();
				draw_stoqueue();
				mainmenu_draw();
				control_judge(u);
				inputqueue(Q, pos[i]);
				
				save_bk_mou(MouseX,MouseY);
				drawmous(MouseX,MouseY);   		//�������       
				cinfo.key = 0;
				get_time(tp, &minute, 1);
				continue;
			}
			else if (cinfo.key == UP)
			{
				queueup(&sto, sto_No, 20);		//������������sto_No��ÿһҳ��ֵ
				i--;
				if (i == -1)
				{
					i = 9;//�����һ��
					//break;
				}
				clrmous(MouseX,MouseY);
				cleardevice();
				draw_stoqueue();
				mainmenu_draw();
				control_judge(u);
				inputqueue(Q, pos[i]);
				save_bk_mou(MouseX,MouseY);
				drawmous(MouseX,MouseY);
				cinfo.key = 0;
				get_time(tp, &minute, 1);
				continue;
			}   //���ж�up��down��
			else
				control_key(&cinfo);
		} //���ˣ�ÿ�μ��̿��ƺ�������

		if(cinfo.func == 2)          //ע�����˳�
		{
			*func = cinfo.func;
			destroyqueue(Q);    	 //���ٶ���
			return;   				 //���ص�ʱ��ջ����Ctr�������ͷŵ�
		}
		if(control_menu(&cinfo))
		{
			clrmous(MouseX,MouseY);
			draw_stoqueue();
			control_judge(u);
			inputqueue(Q, pos[i]);
			get_time(tp, &minute, 1);
			submenu_draw(cinfo.itemnum);
		}
		if(control_func(&cinfo, u, sto_list, &page))
		{
			cinfo.ord = 0;
			cinfo.ord_last = 0;
			cinfo.itemnum = 0;
			cinfo.itemnum_last = 0;
			draw_stoqueue();
			inputqueue(Q, pos[i]);
			get_time(tp, &minute, 1);
			continue;
		}
		if (MouseY > 50 && MouseY < 456 && cinfo.itemnum == 0)
		{
			/*if (mouse_press(0, 50, 640, 456) == 3)*/
			
			if (mouse_press(0, 50, 640, 456) == 2)
			{
				continue;
			}
			else if (mouse_press(0, 50, 640, 456) == 1)//�����㷨(wjm)
			{
				if ((sto_num = queuesearch(sto_No, &pre_k, &k)) != 0)  //����ת����
				{
					search_name(sto_num, name);//��Ʊ��ŵ����Ƶ�����
					if (strlen(name) == 0)
					{
						//printf("wrong");
					}
					sto_market(&cinfo, u, sto_num, name);
					if (cinfo.func == 0)
					{
						cleardevice();
						mainmenu_draw();
						control_judge(u);
						draw_stoqueue();
						inputqueue(Q, pos[i]);
						get_time(tp, &minute, 1);           //�ٸ���func��ֵ���벻ͬ����
						continue;
					}
					continue;
				}
			}
		/*	else if (mouse_press(0, 50, 640, 456) == 3)
			{//�Ҽ����������ѡ��
				sto_num = sto_No[(MouseY - 50) / 20];
				add_fav(u, sto_num);
			}*/
		}
	}
}

/************************************************************************
FUNCTION:control_mouse
DESCRIPTION: �����Ӧ�Բ˵�����
ATTENTION: ��Ϊ��2��3��6���˵����Ӳ˵��������ڵ��֮�������ܺŷ����ı䣬
			�����ղ˵����ֱ�Ϊ��
INPUT:cinfo,u
RETURN:��
************************************************************************/
void control_mouse(Ctr* cinfo,USER* u)    //ͨ�������ѡ��˵�����˵����������Ӳ˵����
{
	if(cinfo->itemnum == 0)
	{
		if(mouse_press(0,0,60,24) == 1)
		{
			cinfo->itemnum = 1;
			cinfo->ord = 0;
			cinfo->ord_last = 0;
			//return ����Ҫ����ѭ��
		}
		else if(mouse_press(60,0,120,24) == 1)
		{
			cinfo->itemnum = 2;
			cinfo->func = 0;         //�����
			cinfo->ord = 0;
			cinfo->ord_last = 0;
		}
		else if(mouse_press(120,0,180,24) == 1)
		{
			cinfo->itemnum = 3;
			cinfo->func = 8;         //���麯��
			cinfo->ord = 0;
			cinfo->ord_last = 0;
		}
		else if(mouse_press(180,0,240,24) == 1)
		{
			cinfo->itemnum = 4;
			cinfo->ord = 0;
			cinfo->ord_last = 0;
		}
		else if(mouse_press(240,0,300,24) == 1)
		{
			cinfo->itemnum = 5;
			cinfo->ord = 0;
			cinfo->ord_last = 0;
		}
		else if(mouse_press(300,0,360,24) == 1)
		{
			cinfo->itemnum = 6;
			if(strlen(u->user) != 0)
			{
				if(strlen(u->bankcard) != 0)      //��¼�˶��ҿ��˻�
				{
					cinfo->func = 14;        //���˲˵�
				}
				else//δ����
				{
					cpop(2);
				}
			}
			else
			{
				clrmous(MouseX, MouseY);
				cpop(1);
				//cinfo->itemnum = 0;
			}
			cinfo->ord = 0;
			cinfo->ord_last = 0;
		}
		return;
	}
	else if(cinfo->itemnum == 1)
	{
		if(mouse_press(0,0,60,24) == 1)
		{
			cinfo->itemnum = 1;
			cinfo->ord = 0;
			cinfo->ord_last = 0;
		}
		else if(mouse_press(60,0,120,24) == 1)
		{
			cinfo->itemnum = 2;
			cinfo->func = 0;
			cinfo->ord = 0;
			cinfo->ord_last = 0;
		}
		else if(mouse_press(120,0,180,24) == 1)
		{
			cinfo->itemnum = 3;
			cinfo->func = 8;
			cinfo->ord = 0;
			cinfo->ord_last = 0;
		}
		else if(mouse_press(180,0,240,24) == 1)
		{
			cinfo->itemnum = 4;
			cinfo->ord = 0;
			cinfo->ord_last = 0;
		}
		else if(mouse_press(240,0,300,24) == 1)
		{
			cinfo->itemnum = 5;
			cinfo->ord = 0;
			cinfo->ord_last = 0;
		}
		else if(mouse_press(300,0,360,24) == 1)
		{
			cinfo->itemnum = 6;
			if(strlen(u->user) != 0)
			{
				if(strlen(u->bankcard) != 0)      //��¼�˶��ҿ��˻�
				{
					cinfo->func = 14;        //����
				}
				else//δ����
				{
					cpop(2);
				}
			}
			else
			{
				clrmous(MouseX, MouseY);
				cpop(1);
				//cinfo->itemnum = 0;
			}
			cinfo->ord = 0;
			cinfo->ord_last = 0;
		}
		else if(mouse_press(360,0,640,480) == 1||
				mouse_press(0,120,640,480) == 1||
				mouse_press(60,24,640,480) == 1)
				{
					cinfo->itemnum = 0;
					//cinfo->itemnum_last = 0;
					cinfo->ord = 0;
					cinfo->ord_last = 0;
				}
		if(mouse_press(0,24,60,48) == 1)
		{
			if(strlen(u->user) == 0)   //���δ��¼
			{
				cinfo->func = 2;        //������Ϊ2���ص��ϲ�
				//destroyqueue(Q);      //���ٶ���
				return ;
			}                         //����¼����Ӧ��������
		}
		else if(mouse_press(0,48,60,72) == 1)
		{
			delay(1000);
			closegraph();
			exit(1);
		}
		else if(mouse_press(0,72,60,96) == 1)
		{
			if(strlen(u->user) != 0)  //���ѵ�¼S
			{
				//cinfo->func = 2;
				memset(u,'\0',sizeof(USER));   //ֱ�ӽ���½״̬ȡ��
				control_judge(u);
				return;      //�ص�ѭ����ȥ
			}
		}
		else if(mouse_press(0,96,60,120) == 1)
		{
			cinfo->func = 15; //���ڽ���
		}
		else if(mouse_press(0,24,60,48) == 2)
		{
			cinfo->ord = 1;
		}
		else if(mouse_press(0,48,60,72) == 2)
		{
			cinfo->ord = 2;
		}
		else if(mouse_press(0,72,60,96) == 2)
		{
			cinfo->ord = 3;
		}
		else if(mouse_press(0,96,60,120) == 2)
		{
			cinfo->ord = 4;
		}
	}
	else if(cinfo->itemnum == 2)
	{
		if(mouse_press(0,0,60,24) == 1)
		{
			cinfo->itemnum = 1;
			cinfo->ord = 0;
			cinfo->ord_last = 0;
		}
		else if(mouse_press(60,0,120,24) == 1)
		{
			cinfo->itemnum = 2;
			cinfo->func = 0;
			cinfo->ord = 0;
			cinfo->ord_last = 0;
		}
		else if(mouse_press(120,0,180,24) == 1)
		{
			cinfo->itemnum = 3;
			cinfo->func = 8;
			cinfo->ord = 0;
			cinfo->ord_last = 0;
		}
		else if(mouse_press(180,0,240,24) == 1)
		{
			cinfo->itemnum = 4;
			cinfo->ord = 0;
			cinfo->ord_last = 0;
		}
		else if(mouse_press(240,0,300,24) == 1)
		{
			cinfo->itemnum = 5;
			cinfo->ord = 0;
			cinfo->ord_last = 0;
		}
		else if(mouse_press(300,0,360,24) == 1)
		{
			cinfo->itemnum = 6;
			if(strlen(u->user) != 0)
			{
				if(strlen(u->bankcard) != 0)      //��¼�˶��ҿ��˻�
				{
					cinfo->func = 14;        //���˲˵�
				}
				else//δ����
				{
					cpop(2);
				}
			}
			else
			{
				clrmous(MouseX, MouseY);
				cpop(1);
				//cinfo->itemnum = 0;
			}
			cinfo->ord = 0;
			cinfo->ord_last = 0;
		}
	}
	else if(cinfo->itemnum == 3)
	{
		if(mouse_press(0,0,60,24) == 1)
		{
			cinfo->itemnum = 1;
			cinfo->ord = 0;
			cinfo->ord_last = 0;
		}
		else if(mouse_press(60,0,120,24) == 1)
		{
			cinfo->itemnum = 2;
			cinfo->func = 0;
			cinfo->ord = 0;
			cinfo->ord_last = 0;
		}
		else if(mouse_press(120,0,180,24) == 1)
		{
			cinfo->itemnum = 3;
			cinfo->func = 8;
			cinfo->ord = 0;
			cinfo->ord_last = 0;
		}
		else if(mouse_press(180,0,240,24) == 1)
		{
			cinfo->itemnum = 4;
			cinfo->ord = 0;
			cinfo->ord_last = 0;
		}
		else if(mouse_press(240,0,300,24) == 1)
		{
			cinfo->itemnum = 5;
			cinfo->ord = 0;
			cinfo->ord_last = 0;
		}
		else if(mouse_press(300,0,360,24) == 1)
		{
			cinfo->itemnum = 6;
			if(strlen(u->user) != 0)
			{
				if(strlen(u->bankcard) != 0)      //��¼�˶��ҿ��˻�
				{
					cinfo->func = 14;        //���˲˵�
				}
				else//δ����
				{
					cpop(2);
				}
			}
			else
			{
				clrmous(MouseX, MouseY);
				cpop(1);
			//	cinfo->itemnum = 0;
			}
			cinfo->ord = 0;
			cinfo->ord_last = 0;
		}
	}
	else if(cinfo->itemnum == 4)
	{
		if(mouse_press(0,0,60,24) == 1)
		{
			cinfo->itemnum = 1;
			cinfo->ord = 0;
			cinfo->ord_last = 0;
		}
		else if(mouse_press(60,0,120,24) == 1)
		{
			cinfo->itemnum = 2;
			cinfo->func = 0;
			cinfo->ord = 0;
			cinfo->ord_last = 0;
		}
		else if(mouse_press(120,0,180,24) == 1)
		{
			cinfo->itemnum = 3;
			cinfo->func = 8;
			cinfo->ord = 0;
			cinfo->ord_last = 0;
		}
		else if(mouse_press(180,0,240,24) == 1)
		{
			cinfo->itemnum = 4;
			cinfo->ord = 0;
			cinfo->ord_last = 0;
		}
		else if(mouse_press(240,0,300,24) == 1)
		{
			cinfo->itemnum = 5;
			cinfo->ord = 0;
			cinfo->ord_last = 0;
		}
		else if(mouse_press(300,0,360,24) == 1)
		{
			cinfo->itemnum = 6;
			if(strlen(u->user) != 0)
			{
				if(strlen(u->bankcard) != 0)      //��¼�˶��ҿ��˻�
				{
					cinfo->func = 14;        //���˲˵�
				}
				else//δ����
				{
					cpop(2);
				}
			}
			else
			{
				clrmous(MouseX, MouseY);
				cpop(1);
			//	cinfo->itemnum = 0;
			}
			cinfo->ord = 0;
			cinfo->ord_last = 0;
		}
		else if(mouse_press(360,0,640,480) == 1||
				mouse_press(0,0,180,480) == 1||
				mouse_press(180,96,640,480) == 1||
				mouse_press(260,24,640,480) == 1)
				{
					cinfo->itemnum = 0;
					cinfo->ord = 0;
					cinfo->ord_last = 0;
				}
		if(mouse_press(180,24,260,48) == 2)
		{
			cinfo->ord = 5;
		}
		else if(mouse_press(180,48,260,72) == 2)
		{
			cinfo->ord = 6;
		}
		else if(mouse_press(180,72,260,96) == 2)
		{
			cinfo->ord = 7;
		}
		else if(mouse_press(180,24,260,48) == 1)
		{
			cinfo->func = 9; //������  
		}
		else if(mouse_press(180,48,260,72) == 1)
		{
			cinfo->func = 10; //������
		}
	/*	else if(mouse_press(180,72,260,96) == 1)
		{
			cinfo->func = 11; //����ѡ��
		}*/
	}
	else if(cinfo->itemnum == 5)
	{
		if(mouse_press(0,0,60,24) == 1)
		{
			cinfo->itemnum = 1;
			cinfo->ord = 0;
			cinfo->ord_last = 0;
		}
		else if(mouse_press(60,0,120,24) == 1)
		{
			cinfo->itemnum = 2;
			cinfo->func = 0;
			cinfo->ord = 0;
			cinfo->ord_last = 0;
		}
		else if(mouse_press(120,0,180,24) == 1)
		{
			cinfo->itemnum = 3;
			cinfo->func = 8;
			cinfo->ord = 0;
			cinfo->ord_last = 0;
		}
		else if(mouse_press(180,0,240,24) == 1)
		{
			cinfo->itemnum = 4;
			cinfo->ord = 0;
			cinfo->ord_last = 0;
		}
		else if(mouse_press(240,0,300,24) == 1)
		{
			cinfo->itemnum = 5;
			cinfo->ord = 0;
			cinfo->ord_last = 0;
		}
		else if(mouse_press(300,0,360,24) == 1)
		{
			cinfo->itemnum = 6;
			if(strlen(u->user) != 0)
			{
				if(strlen(u->bankcard) != 0)      //��¼�˶��ҿ��˻�
				{
					cinfo->func = 14;        //���˲˵�
				}
				else//δ����
				{
					cpop(2);
				}
			}
			else
			{
				clrmous(MouseX, MouseY);
				cpop(1);
			//	cinfo->itemnum = 0;
			}
			cinfo->ord = 0;
			cinfo->ord_last = 0;
		}
		else if(mouse_press(360,0,640,480) == 1||
				mouse_press(0,0,240,480) == 1||
				mouse_press(240,72,640,480) == 1||
				mouse_press(300,24,640,480) == 1)
				{
					cinfo->itemnum = 0;
				//	cinfo->itemnum_last = 0;
					cinfo->ord = 0;
					cinfo->ord_last = 0;
				}
		if(mouse_press(240,24,300,48) == 2)
		{
			cinfo->ord = 8;
		}
		else if(mouse_press(240,48,300,72) == 2)
		{
			cinfo->ord = 9;
		}
		else if(mouse_press(240,24,300,48) == 1)
		{
			if(strlen(u->user) == 0)   //δ��¼
			{
				cpop(1);//��ʾ���ȵ�¼
				cinfo->itemnum = 0;
			}
			else                    //�ѵ�¼
			{
				cinfo->func = 12;
			}
		}
		else if(mouse_press(240,48,300,72) == 1)
		{   //����
			if(strlen(u->user) == 0)
			{
				cpop(1);//��ʾ���ȵ�¼
				cinfo->itemnum = 0;
			}
			else 
			{
				if(strlen(u->bankcard) == 0)
				{
					cpop(2); //��ʾ���ȿ���
					cinfo->itemnum = 0;
				}
				else 
				{
					cinfo->func = 13;  //���ɺ���
				}
			}
		}
	}
	else if(cinfo->itemnum == 6)
	{
		if(mouse_press(0,0,60,24) == 1)
		{
			cinfo->itemnum = 1;
			cinfo->ord = 0;
			cinfo->ord_last = 0;
		}
		else if(mouse_press(60,0,120,24) == 1)
		{
			cinfo->itemnum = 2;
			cinfo->func = 0;
			cinfo->ord = 0;
			cinfo->ord_last = 0;
		}
		else if(mouse_press(120,0,180,24) == 1)
		{
			cinfo->itemnum = 3;
			cinfo->func = 8;
			cinfo->ord = 0;
			cinfo->ord_last = 0;
		}
		else if(mouse_press(180,0,240,24) == 1)
		{
			cinfo->itemnum = 4;
			cinfo->ord = 0;
			cinfo->ord_last = 0;
		}
		else if(mouse_press(240,0,300,24) == 1)
		{
			cinfo->itemnum = 5;
			cinfo->ord = 0;
			cinfo->ord_last = 0;
		}
		else if(mouse_press(300,0,360,24) == 1)
		{
			cinfo->itemnum = 6;
			if(strlen(u->user) != 0)
			{
				if(strlen(u->bankcard) != 0)      //��¼�˶��ҿ��˻�
				{
					cinfo->func = 14;        //���˲˵�
				}
				else//δ����
				{
					cpop(2);
				}
			}
			else
			{
				clrmous(MouseX, MouseY);
				cpop(1);
			//	cinfo->itemnum = 0;
			}
			cinfo->ord = 0;
			cinfo->ord_last = 0;
		}
		else if(mouse_press(360,0,640,480) == 1||
				mouse_press(0,0,360,480) == 1||
				mouse_press(360,72,640,480) == 1)
				{
					cinfo->itemnum = 0;
					cinfo->itemnum_last = 0;
					cinfo->ord = 0;
					cinfo->ord_last = 0;
				}
	}
	if(cinfo->itemnum == 2 || cinfo->itemnum == 3 || cinfo->itemnum == 6)
		cinfo->itemnum = 0;   //���ѡ������顢����,����ת��Ϊ�ղ˵�
	delay(30);
}

/**************************************************
FUNCTION:control_key
DESCRIPTION: ͨ�����̿�ݼ����Ʋ˵�
INPUT: cinfo
RETURN:��
***************************************************/
void control_key(Ctr* cinfo)              //���̿��ƺ���
{
	if(cinfo->key != 0)
	{
		if(cinfo->key == F1)
		{
			cinfo->itemnum = 1;
		}
		else if(cinfo->key == F2)
		{
			cinfo->itemnum = 2;
			cinfo->func = 0;
		}
		else if(cinfo->key == F3)
		{
			cinfo->itemnum = 3;
			cinfo->func = 8;
		}
		else if(cinfo->key == F4)
		{
			cinfo->itemnum = 4;
		}
		else if(cinfo->key == F5)
		{
			cinfo->itemnum = 5;
		}
		else if(cinfo->key == F6)
		{
			cinfo->itemnum = 6;
			cinfo->func = 14;
		}	
		cinfo->key = 0;            //ÿ��������֮���key����
	}
}

/*************************************************************************
FUNCTION:control_func
DESCRIPTION: �������л�����
ATTENTION: ��ÿ��ʵ���˺���֮�󣬴�����һ���ж����Ƿ񷵻������漴�������
INPUT: cinfo,u,sto_list,page
RETURN: �������������򷵻�1�����򷵻�0
**************************************************************************/
int control_func(Ctr* cinfo,USER* u,int* sto_list,int* page)    //ֻ�����غ�����ʹ�ã���ĺ����ȷ���cinfo->func��ֵ���������غ����е���
{
	char name[20] = { 0 };										//����sto_num������name���ַ���
	int sto_num = 0;
	if(cinfo->func == 8)
	{
		cinfo->itemnum = 0;
		cinfo->itemnum_last = 0;

		search_name(1, name);
		if (strlen(name) == 0)
		{
			//printf("wrong");
		}
		sto_market(cinfo, u, 1, name);							//���麯��,1Ϊ��һֻ��
		memset(name, '\0', sizeof(name));
		
		if(cinfo->func == 0)          							//˵���Ƿ���������
		{
			clrmous(MouseX,MouseY);
			cleardevice();
			mainmenu_draw();
			control_judge(u);
			return 1;
		}; //���麯��
	}
	else if(cinfo->func == 9)
	{
		cinfo->itemnum = 0;
		cinfo->itemnum_last = 0;
		*page = 4;
		sto_num = technical_control(cinfo, u, sto_list, page);		//������

		search_name(sto_num, name);									//��Ʊ��ŵ����Ƶ�����
		if (strlen(name) == 0)
		{
			//printf("wrong");
		}
		if (sto_num != 0)
		{
			sto_market(cinfo, u, sto_num, name);
			memset(name, '\0', sizeof(name));
		}

		if(cinfo->func == 0)         								 //˵���ǰ��˻����
		{
			clrmous(MouseX,MouseY);
			cleardevice();
			mainmenu_draw();
			control_judge(u);
			return 1;
		} 							
	}
	else if(cinfo->func == 10)
	{
		cinfo->itemnum = 0;
		cinfo->itemnum_last = 0;
		*page = 1;
		sto_num = technical_control(cinfo, u, sto_list, page);		//������

		search_name(sto_num, name);//��Ʊ��ŵ����Ƶ�����
		if (sto_num != 0)
		{
			sto_market(cinfo, u, sto_num, name);
			memset(name, '\0', sizeof(name));
		}

		if(cinfo->func == 0)     									    //˵���ǰ��˻����
		{
			clrmous(MouseX,MouseY);
			cleardevice();
			mainmenu_draw();
			control_judge(u);
			return 1;
		}
	}
	else if(cinfo->func == 12)
	{
		cinfo->itemnum = 0;
		cinfo->itemnum_last = 0;
		opaccount(cinfo,u);			  //��������
		if(cinfo->func == 0)          //˵���ǰ��˻��������
		{
			clrmous(MouseX,MouseY);
			cleardevice();
			mainmenu_draw();
			control_judge(u);
			return 1;
		}
	}
	else if(cinfo->func == 13)
	{
		cinfo->itemnum = 0;
		cinfo->itemnum_last = 0;
		trade(cinfo, u, 0, 0);  			  //���ɺ���
		if(cinfo->func == 0)       			   //˵���ǰ��˻����
		{
			clrmous(MouseX,MouseY);
			cleardevice();
			mainmenu_draw();
			control_judge(u);
			return 1;
		}
	}
	else if(cinfo->func == 14)      //����
	{
		cinfo->itemnum = 0;
		cinfo->itemnum_last = 0;
		personinfo(cinfo, u);        //���˺���
		if(cinfo->func == 0)
		{
			clrmous(MouseX,MouseY);
			cleardevice();
			mainmenu_draw();
			control_judge(u);
			return 1;
		}
	}
	else if(cinfo->func == 15)       //����
	{
		cinfo->itemnum = 0;
		cinfo->itemnum_last = 0;
		About(cinfo, u);
		if(cinfo->func == 0)
		{
			clrmous(MouseX, MouseY);
			cleardevice();
			mainmenu_draw();
			control_judge(u);
			return 1;
		}
	}	
	return 0;
}

/********************************************************************
FUNCTION: control_menu
DESCRIPTION: �˵��л���չ���Լ��Ӳ˵���������
INPUT: cinfo
RETURN: ��ԭ���в˵��򷵻�Ϊ1�����Ϊ�Ӳ˵����������ǿղ˵���᷵��Ϊ0
********************************************************************/
int control_menu(Ctr* cinfo)          //��ֵΪ0˵���Ǳ����任������ԭ��Ϊ�ղ˵�
{
	if(cinfo->itemnum != cinfo->itemnum_last)
	{
		cinfo->ord = 0;              //�˵��л���ʱ���ord��ord_last����,��ֹ����������
		cinfo->ord_last = 0;
		
		if(cinfo->itemnum_last != 0)
		{
			cleardevice();
			clrmous(MouseX,MouseY);
			mainmenu_draw();
			//submenu_draw(cinfo->itemnum);
			cinfo->itemnum_last = cinfo->itemnum;
			return 1;
		}
		else 
		{
			clrmous(MouseX,MouseY);
			submenu_draw(cinfo->itemnum);
			cinfo->itemnum_last = cinfo->itemnum;
			return 0;
		}
	}
	
	if(cinfo->ord != cinfo->ord_last)
	{
		lightbutton_menu(cinfo->ord);
		recoverbutton_menu(cinfo->ord_last);
		cinfo->ord_last = cinfo->ord;
		return 0;
	}
	return 0;
}

/*************************************
FUNCTION: mainmenu_draw
DESCRIPTION: �������˵�
INPUT: void
RETURN: ��
**************************************/
void mainmenu_draw(void)
{
	setbkcolor(BLACK);
	setfillstyle(1,LIGHTGRAY);
	setcolor(RED);
	setlinestyle(0,0,2);
	bar(0,0,640,24);                        //��24
	rectangle(0,0,639,479);

	puthz(10,5,"ϵͳ",16,24,BLACK);     
	line(60,1,60,24);

	puthz(70,5,"����",16,24,BLACK);
	line(120,1,120,24);

	puthz(130,5,"����",16,24,BLACK);
	line(180,1,180,24);

	puthz(190,5,"ѡ��",16,24,BLACK);
	line(240,1,240,24);

	puthz(250,5,"����",16,24,BLACK);
	line(300,1,300,24);

	puthz(310,5,"����",16,24,BLACK);
	line(360,1,360,24);
	
//	bar(0,480,640,456);
}

/**********************************************
FUNCTION: submenu_draw
DESCRIPTION: �����Ӳ˵�
INPUT: cinfo->itemnum
RETURN:��
**********************************************/
void submenu_draw(short int n)
{
	setfillstyle(1,WHITE);
	switch(n)
	{
		case 1:
			clrmous(MouseX,MouseY);
			delay(10);
			bar(0,24,60,120);
			puthz(10,29,"��½",16,24,DARKGRAY);             //0,25,60,48
			puthz(10,53,"�˳�",16,24,DARKGRAY);             //0,48,60,72
			puthz(10,77,"ע��",16,24,DARKGRAY);             //0,72,60,96
			puthz(10,101,"����",16,24,DARKGRAY);             //0,96,60,120
			break;
		case 2:
			clrmous(MouseX,MouseY);
			delay(10);
			break;
		case 3:
			clrmous(MouseX,MouseY);
			delay(10);
			break;
		case 4:
			clrmous(MouseX,MouseY);
			delay(10);
			bar(180,24,260,72);                                //ѡ�ɲ˵�
			puthz(183,29,"������",16,18,DARKGRAY);                //180,25,260,48
			puthz(183,53,"������",16,18,DARKGRAY);                //180,48,260,72
		//	puthz(183,77,"����ѡ��",16,18,DARKGRAY);              //180,72,260,96
			break;
		case 5:
			clrmous(MouseX,MouseY);
			delay(10);
			bar(240,24,300,72);                                //���ײ˵�
			puthz(250,29,"����",16,24,DARKGRAY);                  //240,25,300,48
			puthz(250,53,"����",16,24,DARKGRAY);                  //240,48,300,72
			break;
		case 6:
			clrmous(MouseX,MouseY);
			delay(10);
			//bar(300,24,380,72);                                //���˲˵�
			//puthz(303,29,"�ʲ�",16,18,BLACK);                  //300,25,380,48
			//puthz(303,53,"��ѡ��",16,18,BLACK);                //300,48,380,72
			break;
	}
}

/************************************
FUNCTION: lightbutton_menu
DESCRIPTION: �˵��ĵ���
INPUT: cinfo->ord
RETURN: ��
*************************************/
void lightbutton_menu(short int ord)
{
	clrmous(MouseX, MouseY);
	delay(10);
	setfillstyle(1,LIGHTBLUE);
	switch(ord)
	{
		case 1:
			bar(0,24,60,48);
			puthz(10,29,"��½",16,24,WHITE);
			break;
		case 2:
			bar(0,48,60,72);
			puthz(10,53,"�˳�",16,24,WHITE);
			break;
		case 3:
			bar(0,72,60,96);
			puthz(10,77,"ע��",16,24,WHITE);
			break;
		case 4:
			bar(0,96,60,120);
			puthz(10,101,"����",16,24,WHITE);
			break;
		case 5:
			bar(180,24,260,48);
			puthz(183,29,"������",16,18,WHITE);
			break;
		case 6:
			bar(180,48,260,72);
			puthz(183,53,"������",16,18,WHITE);
			break;
	/*	case 7:
			bar(180,72,260,96);
			puthz(183,77,"����ѡ��",16,18,WHITE);
			break;*/
		case 8:
			bar(240,24,300,48);
			puthz(250,29,"����",16,24,WHITE); 
			break;
		case 9:
			bar(240,48,300,72);
			puthz(250,53,"����",16,24,WHITE);
			break;
	}
}

/*****************************************
FUNCTION: recoverbutton_menu
DESCRIPTION: �Ӳ˵��Ļָ�
INPUT: cinfo->ord_last
RETURN: ��
*****************************************/
void recoverbutton_menu(short int ord_last)
{	
	clrmous(MouseX, MouseY);
	setfillstyle(1,WHITE);
	switch(ord_last)
	{
		case 1:
			bar(0,24,60,48);
			puthz(10,29,"��½",16,24,DARKGRAY);
			break;
		case 2:
			bar(0,48,60,72);
			puthz(10,53,"�˳�",16,24,DARKGRAY); 
			break;
		case 3:
			bar(0,72,60,96);
			puthz(10,77,"ע��",16,24,DARKGRAY); 
			break;
		case 4:
			bar(0,96,60,120);
			puthz(10,101,"����",16,24,DARKGRAY);
			break;
		case 5:
			bar(180,24,260,48);
			puthz(183,29,"������",16,18,DARKGRAY);                
			break;
		case 6:
			bar(180,48,260,72);
			puthz(183,53,"������",16,18,DARKGRAY);
			break;
	/*	case 7:
			bar(180,72,260,96);
			puthz(183,77,"����ѡ��",16,18,DARKGRAY); 
			break;*/
		case 8:
			bar(240,24,300,48);
			puthz(250,29,"����",16,24,DARKGRAY);
			break;
		case 9:
			bar(240,48,300,72);
			puthz(250,53,"����",16,24,DARKGRAY);
			break;
	}
}

/******************************************
FUNCTION: draw_stoqueue
DESCRIPTION: ���ƻ������
INPUT: void
RETURN: ��
******************************************/
void draw_stoqueue(void)//����	����	�Ƿ�%	�ּ�	�ǵ�	���	����	����	����	����%	����%	��
{
	setbkcolor(BLACK);
	puthz(5, 30, "����", 16, 17, LIGHTGRAY);
	puthz(60, 30, "����", 16, 17, LIGHTGRAY);

	puthz(115, 30, "�Ƿ�", 16, 17, LIGHTGRAY);
	setcolor(LIGHTGRAY);
	settextjustify(LEFT_TEXT, TOP_TEXT);
	settextstyle(1, HORIZ_DIR, 1);
	outtextxy(148, 25, "%");

	puthz(172, 30, "�ּ�", 16, 17, LIGHTGRAY);
	puthz(220, 30, "�ǵ�", 16, 17, LIGHTGRAY);
	puthz(270, 30, "���", 16, 17, LIGHTRED);
	puthz(320, 30, "����", 16, 17, LIGHTGREEN);
	puthz(377, 30, "����", 16, 17, LIGHTGRAY);
	puthz(440, 30, "����", 16, 17, LIGHTGRAY);

	puthz(488, 30, "����", 16, 17, LIGHTRED);
	setcolor(LIGHTRED);
	settextjustify(LEFT_TEXT, TOP_TEXT);
	settextstyle(1, HORIZ_DIR, 1);
	outtextxy(521, 25, "%");

	puthz(540, 30, "����", 16, 17, LIGHTGRAY);
	setcolor(LIGHTGRAY);
	settextjustify(LEFT_TEXT, TOP_TEXT);
	settextstyle(1, HORIZ_DIR, 1);
	outtextxy(573, 25, "%");

	puthz(597, 30, "��", 16, 17, LIGHTGRAY);
	setlinestyle(SOLID_LINE, 0, 1);
	line(45, 24, 45, 456);
	line(112, 24, 112, 456);
	line(162, 24, 162, 456);
	line(210, 24, 210, 456);
	line(260, 24, 260, 456);
	line(310, 24, 310, 456);
	line(360, 24, 360, 456);
	line(425, 24, 425, 456);
	line(483, 24, 483, 456);
	line(537, 24, 537, 456);
	line(587, 24, 587, 456);
	line(0, 456, 640, 456);
}

/*****************************************
FUNCTION: control_judge
DESCRIPTION: �ж��û�״̬
INPUT: u
RETURN: ��
*****************************************/
void control_judge(USER* u)
{
	setfillstyle(1, LIGHTGRAY);
	bar(560, 1, 640, 23);          //�ڸ�
	if(strlen(u->user) == 0)
	{
		puthz(566,5,"�ο�״̬",16,17,LIGHTCYAN);
	}
	else
	{
		puthz(566,5,"�û���¼",16,17,LIGHTBLUE);
	}
}

/*********************************
FUNCTION: cpop
DESCRIPTION: ������ʾ
INPUT: i
RETURN: ��
**********************************/
void cpop(int i)
{
	clrmous(MouseX, MouseY);
	if(i == 1)
	{
		setfillstyle(SOLID_FILL, LIGHTGRAY);
		bar(180, 150, 460, 330);
		setfillstyle(SOLID_FILL, LIGHTRED);
		bar(200, 170, 440, 310);
		puthz(250, 200, "���ȵ�¼", 16, 20, YELLOW);
		puthz(250, 260, "����", 16, 20, YELLOW);
		settextjustify(LEFT_TEXT, TOP_TEXT);
		settextstyle(2, HORIZ_DIR, 6);
		setcolor(WHITE);
		outtextxy(295, 260, "3");
		puthz(310, 260, "��󷵻�", 16, 20, YELLOW);
		delay(1000);
		setfillstyle(SOLID_FILL, LIGHTRED);
		bar(295, 260, 308, 273);
		outtextxy(295, 260, "2");
		delay(1000);
		bar(295, 260, 308, 273);
		outtextxy(295, 260, "1");
		delay(1000);
	}
	else if(i == 2)
	{
		setfillstyle(SOLID_FILL, LIGHTGRAY);
		bar(180, 150, 460, 330);
		setfillstyle(SOLID_FILL, LIGHTRED);
		bar(200, 170, 440, 310);
		puthz(250, 200, "���ȿ���", 16, 20, YELLOW);
		puthz(250, 260, "����", 16, 20, YELLOW);
		settextjustify(LEFT_TEXT, TOP_TEXT);
		settextstyle(2, HORIZ_DIR, 6);
		setcolor(WHITE);
		outtextxy(295, 260, "3");
		puthz(310, 260, "��󷵻�", 16, 20, YELLOW);
		delay(1000);
		setfillstyle(SOLID_FILL, LIGHTRED);
		bar(295, 260, 308, 273);
		outtextxy(295, 260, "2");
		delay(1000);
		bar(295, 260, 308, 273);
		outtextxy(295, 260, "1");
		delay(1000);
	}
}