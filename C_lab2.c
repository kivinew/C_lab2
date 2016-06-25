/*  Кудрявцев И.В. Поток 09.2015. Группа 1.
✈✈✈Вариант 5. Фамилия И.О., номер зачетной книжки, факультет, группа.✈✈✈
Определить структурированный тип, определить набор функций для работы с массивом структур.
В структурированной переменной предусмотреть способ отметки ее как не содержащей данных
(т.е. "пустой"). Функции должны работать с массивом структур или с отдельной структурой
через указатели, а также при необходимости возвращать указатель на структуру. В перечень
функций входят:
- «очистка» структурированных переменных;
- поиск свободной структурированной переменной;
- ввод элементов (полей) структуры с клавиатуры;
- вывод элементов (полей) структуры;
- поиск в массиве структуры с минимальным значением заданного поля;
- сортировка массива структур в порядке возрастания заданного поля (при сортировке можно
использовать тот факт, что в Си++ разрешается присваивание структурированных переменных);
- поиск в массиве структур элемента с заданным значением поля или с наиболее близким к
нему по значению;
- удаление заданного элемента;
- изменение (редактирование) заданного элемента.
- вычисление с проверкой и использованием всех элементов массива по заданному условию и
формуле - определить самую многочисленную группу.
	Префиксы переменных:	i, c - тип int, char	g - глобальные	р - указатель */
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
	//#include <locale.h>

#define TRUE 1
#define FALSE 0
#define ESC 27
//#define INT_MAX 2147000000
typedef struct student
{
	char	cp_name[20],													// 3 строки для записи фамилии,
			cp_department[20],												// факультета,
			cp_group[10];													// и группы.
	int		i_recBook,														// номер зачётки.
			i_isFull;														// флаг: 0 - пустой, 1 - содержит данные
}myType;
struct groupSize
{
	char group[10];
	int countStudents;
};
int	menu(),
	getCleanElem(),
	growArray(),
	sortByName(const void*, const void*),
	sortByDept(const void*, const void*),
	sortByGroup(const void*, const void*),
	sortByRecBook(const void*, const void*),
	getMinValue(),
	findValue(int);
void addElement(),
	showElement(int),
	deleteElement(int),
	editElement(int),
	cleanElem(int),
	gotoxy(int x, int y),
	showAll(),
	sortSelect();
struct groupSize *findLargestGroup();
myType	*createArray();
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
	scanf("%d", &gi_arrSize);												//
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

void addElement()                                                           // добавить элемент
{                                                                           //
	editElement(growArray());                                               // редактировать элемент, номер которого
	return;                                                                 // вернула функция увеличения массива
}                                                                           //

void showElement(int number)												// вывод выбранного элемента
{
	if (number<0||number>=gi_arrSize)
	{
		gcp_lastError = (char*)"Выход за пределы массива (showElement)";
		return;
	}
	myType *tempPtr = structArray+number;
	printf("|%3d|%20s|%20s|%10s|%10d|\n",
		number,
		tempPtr->cp_name,
		tempPtr->cp_department,
		tempPtr->cp_group,
		tempPtr->i_recBook);
	gcp_lastError = (char*)"Ошибок не было (show)";
	return;
}

void showAll()
{
	int i = 0;
	for (; i<gi_arrSize; i++)
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
		gcp_lastError = (char*)"Выход за пределы массива (editElement)";    // 
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
	gcp_lastError = (char*)"Ошибок не было (edit)";                         // 
	return;                                                                 // 
}

void cleanElem(int number)
{
	if (number<0||number>=gi_arrSize)										// 
	{																		// 
		gcp_lastError = (char*)"Выход за пределы массива (clean)";			// 
		return;                                                             // 
	}                                                                       //
	myType *tempPtr = structArray+number;
	if (tempPtr->i_isFull==0)
	{
		gcp_lastError = (char*)"Элемент пуст (clean)";
		return;
	}
	strcpy(tempPtr->cp_department, "");
	strcpy(tempPtr->cp_name, "");
	strcpy(tempPtr->cp_group, "");
	tempPtr->i_recBook = 0;
	tempPtr->i_isFull = 0;
	gcp_lastError = (char*)"Ошибок не было (clean)";
	return;
}

