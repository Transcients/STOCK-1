#include"public.h"
#include"open.h"
#include"lgfunc.h"
#include"control.h"


/***********************************************
opaccount.c
COPYRIGHT: 	dengshumin
FUNCTION: open a new account
ABSTRACT:
		A.open account for user
		B.button lighting and recovering
DATE: 2019/9/22
************************************************/


/*******************************************************************
FUNCTION: opaccount
DESCRIPRION: ��������,���ѿ��������뵯����δ��������п�������
INPUT: cinfo,u
RETURN: ��
********************************************************************/
void opaccount(Ctr* cinfo,USER* u)
{
	int num = 0;              //��ť��
	char B[21] = {0};   //Bankcard
	char BP[8] = {0};
	char BCP[8] = {0};
	short int state1 = 0;
	short int state2 = 0;
	short int state3 = 0;
	memset(cinfo,0,sizeof(Ctr));   //��������Ϣ��ʼ��
	cinfo->func = 1;          //��1��ǿ��������Ľ���
	clrmous(MouseX,MouseY);
	delay(10);
	if(strlen(u->bankcard) == 0)    //δ����
	{
		cleardevice();
		mainmenu_draw();
		control_judge(u);
		draw_opaccount();
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
				draw_opaccount();
				submenu_draw(cinfo->itemnum);
			}
			if(cinfo->func != 1 && cinfo->func != 12)
			{
				clrmous(MouseX,MouseY);
				delay(10);                    //��ֹ����
				return;  //��������������ܼ����ͷ��أ�����ǻ��ԭ����������ж�
			}
			if(MouseX>100&&MouseX<540&&MouseY>120&&MouseY<145)
			{ //���п��ſ�
				if(mouse_press(100,120,540,145) == 2)
				{
					MouseS = 2;
					if(num == 0 && state1 == 0)
					{
						lightbutton_opa( 100, 120, 540, 145, RED, LIGHTGRAY,1);
						num = 1;
					}
					continue;
				}
				else if(mouse_press(100,120,540,145) == 1)
				{
					MouseS = 0;//����
					lightbutton_opa( 100, 120, 540, 145, RED, LIGHTGRAY,1);
					B[0] = '\0';
					inputadmin(B,100,120,19,LIGHTGRAY);
					if(strlen(B) != 0 )
						state1 = 1;
					else	
						state1 = 0;
					continue;
				}
			}
			if(MouseX>100&&MouseX<540&&MouseY>190&&MouseY<215)
			{ //���п������
				if(mouse_press(100,190,540,215) == 2)
				{
					MouseS = 2;
					if(num == 0 && state2 == 0)
					{
						lightbutton_opa(100,190,540,215,RED,LIGHTGRAY,2);
						num = 2;
					}
					continue;
				}
				else if(mouse_press(100,190,540,215) == 1)
				{
					MouseS = 0;
					lightbutton_opa(100,190,540,215,RED,LIGHTGRAY,2);
					BP[0] = '\0';
					inputpassword(BP,100,190,6,LIGHTGRAY);
					if(strlen(BP) != 0)
						state2 = 1;
					else 
						state2 = 0;
					continue;   //����
				}
			}
			if(MouseX > 100 && MouseX < 540 && MouseY > 260 && MouseY<285)
			{ //ȷ�������
				if(mouse_press(100,260,540,285) == 2)
				{
					MouseS = 2;
					if(num == 0 && state3 == 0)
					{
						lightbutton_opa(100,260,540,285,RED,LIGHTGRAY,3);
						num = 3;
					}
					continue;
				}
				else if(mouse_press(100,260,540,285) == 1)
				{
					MouseS = 0;
					lightbutton_opa(100,260,540,285,RED,LIGHTGRAY,3);
					BCP[0] = '\0';
					inputpassword(BCP,100,260,6,LIGHTGRAY);
					if(strlen(BCP) != 0)
						state3 = 1;
					else 
						state3 = 0;
					continue ; //����
				}
			}
			if(MouseX > 143 && MouseX <237 && MouseY > 350 && MouseY <380)
			{   //����
				if(mouse_press(143,350,237,380) == 2)
				{
					if(num == 0)
					{
						MouseS = 1;
						lightbutton_opa(143,350,237,380,WHITE,GREEN,4);
						num = 4;
					}
					continue;
				}
				else if(mouse_press(143,350,237,380) == 1)
				{
					MouseS = 0;
					clrmous(MouseX,MouseY);
					cleardevice();
					delay(10);
					mainmenu_draw();
					control_judge(u);
					draw_opaccount();
					num = 0;
					B[0] = '\0';
					BP[0] = '\0';
					BCP[0] = '\0';
					state1 = 0;
					state2 = 0;
					state3 = 0;
					continue;
				}
			}
			if(MouseX>273 && MouseX < 367 && MouseY > 350 && MouseY <380)
			{   //����
				if(mouse_press(273,350,367,380) == 2)
				{
					if(num == 0)
					{
						MouseS = 1;
						lightbutton_opa(273,350,367,380,WHITE,RED,5);
						num = 5;
					}
					continue;
				}
				else if(mouse_press(273,350,367,380) == 1)
				{
					MouseS = 0;
					if(opaccount_complete(B,BP,BCP,u))
					{
						cinfo->func = 0;
						return ;
					}
					else
					{
						continue;
					}
				}
			}
			if(MouseX > 403 && MouseX < 497 && MouseY > 350 && MouseY <380)
			{   //����
				if(mouse_press(403,350,497,380) == 2)
				{
					if(num == 0)
					{
						MouseS = 1;
						lightbutton_opa(403,350,497,380,WHITE,BLUE,6);
						num = 6;
					}
					continue;
				}
				else if(mouse_press(403,350,497,380) == 1)
				{
					MouseS = 0;
					cinfo->func = 0;
					return ;
				}
			}	
			if(num != 0)
			{
				if (state1 == 0)
					recoverbutton_opa(1);
				if (state2 == 0)
					recoverbutton_opa(2);
				if (state3 == 0)
					recoverbutton_opa(3);
				if (num == 4 || num == 5 || num == 6)
					recoverbutton_opa(num);
				num = 0;
			}
			if(MouseS != 0)
			{
				MouseS = 0;
			}
		}
	}
	else          //�ѿ���
	{
		draw_exist();
		while (1)
		{
			if(!bioskey(1))
			{
				newmouse(&MouseX, &MouseY, &press);
				control_mouse(cinfo,u);
			}
			else if(bioskey(1))
			{
				cinfo->key = bioskey(0);
			}
			control_key(cinfo);
			if(control_menu(cinfo))
			{
				draw_exist();
			}
			if(cinfo->func != 1)
			{
				clrmous(MouseX,MouseY);     //��ֹ���� 
				return;  //������˹��ܼ����ͷ��أ�����ǻ��ԭ����������ж�
			}
			if(mouse_press(280,240,360,280) == 2)    //δ���ȷ�Ͽ�
			{
				if(num == 0)
				{
					MouseS = 1;
					lightbutton_opa(280,240,360,280,WHITE,RED,7);
					num = 7;
				}
				continue;
			}
			else if(mouse_press(280,240,360,280) == 1)
			{
				MouseS = 0;
				cinfo->func = 0;
				break;
			}
			if(num != 0)
			{
				recoverbutton_opa(num);
				num = 0;
			}
			if(MouseS != 0)
			{
				MouseS = 0;
			}
		}
	}
	return;
}

