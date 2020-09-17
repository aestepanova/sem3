#include <iostream>
#include "Prog1.h"

using namespace Prog1;

// основная функция
int main()
{
	element *arr = nullptr; // исходный массив

	int m; // количество строк в матрице
	int n; //number of columns

	const char *pr = ""; // будущее сообщение об ошибке
    //ввод кол-ва строк
    do{
        std::cout << pr << std::endl;
        std::cout << "Enter number of lines: --> ";
        pr = "You are wrong; repeat please!";
        if (getInt(&m) <= 0) // обнаружена ошибка ввода или конец файла
            m=-1;
    } while (m < 1);

    //ввод кол-ва столбцов
    pr = "";
    do{
        std::cout << pr << std::endl;
        std::cout << "Enter number of columns: --> ";
        pr = "You are wrong; repeat please!";
        if (getInt(&n) <= 0) // обнаружена ошибка ввода или конец файла
            n=-1;
    } while (n < 1);

	double res[m]; // vector of result

	arr = input(m, n); // ввод матрицы
	if (!arr){
		std::cout << "incorrect data" << std::endl;
		return 1;
	}

	//код для обработки матрицы

	//код для вывода матрицы

	//код для вывода вектора результата

	//код для освобождения динамической памяти


	//вряд ли понадобится
	/*if (minmax(arr, m, res)){  // вычисление требуемого результата
		std::cout << "Error in allocate memory" << std::endl;
		erase(arr, m);
		return 1;
	}
	output("Sourced matrix", arr, m);
	std::cout << "Result: " << res << std::endl;
	erase(arr, m); // освобождение памяти
	 */

	return 0;
}
