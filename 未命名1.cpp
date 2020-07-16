#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h> 
#define error 0
#define ok 1

typedef double Status; 
typedef struct Employee {
	char id[10];//1.ְ������	 
	char name[10];//2.ְ������ 
	double salary;//3.��λ���� 
	double wages;//4.н������ 
	double allowance;//5.ְ����� 
	double meritpay;//6.��Ч���� 
	double shouldpay;//7.Ӧ������
	double tax;//8.��������˰
	double realpay;//9.ʵ������ 

}EMPLOYEE; //ְ���ṹ������

typedef struct DuLNode
{
	EMPLOYEE data;//������
	struct DuLNode *prior,*next;//����ǰָ��   // ����βָ�� 
}DuLNode,*DuLinkList;
int number=0;

//��ʼ���� 
void CreateList(DuLinkList &L)
{
	L = (DuLNode*)malloc(sizeof(DuLNode));
	L->next = NULL;
	L->prior = L->next;
}
 
//1.��ȡ�ļ� 
int read(DuLinkList &L)
{
	FILE *fp;
	int i;
	DuLinkList p, ptemp;
	char tag;

	p = L;
	ptemp = (DuLNode*)malloc(sizeof(DuLNode));
	fp = fopen("gz.dat", "rb+");
	tag = fgetc(fp);
	rewind(fp);
	if (tag != EOF)
	{
		
			for (i = 0; !feof(fp); i++)
			{
				
				fread(&ptemp->data, sizeof(EMPLOYEE), 1, fp);
				ptemp = (DuLNode*)malloc(sizeof(DuLNode));
				ptemp->next = p->next;
				p->next = ptemp;
				ptemp->prior = p;
				p = ptemp;	
		    }
            free(ptemp);
            
	}
		number = i;
		fclose(fp);
	return ok;
}

//2.���� 
void write(DuLinkList &L)
{
	DuLinkList ptemp;
	FILE *fp;

	ptemp = L->next;
	if (number == 0) printf("ĿǰԱ��������Ϊ0!���������");

	if ((fp = fopen("gz.dat", "wb+")) == NULL)
	{
		printf("���ܴ��ļ�");
		exit(1);
	}

	while (ptemp)
	{
		fwrite(&ptemp->data, sizeof(EMPLOYEE), 1, fp);
		ptemp = ptemp->next;
	}
	fclose(fp);
	
}

//8.��������sui
double grsds(double sum)		//��������˰
{
	double t;
	if (sum > 100000)
		t = 29625.0 + (sum - 100000) * 0.45;
	else if (sum > 80000)
		t = 21700.0 + (sum - 80000) * 0.4;
	else if (sum > 60000)  
		t = 14625.0 + (sum - 60000) * 0.35;
	else if (sum > 40000)
		t = 8625.0 + (sum - 40000) * 0.3;
	else if (sum > 20000)
		t = 3625.0 + (sum - 20000) * 0.25;
	else if (sum > 5000)
		t = 625.0 + (sum - 5000) * 0.2;
	else if (sum > 2000)
		t = 175.0 + (sum - 2000) * 0.15;
	else if (sum > 500)
		t = 25.0 + (sum - 500) * 0.1;
	else
		t = sum * 0.05;
	return t;
} 



//����
void modify_add_scanf(EMPLOYEE &ptemp)
{
	printf("����:\t����:\t��λ����:\tн������:\tְ�����:\t��Ч����:\n");
	scanf("%s %s %lf %lf %lf %lf", ptemp.id, ptemp.name, &ptemp.salary, &ptemp.allowance, &ptemp.meritpay);
	while (strlen(ptemp.id)>10)
	{
		printf("���������ְ�����Ų�����Ҫ������������");
		printf("\t����\t����\t��λ����\tн������\tְ�����\t��Ч����");
		scanf("%s %s %lf %lf %lf %lf %lf %lf", ptemp.id, ptemp.name, &ptemp.salary, &ptemp.allowance, &ptemp.meritpay);
	}//���Ŵ���Ҫ�� 

	while (strlen(ptemp.name)>10)
	{
		printf("������������ֲ�����Ҫ������������");
		printf("\t����\t����\t��λ����\tн������\tְ�����\t��Ч����");
		scanf("%s %s %lf %lf %lf %lf %lf %lf", ptemp.id, ptemp.name, &ptemp.salary, &ptemp.allowance, &ptemp.meritpay);
	}//����������
	ptemp.shouldpay = ptemp.salary + ptemp.wages + ptemp.allowance + ptemp.meritpay;
	ptemp.tax = grsds(ptemp.shouldpay);
	ptemp.realpay = ptemp.shouldpay - ptemp.tax;
}

//��һ������->����
void find(DuLinkList &L)
{
	DuLinkList ptemp;
	char gonghao[20];
	char ch;//����Ƿ��������� 
    ptemp = L;


	printf("������ְ���Ĺ��ţ�");
	scanf("%s", gonghao);

	while (strlen(gonghao) > 10)
	{
		printf("����Ĺ�����������������");
		scanf("%s", gonghao);
	}

	while (ptemp)
	{
		if (strcmp(ptemp->data.id, gonghao) == 0)
		{
			printf("%s %s %lf %lf %lf %lf\n", ptemp->data.id, ptemp->data.name, ptemp->data.salary, ptemp->data.allowance, ptemp->data.meritpay, ptemp->data.shouldpay, ptemp->data.tax, ptemp->data.realpay);
			break;
		}
		ptemp = ptemp->next;
	}
	if (ptemp == NULL)printf("��ְ����Ϣ������");
	//free(ptemp);

}