/**********************************
FUNCTION: draw_opaccount
DESCRIPRION: ���ƿ�������
INPUT: void
RETURN: ��
**********************************/
void draw_opaccount(void)
{
	setbkcolor(BLACK);
	setcolor(WHITE);
	setfillstyle(1,WHITE);
	settextjustify(LEFT_TEXT,TOP_TEXT);
	settextstyle(1,HORIZ_DIR,2);
	
	puthz(100,100,"���п��ţ�ӦΪ",16,17,WHITE);
	outtextxy(219,94,"19");
	puthz(248,100,"λ��",16,17,WHITE);
	bar(100,120,540,145);
	
	puthz(100,170,"���루ӦΪ",16,17,WHITE);
	outtextxy(188,164,"6");
	puthz(202,170,"λ��",16,17,WHITE);
	bar(100,190,540,215);
	
	puthz(100,240,"ȷ������",16,17,WHITE);
	bar(100,260,540,285);
	
	setfillstyle(1, GREEN);
	bar(143, 350, 237, 380);
	puthz(161, 353, "����", 24, 34, WHITE);
	
	setfillstyle(1, RED);
	bar(273, 350, 367, 380);
	puthz(291, 353, "����", 24, 34, WHITE);
	
	setfillstyle(1, BLUE);
	bar(403, 350, 497, 380);
	puthz(421, 353, "����", 24, 34, WHITE);
	
	setfillstyle(1,LIGHTGRAY);
	bar(0,480,640,456);
}

