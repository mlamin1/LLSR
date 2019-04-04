#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>

template<class T>
class Matrix{

	private:
		T **m;
		int rows;
		int cols;

		Matrix<T> InverseMatrix();
	public:
		Matrix(int, int);
		~Matrix();
		const Matrix<T> operator+(const Matrix &right);
		const Matrix<T> operator-(const Matrix &right);
		const Matrix<T> operator*(const Matrix &right);
		const Matrix<T> operator*(const int &right);
		Matrix<T> Transpose();
		Matrix<T> PadMatrix();
		Matrix<T> SliceMatrix(int, int, int, int);
		Matrix<T> Inverse();
		Matrix<T> GetMatrix(std::string);
		Matrix(const Matrix &obj);
		const Matrix<T> operator=(const Matrix &right);
		T &operator[](const int &);
		void printMatrix();
		bool CheckPower(int);
		Matrix<T> GetBeta();		
		Matrix<T> SortedMatrix();
		Matrix<T> RandMatrix();
};

#endif
