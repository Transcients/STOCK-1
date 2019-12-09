#include<io.h>
#include<direct.h>
#include"public.h"
#include"traverse.h"
#include"queue.h"
#include"trade.h"
#include"storead.h"
#define MAXHST 17
#define MAXHOLD 8



/**********************************************
traverse.c
COPYRIGHT: dengshumin
FUNCTION:  get information from database
DATE: 2019/10/29
***********************************************/

/****************************************************
FUNCTION: get_stkname
DESCRIPTION: ����֤ȯ�����ȡ֤ȯ�����Լ��۸�
INPUT: stk_code,stk_name,stk_price
RETURN: ���ҵ���Ʊ�򷵻�λ�ã����򷵻�0
****************************************************/
int get_stkname(char *stk_code,char *stk_name,char *stk_price) //����ֵ��stock��λ��
{
	FILE *fp;
	int len;
	int i = 0, l = 0;   //��Ʊ���ͳ���
	int j = 0, k = 0;
	int m = 0;
	int item = 1;
	char ch = '0';
	char code[7] = {'\0'};
	char name[10] = {'\0'};
	char price[7] = {'\0'};
	if ((fp = fopen("Database\\1.dat", "rb")) == NULL)
	{
		printf("cannot open file stoname.dat");
		delay(2000);
		exit(1);
	}
	for(i = 0;i < 200;i++)  //��200��Ʊ
	{
		memset(code,'\0',7*sizeof(char));
		memset(name,'\0',10*sizeof(char));   	   //ÿ�λ�������һ��
		memset(price,'\0',sizeof(price));
		l = countline(fp,k);   //lΪһ�еĳ���+1('\n')
		for(j = 0,ch = '0',item = 1,m = 0; j < l; j++)
		{
			fseek(fp, j * sizeof(char) + k, SEEK_SET); 
			fread(&ch, sizeof(char), 1, fp);
			//���롢����
			if (ch != '\t' && ch != '\n' && ch != '\r' && ch != ' ')
			{
				if(item == 1)
					code[m] = ch;
				else if(item == 2)
					name[m] = ch;
				else if(item == 6)
					price[m] = ch;
			}
			m++;
			if(ch == '\t')
			{
				m = 0;
				item++;
			}
			else if ((ch == '\n' || ch == '\r' || i == len) && item == 12)
			{
				break;
			}
		}
		if(strcmp(code,stk_code) == 0)
		{
			memset(stk_name,'\0',10*sizeof(char));
			memset(stk_price,'\0',7*sizeof(char));
			strcpy(stk_name,name);
			strcpy(stk_price,price);
			
			if (fclose(fp) != 0)
			{
				printf("cannot close 1.dat");
				delay(2000);
				exit(1);
			}
			return i+1;     	 //����ֵ��stock��λ��i,˵���ǵڼ�ֻ��
		}
		k = k + l;  //kΪ�ļ�ָ���ڲ�λ��
	}
	if (fclose(fp) != 0)
	{
		printf("cannot close 1.dat");
		delay(2000);
		exit(1);
	}
	return 0;    //û�ҵ���Ӧ��Ʊ 	
}


/**************************************************
FUNCTION: get_markettime
DESCRIPTION: ��ȡ����ʱ�䲢��ʾ
INPUT: tp,minute,flag
RETURN: ��
***************************************************/
void get_markettime(struct tm* tp, int* minute, int flag)
{
	char time_str1[10] = { '\0' };   //ʱ��
	char time_str2[11] = { '\0' };   //����
	char time_temp[10] = { '\0' };
	struct tm* time_p;
	time_t t;
	t = time(&t);
	time_p = localtime(&t);
	itoa(1900 + time_p->tm_year, time_temp, 10);
	strcat(time_str2, time_temp);
	strcat(time_str2, "/");

	memset(time_temp, '\0', sizeof(time_temp));
	itoa(1 + time_p->tm_mon, time_temp, 10);
	strcat(time_str2, time_temp);
	strcat(time_str2, "/");

	memset(time_temp, '\0', sizeof(time_temp));
	itoa(time_p->tm_mday, time_temp, 10);
	strcat(time_str2, time_temp);
	//	strcat(time_str2,"/");   //������

	memset(time_temp, '\0', sizeof(time_temp));
	if (time_p->tm_hour >= 10)
		itoa(time_p->tm_hour, time_temp, 10);
	else
	{
		time_temp[0] = '0';
		time_temp[1] = '0' + time_p->tm_hour;
	}
	strcat(time_str1, time_temp);
	strcat(time_str1, ":");

	memset(time_temp, '\0', sizeof(time_temp));
	if (time_p->tm_min >= 10)
		itoa(time_p->tm_min, time_temp, 10);
	else
	{
		time_temp[0] = '0';
		time_temp[1] = '0' + time_p->tm_min;
	}
	strcat(time_str1, time_temp);   	//��ʱ����

	if (*minute != time_p->tm_min || flag == 1)
	{
		settextjustify(LEFT_TEXT, TOP_TEXT);
		settextstyle(2, 0, 5);
		setcolor(LIGHTCYAN);
		outtextxy(3, 40, time_str2);
		outtextxy(3, 64, time_str1);
		*minute = time_p->tm_min;
	}

	tp->tm_year = time_p->tm_year;
	tp->tm_mon = time_p->tm_mon;
	tp->tm_mday = time_p->tm_mday;
	tp->tm_hour = time_p->tm_hour;
	tp->tm_min = time_p->tm_min;
	tp->tm_sec = time_p->tm_sec;
}

