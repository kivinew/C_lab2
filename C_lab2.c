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
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <locale.h>

#define TRUE 1
#define FALSE 0
#define ESC 27

typedef struct student
{
	char	cp_name[20],
			cp_department[20],
			cp_group[10];
	int		i_recBook,
			i_isFull;														// флаг: 0 - пустой, 1 - содержит данные
}myType;

int	menu(),
	getCleanElem(),
	growArray();
void addElement(),
	showElement(int),
	deleteElement(int),
	editElement(int),
	cleanElem(int),
	gotoxy(int, int),
	showAll(),
	sortSelect();
int sortByName(const void*, const void*),
	sortByDept(const void*, const void*),
	sortByGroup(const void*, const void*),
	sortByRecBook(const void*, const void*);
myType* createArray();
/*-------------------------------------------------------------------------------------------------------------------------*/
char *gcp_lastError = NULL;													// строка сообщений об ошибках
myType *structArray;														// глобальный массив структур
int gi_arrSize;															    // и его размер
int gp_sortFuncArr[4];														// массив из четырёх сортировок

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	structArray = createArray();                                            // динамическое выделение памяти для массива
	system("cls");
	while (menu()==TRUE);													// рабочий цикл программы
	free(structArray);														// очистка массива
	return 0;
}

myType* createArray()                                                       // возвращает указатель на массив структур
{                                                                           //
	printf("Введите количество элементов массива: ");                       //
	scanf_s("%d", &gi_arrSize);                                             //
	myType *tempPtr;														//
	tempPtr = (myType*)malloc(gi_arrSize*sizeof(myType));					//
	int i;
	for (i = 0; i<gi_arrSize; i++)											// сдвигаем указатель по массиву
	{                                                                       // и присваиваем его элементам
		strcpy(tempPtr->cp_department, "");
		strcpy(tempPtr->cp_name, "");
		strcpy(tempPtr->cp_group, "");
		tempPtr->i_recBook = 0;
		tempPtr->i_isFull = 0;
		tempPtr++;															// значение эталонной структуры
	}                                                                       // затем сдвигаем указатель structArray
	tempPtr -= i;															// в начало массива
	return tempPtr;															// возвращает указатель на массив структур
}