int getCleanElem()
{
	int i = 0;
	for (; i<gi_arrSize; i++)
	{
		if (structArray->i_isFull==0)
		{
			structArray -= i;
			return i;
		}
		structArray++;
	}
	structArray -= i;
	gcp_lastError = (char*)"Ошибок не было (getClean)";
	return -1;
}

int growArray()																// вызывается при добавлении элемента в массив.
{
	gi_arrSize += 1;                                                        // увеличиваем размер будущего массива. |
	myType *tempPtr = (myType*)malloc((gi_arrSize)*sizeof(myType));			// динамическое выделение памяти        |
	int i = 0;                                                                  // под новый массив размера "size+1".   |
	for (; i<gi_arrSize-1; i++)										// копирование всех					|
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
	if (number<0||number>=gi_arrSize)
	{
		gcp_lastError = (char*)"Выход за пределы массива (deleteElement)";
		return;
	}
	int i = number;
	for (; i<gi_arrSize-1; i++)
	{
		structArray[i] = structArray[i+1];
	}
	cleanElem(i);															// очистка последнего элемента после сдвига
	gcp_lastError = (char*)"Ошибок не было (delete)";
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
	if (choice < '1'||choice > '4')
	{
		gcp_lastError = (char*)"Не верный выбор (sortBy)";
		return;
	}
	choice = choice-'0';														// 
	qsort(structArray, gi_arrSize, sizeof(myType), gp_sortFuncArr[choice-1]);	// вызов библиотечной сортировки
	gcp_lastError = (char*)"Ошибок не было (sortBy)";							// с выбранным полем сортировки
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

int getMinValue()
{
	myType *tempPtr = structArray;
	int min = INT_MAX;
	int i = 0;
	int	iMin = tempPtr->i_recBook;
	for (; i<gi_arrSize; i++)
	{
		if (tempPtr->i_recBook<min)
		{
			min = tempPtr->i_recBook;
			iMin = i;
		}
		tempPtr++;
	}
	gcp_lastError = (char*)"Ошибок не было (minField)";
	return iMin;
}

int findValue(int value)													// поиск записи с ближайшим к value значением.
{																			// 
	int entryNum,															// номер структуры, с нужным значением поля.
		delta,																// разница значений
		min = INT_MAX;														// разница-минимум
	int i = 0;
	for (; i<gi_arrSize; i++)
	{
		delta = abs(value-structArray->i_recBook);							// разница равна нулю,
		if (delta==0)														// при совпадении значений, поэтому...
		{																	// ...
			structArray -= i;												// ...сбрасываем указатель массива в начало
			gcp_lastError = (char*)"Ошибок не было (findValue)";
			return i;														// и возвращаем эту позицию.
		}
		if (delta<min)														// если разница меньше минимума
		{																	//
			min = delta;													//
			entryNum = i;													// запоминаем номер этого элемента
		}
		structArray++;
	}
	structArray -= i;
	gcp_lastError = (char*)"Ошибок не было (findValue)";
	return entryNum;
}

struct groupSize *findLargestGroup()
{
	static struct groupSize result;												// указатель для return
	struct groupSize *temp = 
		(struct groupSize *)malloc(gi_arrSize*sizeof(struct groupSize));		// динамическая память для массива численности групп
	temp->countStudents = 0;
	strcpy(temp->group, "");
	int i,
		j,
		maxIndex,
		maximum = INT_MIN;
	for (i = 0; i < gi_arrSize; i++)											// 1. Заполнение массива численности групп.
	{																			//
		strcpy(temp->group, (structArray + i)->cp_group);						// образец строки для сравнения
		temp->countStudents = 0;
		for (j = 0; j < gi_arrSize; j++)										// проходом по массиву структур, находим
		{																		// совпадение значения группы с образцом...
			if (!strcmp(temp->group, structArray->cp_group))					//
			{																	//
				temp->countStudents++;											// ...и увеличиваем численность данной группы.
			}																	//
			structArray++;														//
		}																		//
		structArray -= j;														// сброс указателя в начало массива.
		temp++;																	//
	}
	temp -= i;																	// сброс указателя в начало массива.
	for (i = 0; i < gi_arrSize; i++)											// 2. Поиск наибольшего значения в массиве численности.
	{																			//
		if (temp->countStudents > maximum)										//
		{																		//
			maximum = temp->countStudents;										//
			maxIndex = i;														// отмечаем индекс максимального элемента массива
		}																		// для вывода результата.
		temp++;																	//
	}																			//
	temp -= i;																	// сброс указателя в начало массива.
	result = *(temp + maxIndex);
	free(temp);
	gcp_lastError = (char*)"Ошибок не было (findLargestGroup)";
	return &result;																// возвращаем указатель на структуру 
}																				// с максимальной численностью.

void gotoxy(int xpos, int ypos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = xpos; scrn.Y = ypos;
	SetConsoleCursorPosition(hOuput, scrn);
}

int menu()
{
	system("cls");
	printf("Размер массива: %d\t"
		"Сообщения об ошибках: %s\n", gi_arrSize, gcp_lastError);
	printf("\t1 - добавить строку\n"
		"\t2 - вывод строки\n"
		"\t3 - изменение элемента\n"
		"\t4 - удаление элемента со сдвигом\n"
		"\t5 - очистка элемента\n"
		"\t6 - вывод свободного элемента\n"
		"\t7 - найти элемент с минимальным значением поля \"№ зачётки\"\n"
		"\t8 - найти элемент со значением поля \"№ зачётки\", близким к указанному\n"
		"\t9 - поиск самой многочисленной группы\n"
		"\t0 - сортировка массива по значениям полей\n"
		"\tESC - выход\n");
	gotoxy(10, 14);
	printf("|  №|        Фамилия И.О.|           Факультет|    Группа| № зачётки|");
	showAll();                                                              // вывод всех элементов.
	char choice;															// переменная выбора пункта меню.
	struct groupSize *searchResult = NULL;									// указатель на структуру с численностью группы.
	int number,																// номер элемента массива.
		value;																// значение поля структуры.
	choice = _getch();
	switch (choice)
	{
	case '1':
		addElement();
		break;
	case '2':
		printf("Номер элемента для вывода: ");
		scanf("%d", &number);
		if (number<0||number>=gi_arrSize)
		{
			gcp_lastError = (char*)"Выход за пределы массива (show)";
			break;
		}
		if ((structArray+number)->i_isFull = 0)
		{
			gcp_lastError = (char*)"Элемент пуст (show)";
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
		scanf("%d", &number);
		editElement(number);
		break;
	case '4':
		printf("Номер элемента для удаления: ");
		scanf("%d", &number);
		deleteElement(number);
		break;
	case '5':
		printf("Номер элемента для очистки: ");
		scanf("%d", &number);
		cleanElem(number);
		break;
	case '6':
		number = getCleanElem();											// функция вернёт номер пустого
		if (number<0)														// или -1, если такого нет
		{
			system("cls");
			gotoxy(20, 10);
			printf("Пустых элементов нет!");
			_getch();
			break;
		}
		system("cls");
		gotoxy(35, 12);
		printf("Пустой элемент №: %d", number);
		gotoxy(10, 14);
		printf("|  №|        Фамилия И.О.|           Факультет|    Группа| № зачётки|\n");
		gotoxy(10, 15+number);
		showElement(number);
		_getch();
		break;
	case '7':
		number = getMinValue();
		system("cls");
		gotoxy(10, 12);
		printf("Запись с минимальным значением номера зачётки: %d\n", number);
		gotoxy(10, 14);
		printf("|  №|        Фамилия И.О.|           Факультет|    Группа| № зачётки|");
		gotoxy(10, 15+number);
		showElement(number);
		_getch();
		break;
	case '8':
		printf("Значение номера зачётки для поиска: ");
		scanf("%d", &value);
		number = findValue(value);
		system("cls");
		gotoxy(10, 12);
		printf("Запись с указанным значением номера зачётки: %d\n", number);
		gotoxy(10, 14);
		printf("|  №|        Фамилия И.О.|           Факультет|    Группа| № зачётки|");
		gotoxy(10, 15+number);
		showElement(number);
		_getch();		break;
	case '9':
		searchResult = findLargestGroup();									// поиск элементов с совпадающими значениями полей
		system("cls");
		gotoxy(20, 10);
		printf("Максимальная численность %d человек обнаружена в группе %s", searchResult->countStudents, searchResult->group);
		_getch();
		break;
	case '0':
		gotoxy(0, 22);
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