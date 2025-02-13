﻿#include <iostream>

using namespace std;

bool is_Reapeting(int array[], int size, int elementToCheck, int elementsIndex) //Функция, проверяющая, повторяется ли элемент в массиве
{
	//Инициализируем счетчик и флажок
	int counter = 0; 
	bool flag = false;

	while (counter < size && !flag) //Пока флажок меньше рамера массива + flag стоит на false
	{
		if (array[counter] == elementToCheck && counter != elementsIndex) //Если элемент по текущему индексу = проверяемуму значению + текущий индекс != индексу проверяемого значения
			flag = true; //Переключает flag на true

		counter++; //Прибавляем 1 к счетчику
	}

	return flag; //Возвращаем значение флага
}

pair<int, bool> TryFindMinimumNonRepeatingElementInArray(int matrix[500][500], int rows, int columns) //Функция, для выполнения поставленно задачи
{
	int array[500]; //Инициализируем одномерный массив
	int size = 0; //Изначально его размер = 0
	int plug = 0; //Затычка, её смысл будет понятен чуть позже

	//В данных вложенных циклах, мы:
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			array[size] = matrix[i][j]; //Заносим все элементы матрицы в наш одномерный массив для удобства

			if (array[size] > plug)
				plug = array[size] + 1; //Если рассматриваем не самый первый элемент матрицы и текущий элемент > предыдущего, значит затычка = текущий элемент + 1

			size++; //Увеличить место в массиве
		}
	}

	int min = plug; //Расскрывается смысл затычки. Она будет служить минимальным значением, так аак благодаря циклу выше, на данный момент она больше всего, что есть в матрице

	for (int i = 0; i < size; i++) //Перебераем все элементы массив
	{
		bool isReapeting = is_Reapeting(array, size, array[i], i); //Через функцию проверяем, повторяется ли этот элемент в массиве

		if (!isReapeting && array[i] < min) //Если текущий элемент не повторяется + меньше ранее найденого минимума,
			min = array[i]; //То отныне текущий элемент и будет считаться нашим минимумом, пока не будет доказано обратное
	}

	return pair<int, bool>(min, min != plug); //Как итог, возвращаем пару, содержащую минимум + изменился ли он от затычки (если нет, значит в матрице каждый элемент повторяется)
}

int main()
{
	setlocale(LC_ALL, "RUS"); //Подключаем русскую локализацию
	srand(time(0)); //Инициализируем генератор случайных чисел

	int rows, columns;

	cout << "Введите кол-во строк и столбцов матрицы" << endl;

	cin >> rows >> columns; //Получаем ввод пользователя

	if (rows < 1 || columns < 1) //Проверяем ввод пользователя на валидность. 
	{
		cout << "Невалидные значения. Кол-во строк и столбцов должно быть >= 1" << endl;
		return 0;
	}

	int matrix[500][500]; //Выделяем память под матрицу

	cout << "Ваша матрица:" << endl << endl;

	for (int i = 0; i < rows; i++) //Данными вложенными циклами заполняем матрицу случаным числами и сразу же её выводим
	{
		for (int j = 0; j < columns; j++)
		{
			matrix[i][j] = rand() % 100;
			cout << matrix[i][j] << "  ";
		}
		
		cout << endl << endl;
	}

	pair<int, bool> functionsOutput = TryFindMinimumNonRepeatingElementInArray(matrix, rows, columns); //Получаем из данной функции 2 вещи: 1 - минимальный элемент, 2 - были в матрицы вообще неповторяющиеся числа

	if (functionsOutput.second) //Поверяем, были ли в матрице не повторяющиеся числа. Если были, то:
		cout << "Минимальный не повторяющийся элемент матрицы = " << functionsOutput.first << endl; //Выводим пользователю минимальный элемент
	else
		cout << "В матрице не найдены не повторяющиеся элементы" << endl; //Иначе же выводим печальную правду
}
