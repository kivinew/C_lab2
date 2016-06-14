/* ���������� ����������������� ���, ���������� ����� ������� ��� ������ � �������� ��������. 
� ����������������� ���������� ������������� ������ ������� �� ��� �� ���������� ������ 
(�.�. "������"). ������� ������ �������� � �������� �������� ��� � ��������� ���������� 
����� ���������, � ����� ��� ������������� ���������� ��������� �� ���������. � �������� 
������� ������:
- �������� ����������������� ����������;
- ����� ��������� ����������������� ����������;
- ���� ��������� (�����) ��������� � ����������;
- ����� ��������� (�����) ��������� � ����������;
- ����� � ������� ��������� � ����������� ��������� ��������� ����;
- ���������� ������� �������� � ������� ����������� ��������� ���� (��� ���������� ����� 
������������ ��� ����, ��� � ��++ ����������� ������������ ����������������� ����������);
- ����� � ������� �������� �������� � �������� ��������� ���� ��� � �������� ������� � 
���� �� ��������. 
- �������� ��������� ��������;
- ��������� (��������������) ��������� ��������.
- ���������� � ��������� � �������������� ���� ��������� ������� �� ��������� ������� � 
������� (��������, ����� ����� �� ���� ������) -  ������ �������������.*/
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <locale.h>
#include <malloc.h>
#define TRUE 1
#define FALSE 0
#define ESC 27
typedef struct student myType;					// ������� ��� ���� "struct student"

struct student
{
	char *cp_name;
	char *cp_initials;
	int i_recBook;
	char *cp_department;
	int i_group;
	int i_isFull;								// 0 - ������, 1 - �������� ������
};

int menu();
myType* createArray();
void enter();
void show();
void delete(myType);
void edit(myType);

int main()
{
    setlocale(LC_ALL, "russian");
	myType single = {"�������", "�.�.",57,"�����������",974,1};
    printf("�������: %s %s", single.cp_name, single.cp_initials);
	myType *structArray = createArray();

    while (menu()==TRUE);

	free(structArray);
    return 0;
}

myType* createArray()
{
    printf("������� ���������� ��������� �������: ");
    int i_arrSize;
    scanf_s("%d", &i_arrSize);
	myType *Students;
    Students = (myType*)malloc(i_arrSize*sizeof(myType));
    return Students;
}

int menu()
{
    system("cls");
    printf("\t1 - ���� ������\n");
    printf("\t2 - ����� ������\n");
	printf("\t3 - ��������� ��������\n");
	printf("\t4 - �������� ��������\n");
	printf("\t5 - ������� ��������\n");
	printf("\t6 - ����� ��������� �������\n");
	printf("\t7 - \n");
	printf("\t8 - \n");
	printf("\t9 - \n");
	printf("\tESC - �����\n");
	char choice;
	while (!_kbhit());
    choice = _getch();
    switch(choice)
    {
        case '1':
            break;
        case '2':
            break;
        case ESC:
            return FALSE;
            break;
    }
    return TRUE;
}

void enter()
{
}

void show()
{
}

void edit(myType someOne)
{
}

void delete(myType someOne)
{

}