/**************************************************************
FUNCTION: get_time
DESCRIPTION: �ڻ���ͽ��׽����ȡʱ�䲢ÿ��һ������ʾ
INPUT: tp,minute,flag
RETURN: ��
***************************************************************/
void get_time(struct tm *tp, int *minute,int flag)
{
	char time_str1[10] = {'\0'};   //ʱ��
	char time_str2[11] = {'\0'};   //����
	char time_temp[10] = {'\0'};
	struct tm *time_p;
	time_t t;
	t = time(&t);
	time_p = localtime(&t);
	itoa(1900+time_p->tm_year,time_temp,10);
	strcat(time_str2,time_temp);
	strcat(time_str2,"/");
	
	memset(time_temp,'\0',sizeof(time_temp));
	itoa(1+time_p->tm_mon,time_temp,10);
	strcat(time_str2,time_temp);
	strcat(time_str2,"/");
	
	memset(time_temp,'\0',sizeof(time_temp));
	itoa(time_p->tm_mday,time_temp,10);
	strcat(time_str2,time_temp);
//	strcat(time_str2,"/");   //������
	
	memset(time_temp,'\0',sizeof(time_temp));
	if(time_p->tm_hour >= 10)
		itoa(time_p->tm_hour,time_temp,10);
	else
	{
		time_temp[0] = '0';
		time_temp[1] = '0' + time_p->tm_hour;
	}
	strcat(time_str1,time_temp);
	strcat(time_str1,":");
	
	memset(time_temp,'\0',sizeof(time_temp));
	if(time_p->tm_min >= 10)
		itoa(time_p->tm_min,time_temp,10);
	else
	{
		time_temp[0] = '0';
		time_temp[1] = '0' + time_p->tm_min;
	}
	strcat(time_str1,time_temp);   	//��ʱ����

	if(*minute != time_p->tm_min || flag == 1)
	{
		settextjustify(LEFT_TEXT,TOP_TEXT);
		settextstyle(2,0,5);
		setfillstyle(1,WHITE);
		bar(0, 456, 640, 480);
		setcolor(MAGENTA);
		outtextxy(590,454,time_str1);
		outtextxy(560,465,time_str2);
		*minute = time_p->tm_min;
	}
	tp->tm_year = time_p->tm_year;
	tp->tm_mon = time_p->tm_mon;
	tp->tm_mday = time_p->tm_mday;
	tp->tm_hour = time_p->tm_hour;
	tp->tm_min = time_p->tm_min;
	tp->tm_sec = time_p->tm_sec;
}


/**************************************
FUNCTION: get_balance1
DESCRIPTION: �����ݿ��ж�ȡ�û����
INPUT: us, stk_balance
RETURN: ��
**************************************/
void get_balance1(USER* us, float* stk_balance)
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
			printf("memoryallocation runs wrong");
			delay(3000);
			exit(1);
		}
		fseek(fp, i * sizeof(USER), SEEK_SET);//ÿ��������һ���û�
		fread(u, sizeof(USER), 1, fp);		  //����Ϣ����u
		if (strcmp(us->user, u->user) == 0)
		{
			memset(us->balance,'\0',sizeof(us->balance));
			strcpy(us->balance,u->balance);    //��������us
			if (u != NULL)
			{
				free(u);
				u = NULL;
			}//��ʱ�ͷ�
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
	}    	//��ȡ���ͷ� 
	//float_to_str(us->balance,10000.00,2);
	turn_a2f(us->balance,stk_balance);      	   //������Ը���������
	/*puthz(10,459,"�������",16,17,BLACK);
	setcolor(DARKGRAY);
	setlinestyle(0,0,1);
	line(89,456,89,480);
	settextjustify(LEFT_TEXT,TOP_TEXT);
	settextstyle(2,0,6);
	outtextxy(99,458,us->balance);*/
}

