﻿/* Определить структурированный тип, определить набор функций для работы с массивом структур. 
В структурированной переменной предусмотреть способ отметки ее как не содержащей данных 
(т.е. "пустой"). Функции должны работать с массивом структур или с отдельной структурой 
через указатели, а также при необходимости возвращать указатель на структуру. В перечень 
функций входят:
- «очистка» структурированных переменных;
- поиск свободной структурированной переменной;
- ввод элементов (полей) структуры с клавиатуры;
- вывод элементов (полей) структуры с клавиатуры;
- поиск в массиве структуры с минимальным значением заданного поля;
- сортировка массива структур в порядке возрастания заданного поля (при сортировке можно 
использовать тот факт, что в Си++ разрешается присваивание структурированных переменных);
- поиск в массиве структур элемента с заданным значением поля или с наиболее близким к 
нему по значению. 
- удаление заданного элемента;
- изменение (редактирование) заданного элемента.
- вычисление с проверкой и использованием всех элементов массива по заданному условию и 
формуле (например, общая сумма на всех счетах) -  дается индивидуально. 
    Префиксы переменных:				i, c - тип int, char	g - глобальные	р - указатель */
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <locale.h>
#include <malloc.h>

#define TRUE 1
#define FALSE 0
#define ESC 27

typedef struct student myType;												// синоним для типа "struct student"

struct student
{
	char	*cp_name,
			*cp_department,
			*cp_group;
	int		i_recBook,
			i_isFull;														// флаг: 0 - пустой, 1 - содержит данные
};

char *gcp_lastError = NULL;
int menu();
int	getCleanElem();
int	growArray();
myType* createArray();
void addElement(),
	showElement(int),
	deleteElement(int),
	editElement(int),
	cleanElem(int),
	gotoxy(int, int),
	showAll();
/*-------------------------------------------------------------------------------------------------------------------------*/
myType *structArray;														// глобальный массив структур
int gi_arrSize;																// и его размер

int main()
{
    setlocale(LC_ALL, "russian");
	myType single = {"Антонов Ю.В.","ИВТ", "974И", 35535, 1};
    printf("Студент: %s %s\n", single.cp_name, single.cp_group);

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

myType* createArray()														// создание динамического массива структур
{
    printf("Введите количество элементов массива: ");
    scanf_s("%d", &gi_arrSize);
	myType *Students;
    Students = (myType*)malloc(gi_arrSize*sizeof(myType));
	int i;
	for (i = 0; i<gi_arrSize; i++)
	{
		Students[i].cp_name = NULL;											// инициализация структур
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
	printf("Размер массива: %d\t", gi_arrSize);
	printf("Последняя ошибка: %s\n", gcp_lastError);
	printf("\t1 - добавить элемент\n"
			"\t2 - вывод данных\n"
			"\t3 - изменение элемента\n"
			"\t4 - удаление элемента из массива\n"
			"\t5 - очистка элемента\n"
			"\t6 - найти свободный элемент\n"
			"\t7 - найти элемент с минимальным значением поля \"Группа\"\n"
			"\t8 - найти элемент со значением поля \"Группа\", близким к указанному\n"
			"\t9 - поиск элементов со значением поля \"Группа\" равным указанному\n"
			"\t0 - сортировка массива по возрастанию значения поля \"Группа\"\n"
			"\tESC - выход\n");
	showAll();
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
			printf("Номер элемента для вывода: ");
			scanf_s("%d", &number);
			gotoxy(10, 15);
			printf("Содержимое %d-го элемента маcсива: \n", number);
			showElement(number);
			_getch();
			break;
		case '3':
			printf("Номер элемента для изменения: ");
			scanf_s("%d", &number);
			editElement(number);
			break;
		case '4':
			printf("Номер элемента для удаления: ");
			scanf_s("%d", &number);
			deleteElement(number);        
			break;
		case '5':
			printf("Номер элемента для очистки: ");
			scanf_s("%d", &number);
			cleanElem(number);
			break;
		case '6':
			number = getCleanElem();										// функция вернёт номер пустого
			if (number>=0)													// или -1, если такого нет
			{
				showElement(number);
			}
			else
			{
				printf("\nПустых элементов нет!\n");
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

void addElement()															// добавить элемент
{																			//
	editElement(growArray());												// редактировать элемент, номер которого
	return;																	// вернула функция увеличения массива
}

void showElement(int number)												// вывод выбранного элемента
{
	if (number < 0 || number >= gi_arrSize)
	{
		gcp_lastError = "Выход за пределы массива (showElement)";
		return;
	}
	printf("|%20s|%20s|%11d|%8s|\n",	
		structArray[number].cp_name, 
		structArray[number].cp_department,
		structArray[number].i_recBook,
		structArray[number].cp_group);
	gcp_lastError = "Ошибок не было";
	return;
}

void showAll()
{
	int i;
	gotoxy(10, 14);
	printf("|Фамилия И.О.        |Факультет           | № зачётки | Группа |\n");
	for (i = 0; i<gi_arrSize; i++)
	{
		gotoxy(10, 15+i);
		showElement(i);
	}
	return;
}

void editElement(int number)
{
	if (number < 0 || number >= gi_arrSize)
	{
		gcp_lastError = "Выход за пределы массива (editElement)";
		return;
	}
	gcp_lastError = "Ошибок не было";
	printf("Введите ФИО:\n");
	scanf_s("%s", structArray[number].cp_name, 40);
	printf("Факультет:\n");
	scanf_s("%s", structArray[number].cp_department, 40);
	printf("Группа:\n");
	scanf_s("%s", structArray[number].cp_group, 40);
	printf("Номер зачетки:\n");
	scanf_s("%i", &structArray[number].i_recBook);
	structArray[number].i_isFull = 1;
	return;
}

void cleanElem(int number)
{
	if (structArray[number].i_isFull==0)
	{
		gcp_lastError = "Элемент пуст";
		return;
	}
	structArray[number].cp_department = NULL;
	structArray[number].cp_name = NULL;
	structArray[number].cp_group = NULL;
	structArray[number].i_recBook = 0;
	structArray[number].i_isFull = 0;
	gcp_lastError = "Ошибок не было";
	return;
}

int getCleanElem()
{
	int i;
	for(i=0; i<gi_arrSize; i++)
	{
		if (!structArray[i].i_isFull)
		{
			return i;
		}
	}
	gcp_lastError = "Ошибок не было";
	return -1;
}

int growArray()																// вызывается при добавлении элемента в массив
{
	gi_arrSize += 1;
	int number = gi_arrSize;
	myType *temp = (myType*)malloc((number)*sizeof(myType));				// новый массив размера "number"
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
		gcp_lastError = "Выход за пределы массива (deleteElement)";
		return;
	}
	int i;
	for (i = number; i < gi_arrSize-1; i++)
	{
		structArray[i] = structArray[i + 1];
	}
	cleanElem(i);														// очистка последнего элемента после сдвига
	gcp_lastError = "Ошибок не было";
	return;
}

void gotoxy(int xpos, int ypos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = xpos; scrn.Y = ypos;
	SetConsoleCursorPosition(hOuput, scrn);
}
