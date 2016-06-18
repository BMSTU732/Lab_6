// Lab6.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <ctime>
using namespace std;

class Ring
{
int r;
public:
	Ring(int a)
	{
		r = a % 10;
	}
	Ring()
	{
		r = 0;
	}
	Ring operator+ (const Ring& a) //перегрузка оператора +
	{
		Ring result(a.r + r);
		return result;
	}
	Ring operator* (const Ring& a) //перегрузка оператора *
	{
		Ring result(a.r*r);
		return result;
	}
	friend std::ostream& operator<< (std::ostream&, const Ring&);

	~Ring() {}
};
std::ostream& operator<< (std::ostream& c, const Ring& d)
{
	c << d.r << '\t';
	return c;
}
template<class T>
class Matrix
{
T **matrix1;
int m, n;
public:
	class Iterator
	{
		typedef std::forward_iterator_tag iterator_category;
		typedef T value_type;
		typedef value_type* pointer;
		typedef value_type& reference;
		//typedef size_t size_type;

	private:
		Matrix<T>* matrix1;
		int tek_n, tek_m;
		int ind = 0;
	public:
		Iterator()
		{}
		Iterator(Matrix<T>* matr, int nn, int mm)
		{
			tek_n = nn;
			tek_m = mm;
			matrix1 = matr;
		}

		T& operator*()
		{
			return (*matrix1)(tek_n, tek_m);
		}

		T& operator-> ()
		{
			return &((*matrix1)(tek_n, tek_m));
		}
		bool operator!= (const Iterator& it) const
		{
			if (tek_n == it.tek_n && tek_m == it.tek_m) 
			{
				return false;
			}
			else { return true; }
		}
		Iterator&  operator++() 
		{
			if (tek_m == matrix1->get_m() - 1) 
			{
				tek_m = 0;
				tek_n++;
			}
			else 
			{
				tek_m++;
			}
			return *this;
		}
	};
	Matrix()
	{
		n = 3, m = 3;
		matrix1 = new T *[n];
		for (int i = 0; i < n; i++)
		{
			matrix1[i] = new T[m];
		}
	}
	Matrix(int nn, int mm)
	{
		n = nn;
		m = mm;
		matrix1 = new T *[n];
		for (int i = 0; i < n; i++)
		{
			matrix1[i] = new T[m];
		}
	}
	T& operator()(int n, int m) { return matrix1[n][m]; 
	}

	Matrix(T** mat, int nn, int mm) 
	{
		n = nn;
		m = mm;
		matrix1 = new T *[n];
		for (int i = 0; i < n; i++)
		{
			matrix1[i] = new T[m];
		}
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				matrix1[i][j] = mat[i][j];
			}
		}
	}
	Iterator begin() 
	{
		return Iterator(this, 0, 0);
	}
	Iterator end() 
	{
		return Iterator(this, n, 0);
	}
	void print_matrix() //печать матрицы
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				matrix1[i][j] = rand() % 100 + 1;
				cout << matrix1[i][j]<<"\t";
			}
			cout << endl;
		}
	}
	int get_m() 
	{
		return m;
	}
	int get_n() 
	{
		return n;
	}
	void print_ptr_matrix() //печать матрицы
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				cout << &matrix[i][j] << "\t";
			}
			cout << endl;
		}
	}
	Ring& index(int a, int b)//обращение по элементу
	{
		return matrix[a][b];
	}
	void setplus(T** sum)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				matrix1[i][j] = sum[i][j];
			}
		}
	}
	Matrix<T> operator+ (Matrix<T> & matrix2) //перегрузка оператора +
	{
		T **sum = new T *[n];
		for (int i = 0; i < n; i++)
		{
			sum[i] = new T[m];
		}

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				sum[i][j] = matrix1[i][j] + matrix2.matrix1[i][j];
			}
		}
		Matrix<T> m;
		m.setplus(sum);
		return m;
	}
	Matrix <T> operator < (Matrix<T> &matrix2) //перегрузка оператора транспонирования
	{
		Matrix sum(*this);
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				sum.matrix1[j][i] = matrix2.matrix1[i][j];
			}
		}
		return sum;
	}

	Matrix<T>  operator* (Matrix<T>&  matrix2)//перегрузка оператора *
	{
		Matrix sum(*this);
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				sum.matrix1[i][j] = 0;
				for (int k = 0; k < n; k++) {
					sum.matrix1[i][j] = sum.matrix1[i][j] + (matrix1[k][j] * matrix2.matrix1[i][k]);
				}
			}
		}
		return sum;
	}

	~Matrix()
	{
		for (int i = 0; i < n; i++)
		{
			delete[] matrix1[i];
		}
		delete[] matrix1;
	}
};

void setcount(int& i)
{
	static int count = 0;
	i = ++count;
	cout << i << " ";
}

int main()
{
	srand(time(NULL));
	Matrix<int> mat1;
	mat1.print_matrix(); //печать матрицы
	for (auto i = mat1.begin(); i != mat1.end(); ++i)
	{
		cout << *i;
	}
	std::cout << "";
	for_each(mat1.begin(), mat1.end(), setcount);
	std::cout << '\t';
	system("PAUSE");
	return 0;
}