/**************************************
FUNCTION: draw_exist
DESCRIPRION: ���Ƶ����˳���ʾ
INPUT: void
RETURN: ��
**************************************/
void draw_exist(void)
{
	setfillstyle(1,LIGHTGRAY);
	bar(165,155,475,315);
	setfillstyle(1,RED);
	bar(170,160,470,310);
	puthz(193,190,"���ѿ���������ȷ�ϰ�ť�˳�",16,18,YELLOW);
	setfillstyle(1,LIGHTRED);
	bar(280,240,360,280);
	puthz(295,249,"ȷ��",24,26,BLUE);
}

/******************************************
FUNCTION: lightbutton_opa
DESCRIPRION: ��������ĵ���
INPUT: x,y,x1,y1,color1,color2,flag
RETURN: ��
*******************************************/
void lightbutton_opa(int x, int y, int x1, int y1, int color1, int color2, int flag)
{
	clrmous(MouseX, MouseY);
	delay(10);
	setcolor(color1);
	setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
	setfillstyle(1, color2);
	bar(x, y, x1, y1);
	rectangle(x, y, x1, y1);	//���߿�

	if (flag == 4)
	{
		puthz(161, 353, "����", 24, 34, LIGHTGREEN);
	}
	else if (flag == 5)
	{
		puthz(291, 353, "����", 24, 34, LIGHTRED);
	}
	else if (flag == 6)
	{
		puthz(421, 353, "����", 24, 34, LIGHTBLUE);
	}
	else if (flag == 7)
	{
		puthz(295, 249, "ȷ��", 24, 26, LIGHTRED);
	}
}

/**************************************************
FUNCTION: recoverbutton_opa
DESCRIPRION: ��������ָ� 
INPUT: status
RETURN: ��
**************************************************/
void recoverbutton_opa(int status)
{
	delay(10);
	clrmous(MouseX, MouseY);
	setfillstyle(1, WHITE);
	switch (status)
	{
	case 1:
		bar(100, 120, 540, 145);
		break;
	case 2:
		bar(100, 190, 540, 215);
		break;
	case 3:
		bar(100, 260, 540, 285);
		break;
	case 4:
		setfillstyle(1, GREEN);
		bar(143, 350, 237, 380);
		puthz(161, 353, "����", 24, 34, WHITE);
		break;
	case 5:
		setfillstyle(1, RED);
		bar(273, 350, 367, 380);
		puthz(291, 353, "����", 24, 34, WHITE);
		break;
	case 6:
		setfillstyle(1, BLUE);
		bar(403, 350, 497, 380);
		puthz(421, 353, "����", 24, 34, WHITE);
		break;
	case 7:
		setfillstyle(1,LIGHTRED);
		bar(280,240,360,280);
		puthz(295,249,"ȷ��",24,26,BLUE);
		break;
	}
}

