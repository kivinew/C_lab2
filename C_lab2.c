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
формуле (например, общая сумма на всех счетах) -  дается индивидуально. 
    Префиксы переменных:				i, c - тип int, char	g - глобальные	р - указатель */
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <locale.h>

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
void addElement(),
	showElement(int),
	deleteElement(int),
	editElement(int),
	cleanElem(int),
	gotoxy(int, int),
	showAll(),
    sortByField();
myType* createArray();
int sortByName(const void*, const void*),
    sortByDept(const void*, const void*),
    sortByGroup(const void*, const void*),
    sortByRecBook(const void*, const void*);
/*-------------------------------------------------------------------------------------------------------------------------*/
myType *structArray;														// глобальный массив структур
int gi_arrSize;															    // и его размер
size_t g_buffSize = 10;                                                     // размер буфера ввода для fgets()
int gp_sort[4];

int main()
{
    setlocale(LC_ALL, "russian");

	myType single = {"Антонов ","ИВТ", "974И", 35535, 1};               // эталонная структура
    printf("Студент: %s %s\n", single.cp_name, single.cp_group);

	structArray = createArray();                                            // динамическое выделение памяти для массива
	int i;
	for (i = 0; i < gi_arrSize; i++)                                        // сдвигаем указатель по массиву
	{                                                                       // и присваиваем его элементам
		*structArray++ = single;                                            // значение эталонной структуры
	}                                                                       // затем сдвигаем указатель structArray
    structArray -= i;                                                       // в начало массива
	system("cls");

    while ( menu()==TRUE );                                                 // рабочий цикл программы

	//free(structArray);                                                    // очистка массива
    return 0;
}

myType* createArray()                                                       // возвращает указатель на массив структур
{                                                                           //
    printf("Введите количество элементов массива: ");                       //
    scanf_s("%d", &gi_arrSize);                                             //
	myType *Students;                                                       //
    Students = (myType*)malloc(gi_arrSize*sizeof(myType));                  //
	int i=0;                                                                //
	while ( i++ < gi_arrSize )                                              //
	{                                                                       //
		Students->cp_name = "- - - - - - - - - - ";                         // инициализация структур
		Students->cp_department = "- - - - - - - - - - ";                   //
        Students->cp_group = "----------";                                  //
		Students->i_recBook = 0;                                            //
		Students->i_isFull = 0;                                             //
        Students++;                                                         //
	}                                                                       //
    Students -= i;                                                          // сброс указателя
    return Students;                                                        //
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
	showAll();                                                              // вывод всех элементов
	char choice;
	while (!_kbhit());                                                      // ожидание выбора
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
            system("cls");
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
			sortByField();
			break;
        case ESC:
            return FALSE;
            break;
    }
    return TRUE;
}

void addElement()                                                           // добавить элемент
{                                                                           //
	editElement(growArray());                                               // редактировать элемент, номер которого
	return;                                                                 // вернула функция увеличения массива
}                                                                           //

void showElement(int number)												// вывод выбранного элемента
{
	if (number < 0 || number >= gi_arrSize)
	{
		gcp_lastError = "Выход за пределы массива (showElement)";
		return;
	}
    myType *ptr = structArray+number;
	printf("|%20s|%20s|%10d|%10s|\n",	
        ptr->cp_name,
        ptr->cp_department,
        ptr->i_recBook,
        ptr->cp_group);
	gcp_lastError = "Ошибок не было (show)";
	return;
}

void showAll()
{
	int i;
	gotoxy(10, 14);
	printf("|Фамилия И.О.        |Факультет           |№ зачётки | Группа   |\n");
	for (i = 0; i<gi_arrSize; i++)
	{
		gotoxy(10, 15+i);
		showElement(i);
	}
	return;
}

void editElement(int number)                                                // 
{                                                                           // 
	if (number < 0 || number >= gi_arrSize)                                 // 
	{																		// 
		gcp_lastError = "Выход за пределы массива (editElement)";           // 
		return;                                                             // 
	}                                                                       // 
    myType *ptr = structArray+number;                                       //
    char buffer[10] = "----------";
    printf("Введите ФИО:\n");                                               // 
    fflush(stdin);
    gets_s(buffer, g_buffSize);                                             // 
    ptr->cp_name = buffer;
    printf("Факультет:\n");                                                 // 
	//scanf_s("%s", ptr->cp_department, 40);                                // 
	//printf("Группа:\n");                                                  // 
	//scanf_s("%s", ptr->cp_group, 40);                                     // 
	//printf("Номер зачетки:\n");                                           // 
	//scanf_s("%i", &ptr->i_recBook);                                       // 
    //   ptr->i_isFull = 1;                                                 // 
    gcp_lastError = "Ошибок не было (edit)";                                // 
    return;                                                                 // 
}

void cleanElem(int number)
{
    myType *ptr = structArray+number;
	if (ptr->i_isFull==0)
	{
		gcp_lastError = "Элемент пуст";
		return;
	}
    ptr->cp_department = "--------------------";
    ptr->cp_name = "--------------------";
    ptr->cp_group = "----------";
    ptr->i_recBook = 0;
    ptr->i_isFull = 0;
	gcp_lastError = "Ошибок не было (clean)";
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
	gcp_lastError = "Ошибок не было (getClean)";
	return -1;
}

int growArray()																// вызывается при добавлении элемента в массив.
{
	gi_arrSize += 1;                                                        // увеличиваем размер   |
	int number = gi_arrSize;                                                // будущего массива.    |
	myType *temp = (myType*)malloc((number)*sizeof(myType));				// динамическое выделение памяти        |
	int i;                                                                  // под новый массив размера "number".   |
	for (i = 0; i<number-1; i++)
	{
		*temp++ = *structArray++;
	}                                                                       //
	temp->cp_department = "";                                               // инициализация    |
	temp->cp_group = "";                                                    // добавленного     |
	temp->cp_name = "";                                                     // в конец          |
	temp->i_recBook = 0;                                                    // массива          |
	temp->i_isFull = 0;                                                     // элемента         |
    temp -= i;                                                              // сдвиг в начало массива временного и  |
    structArray -= i;                                                       // основного указателей.                |
	//free(structArray);                                                    // освобождение памяти из-под старого массива   |
	structArray = temp;                                                     // и ориентирование указателя на новый          |
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
	gcp_lastError = "Ошибок не было (delete)";
	return;
}

void sortByField()
{
    gp_sort[0] = sortByName;
    gp_sort[1] = sortByGroup;
    gp_sort[2] = sortByDept;
    gp_sort[3] = sortByRecBook;
    printf("Вариант сортировки: \n"
        "\t1 - по фамилии"
        "\t2 - по группе"
        "\t3 - по факультету"
        "\t4 - по номеру зачётки");
    int choice;
    while (!_kbhit());
    choice = _getch();
    if (!choice<1||choice > 3)
    {
        qsort(structArray, gi_arrSize, sizeof(*structArray), gp_sort[choice-1]);
    }
    else
    {
        gcp_lastError = "Не верный выбор (sortBy)";
        return;
    }
    gcp_lastError = "Ошибок не было (sortBy)";
    return;
}

int sortByName(const void *arg1, const void *arg2)
{
    
    return 1;
}

int sortByGroup(const void *arg1, const void *arg2)
{

    return 1;
}

int sortByDept(const void *arg1, const void *arg2)
{

    return 1;
}

int sortByRecBook(const void *arg1, const void *arg2)
{

    return 1;
}

void gotoxy(int xpos, int ypos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = xpos; scrn.Y = ypos;
	SetConsoleCursorPosition(hOuput, scrn);
}
