#include"storead.h"
#include"public.h"
#include"database.h"

/*****************************************
stodayread.c
COPYRIGHT:	weijingmin
FUNCTION:	sto daybyday information
ABSTRACT:
		A.get one stock for 150 days
		B.change string to float and int
DATE:2019/10/12
******************************************/



/*int check_database(int sto_number)//���ظ����ݿ�����ֵ
{
	FILE* fp = NULL;
	long int len;
	long int i;
	int line = 0;
	char ch = '\0';
	char ctl[30] = "Database\\dayinfo\\", num[4] = { '\0' };//Ŀ¼
	itoa(sto_number, num, 10);//��Ʊ�������ת���������ļ���ȡ
	strcat(ctl, num);
	strcat(ctl, ".dat");


	if ((fp = fopen(ctl, "rb")) == NULL)
	{
		printf("cannot open dayinfo\\%d", sto_number);
		delay(3000);
		exit(1);
	}
	fseek(fp, 0, SEEK_END);
	len = ftell(fp);

	for (i = 0; i < len; i++)
	{
		fseek(fp, i * sizeof(char), SEEK_SET);
		fread(&ch, sizeof(char), 1, fp);
		if (ch == '\n')
		{
			line++;//�������ݿ������
		}
	}
	line -= 10;
	return line;
}*/

/*********************************************
FUNCTION:sto_daybyday2float
DESCRIPTION:��������������Ϣת��Ϊ������
INPUT:sto_num,No_date,read_days,info
RETURN:��
***********************************************/
void sto_daybyday2float(int sto_num, long int No_date, long int read_days, STODAYFLOAT info[])//Ҫ��ȡ������
{
	int i = 0;
	STODAYCHAR s[150];
	//STODAYCHAR* s = NULL;//sΪָ��ܶ����Ʊ��Ϣ��ָ��
	/*if ((info = (STODAYFLOAT*)malloc(read_days * sizeof(STODAYFLOAT))) == NULL)
	{
		printf("memoryallcation runs wrong");
		delay(3000);
		exit(1);
	}*/
	
	/*if ((s = (STODAYCHAR*)malloc(read_days * sizeof(STODAYCHAR))) == NULL)
	{
		printf("memoryallocation runs wrong");
		delay(3000);
		exit(1);
	}*/
	memset(s, '\0', 150 * sizeof(STODAYCHAR));

	sto_daybyday(sto_num, No_date, read_days, s);//����sto_daybyday
	for (i = 0; i < read_days; i++)
	{
		turn_a2_f_t(&s[i], &info[i]);
		/*if(s[i].open=='\0')//���޸ģ�����
		{
			break;//�������ݿ�ĩ�ˣ�ֹͣ��ȡ
		}*/
	}
	/*if (s != NULL)
	{
		free(s);
		s = NULL;
	}*/
}