/***************************************************************************
FUNCTION: input_balance
DESCRIPTION: �������������Ʊ֮���������仯�����д�����ݿ���
INPUT: us,stk_balance
RETURN: ��
***************************************************************************/
void input_balance(USER* us,float stk_balance)
{
	int i;
	int len;
	FILE* fp;		
	USER* u = NULL;
	float_to_str(us->balance,stk_balance,2); //���������û���Ϣ��
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
			printf("memoryallocation runs wrong");
			delay(3000);
			exit(1);
		}
		fseek(fp, i * sizeof(USER), SEEK_SET);//ÿ��������һ���û�
		fread(u, sizeof(USER), 1, fp);		  //����Ϣ����u
		if (strcmp(us->user, u->user) == 0)
		{
			memset(u->balance,'\0',sizeof(u->balance));     //����u
			strcpy(u->balance,us->balance);                 //����Ϣ����
			fseek(fp, i * sizeof(USER), SEEK_SET);
			fwrite(u, sizeof(USER), 1, fp);       //���޸Ĺ����������д�� 
			if (u != NULL)
			{
				free(u);
				u = NULL;
			}//��ʱ�ͷ�
			if (fclose(fp) != 0)
			{
				printf("\n cannot close Database");
				exit(1);
			}
			return;
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
		delay(2000);
		exit(1);
	}
	return;
}

/*****************************************
FUNCTION: read_balance
DESCRIPTION: ����ǰ������
INPUT: stk_balance
RETURN: ��
******************************************/
void read_balance(float stk_balance)
{
	char STK_BALANCE[15] = {'\0'};
	float_to_str(STK_BALANCE,stk_balance,2);
	puthz(10,459,"�������",16,17,BLACK);
	setcolor(DARKGRAY);
	setlinestyle(0,0,1);
	line(89,456,89,480);
	settextjustify(LEFT_TEXT,TOP_TEXT);
	settextstyle(2,0,6);
	outtextxy(99,458,STK_BALANCE);
}

