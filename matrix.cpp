#include <iostream>
#include "matrix.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <fstream>


/***********************************************************************************************/
//Non-Default Constructor									/
//Accepts the rows and cols from user and makes a matrix of the size of rows and cols and fills /
//with 0s											/
/***********************************************************************************************/
	template<class T>
Matrix<T>::Matrix(int n_rows, int n_cols)
{
	rows = n_rows;
	cols = n_cols;
	m = new T*[rows];					//dynamically allocate space for the amount of rows 
	for(int i = 0; i < rows; i++)
	{
		m[i] = new T[cols];				//dynamically allocate space for the amount of columns

		for(int j = 0; j < cols; j++)
		{	
			m[i][j] = 0;				//Fill the matrix with 0s just for default.
		}
	}
}


/***********************************************************************************************/
//Destructor											/
//Used to delete and free the space that was used in my constructor.				/
//Once a function runs and ends, if there was allocations done in the function, the destructor	/
//gets called to free the space									/
/***********************************************************************************************/
	template<class T>
Matrix<T>::~Matrix()
{
	for(int i = 0; i < rows; i++)				
	{
		delete [] m[i];
	}
	delete [] m;
}




/***********************************************************************************************/
//Copy Constructor										/
//Used to copy data over to another object of the matrix type.					/
//Used when a matrix is created with out assigning its rows and cols, but instead its is "=" to /
//another matrix.										/
/***********************************************************************************************/
	template<class T>
Matrix<T>::Matrix(const Matrix &obj)
{
	rows = obj.rows;		//To avoid segmatation fault, make sure the rows and cols of the object is simalar to the new matrix.			
	cols = obj.cols;
	m = new T*[rows];
	for(int i = 0; i < rows; i++)
	{
		m[i] = new T[cols];
		for(int j = 0; j < cols; j++)
		{
			m[i][j] = obj.m[i][j];
		}
	}
}





/***********************************************************************************************/
//Bracket Operator overloaded.									/
//It is used to return the the position of the matrix just incase a matrix is compared to 	/
//another, or the values are being transfered to another matrix					/
/***********************************************************************************************/

	template<class T>
T &Matrix<T>::operator[](const int &num)
{
	if(num < 0)
		return *this->m[0];			//return the first value if num is less than 0.
	if(num >= rows)
		return *this->m[rows - 1];		//return the last value if num is greater than or = to rows
	if(num >= cols)
		return *this->m[cols - 1];		//return the last value if num is greater than or = to cols

	return *this->m[num];
}



/***********************************************************************************************/
//Transpose function										/
//This function makes a matrix and the rows of the old matrix becomes the column of the new one	/
/***********************************************************************************************/
	template<class T>
Matrix<T> Matrix<T>::Transpose()
{
	Matrix<T> A(cols, rows);
	for(int i = 0; i < A.rows; i++)
	{
		for(int j = 0; j < A.cols; j++)
		{
			A.m[i][j] = m[j][i];				//Simply flip the i and j positions. 
		}
	}
	return A;
}




/***********************************************************************************************/
//PadMatrix function										/
//This function is used to make matrices n x n if there are not aalready that.			/
/***********************************************************************************************/
	template<class T>
Matrix<T> Matrix<T>::PadMatrix()
{
	int temp = ceil(log2(rows));					//Used to determine the size of the new matrix to be padded.
	int k = (pow(2,temp) - rows);					//Used to determine the size of the new matrix to be padded.

	Matrix<T> B(rows + k, rows + k);
	for(int i = 0; i < B.rows; i++)
	{
		for(int j = 0; j < B.rows; j++)
		{
			if(i < rows && j < cols)			//this validation puts the actual data into the top left of the new matrix
			{
				B.m[i][j] = m[i][j];

			}
			else if(i == j)
			{
				B.m[i][j] = 1;				//This validation does a mini identity matrix in the buttom right of the matirx
			}
			else
			{
				B.m[i][j] = 0;				//This validation puts 0s in the top right and buttom left of the matrix
			}
		}
	}
	return B;
}




/***********************************************************************************************/
//SlicMatrix function										/
//This function is used to get mini matrices from a big matix and assign them to anotger matrix	/
/***********************************************************************************************/
	template<class T>
