#include"public.h"
#include"qsearch.h"
#include"database.h"
#include"control.h"
#include"market.h"
#include"techline.h"
#include"storead.h"
#include"marketfc.h"


/*******************************
qsearch.c
COPYRIGHT:	weijingmin
FUNCTION:	for skip and search
ABSTRACT:
		A.hushen->market
		B.marketstochange
DATE:2019/10/31
********************************/

/*********************************************
FUNCTION:output_stoname
DESCRIPTION�����������ӡ��ϣ���Ҷ�Ӧ�Ĺ�Ʊ��
INPUT:name
RETURN:��
***********************************************/
void output_stoname(char* name)
{
	settextjustify(LEFT_TEXT, TOP_TEXT);
	settextstyle(2, HORIZ_DIR, 6);
	setcolor(LIGHTMAGENTA);
	if (name[0] >= '!' && name[0] <= 'z')
	{
		outtextxy(4, 124 - 2, "*ST");
		puthz(4 + 28, 124, name + 3, 16, 17, LIGHTMAGENTA);
	}
	else
	{
		puthz(4, 124, name, 16, 17, LIGHTMAGENTA);
	}
}

/*********************************************
FUNCTION:search_name
DESCRIPTION����ϣ˳����ң�sto_num�ؼ���ȫƥ��
INPUT:sto_num,search_name
RETURN:��
***********************************************/
void search_name(int sto_num, char* search_name)
{
	int i, j;
	long int len;
	FILE* fp = NULL;
	char ch = '0';
	char name[20] = { 0 };//������ȡ���ַ���
	int item = 1;
	int m = 0;//�ַ����
	int line = 0;//�ؼ���
	if ((fp = fopen("Database\\name.dat", "rb")) == NULL)
	{
		printf("cannot open num.dat");
		delay(3000);
		exit(1);
	}
	//memset(search_name, '\0', sizeof(search_name));
	fseek(fp, 0, SEEK_END);
	len = ftell(fp);
	for (i = 0; i < len; i++)
	{
		fseek(fp, i * sizeof(char), SEEK_SET);
		fread(&ch, sizeof(char), 1, fp);
		if (ch != '\t' && ch != '\n' && ch != '\r' && ch != ' ')
		{
			if (item == 1);
			else if (item == 2)
			{
				name[m] = ch;
			}
		}
		m++;
		if (ch == '\t')
		{
			item++;
			m = 0;
		}
		else if (ch == '\n' || i == len && item == 2)//��һ�ж�����
		{
			line++;
			if (line == sto_num)//��ϣ˳����ң��ؼ���ȫƥ��
			{
				strcpy(search_name, name);//�����ƿ�����search_name�ĵ�ַ
				/*for (j = 0; j < strlen(name); j++)
				{
					search_name[j] = name[j];
				}*/
				break;
			}
			else
			{
				memset(name, '\0', sizeof(name));
				item = 1;
				m = 0;//��������һ��
			}
		}
	}
	if (fclose(fp) != 0)
	{
		printf("cannot close num.dat");
		delay(3000);
		exit(1);
	}
}

/*********************************************
FUNCTION:queueup
DESCRIPTION���������·�������sto_No��ÿһҳ��ֵ
INPUT:sto,sto_No,queuesize
RETURN:��
***********************************************/
void queueup(int* sto, int* sto_No,int queuesize)
{
	int i;
	if (*sto == queuesize + 1)
	{
		*sto = 201 - queuesize; //��Ʊ����һ�棬�´θ�ֵҪ�����һ�濪ʼ
	}
	else if ((*sto) - queuesize * 2 >= 1)
	{
		(*sto) -= (queuesize * 2);
	}
	for (i = 0; i < queuesize; i++)
	{
		sto_No[i] = *sto;
		(*sto)+=1;
	}
}