/************************************************
FUNCTION: get_hst
DESCRIPTION: ��ȡ��ʷ���׼�¼
INPUT: u,page
RETURN: �����ж���ҳ
************************************************/
int get_hst(USER* u,int page)  //��pageҳ
{
	FILE* fp;
	Hstdata hst;        //��ʷ�ɽ�
	char STK_ADR[50] = {'\0'};
	int len;
	int i = 0,l = 0;    
	int j = 0,k = 0;
	int m = 0;
	int t = 0;          //���λ��
	int item = 1;
	char ch = '0';
	strcpy(STK_ADR,"database\\USER\\");   //����'\0'����
	strcat(STK_ADR,u->user);
	strcat(STK_ADR,"\\");
	strcat(STK_ADR,"history.dat");
	if((fp=fopen(STK_ADR,"rb"))==NULL)
	{
		//printf("can't find the file history.dat while init the data of stock!\n");
		//delay(1000);
		//exit(1);
		return 0;  //����򲻿�����0ҳ
	}      //ֻ��
	fseek(fp, 0, SEEK_END);
	len = ftell(fp) / sizeof(Hstdata); //���㽻�״�����һ�������ʾ17��
	k = (page - 1) * MAXHST * sizeof(Hstdata);                          //��pageҳ����ʼλ��(Ҳ��int65535�᲻����)
	for(i = MAXHST * (page - 1);i < len && i< MAXHST * page; i++)	    //һ�����17ֻ
	{
		memset(&hst,'\0',sizeof(Hstdata));   //��ʼ��
		//k = (page - 1) * MAXHST * sizeof(Hstdata);       //��ʼʱ�ļ�λ��
		l = countline(fp,k);   //lΪһ�еĳ���+1('\n')
		for(j = 0,ch = '0',item = 1,m = 0; j < l; j++)
		{
			fseek(fp, j * sizeof(char) + k,SEEK_SET);
			fread(&ch, sizeof(char),1 , fp);
			if(ch != '\t' && ch != '\n' && ch != '\r' && ch != ' ')
			{
				if(item == 1)
					hst.sto_date[m] = ch;
				else if(item == 2)
					hst.sto_code[m] = ch;
				else if(item == 3)
					hst.sto_name[m] = ch;
				else if(item == 4)
					hst.sto_flag[m] = ch;
				else if(item == 5)
					hst.sto_num[m] = ch;
				else if(item == 6)
					hst.sto_price[m] = ch;
				else if(item == 7)
					hst.sto_amount[m] = ch;
			}
			m++;
			if(ch == '\t')
			{
				m = 0;
				item++;
			}
			else if ((ch == '\n' || ch == '\r' || i == len) && item == 12)
			{
				break;        //��������س�����
			}
		}
		k = k + l;  //kΪ�ļ�ָ���ڲ�λ��
		t = i - (page - 1) * MAXHST;          //���λ��
		if(hst.sto_flag[0] == '1')   //����
		{
			setcolor(LIGHTRED);
			puthz(120+74*3+21,26 + 24 * (t + 1) + 5,"����",16,17,LIGHTRED);
			puthz(120 + 74 * 2 + 5,26 + 24 * (t + 1) + 5,hst.sto_name,16,17,LIGHTRED); //֤ȯ����
		}
		else if(hst.sto_flag[0] == '2')
		{
			setcolor(LIGHTBLUE);     //����
			puthz(120 + 74 * 3 + 21, 26 + 24 * (t + 1) + 5,"����",16,17,LIGHTBLUE);
			puthz(120 + 74 * 2 + 5, 26 + 24 * (t + 1) + 5, hst.sto_name,16,17,LIGHTBLUE); //֤ȯ����
		}
		settextjustify(LEFT_TEXT,TOP_TEXT);
		settextstyle(2,0,4);
		outtextxy(120 + 74 * 0 + 4,26 + 24 * (t + 1) + 5,hst.sto_date);  //�ɽ�����
		
		settextstyle(2,0,5);
		outtextxy(120 + 74 * 1 + 4,26 + 24 * (t + 1) + 5,hst.sto_code);  //֤ȯ����
		
		outtextxy(120 + 74 * 4 + 4,26 + 24 * (t + 1) + 5,hst.sto_num);   //�ɽ�����
		
		outtextxy(120 + 74 * 5 + 4,26 + 24 * (t + 1) + 5,hst.sto_price); //�ɽ�����
		
		outtextxy(120 + 74 * 6 + 4,26 + 24 * (t + 1) + 5,hst.sto_amount);//�ɽ����
	}   //��ʾ���
	if((len % MAXHST) != 0)
	{
		if (fclose(fp) != 0)
		{
			printf("cannot close 1.dat");
			delay(2000);
			exit(1);
		}
		return len / MAXHST + 1;           //�����ж���ҳ
	}
	else                                   //���պ���һҳ
	{
		if (fclose(fp) != 0)
		{
			printf("cannot close 1.dat");
			delay(2000);
			exit(1);
		}
		return len / MAXHST ;           //�����ж���ҳ
	}
}