Matrix<T> Matrix<T>::SliceMatrix(int tr, int tc, int br, int bc)
{
	int trows = br - tr;						//Subtract the buttom row form top row to get the new matrix row.
	int tcols = bc - tc;						//Subtract the buttom column form top column to get the new matrix column.
	Matrix<T> temp(trows, tcols);
	for(int i = 0; i < trows; i++)
	{
		for(int j = 0; j < tcols; j++)
		{
			temp.m[i][j] = m[i + tr][j + tc];		//increment i starting from tr, and j starting from tc, both came in as parameters.
		}
	}
	return temp;
}	



/***********************************************************************************************/
//CheckPower function										/
//A boolean function used to check and see if the row or column of the matrix is a poer of 2s	/
/***********************************************************************************************/
	template<class T>
bool Matrix<T>::CheckPower(int num)
{	
	bool result = true;
	while(num != 1)
	{
		if(num % 2 == 0)
		{
			num = num / 2;
			continue;
		}
		else
		{
			result = false;
			break;
		}
	}
	return result;
}


/***********************************************************************************************/
//GetMatrix function										/
//This function is used to get the data from command line and input it in a matix and return	/
//the matrix											/
/***********************************************************************************************/
	template<class T>
Matrix<T> Matrix<T>::GetMatrix(std::string fname)
{
	std::ifstream infile;					//Declare an ifstream called infile
	infile.open(fname);					//Open the file data by the .open() function in ifstream
	if(infile.fail())					//Validation check if there is an error opening the file
	{
		std::cerr << "ERROR opening file" << std::endl;
		exit(1);
	}

	int rowcount = 0;
	int colcount = 1;
	std::string temp;

	while(std::getline(infile,temp))			//using getline function to get the data and store in a temp string.
	{	
		if(rowcount == 0)				//Used to determine the rows and column of the matrix by counting the data in file
		{
			int size = temp.length();
			for(int i = 0; i < size; i++)
			{
				if(temp[i] == '\t'|| temp[i] == ' ')		//Validation to check the spaces or tabs between data.
					colcount++;	
			}
		}
		rowcount++;	
	}

	infile.clear();								//Check for error and clear
	infile.seekg(0);							//Used to set infile cursor to the first data in the file.

	Matrix<T> A(rowcount, colcount);
	Matrix<T> b(rowcount, 1);
	int index = 0;
	while(!infile.eof())							//Validation to input data in the matrix until the end of line of infile
	{
		for(int j = 0; j < colcount; j++)
		{
			infile >> A.m[index][j];
		}
		index++;
	}
	infile.close();
	return A;	
}


/***********************************************************************************************/
//GetBeta Matrix function									/
//This function does all the equtiob for the linear regression and returns a matrix 		/
//with the answer.										/
/***********************************************************************************************/
template<class T>
Matrix<T> Matrix<T>::GetBeta()
{
	Matrix<T> Temp = *this;				//Used copy constructor to assign this to a temp matrix.
	Matrix<T> b(Temp.rows, 1);

	for(int i = 0; i < Temp.rows; i++)		//assigns the last column of temp matrix to b.
	{
		b.m[i][0] = Temp.m[i][Temp.cols- 1];
	}

	for(int i = 0; i < Temp.rows; i++)		//Change the values of the last column of temp to 1
	{
		Temp.m[i][Temp.cols- 1] = 1;
	}

	Matrix<T> A_T(Temp.rows, Temp.cols);		// creates a temp transposed matrix.
	A_T = Temp.Transpose();
	Matrix<T> W = A_T * Temp;
	Matrix<T> W_I = W.Inverse();
	Matrix<T> X = A_T * b;
	Matrix<T> H = W_I * X;
	return H;
}




/***********************************************************************************************/
//Public Inverse Matrix function								/
//This function check if the matrix is a power of 2, then it calls a private inerse matrix 	/
/***********************************************************************************************/
	template<class T>
Matrix<T> Matrix<T>::Inverse()
{	
	Matrix<T> Temp(0, 0);
	       Temp = *this;					//assign this to a temp matrix.
	bool isPower = CheckPower(Temp.cols);			//call checkpower function to check the row or cols if its a power of 2s
	if(!isPower)						//Validaiton that if it not a power of 2s, pad matirx function is called.
	{	printf("in isPower if statement \n");
		Temp = Temp.PadMatrix();
	}
	Temp = Temp.InverseMatrix();				//Private inverse matrix function is called
	return Temp.SliceMatrix(0,0,rows,cols);			//since matrix might have been padded call slice function before and specify range to return.
}

