#include <iostream>
#include "TMatrix.h"

int main()
{
	int mode = 1;
	std::cout << "Testing the triangular matrix support program" << std::endl;
	while ((mode == 1) || (mode == 2))
	{
		std::cout << "Select operating mode" << std::endl;
		std::cout << "1 - manual input" << std::endl;
		std::cout << "2 - auto input" << std::endl;
		std::cout << "Input any other value to close the program" << std::endl;
		std::cin >> mode;
		switch (mode)
		{
		case 1:
		{
			try
			{
				int size;
				std::cout << "Input matrix A size" << std::endl;
				std::cin >> size;
				TMatrix<double> A(size);
				std::cout << "Input matrix A values" << std::endl;
				std::cin >> A;
				std::cout << "Input matrix B size" << std::endl;
				std::cin >> size;
				TMatrix<double> B(size);
				std::cout << "Input matrix B values" << std::endl;
				std::cin >> B;
				std::cout << "Input vector v size" << std::endl;
				std::cin >> size;
				TVector<double> v(size);
				std::cout << "Input vector v values" << std::endl;
				std::cin >> v;
				std::cout << "Matrix A" << std::endl << A;
				std::cout << "Determinant A = " << A.determinant() << std::endl;
				std::cout << "Matrix B" << std::endl << B;
				std::cout << "Determinant B = " << B.determinant() << std::endl;;
				std::cout << "Vector v" << std::endl << v << std::endl;
				std::cout << "Length v = " << v.Length() << std::endl;
				TMatrix<double> C(A);
				C = C + B;
				std::cout << "Matrix C = A + B = " << std::endl;
				std::cout << A + B << std::endl;
				std::cout << "Matrix A * B = " << std::endl;
				std::cout << A * B << std::endl;
				std::cout << "Matrix A + 10 = " << std::endl;
				std::cout << A + 10 << std::endl;
				std::cout << "Matrix A - 10 = " << std::endl;
				std::cout << A - 10 << std::endl;
				std::cout << "Matrix A * 10 = " << std::endl;
				std::cout << A * 10 << std::endl;
				std::cout << "Vector A * v = " << std::endl;
				std::cout << A * v << std::endl;
			}
			catch (char* c)
			{
				std::cout << c << std::endl;
			}
			break;
		}
		case 2:
		{
			TVector<TVector<double> > VA(5);
			TMatrix<double> b(5);
			TVector<double> v(5);
			for (int i = 0; i < 5; i++)
			{
				TVector<double> temp(5 - i, i);
				for (int j = i; j < 5; j++)
					temp[j] = i * j + 7;
				VA[i] = temp;
			}
			for (int i = 3; i < 8; i++)
				for (int j = i; j < 8; j++)
					b[i - 3][j - 3] = (i * 11 + j) * 2 - 29;
			for (int i = 5; i < 10; i++)
				v[i - 5] = (i + 7) * 5 - 28;
			std::cout << "Vector<Vector> a = " << std::endl;
			for (int i = 0; i < 5; i++)
				std::cout << VA[i] << std::endl;
			std::cout << "Converting Vector<Vector> A into matrix A" << std::endl;
			TMatrix<double> a(VA);
			std::cout << "Matrix a = " << std::endl << a << std::endl;
			std::cout << "Determinant a = " << a.determinant() << std::endl;
			std::cout << "Copy constructor testing" << std::endl;
			std::cout << "Matrix c(a):" << std::endl;
			TMatrix<double> c(a);
			std::cout << c << std::endl;
			std::cout << "Matrix b = " << std::endl << b << std::endl;
			std::cout << "c = b (= test):" << std::endl;
			c = b;
			std::cout << c << std::endl;
			std::cout << "Matrix a + b = " << std::endl << a + b << std::endl;
			std::cout << "Matrix a - b = " << std::endl << a - b << std::endl;
			std::cout << "Matrix a * b = " << std::endl << a * b << std::endl;
			std::cout << "Matrix a + 10 = " << std::endl << a + 10 << std::endl;
			std::cout << "Matrix a - 10 = " << std::endl << a - 10 << std::endl;
			std::cout << "Matrix a * 10 = " << std::endl << a * 10 << std::endl;
			std::cout << "Vector v = " << std::endl << v << std::endl;
			std::cout << "Length = " << v.Length() << std::endl;
			std::cout << "Vector a * v = " << std::endl << a * v << std::endl;
			std::cout << "Length = " << (a * v).Length() << std::endl;
			break;
		}
		default:
			return 0;
		}
	}
	return 0;
}