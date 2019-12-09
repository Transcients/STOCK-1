#include"public.h"
#include"fsearch.h"
#include"database.h"
#include"storead.h"


/*****************************************
fsearch.c
COPYRIGHT:	weijingmin
FUNCTION:	fundamental search
ABSTRACT:
		A.fundamental search
		B.abstract infomation from fund.dat
DATE:2019/11/3
******************************************/


/*********************************************
FUNCTION:F_search
DESCRIPTION����ȡFUND���ݿⲢ������������
INPUT:info,u
RETURN:��
***********************************************/
void F_search(int* count, int opt[][2], int* sto_list)//��ȡ�ļ�
{
	int i;
	long int len;
	int item = 1;
	int m = 0;
	int cnt = 0;//sto_list���
	int num = 0;//��Ʊ���
	char ch;//������ȡ���ֽ�
	FUND* s = NULL;
	FILE* fp = NULL;

	clrmous(MouseX,MouseY);
	memset(sto_list, 0, 200 * sizeof(int));
	if ((fp = fopen("Database\\fund.dat", "rb")) == NULL)
	{
		printf("cannot open file fund.dat");
		delay(3000);
		exit(1);
	}
	if ((s = (FUND*)malloc(sizeof(FUND))) == NULL)
	{
		printf("memoryallocation runs wrong in fsearch.c");
		delay(3000);
		exit(1);
	}
	memset(s, '\0', sizeof(FUND));
	fseek(fp, 0, SEEK_END);
	len = ftell(fp);//���ļ�����
	
	setlinestyle(SOLID_LINE, 0, 1);
	setcolor(WHITE);
	rectangle(218, 442, 422, 459);
	setfillstyle(SOLID_FILL, LIGHTGRAY);
	bar(220, 444, 420, 457);

	for (i = 0; i < len; i++)
	{
		fseek(fp, i * sizeof(char), SEEK_SET);
		fread(&ch, sizeof(char), 1, fp);
		if (ch != '\t' && ch != '\n' && ch != '\r' && ch != ' ')
		{
			if (item == 1)
			{
				s->PE[m] = ch;//��ӯ��
			}
			else if (item == 2)
			{
				s->LEV[m] = ch;//�ʲ���ծ��
			}
			else if (item == 3)
			{
				s->PB[m] = ch;//�о���
			}
			else if (item == 4)
			{
				s->NP[m] = ch;//��������
			}
			else if (item == 5)
			{
				s->DE[m] = ch;//Ȩ���
			}
		}
		m++;//��ȡ������
		if (ch == '\t')
		{
			m = 0;//����
			item++;
		}
		else if ((ch == '\n'|| i == len) && item == 5)//��һ�ж���
		{
			num++;//��Ʊ���
			refresh_progress2(num, RED);
			if (fundsearch(count, opt, s) == 1)
			{
				sto_list[cnt] = num;
				cnt++;//��ȼ�����������
			}

			memset(s, '\0', sizeof(FUND));
			item = 1;
			m = 0;
		}
	}
	if (fclose(fp) != 0)
	{
		printf("cannot close fund.dat");
		delay(3000);
		exit(1);
	}

	if (s != NULL)
	{
		free(s);
		s = NULL;
	}
}

/*********************************************
FUNCTION:refresh_progress2
DESCRIPTION�����½�����
INPUT:progress,color
RETURN:��
***********************************************/
void refresh_progress2(int progress, int color)
{
	setfillstyle(SOLID_FILL, color);
	bar(220, 444, 220 + progress, 457);
}

/*********************************************
FUNCTION:fundsearch
DESCRIPTION������������
INPUT:count,opt[][2],s
RETURN:��
***********************************************/
int fundsearch(int* count, int opt[][2], FUND* s)//���������
{
	float index = 0;
	delay(30);
	if (count[0] == 1)//��ӯ��ѡ��
	{
		turn_a2f(s->PE, &index);
		if (index<opt[0][1] && index>opt[0][0]);
		else
		{
			return 0;
		}
	}
	if (count[1] == 1)//�ʲ���ծ��ѡ��
	{
		turn_a2f(s->LEV, &index);
		if (index<opt[1][1] && index>opt[1][0]);
		else
		{
			return 0;
		}
	}
	if (count[2] == 1)//�о���ѡ��
	{
		turn_a2f(s->PB, &index);
		if (index<opt[2][1] && index>opt[2][0]);
		else
		{
			return 0;
		}
	}
	if (count[3] == 1)//������ѡ��
	{
		turn_a2f(s->NP, &index);
		if (index<opt[3][1] && index>opt[3][0]);
		else
		{
			return 0;
		}
	}
	if (count[4] == 1)//Ȩ���ѡ��
	{
		turn_a2f(s->DE, &index);
		if (index<opt[4][1] && index>opt[4][0]);
		else
		{
			return 0;
		}
	}
	return 1;//�ߵ���һ��˵��ǰ�涼��������
}