/***********************************************************************************************/
//Inverse Matrix function									/
//Private function used to do the inverse algorithm given by professor				/
/***********************************************************************************************/
	template<class T>
Matrix<T> Matrix<T>::InverseMatrix()
{
	Matrix<T> Temp(rows,cols);

	if(rows == 1)							//Basse case validation because the function will be recursive.
	{
		Matrix<T>temp(1,1);
		if(m[0][0] != 0)					//Validation just incase the value 0.
		{
			temp.m[0][0] = 1 / m[0][0];
		}

		return temp;
	}
	
	Matrix<T> B = SliceMatrix(0,0,rows / 2,rows / 2);		//Top left of the matrix.

	Matrix<T> C = SliceMatrix(rows / 2,0,rows,(rows / 2));		//Bottom left of the matrix.

	Matrix<T> C_T = SliceMatrix(0, rows/2, (rows/2), rows);		//Top right of the matrix.

	Matrix<T> D = SliceMatrix(rows / 2,rows / 2,rows,rows);		//Bottom right of the matrix.

	Matrix<T> B_inverse = B.InverseMatrix();
	Matrix<T> W = C * B_inverse;
	Matrix<T> W_trasposed = B_inverse * C_T;
	Matrix<T> X = W * C_T;
	Matrix<T> S = D - X;
	Matrix<T> V = S.InverseMatrix();
	Matrix<T> Y = V * W;
	Matrix<T> Y_transpose = Y.Transpose();
	int num = -1;
	Matrix<T> J = Y_transpose * num;
	Matrix<T> U = Y * num;
	Matrix<T> Z = W_trasposed * Y;
	Matrix<T> R = B_inverse + Z;

	//I like to call this reverse slicing. these are used to assemble the final data after the algorithm is done.

	for(int i = 0; i < (rows / 2); i++)				//Used to assemble top left of the final matrix
	{
		for(int j = 0; j < (rows / 2); j++)
		{
			Temp.m[i][j] = R.m[i][j];
		}
	}

	for(int i = 0; i < (rows - (rows / 2)); i++)			//Used to assemble buttom left of the final matrix
	{
		for(int j = 0; j < (rows / 2); j++)
		{
			Temp.m[i + (rows / 2)][j] = U.m[i][j];
		}
	}


	for(int i = 0; i < (rows / 2); i++)				//Used to assemble top right of the final matrix
	{	
		for(int j = 0; j < (rows - (rows / 2)); j++)
		{
			Temp.m[i][j + (rows / 2)] = J.m[i][j];
		}
	}

	for(int i = 0; i < (rows - (rows / 2)); i++)			//Used to assembly buttom right of the final matrix
	{
		for(int j = 0; j < (rows - (rows / 2)); j++)
		{
			Temp.m[i + (rows / 2)][j + (rows / 2)] = V.m[i][j];
		}
	}
	return Temp;
}



/***********************************************************************************************/
//Equal Operator										/
//Used to Assign one matirx to another by putting all the values in the new matrix.		/
/***********************************************************************************************/
	template<class T>
const Matrix<T> Matrix<T>::operator=(const Matrix &right)
{
	//free space if it was in use.
	for(int i = 0; i < rows; i++)
	{
		delete [] m[i];
	}
	delete [] m;


	rows = right.rows;
	cols = right.cols;
	m = new T*[rows];

	for(int i = 0; i < rows; i++)	
	{
		m[i] = new T[cols];
		for(int j = 0; j < cols; j++)			//Assigns the values of the matrix on the right side to the matrix on the left.
		{
			m[i][j] = right.m[i][j];
		}
	}
	return *this;						//Returns the matrix that just got all the values.
}




/***********************************************************************************************/
//Print matrix function										/
//Prints out the matrix that calls the print function						/
/***********************************************************************************************/
	template<class T>
void Matrix<T>::printMatrix()
{
	for(int i = 0; i < rows; i++)
	{
		std::cout << "|";
		for(int j = 0; j < cols; j++)
		{
			std::cout << m[i][j] << " ";
		}
		std::cout << "|";
		std::cout << std::endl;
	}
	std::cout << std::endl;
}