/******************************
FUNCTION: opaccount_complete
DESCRIPRION: ��������Լ��ж�
INPUT: b,bp,bcp,u
RETURN: ��
******************************/
int opaccount_complete(char* b,char* bp,char* bcp,USER* u)
{
	int i;
	int state1 = 0;            //���п��������ʽ�Ƿ���ȷ�ı���
	int state2 = 0;            //���п����������ʽ�Ƿ���ȷ�ı���
	int state3 = 0;            //ȷ�����������ʽ�Ƿ���ȷ�ı���
	while(1)
	{
		setfillstyle(1,BLACK);
		bar(396,100,540,116);
		bar(443,170,540,186);
		bar(455,240,540,256);
		judge(b, &state1,490,100);
		judge(bp,&state2,490,170);
		judge(bcp, &state3, 490, 240);
		if(state1 == 1 || state2 == 1 || state3 == 1)
			break;
		else if(state1 == 0&&state2 == 0&&state3 == 0)  //ȫ��������
		{
			if(judge_samecredit(b,1))          //�ѿ�������0��δ��������1
			{
				state1 = checkright_bankcard(b);
				state2 = checkright_bankpassword(bp);
				state3 = checkright_bankconfirmedpassword(bp,bcp);
				if(state1 != 0 || state2 != 0 || state3 != 0)
				{
					break;
				}
				else if(state1 == 0 && state2 == 0 && state3 == 0)
				{
					if(input_database_bk(b,bp,u))
					{
						puthz(280,390,"�����ɹ���",16,17,RED);
						delay(2000);
						return 1;
					}
					else
					{
						printf("Something Wrong");
						delay(2000);
						exit(1);
					}
				}
			}
			else if(judge_samecredit(b,1))
			{
				state1 = checkright_bankcard(b);
				state2 = checkright_bankpassword(bp);
				state3 = checkright_bankconfirmedpassword(bp,bcp);
				break;
			}
		}
	}
	return 0;
}

/**********************************************
FUNCTION: checkright_bankcard
DESCRIPRION: ������п����Ƿ�淶,��������ʾ
INPUT: b
RETURN: �淶�򷵻�1�����򷵻�0
**********************************************/
int checkright_bankcard(char* str)
{
	if(strlen(str) != 19)
	{
		setcolor(RED);
		settextjustify(LEFT_TEXT,TOP_TEXT);
		settextstyle(1,HORIZ_DIR,2);
		puthz(396,100,"���п���ӦΪ",16,17,RED);
		outtextxy(497,94,"19");
		puthz(524,100,"λ",16,17,RED);
		return 1;
	}  
	else
	{
		setcolor(BLUE);
		setlinestyle(SOLID_LINE,0,3);
		line(545,128,555,138);
		line(555,138,565,118);
		return 0;
	}
}

/*************************************************************
FUNCTION: checkright_bankpassword
DESCRIPRION: ������п������Ƿ�淶����������ʾ
INPUT: bp
RETURN: �淶�򷵻�1�����򷵻�0
*************************************************************/
int checkright_bankpassword(char* str)
{
	if(strlen(str) != 6)
	{
		setcolor(RED);
		settextjustify(LEFT_TEXT,TOP_TEXT);
		settextstyle(1,HORIZ_DIR,2);
		puthz(443,170,"����ӦΪ",16,17,RED);
		outtextxy(512,164,"6");
		puthz(524,170,"λ",16,17,RED);
		return 1;
	}
	else
	{
		setcolor(BLUE);
		setlinestyle(SOLID_LINE,0,3);
		line(545,198,555,208);
		line(555,208,565,188);
		return 0;
	}
}

/***************************************************
FUNCTION: checkright_bankconfirmedpassword
DESCRIPRION: ������������Ƿ�һ�£���������ʾ
INPUT: bp,bcp
RETURN: �淶�򷵻�1�����򷵻�0
***************************************************/
int checkright_bankconfirmedpassword(char* str1,char* str2)
{
	if(strcmp(str1, str2) != 0)
	{
		puthz(455 ,240,"���β�һ��",16,17,RED);
		return 1;
	}
	else 
	{
		setcolor(BLUE);
		setlinestyle(SOLID_LINE,0,3);
		line(545,268,555,278);
		line(555,278,565,258);
		return 0;
	}
}

