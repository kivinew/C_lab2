/* Определить структурированный тип, определить набор функций для работы с массивом структур. 
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
формуле (например, общая сумма на всех счетах) -  дается индивидуально.*/
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <locale.h>
#include <malloc.h>
#define TRUE 1
#define FALSE 0
#define ESC 27
typedef struct student myType;									// синоним для типа "struct student"

struct student
{
	char *cp_name;
	char *cp_department;
	int i_recBook;
	int i_group;
	int i_isFull;								// 0 - пустой, 1 - содержит данные
};

int menu();
myType* createArray();
void enter(int);
void show(int);
void delete(int);
void edit(int);
void clean(int);
int getClean();
myType *structArray;											// глобальный массив структур
int i_arrSize;													// и его размер

int main()
{
    setlocale(LC_ALL, "russian");
	myType single = {"Антонов Ю.В.",57,"Информатика",974,1};
    printf("Студент: %s %i", single.cp_name, single.i_group);
	structArray = createArray();

    while (menu()==TRUE);

	free(structArray);
    return 0;
}

myType* createArray()											// 
{
    printf("Введите количество элементов массива: ");
    scanf_s("%d", &i_arrSize);
	myType *Students;
    Students = (myType*)malloc(i_arrSize*sizeof(myType));
    return Students;
}

int menu()
{
    system("cls");
    printf("\t1 - ввод данных\n");
    printf("\t2 - вывод данных\n");
	printf("\t3 - изменение элемента\n");
	printf("\t4 - удаление элемента\n");
	printf("\t5 - очистка элемента\n");
	printf("\t6 - найти свободный элемент\n");
	printf("\t7 - найти элемент с минимальным значением поля \"Группа\"\n");
	printf("\t8 - найти элемент со значением поля \"Группа\", близким к указанному\n");
	printf("\t9 - поиск элементов со значением поля \"Группа\" равным указанному\n");
	printf("\t0 - сортировка массива по возрастанию значения поля \"Группа\"\n");
	printf("\tESC - выход\n");
	char choice;
	while (!_kbhit());
    choice = _getch();
	int number;
	switch(choice)
    {
        case '1':
			printf("Номер элемента для ввода: ");
			scanf_s("%d", &number);
			enter(number);
            break;
        case '2':
			printf("Номер элемента для вывода: ");
			scanf_s("%d", &number);
			show(number);
			break;
		case '3':
			printf("Номер элемента для изменения: ");
			scanf_s("%d", &number);
			edit(number);
			break;
		case '4':
			printf("Номер элемента для удаления: ");
			scanf_s("%d", &number);
			delete(number);        
			break;
		case '5':
			printf("Номер элемента для очистки: ");
			scanf_s("%d", &number);
			clean(number);
			break;
		case '6':
			number = getClean();
			if (number>=0)
			{
				show(number);
			}
			else
			{
				printf("\nПустых элементов нет!\n");
			}
			break;
		case '7':
			getMinField();
			break;
		case '8':
			getFieldIs();
            break;
		case '9':
			searchByCondition();
			break;
		case '0':
			sortByField();
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
}

void edit(int number)
{
}

void clean(int number)
{
	structArray[number].cp_department = NULL;
	structArray[number].cp_name = NULL;
	structArray[number].i_group = 0;
	structArray[number].i_recBook = 0;
	structArray[number].i_isFull = 0;
}

int getClean()
{
	int number;
	for(int i=0; i<i_arrSize; i++)
		if (!structArray[i].i_isFull)
		{
			return number;
		}
	return -1;
}

void delete(int number)
{
	myType *temp = structArray;									// новый массив меньшего размера
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