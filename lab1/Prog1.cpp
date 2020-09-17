#include <iostream>
#include "Prog1.h"

namespace Prog1{
	// функция ввода матрицы
	element* input(int &rm, int &rn)
	{
        element *lines = nullptr;  // динамический массив строк матрицы
	    ///ввод кол-ва строк в матрице и создание массива из указателей на элементы матрицы

		// выделяем память под массив структур - строк матрицы
		try{
			lines = new element[rm];
		}
		catch (std::bad_alloc &ba)
		{
			std::cout << "------ too many rows in matrix: " << ba.what() << std::endl;
			return nullptr;
		}

		//выделение памяти под вспомогательную строку, из которой значения будут копироваться в матрицу
        double* tmpLine;
        try{
            tmpLine = new double[rn]();
        }
        catch (std::bad_alloc &bb)
        {
            std::cout << "------ too many rows in matrix: " << bb.what() << std::endl;
            return nullptr;
        }

        //непосредственный ввод матрицы
        int i;
        do{
            std::cout<< std::endl << "To stop entering non-zero lines, please type '-1'" << std::endl;
            std::cout<< "Enter number of line from 0 to "<< rm-1 << " ---> ";
            getInt(&i);
            while ((i<-1)||(i>rm-1)){ //rm отвечает за кол-во строк в матрице
                std::cout << "Your input is incorrect! Try again." << std::endl;
                std::cout<< "Enter number of line from 0 to "<< rm-1 << " ---> ";
                getInt(&i);
            }
            if (i == -1) break;
            std::cout<< "To stop entering non-zero elements at line #" << i<<", please type '-1'" << std::endl;
            std::cout << "Enter index of the element from 0 to " << rn-1 << ": "<< std::endl;

            //ввод во временную строку
            int j;
            do{
                getInt(&j);
                while ((j<-1)||(j>rn-1)){
                    std::cout << "Your input is incorrect! Try again." << std::endl;
                    std::cout<< "Enter index from 0 to "<< rn-1 << " ---> "; //rn отвечает за максимальное колво элементов в строке
                    getInt(&j);
                }
                if (j!=-1) {
                    std::cout<< "Value of element [" << i << ", "<< j <<"] : ";
                    getDouble(&tmpLine[j]);
                }else break;
                std::cout<< std::endl << "To stop entering non-zero elements at line #" << i<<", please type '-1'" << std::endl;
                std::cout << "Enter index of the element from 0 to " << rn-1 << ": "<< std::endl;
            }while (j!=-1);
            std::cout << "Entering elements of line №" << i << " is finished" << std::endl;

            ////
            ///copy to matrix
            /////

        }while(i > -1);
        //////////////////////////////////////

		/*for (int i = 0; i < m; i++){
			// теперь для каждой строки матрицы вводим количество столбцов 
			pr = "";
			do{
				std::cout << pr << std::endl;
				std::cout << "Enter number of items in line #" << (i + 1) << " --> ";
				pr = "You are wrong; repeat please!";
				if (getNum(lines[i].n) < 0){ // обнаружена ошибка ввода или конец файла
					erase(lines, i); // освобождение памяти, занятой ранее введенными строками
					return nullptr;
				}
			} while (lines[i].n < 1);

 
			// и выделяем необходимую память под элементы строки
			try{
				lines[i].a = new double[lines[i].n];
			}
			catch (std::bad_alloc &ba)
			{
				std::cout << "------ too many items in matrix: " << ba.what() << std::endl;
				erase(lines, i);
				return nullptr;
			}

			// теперь можно вводить сами элементы данной строки матрицы
			std::cout << "Enter items for matrix line #" << (i + 1) << ":" << std::endl;
			for (int j = 0; j < lines[i].n; j++){
				if (getNum(lines[i].a[j]) < 0){ // обнаружена ошибка ввода или конец файла
					erase(lines, i + 1); // освобождение памяти, занятой ранее введенными строками
					return nullptr;
				}
			}
		}
		// формируем результат - количество строк в матрице
		rm = m;*/
		return lines;
	}
	//моя функция ввода строки
	element* inputStr(int n, element lines){
        int i;
        element* line = nullptr;
        do{
            std::cout<< "To stop entering not null lines, please type '-1'" << std::endl;
            std::cout<< "Enter number of line from 0 to "<< n-1 << " ---> ";
            while ((getInt(&i)<0)||(i<-1)||(i>n-1))
            {
                std::cout << "Your input is incorrect! Try again." << std::endl;
                std::cout<< "Enter number of line from 0 to "<< n-1 << " ---> ";
                getInt(&i);
            }
            std::cout << i << std::endl;
        }while(i > -1);
        return line;
	}

	void copyToMatrix(element* lines, double *line, int i, int n){
	    element* tmp = new element;
	    tmp->next = nullptr;

	    element head = lines[i];
	    for (int j=0; j<n; j++){
	        if (line[j] != 0) {
                lines[i].index = j;
                lines[i].val = line[j];
                lines[i].next = tail;
                tail = lines[i];
	        }
	    }

	};
    int getInt(int *a) {
        int n;
        do {
            n = scanf("%d", a);
            if (n < 0 || (*a >= 2147483647))
                return -1;
            if (n == 0){
                printf("%s\n", "Error! Please, repeat your input: ");
                scanf("%*[^\n]");
            }
        } while (n == 0);
        return 1;
    }

    int getDouble(double *a) {
        int n;
        do {
            n = scanf("%lf", a);
            if (n < 0)
                return -1;
            if (n == 0) {
                printf("%s\n", "Error! Please, repeat your input: ");
                scanf("%*[^\n]");
            }
        } while (n == 0);
        return 1;
    }
}


	// функция вывода
	/*void output(const char *msg, line *a, int m)
	{
		int i, j;
		std::cout << msg << ":\n";
		for (i = 0; i < m; ++i){
			for (j = 0; j < a[i].n; ++j)
				std::cout << a[i].a[j] << "  ";
			std::cout << std::endl;
		}
	}

	// функция освобождения занятой памяти
	line *erase(line *&lines, int m)
	{
		int i;
		for (i = 0; i < m; i++)
			delete[] lines[i].a;
		delete[] lines;
		return nullptr;
	}
	
	// функция вычисления главного результата
	int minmax(struct line lines[], int m, double & res)
	{
		double *s = nullptr;
		try{
			s = new double[m]; // вектор для получения max элементов в строке - по строкам
		}
		catch (std::bad_alloc &ba)
		{
			std::cout << ba.what() << std::endl;
			return 1;
		}
		int i;
		for (i = 0; i < m; i++)
			s[i] = minmax(lines[i].a, lines[i].n, isgreater);
		res = minmax(s, m, isless);
		delete[] s;
		return 0;
	}

	// функция вычисления min/max элемента вектора
	double minmax(double a[], int m, int(*f)(double, double))
	{
		double res = a[0];
		int i;
		for (i = 0; i < m; ++i)
		if (f(a[i], res) > 0)
			res = a[i];
		return res;
	}
}*/