/***********************************************************************************************/
//Addition Operator between 2 matrices								/
//Overloaded the + operator so if 2 matrices was added this function gets called		/
/***********************************************************************************************/
	template<class T>
const Matrix<T> Matrix<T>::operator+(const Matrix &right)
{

	
	if(rows != right.rows && cols != right.cols)					//Validation check if there is an error opening the file
	{
		std::cerr << "Invalid sizez of matrix for Additions" << std::endl;
		exit(1);
	}

	Matrix<T> C(rows, right.cols);					//make sure the new matrix to hold the sum of both matrices has a valid size
	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < cols; j++)
		{
			C.m[i][j] = m[i][j] + right.m[i][j];		//add each position of the matrices and assign them to a position in the new matrix.
		}
	}
	return C;							//return the new matrix with both matrices sums.
}



/***********************************************************************************************/
//Subtracting Operator bewteen 2 matrices							/
//Overloaded the - operator so if 2 matrices was subtracted this function gets called		/
/***********************************************************************************************/
	template<class T>
const Matrix<T> Matrix<T>::operator-(const Matrix &right)
{

	
	
	if(rows != right.rows && cols != right.cols)					//Validation check if there is an error opening the file
	{
		std::cerr << "Invalid sizes of matrix for Subtractions" << std::endl;
		exit(1);
	}

	Matrix<T> C(rows, right.cols);					//make sure the new matrix to hold the differences of both matrices has a valid size
	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < cols; j++)
		{
			C.m[i][j] = m[i][j] - right.m[i][j];		//subtracts each position of the matrices and assign them to a position in the new matrix.	
		}
	}
	return C;							//return the new matrix with both matrices differences.
}



/***********************************************************************************************/
//Multiply Operator between 2 matrices								/
///Overloaded the * operator so if 2 matrices was added this function gets called		/
/***********************************************************************************************/
	template<class T>
const Matrix<T> Matrix<T>::operator*(const Matrix &right)
{

	
	if(cols != right.rows)					//Validation check if there is an error opening the file
	{
		std::cerr << "Invalid sizes for Multiplication" << std::endl;
		exit(1);
	}


	Matrix<T> C(rows, right.cols);					//make sure the new matrix to hold the product of both matrices has a valid size
	for(int i = 0; i < C.rows; i++)
	{
		for(int j = 0; j < C.cols; j++)
		{
			for(int l = 0; l < right.rows; l++)
			{
				C.m[i][j] += m[i][l] * right.m[l][j];	//multiplies each position of the matrices and assign them to a position in the new matrix.
			}	
		}
	}
	return C;							//return the new matrix with both matrices products.
}



/***********************************************************************************************/
//Multiply Operator between a matrix and an integer number.					/
//Overloaded the * operator so if a matrix and an integer number was multiplied,		/ 
//this function gets called									/
/***********************************************************************************************/
	template<class T>
const Matrix<T> Matrix<T>::operator*(const int &right)
{
	Matrix<T> C(rows, cols);					//make sure the new matrix to hold the product of a matrix and an integer num has a valid size
	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < cols; j++)
		{
			C.m[i][j] +=  right * m[i][j];		//multiplies each position of the matrix and the num and assign them to a position in the new matrix.
		}
	}
	return C;							//return the new matrix with the products of the matrix and the number.
}




/***********************************************************************************************/
//Sorted Matrix function									/
//Used to make accept the rows and cols from user and make a matrix of the size of rows and cols/
/***********************************************************************************************/
template<class T>
Matrix<T> Matrix<T>::SortedMatrix()
{
	Matrix<T> Temp(rows, cols);
	int num = 0;
	for(int i = 0; i < rows; i++)
	{
		//	A.m[i] = new int[cols];
		for(int j = 0; j < cols; j++)
		{
			Temp.m[i][j] = (num + 1);
			num++;
		}
	}
	return Temp;
}




/***********************************************************************************************/
//Random Matrix function									/
//Used to make accept the rows and cols from user and make a matrix of the size of rows and cols/
/***********************************************************************************************/
template<class T>
Matrix<T> Matrix<T>::RandMatrix()
{
	Matrix<T> Temp(rows, cols);
	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < cols; j++)
		{
			Temp.m[i][j] = rand() % 50 + 1;
		}
	}
	return Temp;
}
