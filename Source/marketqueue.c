#include"public.h"
#include"market.h"


/*****************************************
marketqueue.c
COPYRIGHT:	weijingmin
FUNCTION:	extract info to marketqueue
ABSTRACT:
		A.extract stock info
		B.create circle line
DATE:2019/10/7
******************************************/


/*********************************************
FUNCTION:klinequeue
DESCRIPTION�������Ź�Ʊ��Ϣ�Ķ���
INPUT:Q
RETURN:��
***********************************************/
void klinequeue(MarketQueue* Q)
{
	/*Q->base = (Stoname*)malloc(MAXMARKETSIZE * sizeof(Stoname));
	if (!Q->base)
	{
		printf("memory allocation runs wrong");
		delay(2000);
		closegraph();
		exit(1);
	}*/
	Q->base->number=0;
	memset(Q->base->code,'\0',sizeof(Q->base->code));
	memset(Q->base->name,'\0',sizeof(Q->base->name));
	Q->front = Q->rear = 0;
	input_klinequeue(Q, 0);
	return;
}

/*********************************************
FUNCTION:input_klinequeue
DESCRIPTION�����и�ֵ
INPUT:Q,k
RETURN:��
***********************************************/
void input_klinequeue(MarketQueue* Q, int k)
{
	FILE* fp;
	int i, j;
	int m = 0;
	Q->rear = 0;
	if ((fp = fopen("Database\\name.dat", "rb")) == NULL)
	{
		printf("cannot open file stoname.dat");
		delay(2000);
		exit(1);
	}
	for (i = 0; i < MAXMARKETSIZE; i++)
	{
		Q->base[Q->rear].number = i;//����ù�Ʊλ����һҳ�ĵڼ���
		//memset(Q->base + Q->rear, '\0', sizeof(Stodata));
		memset(Q->base[Q->rear].code, '\0', 7 * sizeof(char));
		memset(Q->base[Q->rear].name, '\0', 10 * sizeof(char));
		j = en_klinequeue(Q, fp, m, k);//jΪһ�еĳ���+1('\n')
		k = k + j;//kΪ�ļ�ָ���ڲ�λ��
		m += 36;
		Q->rear = (Q->rear + 1) % (MAXMARKETSIZE);
	}

	if (fclose(fp) != 0)
	{
		printf("cannot close 1.dat");
		delay(2000);
		exit(1);
	}
	return;
}

/*********************************************
FUNCTION:input_klinequeue
DESCRIPTION����ͷ���β���Ԫ�أ�
	���·�ҳ��ͷָ�븳ֵ�����Ϸ�ҳ��βָ�븳ֵ
INPUT:q,fp1,line,prelen
RETURN:len
***********************************************/
int en_klinequeue(MarketQueue* q, FILE* fp1, int line, int prelen)
{
	int i = 0;
	int item = 0;
	int m = 0;
	int len = 0;
	char ch = '0';
	setcolor(LIGHTGRAY);
	settextjustify(LEFT_TEXT, TOP_TEXT);
	settextstyle(0, HORIZ_DIR, 1);
	while (ch != '\n')
	{
		fseek(fp1, i * sizeof(char) + prelen, SEEK_SET);
		fread(&ch, sizeof(char), 1, fp1);
		len++;
		i++;//����һ�еĳ���
	}
	for (i = 0; i < len; i++)
	{
		fseek(fp1, i * sizeof(char) + prelen, SEEK_SET);
		fread(&ch, sizeof(char), 1, fp1);
		if (ch != '\t' && ch != '\n' && ch != '\r' && ch != ' ')
		{
			if (item == 0)//����
			{
				q->base[q->rear].code[m] = ch;
			}
			if (item == 1)//����
			{
				q->base[q->rear].name[m] = ch;
			}
		}
		m++;
		if (ch == '\t')
		{
			m = 0;
			item++;
		}

		else if ((ch == '\n' || ch == '\r' || i == len) && item == 12)
		{
			break;
		}
	}
	setcolor(YELLOW);
	outtextxy(2, 148 + line, q->base[q->rear].code);

	if (q->base[q->rear].name[0] >= '!' && q->base[q->rear].name[0] <= 'z')
	{
		outtextxy(2, 158 + line + 5, "*ST");
		puthz(2 + 24, 158 + line, q->base[q->rear].name + 3, 16, 17, YELLOW);
	}
	else
	{
		puthz(2, 158 + line, q->base[q->rear].name, 16, 17, YELLOW);
	}
	return len;
}

/*void destroy_klinequeue(MarketQueue* q)//���ٶ���
{
	if ((q->base) != NULL)
	{
		free(q->base);
		q->base = NULL;
	}
	if (q != NULL)
	{
		free(q);
		q = NULL;
	}
}*/

/*********************************************
FUNCTION:count_klinequeue
DESCRIPTION����ÿһҳ�ж೤
INPUT:k
RETURN:k(һҳ�ļ���λ��)
***********************************************/
int count_klinequeue(int k)
{
	FILE* fp;
	int i, j;
	if ((fp = fopen("Database\\name.dat", "rb")) == NULL)
	{
		printf("cannot open file stoname1.dat");
		delay(2000);
		exit(1);
	}
	fseek(fp, k, SEEK_SET);
	for (i = 0; i < MAXMARKETSIZE; i++)
	{
		j = countline_kline(fp, k);//jΪһ�еĳ���+1('\n')
		k = k + j;//kΪ�ļ�ָ���ڲ�λ��
	}
	if (fclose(fp) != 0)
	{
		printf("cannot close 1.dat");
		delay(2000);
		exit(1);
	}
	return k;//һҳ�ļ���λ��
}

/*********************************************
FUNCTION:countline_kline
DESCRIPTION����ÿ���ж೤
INPUT:fp1,prelen
RETURN:len
***********************************************/
int countline_kline(FILE* fp1, int prelen)
{
	int len = 0;
	int i = 0;
	char ch = '0';
	while (ch != '\n')
	{
		fseek(fp1, i * sizeof(char) + prelen, SEEK_SET);
		fread(&ch, sizeof(char), 1, fp1);
		len++;
		i++;//����һ�еĳ���
	}
	return len;
}