/*******************************************************************
FUNCTION: get_hold_stk
DESCRIPTION: ��ȡ�ֲ����ݿ���ĳһֻ��
ATTENTION: �������������Ʊ���ڳֲ��н��е�ֻ��Ʊ�Ĳ���
INPUT: hold,STK_NAME,STK_ADR
RETURN: ���ҵ���Ʊ�򷵻�λ�ã����򷵻�0
*******************************************************************/
int get_hold_stk(Hold* hold, char* STK_NAME, char* STK_ADR)         //��ȡ�ֲ����ݿ���ĳһֻ��
{      //ֱ����hold����
	FILE* fp;
	int len;
	int i = 0, l = 0;   //��Ʊ���ͳ���
	int j = 0, k = 0;
	int m = 0;
	int item = 1;
	char ch = '0';
	if((fp = fopen(STK_ADR,"rb")) == NULL)
	{
		return;
	}	//����򲻿��ͷ���
	fseek(fp, 0, SEEK_END);
	len = ftell(fp) / sizeof(Hold);  //����ֹɹ���
	for(i = 0;i < len; i++)
	{
		memset(hold,'\0',sizeof(Hold));
		l = countline(fp,k);     //lΪһ�еĳ���+1('\n')
		for(j = 0,ch = '0',item = 1,m = 0; j < l; j++)
		{
			fseek(fp, j * sizeof(char) + k, SEEK_SET);
			fread(&ch, sizeof(char), 1, fp);
			if(ch != '\t' && ch != '\n' && ch != '\r' && ch != ' ')
			{
				if(item == 1)
					hold->sto_date[m] = ch;
				else if(item == 2)
					hold->sto_code[m] = ch;
				else if(item == 3)
					hold->sto_name[m] = ch;
				else if(item == 4)
					hold->sto_num[m] = ch;
				else if(item == 5)
					hold->sto_price[m] = ch;
				else if(item == 6)
					hold->sto_day[m] = ch;
			}
			m++;
			if(ch == '\t')
			{
				m = 0;
				item++;
			}
			else if ((ch == '\n' || ch == '\r' || i == len) && item == 12)
			{
				break;        //��������س�����
			}
		}
		k = k + l;
		if(strcmp(STK_NAME,hold->sto_name) == 0)
		{    //������ҵ���Ʊ
			if (fclose(fp) != 0)
			{
				printf("cannot close hold.dat");
				delay(2000);
				exit(1);
			}
		//	printf("%d",i+1);
			return i + 1 ;
		}
	} //û�ҵ���Ʊ
	memset(hold,'\0',sizeof(Hold));
	if (fclose(fp) != 0)
	{
		printf("cannot close hold.dat");
		delay(2000);
		exit(1);
	}
	return 0;   //û�ҵ���Ӧ��Ʊ
}

/************************************************************
FUNCTION: get_hold_day
DESCRIPTION: ��ȡ�����³ֲ�ʱ��
INPUT: prime,now
RETURN: �ֲ�����
*************************************************************/
int get_hold_day(int* prime,int* now)
{
	int y1, m1; 
	int y2, m2;	
	long d1, d2;
	m1 = (prime[1] + 9) % 12;  //�����ж������Ƿ����3�£�2�����ж�����ı�ʶ���������ڼ�¼��3�µļ��������
	y1 = prime[0] - m1 / 10;   //�����1�º�2�£��򲻰�����ǰ�꣨��Ϊ�Ǽ��㵽0��3��1�յ���������
	d1 = 365*y1 + y1/4 - y1/100 + y1/400 + (m1*306 + 5)/10 + (prime[2] - 1);
	//���� 365*y1 �ǲ�����������һ�������.
	//y1/4 - y1/100 + y1/400  �Ǽ���������������һ�죬
	m2 = (now[1] + 9) % 12;
	y2 = now[0] - m2/10;
	d2 = 365*y2 + y2/4 - y2/100 + y2/400 + (m2*306 + 5)/10 + (now[2] - 1);
	//(m2*306 + 5)/10 ���ڼ��㵽��ǰ�µ�3��1�ռ��������306=365-31-28��1�º�2�£���5��ȫ���в���31���·ݵĸ���
	//(day_start - 1)���ڼ��㵱ǰ�յ�1�յļ��������
	return (int)(d2 - d1);
}

