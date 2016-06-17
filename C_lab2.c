/* ���������� ����������������� ���, ���������� ����� ������� ��� ������ � �������� ��������. 
� ����������������� ���������� ������������� ������ ������� �� ��� �� ���������� ������ 
(�.�. "������"). ������� ������ �������� � �������� �������� ��� � ��������� ���������� 
����� ���������, � ����� ��� ������������� ���������� ��������� �� ���������. � �������� 
������� ������:
- �������� ����������������� ����������;
- ����� ��������� ����������������� ����������;
- ���� ����� ��������� � ����������;
- ����� ����� ���������;
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

typedef struct student myType;												// ������� ��� struct student
struct student
{
	char	*cp_name,
			*cp_department,
			*cp_group;
	int		i_recBook,
			i_isFull;														// ����: 0 - ������, 1 - �������� ������
};
/*--------------------------------------------------------------------------------------------------------------------*/
int menu(),
	getClean();
myType* createArray();
void enter(int),
	show(int),
	delete(int),
	edit(int),
	clean(int);
void gotoxy(int, int);
/*-------------------------------------------------------------------------------------------------------------------*/
myType *structArray;														// ���������� ������ ��������
int i_arrSize;																// � ��� ������

int main()
{
    setlocale(LC_ALL, "russian");
	myType single = {"������� �.�.","�����������", "974���", 35535, 1};
    printf("�������: %s %s\n", single.cp_name, single.cp_group);

	structArray = createArray();
	structArray[0] = single;

    while ( menu()==TRUE );

	free(structArray);
    return 0;
}

myType* createArray()														// �������� ������������� ������� ��������
{
    printf("������� ���������� ��������� �������: ");
    scanf_s("%d", &i_arrSize);
	myType *Students;
    Students = (myType*)malloc(i_arrSize*sizeof(myType));
	int i;
	for (i = 0; i<i_arrSize; i++)
	{
		Students[i] = {"1", "2", "3", 0, 0};
	}
    return Students;
}

int menu()
{
    system("cls");
    printf("\t1 - ���� ������\n");
    printf("\t2 - ����� ������\n");
	printf("\t3 - ��������� ��������\n");
	printf("\t4 - �������� �������� �� �������\n");
	printf("\t5 - ������� ��������\n");
	printf("\t6 - ����� ��������� �������\n");
	printf("\t7 - ����� ������� � ����������� ��������� ���� \"������\"\n");
	printf("\t8 - ����� ������� �� ��������� ���� \"������\", ������� � ����������\n");
	printf("\t9 - ����� ��������� �� ��������� ���� \"������\" ������ ����������\n");
	printf("\t0 - ���������� ������� �� ����������� �������� ���� \"������\"\n");
	printf("\tESC - �����\n");
	char choice;
	while (!_kbhit());
    choice = _getch();
	int number;
	switch(choice)
    {
        case '1':
			printf("����� �������� ��� �����: ");
			scanf_s("%d", &number);
			enter(number);
            break;
        case '2':
			printf("����� �������� ��� ������: ");
			scanf_s("%d", &number);
			show(number);
			break;
		case '3':
			printf("����� �������� ��� ���������: ");
			scanf_s("%d", &number);
			edit(number);
			break;
		case '4':
			printf("����� �������� ��� ��������: ");
			scanf_s("%d", &number);
			delete(number);        
			break;
		case '5':
			printf("����� �������� ��� �������: ");
			scanf_s("%d", &number);
			clean(number);
			break;
		case '6':
			number = getClean();											// ������� ����� ����� �������
			if (number>=0)													// ��� -1, ���� ������ ���
			{
				show(number);
			}
			else
			{
				printf("\n������ ��������� ���!\n");
			}
			_getch();
			break;
		case '7':
			//getMinField();
			break;
		case '8':
			//getFieldIs();
            break;
		case '9':
			//searchByCondition();
			break;
		case '0':
			//sortByField();
			break;
        case ESC:
            return FALSE;
            break;
    }
    return TRUE;
}

void enter(int number)
{

}

void show(int number)
{
	gotoxy(10,15);
	printf("���������� %d-�� �������� ��c����: \n", number);
	printf("|������� �.�.        |���������           | � ������� | ������ |\n");
	printf("|%20s|%20s|%11d|%8s|\n",	
		structArray[number].cp_name, 
		structArray[number].cp_department,
		structArray[number].i_recBook,
		structArray[number].cp_group);
	_getch();
	return;
}

void edit(int number)
{

}

void clean(int number)
{
	structArray[number].cp_department = NULL;
	structArray[number].cp_name = NULL;
	structArray[number].cp_group = NULL;
	structArray[number].i_recBook = 0;
	structArray[number].i_isFull = 0;
}

int getClean()
{
	int i;
	for(i=0; i<i_arrSize; i++)
		if (!structArray[i].i_isFull)
		{
			return i;
		}
	return -1;
}

void delete(int number)
{
	myType *temp = structArray;												// ����� ������ �������� �������
	temp = (myType*)malloc((i_arrSize-1)*sizeof(myType));
	int i;
	for (i = 0; i<i_arrSize; i++)
	{
		if (i < number)
		{
			temp[i] = structArray[i];
		}
		else
		{
			temp[i] = structArray[i+1];
		}
	}
	free(structArray);
	structArray = temp;
	return;
}

void gotoxy(int xpos, int ypos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = xpos; scrn.Y = ypos;
	SetConsoleCursorPosition(hOuput, scrn);
}