/*********************************************
FUNCTION:sto_daybyday
DESCRIPTION:��ȡ��ָ��������ʼ�Ĺ�Ʊ��Ϣ
INPUT:sto_number,start_date,days,stk
RETURN:��
***********************************************/
void sto_daybyday(int sto_number, long int start_date, long int days, STODAYCHAR* stk)//��Ʊ��ţ���Ʊ��ȡ��ʼ���ڣ���ȡ����
{
	FILE* fp;
	int line_num = 1, i = 0, j = 0;//iΪ�ļ�ָ��ָ��λ�õı������jΪ��i�����Ƶı��
	int m = 0, d = 0;//mΪÿ���ַ���Ӧ�ļ��ı�ţ�dΪ�ҹ�Ʊ���ڵı����
	int item = 0;
	long int len;
	char ch = '\0';
	char ctl[30] = "Database\\dayinfo\\", num[4] = { '\0' };//Ŀ¼
	itoa(sto_number, num, 10);//��Ʊ�������ת���������ļ���ȡ
	strcat(ctl, num);
	strcat(ctl, ".dat");

	
	if ((fp = fopen(ctl, "rb")) == NULL)
	{
		printf("cannot open dayinfo\\%d", sto_number);
		delay(3000);
		exit(1);
	}
	fseek(fp, 0, SEEK_END);
	len = ftell(fp);
	for (i = 0; line_num < start_date && i < len; i++)
	{
		fseek(fp, i * sizeof(char), SEEK_SET);
		fread(&ch, sizeof(char), 1, fp);
		if (ch == '\n')
		{
			line_num++;
			i++;//���ж�ȡ
		}
	}
	if (i != 0)
	{
		i--;//����һ�񣬴�ĳ�ŵĵ�0��ʼ��ȡ 
	}

	//��������ڱ�Ų�����
	if (i == len)
	{
		if (fclose(fp) != 0)//�ر��ļ�
		{
			printf("Error in closing file \"StkInfo\\%d\".\n", sto_number);
			delay(3000);
			exit(1);
		}
		return;
	}
	else
	{
		while (1)
		{
			fseek(fp, (i + j) * sizeof(char), SEEK_SET);//��Ҫ��ȡ������λ�������ȡ,��ʱ�ļ�ָ��λ���ڴ���ȡ������λ��
			fread(&ch, sizeof(char), 1, fp);
			if (ch != '\t' && ch != '\n' && ch != '\r' && ch != ' ')
			{

				if (item == 0)
				{
					stk[d].date[m] = ch;
				}
				else if (item == 1)
				{
					stk[d].open[m] = ch;
				}
				else if (item == 2)
				{
					stk[d].high[m] = ch;
				}
				else if (item == 3)
				{
					stk[d].low[m] = ch;
				}
				else if (item == 4)
				{
					stk[d].close[m] = ch;
				}
				else if (item == 5)
				{
					stk[d].VOL[m] = ch;
				}
				else if (item == 6)
				{
					stk[d].VOT[m] = ch;
				}
			}
			if (ch != '\n')
			{
				m++;//������
			}
			if (ch == '\t')
			{
				m = 0;
				item++;//����һ������
			}
			else if ((ch == '\n') && (item == 6))
			{
				d++;//������ź���
				if (d == days)
				{
					break;//����Ҫ����λ��
				}
				else
				{
					item = 0;
					m = 0;//������Ź���
				}
			}
			j++;//ÿ�ζ�һ���ַ���������Ӧ�Ĳ�������������½���ѭ��
		}
	}
	if (fclose(fp) != 0)
	{
		printf("cannot close dayinfo\\%d after read", sto_number);
		delay(3000);
		exit(1);
	}
}

/*********************************************
FUNCTION:turn_a2_f_t
DESCRIPTION:�ַ���תΪ���λ򸡵��Ϳ��ƺ���
INPUT:sto_number,start_date,days,stk
RETURN:��
***********************************************/
void turn_a2_f_t(STODAYCHAR* str, STODAYFLOAT* f)
{
	turn_a2i(str->date, &(f->Year), &(f->Month), &(f->Day));
	turn_a2f(str->open, &(f->Open));
	turn_a2f(str->high, &(f->High));
	turn_a2f(str->low, &(f->Low));
	turn_a2f(str->close, &(f->Close));
	turn_a2f(str->VOL,&(f->VOL));//�˴��д�����!
	//f->VOL = (atoi(str->VOL));
	turn_a2f(str->VOT, &(f->VOT));
}

/*********************************************
FUNCTION:turn_a2f
DESCRIPTION:��ÿ��ָ�궼ת��Ϊ������
INPUT:str,price
RETURN:��
***********************************************/
void turn_a2f(char* str, float* price)
{
	float price1 = 0.0, price3 = 0.0;
	float price2 = 1.0;
	int i, j;
	for (i = 0; str[i] != '.'&&str[i]!='\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			price1 *= 10.0;
			price1 += (float)(str[i] - '0');//��������
		}
	}
	for (j = i; str[j] != '\0'; j++)
	{
		if (str[j] >= '0' && str[j] <= '9')
		{
			price2 /= 10.0;//����λ��
			price3 *= 10.0;
			price3 += (float)(str[j] - '0');//С������
		}
	}
	*price = price1 + price2 * price3;
}

/*********************************************
FUNCTION:turn_a2i
DESCRIPTION:dateת��Ϊint
INPUT:str,y,m,d
RETURN:��
***********************************************/
void turn_a2i(char* str, int* y, int* m, int* d)//date�л���int
{
	int k = 0;
	int i, j = 0;
	int num[3] = { 0 };
	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			k *= 10;
			k += (int)(str[i] - '0');
		}
		else if (str[i] == '/')
		{
			num[j] = k;	//���ڸ�������
			j++;
			k = 0;		//�����ڵ����¹��� 
		}
	}
	num[j] = k;
	*y = num[0];
	*m = num[1];
	*d = num[2];
}