/******************************************************
FUNCTION: get_hold
DESCRIPTION: ��ȡ�ֲ���Ϣ
INPUT: u,page
RETURN: �����ж���ҳ
*******************************************************/
int get_hold(USER* u,int page)             
{  //�ڸ��˽����ȡ�ֲ���Ϣ 
	FILE* fp;
	Hold hold;
	char STK_ADR[50] = {'\0'};  
	int i = 0, j = 0;
	int l= 0, k = 0;
	int m = 0, t = 0;
	int len = 0, item = 0;
	char ch = '0';
	memset(&hold, '\0', sizeof(Hold));
	strcpy(STK_ADR,"database\\USER\\");      //����'\0'����
	strcat(STK_ADR,u->user);
	//�ɴ����ļ���
	if(access(STK_ADR, 0) == -1)             //�������ļ���
	{
		if(mkdir(STK_ADR) != 0)              //δ�ɹ�����
		{
			printf("The file opens failued");
		}
	}//��������ֱ�Ӵ�
	strcat(STK_ADR,"\\");
	strcat(STK_ADR,"hold.dat"); 
	if((fp = fopen(STK_ADR, "rb")) == NULL)
	{
		return 0;
	}
	fseek(fp, 0, SEEK_END);
	len = ftell(fp) / sizeof(Hold);          //����ֹɹ���
	k = (page - 1) * MAXHOLD * sizeof(Hold);
	for(i = MAXHOLD * (page - 1); i < MAXHOLD * page && i < len; i++)
	{
		memset(&hold, '\0', sizeof(Hold));  //��ʾ8ֻ���ڵ�
		l = countline(fp,k);                 //
		for(j = 0,ch = '0',item = 1,m = 0;j < l;j++)
		{
			fseek(fp, j * sizeof(char) + k, SEEK_SET);//��ʾ
			fread(&ch, sizeof(char), 1, fp);
			if(ch != '\t' && ch != '\n' && ch != '\r' && ch != ' ')
			{
				if(item == 1)
					hold.sto_date[m] = ch;
				else if(item == 2)
					hold.sto_code[m] = ch;
				else if(item == 3)
					hold.sto_name[m] = ch;
				else if(item == 4)
					hold.sto_num[m] = ch;
				else if(item == 5)
					hold.sto_price[m] = ch;
				else if(item == 6)
					hold.sto_day[m] = ch;
			}
			m++;
			if(ch == '\t')
			{
				m = 0;
				item++;
			}
			else if ((ch == '\n' || ch == '\r' || i == len) && item == 12)
			{
				break;        //��������س�����
			}
		}
		k = k + l;            //kΪ�ļ�ָ���ڲ�λ��
		t = i - (page - 1) * MAXHOLD;
		settextjustify(LEFT_TEXT,TOP_TEXT);
		settextstyle(2, 0, 5);
		setcolor(RED);
		outtextxy(53, 300 + 20 * (t + 1), hold.sto_date);
		
		settextstyle(2,0,6);
		setcolor(GREEN);
		outtextxy(63 + 90 * 1, 297 + 20 * (t + 1), hold.sto_code);
		
		puthz(58 + 90 * 2, 297 + 20 * (t + 1) + 2, hold.sto_name, 16, 17, BLUE);
		
		setcolor(LIGHTMAGENTA);
		outtextxy(63 + 90 * 3, 297 + 20 * (t + 1), hold.sto_num);
			
		setcolor(LIGHTBLUE);
		outtextxy(63 + 90 * 4, 297 + 20 * (t + 1), hold.sto_price);
		
		setcolor(DARKGRAY);
		outtextxy(63 + 90 * 5, 297 + 20 * (t + 1), hold.sto_day);
	}
	fseek(fp, 0, SEEK_END);
	if((len % MAXHOLD) != 0)
	{
		if (fclose(fp) != 0)
		{
			printf("cannot close 1.dat");
			delay(2000);
			exit(1);
		}
		return len / MAXHOLD + 1;           //�����ж���ҳ
	}
	else      //ǡ��ĳһҳ
	{
		if (fclose(fp) != 0)
		{
			printf("cannot close 1.dat");
			delay(2000);
			exit(1);
		}
		return len / MAXHOLD ;           //�����ж���ҳ
	}           
}

/*****************************
FUNCTION: get_asset
DESCRIPTION: ��ȡ�ʲ�
INPUT: u
RETURN: ��
*****************************/
void get_asset(USER* u)
{
	settextjustify(LEFT_TEXT,TOP_TEXT);
	settextstyle(2,0,7);
	setcolor(DARKGRAY);
	outtextxy(145, 170, u->user);
	outtextxy(145, 210, u->bankcard);
	outtextxy(145, 250, u->balance);
}