//5.�޸� 
void modify(DuLinkList &L)
{
	char gonghao[20];
	DuLinkList ptemp;
	ptemp = L;

	printf("����������Ҫ�޸ĵ�ְ���ţ�\n");
	scanf("%s", gonghao);

	while (strlen(gonghao) > 10)
	{
		printf("������Ĺ�������Ӧ��ְ�������ڣ���������������룡");
		printf("�����������޸ĵ�ְ����");
		scanf("%s", gonghao);
	}//while

	while (ptemp)
	{
		if (strcmp(gonghao, ptemp->data.id) == 0)
		{
			modify_add_scanf(ptemp->data);
		}
		else
		{
			printf("������Ĺ���û�ж�Ӧ��ְ�����ݣ������Ƿ��д���");
		}
		ptemp = ptemp->next;
	}
} 

//7.���
/**************7.���ְ����������***********************/
void add(DuLinkList &L)
{
	DuLinkList ptemp;
	ptemp = (DuLNode*)malloc(sizeof(DuLNode));

	if (L->next == NULL)
	{
		ptemp->next = L->next;
		L->next = ptemp;
		ptemp->prior=L;
		printf("�����ְ����Ϣ");
		modify_add_scanf(ptemp->data);
	}
	else
	{
		ptemp->prior = L;
		ptemp->next = L->next;	
		L->next->prior = ptemp;
		L->next = ptemp;
		printf("�����ְ����Ϣ");
		modify_add_scanf(ptemp->data);
	}
}

//6.ɾ��
 /***************ɾ��*******************/
void del(DuLinkList &L)
{
	char gonghao[20];
	DuLinkList ptemp;
	ptemp = L;
	int i;
	char ch;

	printf("����������ɾ���Ĺ��ţ�\n");
		scanf("%s", gonghao);
	for (i = 0; ptemp; i++)
	{
		if (strcmp(gonghao, ptemp->data.id) == 0)
		{
			printf("�Ƿ�ȷ��ɾ����Ա����������Ϣ��y/n)");
			scanf(" %c", &ch);
			if (ch == 'y' || ch == 'Y')
			{
				printf("��ɾ����%s %s��ȫ����Ϣ",ptemp->data.id,ptemp->data.name);
				break;
			}
		}
		ptemp = ptemp->next;
	}
	//û�ҵ�
	if (ptemp == NULL || i == number)
	{
		printf("δ�ҵ���ְ����Ϣ��");
			
	}
	//��ĩβ�ҵ�
	if (ptemp->next == NULL)
	{
		ptemp->prior->next = ptemp->next;
	}
	//�м������ҵ�
	if (ptemp->next != NULL)
	{
		ptemp->prior->next = ptemp->next;
		ptemp->next->prior = ptemp->prior;
	}
	free(ptemp);
}

//4.���
void list(DuLinkList &L)
{
	DuLinkList ptemp;
	ptemp = L;

	printf("\t����\t��λ����\tн������\tְ�����\t��Ч����\tʵ������\t��������˰\tʵ������\n");
	while (ptemp)
	{
		printf("\t%s\t%s\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\n", ptemp->data.id, ptemp->data.name, &ptemp->data.salary, &ptemp->data.allowance, &ptemp->data.meritpay, &ptemp->data.shouldpay, &ptemp->data.tax, &ptemp->data.realpay);
		ptemp = ptemp->next;
	}

	free(ptemp);

} 

//�˵�ҳ��
void menu()
{
	system("cls");
	printf("\t\t\t*********************************************************\n");
	printf("\t\t\t************* ְ�����ʹ���ϵͳ **************************\n");
	printf("\t\t\t*            1-----��ѯְ����Ϣ                     *****\n");
	printf("\t\t\t*            2-----�޸�ְ����Ϣ                   *******\n");
	printf("\t\t\t*            3-----���ְ����Ϣ                  ********\n");
	printf("\t\t\t*            4-----����ְ��ID��ɾ��             *********\n");
	printf("\t\t\t*            5-----����Ա����Ϣ               ***********\n");
	printf("\t\t\t*            6-----���ȫ��ְ����Ϣ          ************\n");
	printf("\t\t\t*            7-----�˳�����                **************\n");
	printf("\t\t\t*********************************************************\n");
	printf("    \t \t\t\t  ����������ѡ��:");

}

/*void PrintfAll(DuLinkList &L)
{
	DuLinkList ptemp=L;
	
	while(ptemp)
	{
		printf("%s %s %lf %lf %lf %lf\n", ptemp->data.id, ptemp->data.name, ptemp->data.salary, ptemp->data.allowance, ptemp->data.meritpay, ptemp->data.shouldpay, ptemp->data.tax, ptemp->data.realpay);
	
	}
		
}*/

//9.main
 int main()
{
	int sele;
	DuLinkList L;
	
	menu();
	CreateList(L);
	read(L);
    /*PrintfAll(L);*/ 
	
	scanf("%d", &sele);
	while (sele<1 || sele>7)
	{
		printf("�������ѡ�������1-7֮�䣬����֮����������");
		scanf("%d", &sele);
	}
	switch (sele)
	{
	case 1:  find(L); break;
	case 2 : modify(L); break;
	case 3 : add(L); break;
	case 4 : del(L); break;
	case 5 : write(L); break;
	case 6 : list(L); break;
	default : exit(0); break;	
	}
}
