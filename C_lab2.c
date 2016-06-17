/* Определить структурированный тип, определить набор функций для работы с массивом структур. 
В структурированной переменной предусмотреть способ отметки ее как не содержащей данных 
(т.е. "пустой"). Функции должны работать с массивом структур или с отдельной структурой 
через указатели, а также при необходимости возвращать указатель на структуру. В перечень 
функций входят:
- «очистка» структурированных переменных;
- поиск свободной структурированной переменной;
- ввод полей структуры с клавиатуры;
- вывод полей структуры;
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

typedef struct student myType;												// синоним для struct student
struct student
{
	char	*cp_name,
			*cp_department,
			*cp_group;
	int		i_recBook,
			i_isFull;														// флаг: 0 - пустой, 1 - содержит данные
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
myType *structArray;														// глобальный массив структур
int i_arrSize;																// и его размер

int main()
{
    setlocale(LC_ALL, "russian");
	myType single = {"Антонов Ю.В.","Информатика", "974ИВТ", 35535, 1};
    printf("Студент: %s %s\n", single.cp_name, single.cp_group);

	structArray = createArray();
	structArray[0] = single;

    while ( menu()==TRUE );

	free(structArray);
    return 0;
}

myType* createArray()														// создание динамического массива структур
{
    printf("Введите количество элементов массива: ");
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
    printf("\t1 - ввод данных\n");
    printf("\t2 - вывод данных\n");
	printf("\t3 - изменение элемента\n");
	printf("\t4 - удаление элемента из массива\n");
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
			number = getClean();											// функция вернёт номер пустого
			if (number>=0)													// или -1, если такого нет
			{
				show(number);
			}
			else
			{
				printf("\nПустых элементов нет!\n");
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
	printf("Содержимое %d-го элемента маcсива: \n", number);
	printf("|Фамилия И.О.        |Факультет           | № зачётки | Группа |\n");
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
	myType *temp = structArray;												// новый массив меньшего размера
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