/****************************************************
FUNCTION: get_buy
DESCRIPTION: ���ݹ�Ʊλ������ȡ���ݿ����ĳֻ��
INPUT: stk_locat,stk_code,stk_name,stk_price
RETURN: ��
*****************************************************/
void get_buy(int stk_locat,char* stk_code,char* stk_name, char* stk_price)
{         
	FILE* fp;
	int i = 0, l = 0;
	int j = 0, k = 0;
	int m = 0;
	int item = 1;
	char ch = '0';
	if ((fp = fopen("Database\\1.dat", "rb")) == NULL)
	{
		printf("cannot open file stoname.dat");
		delay(2000);
		exit(1);
	}
	memset(stk_code,'\0',7*sizeof(char));
	memset(stk_name,'\0',10*sizeof(char));   	   
	memset(stk_price,'\0',sizeof(stk_price));
	for(i = 0; i < stk_locat - 1; i++)
	{
		l = countline(fp,k);
		k = k + l;
	}//��ȡ��stk_locat�е�λ��
	l = countline(fp,k);
	for(j = 0,ch = '0',item = 1,m = 0;j < l; j++)
	{
		fseek(fp, j * sizeof(char) + k, SEEK_SET);
		fread(&ch, sizeof(char), 1, fp);
		if (ch != '\t' && ch != '\n' && ch != '\r' && ch != ' ')
		{
			if(item == 1)
				stk_code[m] = ch;
			else if(item == 2)
				stk_name[m] = ch;
			else if(item == 6)
				stk_price[m] = ch;
		}
		m++;
		if(ch == '\t')
		{
			m = 0;
			item++;
		}
		else if(ch == '\n' || ch == '\r') 
		{
			break;
		}
	}
	if(fclose(fp) != 0)
	{
		printf("cannot close 1.dat");
		delay(1000);
		exit(1);
	}
}

/****************************************
FUNCTION: update_hold_day
DESCRIPTION: ���³ֲ�����
INPUT: tp,u
RETURN: ��
****************************************/
void update_hold_day(struct tm* tp, USER* u)
{
	FILE* fp;
	Hold hold;
	int len;
	int i = 0, l = 0;
	int j = 0, k = 0;
	int m = 0;
	int item = 1;
	int prime[3] = {0};
	int now[3] = {0};
	int day = 0;
	char ch = '0';
	char STK_ADR[50] = {'\0'};    		     //��ַ��
	memset(&hold,'\0',sizeof(Hold));  		 //��ʼ��
	strcpy(STK_ADR,"database\\USER\\");      //����'\0'����
	strcat(STK_ADR,u->user);
	if(access(STK_ADR, 0) == -1)             //�������ļ���
	{
		if(mkdir(STK_ADR) != 0)              //δ�ɹ�����
		{
			printf("The file opens failued");
		}
	}//��������ֱ�Ӵ�
	strcat(STK_ADR,"\\");
	strcat(STK_ADR,"hold.dat");
	if((fp = fopen(STK_ADR, "rb+")) == NULL)
	{
		return; //��������ڳֲ�ֱ�ӷ��أ����·���
	}
	fseek(fp, 0, SEEK_END);
	len = ftell(fp) / sizeof(Hold);  //����ֹɹ���
	now[0] = tp->tm_year + 1900;
	now[1] = tp->tm_mon + 1;
	now[2] = tp->tm_mday;
	for(i = 0;i < len; i++)
	{
		memset(&hold,'\0',sizeof(Hold));
		l = countline(fp,k);     //lΪһ�еĳ���+1('\n')
		for(j = 0,ch = '0',item = 1,m = 0; j < l; j++)
		{
			fseek(fp, j * sizeof(char) + k, SEEK_SET);
			fread(&ch, sizeof(char), 1, fp);
			if(ch != '\t' && ch != '\n' && ch != '\r' && ch != ' ')
			{
				if(item == 1)
					hold.sto_date[m] = ch;
				else if(item == 2)
					hold.sto_code[m] = ch;
				else if(item == 3)
					hold.sto_name[m] = ch;
				else if(item == 4)
					hold.sto_num[m] = ch;
				else if(item == 5)
					hold.sto_price[m] = ch;
			/*	else if(item == 6)
					hold.sto_day[m] = ch;   //����������*/
			}
			m++;
			if(ch == '\t')
			{
				m = 0;
				item++;
			}
			else if ((ch == '\n' || ch == '\r' || i == len) && item == 12)
			{
				break;        //��������س�����
			}
		}
		k = k + l;
		turn_a2i(hold.sto_date, prime, prime + 1, prime + 2);
		day = get_hold_day(prime, now);
		itoa(day, hold.sto_day, 10);
		hold.sto_date[10] = '\t';
		hold.sto_code[6] = '\t';  
		hold.sto_name[9] = '\t';
		hold.sto_num[9] = '\t';
		hold.sto_price[6] = '\t';
		hold.sto_day[3] = '\n';
		fseek(fp, i * sizeof(Hold), SEEK_SET);
		fwrite(&hold, sizeof(Hold), 1, fp);
	}
	if (fclose(fp) != 0)
	{
		printf("\n cannot close Database");
		exit(1);
	}
}