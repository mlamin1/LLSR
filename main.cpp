#include <iostream>
#include "matrix.h"
#include <stdlib.h>
#include <chrono>
#include <cmath>
#include <time.h>
#include "matrix.cpp"


int main(int agrc, char **argv)
{
	int option;
	do{
		printf("Menu Option \n");
		printf("Input 1 to run the linear least squares output \n");
		printf("input 2 to test different matrix subroutines \n");
		printf("Input 3 to end program: ");
		std::cin>> option;

		if(option == 1)
		{
			printf("Linear Least Squares Output \n");
			printf("Based on the file: %s", argv[1]);
			printf(" Your Optimal Vector Beta: \n");
			Matrix<double> J(1, 1);
			J = J.GetMatrix(argv[1]);
			auto start = std::chrono::system_clock::now();
			J = J.GetBeta();
			auto end = std::chrono::system_clock::now();
			std::chrono::duration<double> elapsed_seconds = end-start;
			std::time_t end_time = std::chrono::system_clock::to_time_t(end);
			std::cout << "finished at " << std::ctime(&end_time) << "elapsed time: " << elapsed_seconds.count() << "s\n";	
			J.printMatrix();
		}

		else if(option == 2)
		{
			int choice;
			do{
				printf("Matrix Subroutines \n");
				printf("Matrix Option \n");
				printf("Input 1 for Adding Matrix \n");
				printf("Input 2 for Subtracting Matrix \n");
				printf("Input 3 for Multipling Matrix \n");
				printf("Input 4 for Transpose Matrix \n");
				printf("Input 5 for Inverse Matrix \n");
				printf("Input 6 to End the test: ");
				std::cin >> choice;

				if(choice == 1)
				{
					printf("%s\n", "Addition matrix");
					int row1;
					int row2;
					int col1;
					int col2;
					int matchoice;
					int mat2choice;
					printf("%s", "input the size of the row of your first matrix: ");
					std::cin >> row1;
					printf("%s", "input the size of the column of your first matrix: ");
					std::cin >> col1;
					Matrix<double> A(row1, col1);
					printf("%s", "input 1 for sorted matrix, 2 for rand matrix: ");
					std::cin >> matchoice;
					switch(matchoice)
					{
						case 1: A = A.SortedMatrix();
							break;
						case 2: A = A.RandMatrix();
					}
					//	printf("%s\n", "This is your first matrix");
					//A.printMatrix();
					std::cout << std::endl;


					printf("%s", "input the size of the row of your second matrix: ");
					std::cin >> row2;
					printf("%s", "input the size of the column of your second matrix: ");
					std::cin >> col2;
					Matrix<double> B(row2, col2);
					printf("%s", "input 1 for sorted matrix, 2 for rand matrix, 3 for Descending matrix: ");
					std::cin >> mat2choice;
					switch(mat2choice)
					{
						case 1: B = B.SortedMatrix();
							break;
						case 2: B = B.RandMatrix();
					}
					//	printf("%s\n", "This is your second matrix");
					//B.printMatrix();
					std::cout << std::endl;
					Matrix<double> C(row1, col1);
					auto start = std::chrono::system_clock::now();
					C = A + B;
					auto end = std::chrono::system_clock::now();
					std::chrono::duration<double> elapsed_seconds = end-start;
					std::time_t end_time = std::chrono::system_clock::to_time_t(end);
					std::cout << "finished at " << std::ctime(&end_time) << "elapsed time: " << elapsed_seconds.count() << "s\n";
					printf("%s\n", "This is your final matrix");
					C.printMatrix();
				}

				if(choice == 2)
				{

					printf("%s\n", "Subtraction matrix");
					int row1;
					int row2;
					int col1;
					int col2;
					int matchoice;
					int mat2choice;
					printf("%s", "input the size of the row of your first matrix: ");
					std::cin >> row1;
					printf("%s", "input the size of the column of your first matrix: ");
					std::cin >> col1;
					Matrix<double> A(row1, col1);
					printf("%s", "input 1 for sorted matrix, 2 for rand matrix: ");
					std::cin >> matchoice;
					switch(matchoice)
					{
						case 1: A = A.SortedMatrix();
							break;
						case 2: A = A.RandMatrix();
					}
					//	printf("%s\n", "This is your first matrix");
					//A.printMatrix();
					std::cout << std::endl;


					printf("%s", "input the size of the row of your second matrix: ");
					std::cin >> row2;
					printf("%s", "input the size of the column of your second matrix: ");
					std::cin >> col2;
					Matrix<double> B(row2, col2);
					printf("%s", "input 1 for sorted matrix, 2 for rand matrix: ");
					std::cin >> mat2choice;
					switch(mat2choice)
					{
						case 1: B = B.SortedMatrix();
							break;
						case 2: B = B.RandMatrix();
					}
					//	printf("%s\n", "This is your second matrix");
					//B.printMatrix();
					std::cout << std::endl;
					Matrix<double> C(row1, col1);
					auto start = std::chrono::system_clock::now();
					C = A - B;
					auto end = std::chrono::system_clock::now();
					std::chrono::duration<double> elapsed_seconds = end-start;
					std::time_t end_time = std::chrono::system_clock::to_time_t(end);
					std::cout << "finished at " << std::ctime(&end_time) << "elapsed time: " << elapsed_seconds.count() << "s\n";
					printf("%s\n", "This is your final matrix");
					C.printMatrix();
				}

				if(choice == 3)
				{
					printf("%s\n", "Multiplication matrix");
					int row1;
					int row2;
					int col1;
					int col2;
					int matchoice;
					int mat2choice;
					printf("%s", "input the size of the row of your first matrix: ");
					std::cin >> row1;
					printf("%s", "input the size of the column of your first matrix: ");
					std::cin >> col1;
					Matrix<double> A(row1, col1);
					printf("%s", "input 1 for sorted matrix, 2 for rand matrix: ");
					std::cin >> matchoice;
					switch(matchoice)
					{
						case 1: A = A.SortedMatrix();
							break;
						case 2: A = A.RandMatrix();
					}
					//	printf("%s\n", "This is your first matrix");
					//A.printMatrix();
					std::cout << std::endl;

					printf("%s", "input the size of the row of your second matrix \n");
					printf("REMEMBER!! the number columns of the first matrix needs to match the number of rows of second matrix: ");
					std::cin >> row2;
					printf("%s", "input the size of the column of your second matrix: ");
					std::cin >> col2;

					Matrix<double> B(row2, col2);
					printf("%s", "input 1 for sorted matrix, 2 for rand matrix: ");
					std::cin >> mat2choice;
					switch(mat2choice)
					{
						case 1: B = B.SortedMatrix();
							break;
						case 2: B = B.RandMatrix();
					}
					//	printf("%s\n", "This is your second matrix");
					//B.printMatrix();
					std::cout << std::endl;
					Matrix<double> C(row1, col2);	
					auto start = std::chrono::system_clock::now();
					C = A * B;
					auto end = std::chrono::system_clock::now();
					std::chrono::duration<double> elapsed_seconds = end-start;
					std::time_t end_time = std::chrono::system_clock::to_time_t(end);
					std::cout << "finished at " << std::ctime(&end_time) << "elapsed time: " << elapsed_seconds.count() << "s\n";
					printf("%s\n", "This is your final matrix");
					C.printMatrix();
				}

				if(choice == 4)
				{
					printf("Transpose Matrix \n");

					int row;
					int col;
					printf("%s", "Input the size of the row: ");
					std::cin >> row;
					printf("%s", "Input the size of the column: ");
					std::cin >> col;
					Matrix<double> A(row, col);
					int matrix;
					printf("%s", "Input 1 for sorted matrix, 2 for rand matrix: ");
					std::cin >> matrix;
					switch(matrix)
					{
						case 1: A = A.SortedMatrix();
							break;
						case 2: A = A.RandMatrix();
					}
					printf("This is the original matrix \n");
					A.printMatrix();
					A = A.Transpose();
					printf("This is the transpose of the matrix \n");
					A.printMatrix();
				}

				if(choice == 5)
				{
					printf("Inverse Matrix test \n");

					int row;
					int col;
					printf("%s", "Input the size of the row: ");
					std::cin >> row;
					printf("%s", "Input the size of the column: ");
					std::cin >> col;
					Matrix<double> A(row, col);
					int matrix;
					printf("%s", "Input 1 for sorted matrix, 2 for rand matrix: ");
					std::cin >> matrix;
					switch(matrix)
					{
						case 1: A = A.SortedMatrix();
							break;
						case 2: A = A.RandMatrix();
					}
					printf("This is the original matrix \n");
					A.printMatrix();
					A = A.Inverse();
					printf("This is the transpose of the matrix \n");
					A.printMatrix();
				}

			}while(choice != 6);
		}
	}while(option != 3);
	return 0;
}