int menu()
{
	system("cls");
	printf(	"Размер массива: %d\t"
			"Сообщения об ошибках: %s\n", gi_arrSize, gcp_lastError);
	printf(	"\t1 - добавить строку\n"
			"\t2 - вывод строки\n"
			"\t3 - изменение элемента\n"
			"\t4 - удаление элемента со сдвигом\n"
			"\t5 - очистка элемента\n"
			"\t6 - вывод свободного элемента\n"
			"\t7 - найти элемент с минимальным значением поля \"Группа\"\n"
			"\t8 - найти элемент со значением поля \"Группа\", близким к указанному\n"
			"\t9 - поиск элементов со значением поля \"Группа\" равным указанному\n"
			"\t0 - сортировка массива по возрастанию значения поля \"Группа\"\n"
			"\tESC - выход\n");
	gotoxy(10, 14);
	printf("|  №|        Фамилия И.О.|           Факультет|    Группа| № зачётки|");
	showAll();                                                              // вывод всех элементов
	char choice;
	choice = _getch();
	int number, emptyNumber;												// номер элемента/"пустого" элемента
	switch (choice)
	{
	case '1':
		addElement();
		break;
	case '2':
		printf("Номер элемента для вывода: ");
		scanf_s("%d", &number);
		if (number < 0||number >= gi_arrSize)
		{
			gcp_lastError = "Выход за пределы массива (show)";
			break;
		}
		if ((structArray+number)->i_isFull = 0)
		{
			gcp_lastError = "Элемент пуст (show)";
			break;
		}
		system("cls");
		gotoxy(10, 12);
		printf("Содержимое %d-го элемента маcсива: \n", number);
		gotoxy(10, 14);
		printf("|  №|        Фамилия И.О.|           Факультет|    Группа| № зачётки|");
		gotoxy(10, 15+number);
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
		emptyNumber = getCleanElem();									// функция вернёт номер пустого
		if (emptyNumber < 0)											// или -1, если такого нет
		{
			system("cls");
			gotoxy(20, 10);
			printf("Пустых элементов нет!");
			_getch();
			break;
		}			
		system("cls");
		gotoxy(35, 12);
		printf("Пустой элемент №: %d", emptyNumber);
		gotoxy(10, 14);
		printf("|  №|        Фамилия И.О.|           Факультет|    Группа| № зачётки|\n");
		gotoxy(10, 15+emptyNumber);
		showElement(emptyNumber);
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
		gotoxy(0,22);
		printf("\tВариант сортировки: \n"
			   "\t1 - по фамилии"
			   "\t2 - по факультету"
			   "\t3 - по группе"
			   "\t4 - по номеру зачётки");
		sortSelect();
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
	if (number<0 || number>=gi_arrSize)
	{
		gcp_lastError = "Выход за пределы массива (showElement)";
		return;
	}
	myType *tempPtr = structArray + number;
	printf("|%3d|%20s|%20s|%10s|%10d|\n",
		number,
		tempPtr->cp_name,
		tempPtr->cp_department,
		tempPtr->cp_group,
		tempPtr->i_recBook);
	gcp_lastError = "Ошибок не было (show)";
	return;
}

void showAll()
{
	int i;
	for (i = 0; i<gi_arrSize; i++)
	{
		gotoxy(10, 15+i);
		showElement(i);
	}
	return;
}

void editElement(int number)                                                // 
{                                                                           // 
	if (number<0||number>=gi_arrSize)										// 
	{																		// 
		gcp_lastError = "Выход за пределы массива (editElement)";           // 
		return;                                                             // 
	}                                                                       //
	myType *tempPtr = structArray+number;                                   // указатель ориентирую на выбранный элемент структуры
	printf("Введите ФИО: ");												// и запрашиваю новые данные полей
	scanf("%s", tempPtr->cp_name);											// 
	printf("Факультет: ");													// 
	scanf("%s", tempPtr->cp_department);									// 
	printf("Группа: ");														// 
	scanf("%s", tempPtr->cp_group);											// 
	printf("Номер зачётки: ");												// 
	scanf("%i", &tempPtr->i_recBook);										// 
	tempPtr->i_isFull = 1;													// 
	gcp_lastError = "Ошибок не было (edit)";                                // 
	return;                                                                 // 
}

void cleanElem(int number)
{
	if (number<0||number>=gi_arrSize)										// 
	{																		// 
		gcp_lastError = "Выход за пределы массива (clean)";					// 
		return;                                                             // 
	}                                                                       //
	myType *tempPtr = structArray + number;
	if (tempPtr->i_isFull==0)
	{
		gcp_lastError = "Элемент пуст (clean)";
		return;
	}
	strcpy(tempPtr->cp_department, "");
	strcpy(tempPtr->cp_name, "");
	strcpy(tempPtr->cp_group, "");
	tempPtr->i_recBook = 0;
	tempPtr->i_isFull = 0;
	gcp_lastError = "Ошибок не было (clean)";
	return;
}

int getCleanElem()
{
	int i;
	for (i = 0; i<gi_arrSize; i++)
	{
		if (structArray->i_isFull == 0)
		{
			structArray -= i;
			return i;
		}
		structArray++;
	}
	structArray -= i;
	gcp_lastError = "Ошибок не было (getClean)";
	return -1;
}

int growArray()																// вызывается при добавлении элемента в массив.
{
	gi_arrSize += 1;                                                        // увеличиваем размер будущего массива. |
	myType *tempPtr = (myType*)malloc((gi_arrSize)*sizeof(myType));			// динамическое выделение памяти        |
	int i;                                                                  // под новый массив размера "size+1".   |
	for (i = 0; i<gi_arrSize-1; i++)										// копирование всех					|
	{																		// элементов исходного массива		|
		*tempPtr++ = *structArray++;										// в новый путём сдвига указателей.	|
	}                                                                       //
	tempPtr -= i;                                                           // сдвиг в начало массива временного и  |
	structArray -= i;                                                       // основного указателей.                |
	free(structArray);														// освобождение памяти из-под старого массива   |
	structArray = tempPtr;                                                  // и ориентирование указателя на новый          |
	return gi_arrSize-1;
}

void deleteElement(int number)
{
	if (number < 0 || number >= gi_arrSize)
	{
		gcp_lastError = "Выход за пределы массива (deleteElement)";
		return;
	}
	int i;
	for (i = number; i<gi_arrSize-1; i++)
	{
		structArray[i] = structArray[i+1];
	}
	cleanElem(i);															// очистка последнего элемента после сдвига
	gcp_lastError = "Ошибок не было (delete)";
	return;
}

void sortSelect()																// сортировка массива по полям
{
	gp_sortFuncArr[0] = sortByName;												// заполняю массив сортировок
	gp_sortFuncArr[1] = sortByDept;												//
	gp_sortFuncArr[2] = sortByGroup;											//
	gp_sortFuncArr[3] = sortByRecBook;											//
	int choice;
	choice = _getch();
	if (choice < '1' || choice > '4')
	{
		gcp_lastError = "Не верный выбор (sortBy)";
		return;
	}
	choice = choice -'0';														// 
	qsort(structArray, gi_arrSize, sizeof(myType), gp_sortFuncArr[choice-1]);	// вызов библиотечной сортировки
	gcp_lastError = "Ошибок не было (sortBy)";									// с выбранным полем сортировки
	return;
}

int sortByName(const void *arg1, const void *arg2)
{
	myType *one = (myType*)arg1;
	myType *two = (myType*)arg2;
	return strcmp(one->cp_name, two->cp_name);									// сравнение двух строк (библ.функция)
}

int sortByGroup(const void *arg1, const void *arg2)
{
	myType *one = (myType*)arg1;
	myType *two = (myType*)arg2;
	return strcmp(one->cp_group, two->cp_group);								// сравнение двух строк (библ.функция)
}

int sortByDept(const void *arg1, const void *arg2)
{
	myType *one = (myType*)arg1;
	myType *two = (myType*)arg2;
	return strcmp(one->cp_department, two->cp_department);						// сравнение двух строк (библ.функция)
}

int sortByRecBook(const void *arg1, const void *arg2)
{
	int one = ((myType*)arg1)->i_recBook;
	int two = ((myType*)arg2)->i_recBook;
	return one-two;
}

void gotoxy(int xpos, int ypos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = xpos; scrn.Y = ypos;
	SetConsoleCursorPosition(hOuput, scrn);
}