/*********************************************
FUNCTION:queueup
DESCRIPTION���������Ϸ�������sto_No��ÿһҳ��ֵ
INPUT:sto,sto_No,queuesize
RETURN:��
***********************************************/
void queuedown(int* sto, int* sto_No, int queuesize)
{
	int i;
	if (*sto == 201)
	{
		*sto = 1;//��Ʊ�����һ�棬��ֵҪ�ӵ�һ�濪ʼ
	}
	for (i = 0; i < queuesize; i++)
	{
		sto_No[i] = *sto;
		(*sto)+=1;
	}
}

/*********************************************
FUNCTION:change_sto
DESCRIPTION���ı���ʾ�Ĺ�Ʊ
INPUT:sto_num,pos,No_date,
	info,upinfo,downinfo,max,min
RETURN:��
***********************************************/
void change_sto(int* sto_num, int* pos, int No_date, STODAYFLOAT info[], UPLINE* upinfo, DOWNLINE* downinfo, float* max, float* min)//posΪ�����һ���Ʊ��ŵ�����
{
	int i = 0, j;
	//int maxline = 0;
	if (mouse_press(0, 144, 72, 432) == 1)
	{
		i = (MouseY - 144) / 36;
		*sto_num = pos[i];
	}
	//maxline = check_database(*sto_num);//�µ����ݿ�ĩ�˵��������ظ�maxline
	clrmous(MouseX, MouseY);
	setfillstyle(SOLID_FILL, BLACK);
	for (j = 0; j < 8; j++)
	{
		bar(60, 145 + 36 * j, 71, 145 + 36 * j + 7);//����ԭ���
	}
	setfillstyle(SOLID_FILL, LIGHTBLUE);
	bar(60, 145 + 36 * i, 71, 145 + 36 * i + 7);
	setcolor(RED);
	line(60, 145 + 36 * i, 60, 145 + 36 * i + 7);
	line(60, 145 + 36 * i + 7, 71, 145 + 36 * i + 7);//���
	/*if (No_date >= maxline - 150)
	{
		No_date = maxline - 300;//����Ʊ����������ͬ����������µ����ݿ��β�ˣ���Ҫ--��
	}*/
	sto_daybyday2float(*sto_num, No_date, 150, info);//1Ϊ��Ʊ��ţ�1Ϊ��ʼ������150Ϊ��ȡ����
	get_border(info, max, min, 150);//150Ϊ��ȡ����
	setfillstyle(SOLID_FILL, BLACK);
	bar(81, 73, 619, 341);
	bar(81, 343, 619, 455);//�ڸ�֮ǰ����ͼ��ͼͼ��
	for (i = 0; i < 11; i++)
	{
		for (j = 0; j < 135; j++)
		{
			putpixel(80 + 4 * j, 72 + 40 * i, RED);
		}
	}
	Kline_draw(info, *max, *min);
	MA_draw(info, upinfo, *max, *min);
	VOL_draw(info, downinfo);

	//return maxline;
}

/*********************************************
FUNCTION:queuesearch
DESCRIPTION��������ǣ���������������ת
INPUT:sto_No,pre_k,k
RETURN:0/sto_num
***********************************************/
int queuesearch(int* sto_No, int* pre_k, int* k)
{
	int j;
	int sto_num = 0;//���������Ĳ���
	delay(10);
	clrmous(MouseX, MouseY);
	setlinestyle(SOLID_LINE, 0, 1);
	setcolor(BLACK);
	for (j = 1; j <= 20; j++)
	{
		line(0, 50 + 20 * j, 640, 50 + 20 * j);
	}//����֮ǰ��
	*pre_k = *k;
	*k = (MouseY - 50) / 20 + 1;
	setcolor(YELLOW);
	line(0, 50 + 20 * (*k), 640, 50 + 20 * (*k));//���λ��
	save_bk_mou(MouseX, MouseY);
	drawmous(MouseX, MouseY);
	delay(300);//����Ҫ�ܴ󣬲�Ȼpre_k��k���ж���ܿ죡����
	if (*pre_k == *k)
	{
		sto_num = sto_No[*k-1];
		//cinfo->func = 8;
		//sto_market(cinfo, u, sto_num); //���޷���ת����
		return sto_num;
	}
	return 0;
}