/******************************************************
FUNCTION: judge_samecredit
DESCRIPRION: ���ÿ��Ƿ��ѱ�����
INPUT: new_credit,flag
RETURN: ���ѿ����򷵻�0�����򷵻�1
*******************************************************/
int judge_samecredit(char* new_credit,int flag)
{
	int len;
	int i;
	FILE* fp;
	USER* u = NULL;
	if ((fp = fopen("database\\UserData.dat", "rb+")) == NULL)//�������ݿ�
	{
		printf("cannot open file UserData.dat");
		delay(3000);
		exit(1);
	}
	fseek(fp, 0, SEEK_END);
	len = ftell(fp) / sizeof(USER);
	for (i = 0; i < len; i++)
	{
		if ((u = (USER*)malloc(sizeof(USER))) == NULL)
		{
			printf("memoryallocation runs wrong in opaccount.c");
			delay(3000);
			exit(1);
		}
		fseek(fp, i * sizeof(USER), SEEK_SET);
		fread(u, sizeof(USER), 1, fp);
		if(strcmp(u->bankcard,new_credit) == 0)
		{
			switch(flag)
			{
			case 1:
				puthz(455,100,"�ÿ��ѿ���",16,17,RED);
				break;
			case 2:
				break;
			default:
				//printf("something wrong");
				delay(3000);
				exit(1);
			}
			if (u != NULL)
			{
				free(u);
				u = NULL;
			}
			if(fclose(fp) != 0)
			{
				printf("\n cannot close Database.");
				delay(3000);
				exit(1);
			}
			return 0;
		}
		if(u != NULL)
		{
			free(u);
			u = NULL;
		}
	}
	if (u != NULL)
	{
		free(u);
		u = NULL;
	}

	if (fclose(fp) != 0)
	{
		printf("\n cannot close Database.");
		delay(3000);
		exit(1);
	}
	return 1;
}

/**************************************************
FUNCTION: input_database_bk
DESCRIPRION: ��������Ϣ�������ݿ���
INPUT: bankcard,bankcode,u
RETURN: ���뷵��1�����򷵻�0
**************************************************/
int input_database_bk(char* bankcard,char* bankcode,USER* us)
{
	int i;
	int len;
	FILE* fp;
	USER* u = NULL;
	if ((fp = fopen("database\\UserData.dat", "rb+" )) == NULL)
	{
		printf("cannot open file UserDat.dat");
		delay(3000);
		exit(1);
	}
	fseek(fp, 0, SEEK_END);//�ļ�ָ�붨λ�����һλ
	len = ftell(fp) / sizeof(USER);//�����û�����
	for (i = 0; i < len; i++)
	{
		if ((u = (USER*)malloc(sizeof(USER))) == NULL)
		{
			printf("memoryallocation runs wrong in opaccount.c");
			delay(3000);
			exit(1);
		}
		fseek(fp, i * sizeof(USER), SEEK_SET);//ÿ��������һ���û�
		fread(u, sizeof(USER), 1, fp);//����Ϣ����u
		if (strcmp(us->user, u->user) == 0)
		{
			strcpy(us->bankcard,bankcard);
			strcpy(us->bankpassword,bankcode);
			strcpy(u->bankcard,bankcard);
			strcpy(u->bankpassword,bankcode);
			fseek(fp, i * sizeof(USER), SEEK_SET);
			fwrite(u, sizeof(USER), 1, fp); //�޸����һ��Ҫ�ǵ�д������ ���Ĭ��Ϊ0
			if (u != NULL)
			{
				free(u);
				u = NULL;
			}
			if (fclose(fp) != 0)
			{
				printf("\n cannot close Database");
				exit(1);
			}
			delay(2000);
			return 1;
		}
		if (u != NULL)
		{
			free(u);
			u = NULL;
		}
	}
	if (u != NULL)
	{
		free(u);
		u = NULL;
	}
	if (fclose(fp) != 0)
	{
		printf("\n cannot close Database");
		exit(1);
	}
	return 0;
}