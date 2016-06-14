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
typedef struct student myType;					// синоним для типа "struct student"

struct student
{
	char *cp_name;
	char *cp_initials;
	int i_recBook;
	char *cp_department;
	int i_group;
	int i_isFull;								// 0 - пустой, 1 - содержит данные
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
	myType single = {"Антонов", "Ю.В.",57,"Информатика",974,1};
    printf("Студент: %s %s", single.cp_name, single.cp_initials);
	myType *structArray = createArray();

    while (menu()==TRUE);

	free(structArray);
    return 0;
}

myType* createArray()
{
    printf("Введите количество элементов массива: ");
    int i_arrSize;
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
	printf("\t7 - \n");
	printf("\t8 - \n");
	printf("\t9 - \n");
	printf("\tESC - выход\n");
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