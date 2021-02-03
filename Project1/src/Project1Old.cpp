//============================================================================
// Name        : Project1.cpp
// Author      : kill this
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
/*
#include <iostream>
using namespace std;

class CSR{
	protected:
		int n;
		int m;
		int nonZeros;
		int* values;
		int* rowPtr;
		int* colPos;
	public:
		CSR ();
		CSR (CSR& matrixB);
		CSR (int rows, int cols, int numNonZeros);
		int getNumRows();
		int getNumCols();
		void addValue (int location, int value);
		void addColumn (int location, int col);
		void addRow (int& temporary, int location, int row);
		void display ();
		int* matrixVectorMultiply (int* inputVector);
		//CSR* matrixMultiply (CSR& matrixB);
		~CSR ();
};

CSR::CSR(){
	n = 0;
	m = 0;
	values = NULL;
	rowPtr = NULL;
	colPos = NULL;
}

CSR::CSR (CSR& matrixB){
	cout << "copying" << endl;

	n = matrixB.getNumRows();
	m = matrixB.getNumCols();
	nonZeros = matrixB.nonZeros;

	values = new int[nonZeros];
	rowPtr = new int[n];
	colPos = new int[nonZeros];

	for (int vals = 0; vals < nonZeros; vals++){
		values[vals] = matrixB.values[vals];
	}


	for (int rows = 0; rows < n; rows++){
		rowPtr[rows] = matrixB.rowPtr[rows];
	}

	for (int cols = 0; cols < nonZeros; cols++){
		colPos[cols] = matrixB.colPos[cols];
	}

	cout << "copying" << endl;
}

CSR::CSR (int rows, int cols, int numNonZeros) {
	n = rows;
	m = cols;
	nonZeros = numNonZeros;
	values = new int [nonZeros];
	colPos = new int [nonZeros];
	rowPtr = new int [n];
}

int CSR::getNumRows(){
	return n;
}

int CSR::getNumCols(){
	return m;
}

void CSR::addValue(int location, int value){
	values[location] = value;
}

void CSR::addColumn (int location, int col){
	colPos[location] = col;
}


void CSR::addRow (int& temporary, int location, int row){
	for (int i = 0; i < getNumRows(); i++){
		if (row == i && row != temporary){
			//cout << "test" << endl;
			rowPtr[i] = location;
			temporary = row;
			break;
		}
	}
}

void CSR::display (){
	//int** matrix = new int*[getNumRows()];

	//for (int i = 0; i < getNumRows(); i++){
	//		matrix[i] = new int[getNumCols()];
	//}
	/*

	for (int j = 0; j < getNumRows(); j++){
		int start = rowPtr[j];
		int end = nonZeros;

		if (j != (getNumRows() - 1)){

			end = rowPtr[j+1];
		}
		else {
			end = nonZeros;
		}


		for (int k = start; k < end; k++){
			//matrix[j][colPos[k]] = values[k];
			cout << values[k] << " (" << k << ") " ;
		}
		cout << endl;
	}
	*/

	/*
	 for(int r = 0; r < getNumRows(); r++){
		 for(int c = 0; c < getNumCols(); c++){
			 cout << matrix[r][c] << " ";
	     }
	     cout << endl;
	 }


	for (int vals = 0; vals < nonZeros; vals++){
		cout << values[vals] << " ";
	}
	cout << endl;

	for (int rows  = 0; rows < getNumRows(); rows++){
		cout << rowPtr[rows] << " ";
	}
	cout << endl;

	for (int cols = 0; cols < nonZeros; cols++){
		cout << colPos[cols] << " ";
	}
	cout << endl;

}

int* CSR::matrixVectorMultiply (int* inputVector){
	int* outputVector = new int [n];
	for (int i=0; i < n; i++)
		outputVector[i] = 0;

	for (int i=0; i < n; i++){
		int start = rowPtr[i];
		int end = 0;

		if (i == n-1){
			end = nonZeros;
		}
		else {
			end = rowPtr[i+1];
		}

		for (int j=start; j < end; j++){
			outputVector[i] = outputVector[i] + values[j] * inputVector[colPos[j]];
		}
	}
	return outputVector;
}

//CSR* matrixMultiply (CSR& matrixB){

//}

CSR::~CSR ( ) {
	if (values != NULL)
		delete [ ] values;
	if (rowPtr != NULL)
		delete [ ] rowPtr;
	if (colPos != NULL)
		delete [ ] colPos;
	cout << "CSR Object Destroyed!!" << endl;
	n = 0;
	m = 0;
	nonZeros = 0;
}

int main ( ) {
	int temp = -1;
	CSR* A;
	CSR* B;
	int* aVector;
	int numRows, numColumns, numNonZeros;
	int row, col, value;   //read in the first matrix
	cin >> numRows >> numColumns;
	cin >> numNonZeros;
	A = new CSR (numRows, numColumns, numNonZeros);
	for (int i=0; i < numNonZeros; i++) {
		cin >> row >> col >> value;
		(*A).addValue (i, value);
		(*A).addRow (temp, i, row);//needs to be done cleverly in the method
		(*A).addColumn (i, col);
	}
	(*A).display ();

	cout << "test" << endl;

	CSR* C = new CSR (*A); //calling the copy constructor
	(*C).display ();


	//read in the second matrix which is similar to the first into the CSR pointer object B and display; Write code for this

	//(*B).display ( );
	//read in the vector
	cin >> numColumns;
	aVector = new int [numColumns];
	for (int i=0; i < numColumns; i++)
		cin >> aVector[i]; //Matrix-Vector Multiplication

	int* resultVector = (*A).matrixVectorMultiply (aVector);
	for (int i=0; i < (*A).getNumRows ( ); i++)
		cout << resultVector [i] << " ";

	cout << endl;

	//Matrix-Matrix Multiplication

	//CSR* resultMatrix = (*C).matrixMultiply (*B);
	//(*resultMatrix).display ( );

	// Call the destructors
	delete [ ] aVector;
	delete [ ] resultVector;
	delete A;
	delete B;
	//delete C;
	//delete resultMatrix;

	return 0;
}
*/
