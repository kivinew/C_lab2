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

typedef struct student myType;												// ������� ��� ���� "struct student"

struct student
{
	char	*cp_name,
			*cp_department,
			*cp_group;
	int		i_recBook,
			i_isFull;														// ����: 0 - ������, 1 - �������� ������
};

char *gcp_lastError = NULL;
int menu();
myType* createArray();
void addElement();
void showElement(int);
int growStructArray();
void deleteElement(int);
void editElement(int);
void cleanElem(int);
int getcleanElem();
void gotoxy(int, int);
myType *structArray;														// ���������� ������ ��������
int gi_arrSize;																// � ��� ������

int main()
{
    setlocale(LC_ALL, "russian");
	myType single = {"������� �.�.","�����������", "974���", 35535, 1};
    printf("�������: %s %s\n", single.cp_name, single.cp_group);

	structArray = createArray();
	int i;
	for (i = 0; i < gi_arrSize; i++)
	{
		structArray[i] = single;
	}
	system("cls");
    while ( menu()==TRUE );

	free(structArray);
    return 0;
}

myType* createArray()														// �������� ������������� ������� ��������
{
    printf("������� ���������� ��������� �������: ");
    scanf_s("%d", &gi_arrSize);
	myType *Students;
    Students = (myType*)malloc(gi_arrSize*sizeof(myType));
	int i;
	for (i = 0; i<gi_arrSize; i++)
	{
		Students[i].cp_name = NULL;											// ������������� ��������
		Students[i].cp_department = NULL;
		Students[i].cp_group = NULL;
		Students[i].i_recBook = 0;
		Students[i].i_isFull = 0;
}
    return Students;
}

int menu()
{
    system("cls");
	printf("������ �������: %d\t", gi_arrSize);
	printf("��������� ������: %s\n", gcp_lastError);
    printf("\t1 - �������� �������\n");
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
			addElement();

            break;
        case '2':
			printf("����� �������� ��� ������: ");
			scanf_s("%d", &number);
			showElement(number);
			break;
		case '3':
			printf("����� �������� ��� ���������: ");
			scanf_s("%d", &number);
			editElement(number);
			break;
		case '4':
			printf("����� �������� ��� ��������: ");
			scanf_s("%d", &number);
			deleteElement(number);        
			break;
		case '5':
			printf("����� �������� ��� �������: ");
			scanf_s("%d", &number);
			cleanElem(number);
			break;
		case '6':
			number = getcleanElem();										// ������� ����� ����� �������
			if (number>=0)													// ��� -1, ���� ������ ���
			{
				showElement(number);
			}
			else
			{
				printf("\n������ ��������� ���!\n");
				_getch();
			}
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

void addElement()															// �������� �������
{																			//
	editElement(growStructArray());											// ������������� �������, ����� ��������
	return;																	// ������� ������� ���������� �������
}

void showElement(int number)												// ����� ���������� ��������
{
	if (number < 0 || number >= gi_arrSize)
	{
		gcp_lastError = "����� �� ������� ������� (showElement)";
		return;
	}
	gotoxy(10,15);
	printf("���������� %d-�� �������� ��c����: \n", number);
	printf("|������� �.�.        |���������           | � ������� | ������ |\n");
	printf("|%20s|%20s|%11d|%8s|\n",	
		structArray[number].cp_name, 
		structArray[number].cp_department,
		structArray[number].i_recBook,
		structArray[number].cp_group);
	_getch();
	gcp_lastError = "������ �� ����";
	return;
}

void editElement(int number)
{
	if (number < 0 || number >= gi_arrSize)
	{
		gcp_lastError = "����� �� ������� ������� (editElement)";
		return;
	}
	gcp_lastError = "������ �� ����";
	printf("������� ���:\n");
	scanf_s("%s", structArray[number].cp_name, 40);
	printf("���������:\n");
	scanf_s("%s", structArray[number].cp_department, 40);
	printf("������:\n");
	scanf_s("%s", structArray[number].cp_group, 40);
	printf("����� �������:\n");
	scanf_s("%i", &structArray[number].i_recBook);
	structArray[number].i_isFull = 1;
	return;
}

void cleanElem(int number)
{
	structArray[number].cp_department = NULL;
	structArray[number].cp_name = NULL;
	structArray[number].cp_group = NULL;
	structArray[number].i_recBook = 0;
	structArray[number].i_isFull = 0;
	return;
}

int getcleanElem()
{
	int i;
	for(i=0; i<gi_arrSize; i++)
	{
		if (!structArray[i].i_isFull)
		{
			return i;
		}
	}
	gcp_lastError = "������ �� ����";
	return -1;
}

int growStructArray()														// ���������� ��� ���������� �������� � ������
{
	gi_arrSize += 1;
	int number = gi_arrSize;
	myType *temp;													// ����� ������ ������� "number"
	temp = (myType*)malloc((number)*sizeof(myType));
	int i;
	for (i = 0; i<number-1; i++)
	{
		temp[i] = structArray[i];
	}
	temp[i].cp_department = NULL;
	temp[i].cp_group = NULL;
	temp[i].cp_name = NULL;
	temp[i].i_recBook = 0;
	temp[i].i_isFull = 0;
	free(structArray);
	structArray = temp;
	return number;
}

void deleteElement(int number)
{
	if (number >= gi_arrSize)
	{
		gcp_lastError = "����� �� ������� ������� (deleteElement)";
		return;
	}
	int i;
	for (i = number; i < gi_arrSize-1; i++)
	{
		structArray[i] = structArray[i + 1];
	}
	cleanElem(i);														// ������� ���������� �������� ����� ������
	gcp_lastError = "������ �� ����";
	return;
}

void gotoxy(int xpos, int ypos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = xpos; scrn.Y = ypos;
	SetConsoleCursorPosition(hOuput, scrn);
}
