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
	int i_isFull;								// 0 - пустой, 1 - содержит данные
};

int menu();
struct student* createArray();

int main()
{
    setlocale(LC_ALL, "russian");
    struct student single = {"Антонов", "Ю.В.",57,"Информатика",974,1};
    printf("Студент: %s %s", single.cp_name, single.cp_initials);

    while (menu()==TRUE);
    return 0;
}

struct student* createArray()
{
    printf("Введите количество элементов массива: ");
    int arrSize;
    scanf("%d", &arrSize);
    
    struct student *Students;
    Students = (struct student*)malloc(arrSize*sizeof(struct student));
    return Students;
}

int menu()
{
    system("cls");
    printf("\t1 - ввод данных");
    printf("\t2 - вывод данных");
    printf("\tESC - выход");
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