#include"public.h"
#include"queue.h"
#include"database.h"

/*****************************************
queue.c
COPYRIGHT:	weijingmin
FUNCTION:	extract info to hushenqueue
ABSTRACT:
		A.extract stock info from hushen
		B.create circle line
DATE:2019/9/23
******************************************/

/*********************************************
FUNCTION:initqueue
DESCRIPTION�������Ź�Ʊ��Ϣ�Ķ���
INPUT:Q
RETURN:��
***********************************************/
void initqueue(StoQueue* Q)
{
	Q->base = (Stodata*)malloc(MAXQSIZE * sizeof(Stodata));
	if (!Q->base)
	{
		printf("memory allocation runs wrong in queue.c");
		delay(2000);
		closegraph();
		exit(1);
	}
	Q->front = Q->rear = 0;
	inputqueue(Q, 0);
	return;
}

/*********************************************
FUNCTION:inputqueue
DESCRIPTION�����и�ֵ
INPUT:Q,k
RETURN:��
***********************************************/
void inputqueue(StoQueue* Q,int k)
{
	FILE* fp = NULL;
	int i, j;
	int m = 0;
	Q->rear = 0;
	if ((fp = fopen("Database\\1.dat", "rb")) == NULL)
	{
		printf("cannot open file 1.dat");
		delay(2000);
		exit(1);
	}
	for (i = 0; i < MAXQSIZE; i++)          //һ�ζ�ʮֻ
	{
		memset(Q->base+Q->rear, '\0', sizeof(Stodata));
		j = enqueue(Q, fp, m, k);//jΪһ�еĳ���+1('\n')
		k =k + j;//kΪ�ļ�ָ���ڲ�λ��
		m += 20;  //y+20
		Q->rear = (Q->rear + 1) % (MAXQSIZE);
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
FUNCTION:enqueue
DESCRIPTION����ͷ���β���Ԫ�أ�
	���·�ҳ��ͷָ�븳ֵ�����Ϸ�ҳ��βָ�븳ֵ
INPUT:q,fp1,line,prelen
RETURN:len
***********************************************/
int enqueue(StoQueue* q, FILE* fp1, int line, int prelen)
{   //��ÿ�е�
	int i = 0;
	int item = 1;
	int m = 0;
	int len = 0;
	char ch = '0';
	setcolor(LIGHTGRAY);
	settextjustify(LEFT_TEXT, TOP_TEXT);
	settextstyle(0, HORIZ_DIR, 1);
	while (ch != '\n')
	{
		fseek(fp1, i * sizeof(char)+prelen, SEEK_SET);
		fread(&ch, sizeof(char), 1, fp1);
		len++;
		i++;//����һ�еĳ���
	}
	for (i = 0; i < len; i++)
	{
		fseek(fp1, i * sizeof(char) + prelen, SEEK_SET);
		fread(&ch, sizeof(char), 1, fp1);
		//����	����	�Ƿ�%	�ּ�	�ǵ�	���	����	����	����	����%	����%	��
		if (ch != '\t' && ch != '\n' && ch != '\r' && ch != ' ')
		{
			/*if (item == 0)//����
			{
				q->base[q->rear].number[m] = ch;
			}*/
			if (item == 1)
			{
				q->base[q->rear].code[m] = ch;
			}
			else if (item == 2)
			{
				q->base[q->rear].name[m] = ch;
			}
			else if (item == 3)
			{
				q->base[q->rear].dat1[m] = ch;
			}
			else if (item == 4)
			{
				q->base[q->rear].dat2[m] = ch;
			}
			else if (item == 5)
			{
				q->base[q->rear].dat3[m] = ch;
			}
			else if (item == 6)
			{
				q->base[q->rear].dat4[m] = ch;
			}
			else if (item == 7)
			{
				q->base[q->rear].dat5[m] = ch;
			}
			else if (item == 8)
			{
				q->base[q->rear].dat6[m] = ch;
			}
			else if (item == 9)
			{
				q->base[q->rear].dat7[m] = ch;
			}
			else if (item == 10)
			{
				q->base[q->rear].dat8[m] = ch;
			}
			else if (item == 11)
			{
				q->base[q->rear].dat9[m] = ch;
			}
			else if (item == 12)
			{
				q->base[q->rear].dat10[m] = ch;
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
	outtextxy(0, 55 + line, q->base[q->rear].code);

	if (q->base[q->rear].name[0] >= '!' && q->base[q->rear].name[0] <= 'z')
	{
		outtextxy(47, 50 + line + 5, "*ST");
		puthz(47+24, 50 + line, q->base[q->rear].name+3, 16, 17, YELLOW);
	}
	else
	{
		puthz(47, 50 + line, q->base[q->rear].name, 16, 17, YELLOW);
	}

	if (q->base[q->rear].dat1[0] == '-')
	{
		setcolor(GREEN);
	}
	else
	{
		setcolor(RED);
	}
	outtextxy(114, 55 + line, q->base[q->rear].dat1);//�Ƿ�
	setcolor(LIGHTGRAY);
	outtextxy(164, 55 + line, q->base[q->rear].dat2);//�ּ�

	if (q->base[q->rear].dat3[0] == '-')
	{
		setcolor(GREEN);
	}
	else
	{
		setcolor(RED);
	}
	outtextxy(214, 55 + line, q->base[q->rear].dat3);//�ǵ�

	setcolor(LIGHTGRAY);
	outtextxy(264, 55 + line, q->base[q->rear].dat4);//���
	outtextxy(314, 55 + line, q->base[q->rear].dat5);//����
	
	setcolor(YELLOW);
	outtextxy(364, 55 + line, q->base[q->rear].dat6);//����
	
	setcolor(MAGENTA);
	outtextxy(429, 55 + line, q->base[q->rear].dat7);//����
	
	if (q->base[q->rear].dat8[0] == '-')
	{
		setcolor(GREEN);
	}
	else
	{
		setcolor(RED);
	}
	outtextxy(487, 55 + line, q->base[q->rear].dat8);//����

	setcolor(LIGHTGRAY);
	outtextxy(541, 55 + line, q->base[q->rear].dat9);//����
	
	outtextxy(591, 55 + line, q->base[q->rear].dat10);//��
	return len;
}


/*int dequeue(StoQueue* q, int flag)//ɾ������
{
	if (q->front == q->rear)
	{
		printf("queue full!");
		delay(2000);
		exit(1);
	}
	switch(flag)
	{
		case 1:
			q->front = (q->front + 1) % MAXQSIZE;//���·�ҳʱ��βָ��+1
			break;
		case 2:
			q->rear = (q->rear - 1);//���Ϸ�ҳʱ��ͷָ��-1
			if (q->rear == -1)
			{
				q->rear = 20;
			}
			break;
	}
	return 1;
}*/

/*********************************************
FUNCTION:destroyqueue
DESCRIPTION�����ٶ���
INPUT:q
RETURN:��
***********************************************/
void destroyqueue(StoQueue* q)
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
}

/*********************************************
FUNCTION:countqueue
DESCRIPTION����ÿһҳ�ж೤
INPUT:k
RETURN:k(һҳ�ļ���λ��)
***********************************************/
int countqueue(int k)
{
	FILE* fp = NULL;
	int i, j;
	if ((fp = fopen("Database\\1.dat", "rb")) == NULL)
	{
		printf("cannot open file 1.dat");
		delay(2000);
		exit(1);
	}
	fseek(fp, k, SEEK_SET);
	for (i = 0; i < MAXQSIZE; i++)
	{
		j = countline(fp, k);//jΪһ�еĳ���+1('\n')
		k = k + j;//kΪ�ļ�ָ���ڲ�λ��
	}
	if (fclose(fp) != 0)
	{
		printf("cannot close 1.dat");
		delay(2000);
		exit(1);
	}
	return k;
}

/*********************************************
FUNCTION:countline
DESCRIPTION����ÿ���ж೤
INPUT:fp1,prelen
RETURN:len
***********************************************/
int countline(FILE* fp1, int prelen)
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