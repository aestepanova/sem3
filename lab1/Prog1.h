namespace Prog1{
    //элемент матрицы, которая представлена массивом указателей на строки
	struct element{
	    int index;
	    double val;
	    element* next;
	};



	// шаблон функций ввода одного значения
	template <class T>
	int getNum(T &a)
	{
		std::cin >> a;
		if (!std::cin.good())	// обнаружена ошибка ввода или конец файла
			return -1;
		return 1;
	}

    int getInt(int *a);
    int getDouble(double *a);
	// функции сравнения
	inline int isgreater(double a, double b)
	{
		return a > b;
	}

	inline int isless(double a, double b)
	{
		return a < b;
	}

	// прототипы функций
    element *input(int &, int &); // ввод матрицы
    element *inputStr(int n, element *pElement);
//	void output(const char *msg, line a[], int m); // вывод матрицы
//	line *erase(line *&a, int m); // освобождение занятой памяти
//	int minmax(line a[], int m, double &); // вычисление главного результата
	double minmax(double a[], int m, int(*f)(double, double)); // вычисление min/max элемента вектора
}
