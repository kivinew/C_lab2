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
#include <locale.h>
#include <malloc.h>
#define TRUE 1
#define FALSE 0

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
struct student* createArray();

int main()
{
    setlocale(LC_ALL, "russian");
    struct student single = {"�������", "�.�.",57,"�����������",974,1};
    printf("�������: %s %s", single.cp_name, single.cp_initials);

    while (menu()==TRUE);
    return 0;
}

struct student* createArray()
{
    printf("������� ���������� ��������� �������: ");
    int arrSize;
    scanf("%d", &arrSize);
    
    struct student *Students;
    Students = (struct student*)malloc(arrSize*sizeof(struct student));
    return Students;
}

int menu()
{
    system("cls");
    printf("\t1 - ���� ������");
    printf("\t2 - ����� ������");
    printf("\tESC - �����");
    while (!_kbhit());
    char choice;
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
        case default:
            break;
    }
    return TRUE;
}