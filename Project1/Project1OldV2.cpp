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

int temp = 0;

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
		int getNumNonZeros();
		int* getValues();
		int* getRowPtr();
		int* getColPos();
		void addValue (int value);
		void addColumn (int col);
		void addRow (int row);
		void setValues (int* valuesArray);
		void setRowPtr (int* rowPtrArray);
		void setColPos (int* colPosArray);
		void fill(int*& array, int filled);
		void truncate(int*& array, int end);
		void display ();
		int* matrixVectorMultiply (int* inputVector);
		int** transpose(CSR& matrix);
		CSR* matrixMultiply (CSR& matrixB);
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

	fill(rowPtr, 0);
}

int CSR::getNumRows(){
	return n;
}

int CSR::getNumCols(){
	return m;
}

int CSR::getNumNonZeros(){
	return nonZeros;
}

int* CSR::getValues(){
	return values;
}

int* CSR::getRowPtr(){
	return rowPtr;
}

int* CSR::getColPos(){
	return colPos;
}
void CSR::addValue(int value){

	//cout << "\n old values: " << values[0] << ", " << values[1] << ", " << values[2] << ", " << values[3] << endl;

	//cout << values[2] << endl;

	//shiftLeft(values);
	//values[nonZeros-1] = value;

	values[temp] = value;

	//cout << "\n values: " << values[0] << ", " << values[1] << ", " << values[2] << ", " << values[3] << endl;
}

void CSR::addColumn (int col){
	//shiftLeft(colPos);
	//colPos[nonZeros-1] = col;

	colPos[temp] = col;
}

void CSR::addRow (int row){

	for (int i = 0; i < getNumRows(); i++){

		if (i == row && rowPtr[row] == 0 && i != 0){

			rowPtr[row] = temp;
			break;
		}
	}
}

void CSR::setValues (int* valuesArray){
	values = valuesArray;
}

void CSR::setRowPtr (int* rowPtrArray){
	rowPtr = rowPtrArray;
}

void CSR::setColPos (int* colPosArray){
	colPos = colPosArray;
}


void CSR::fill (int*& array, int filled){
	int size = sizeof(array) / sizeof(array[0]);
	for (int i = 0; i <= size; i++){
		array[i] = filled;
	}
}

void CSR::truncate (int*& array, int end){
	int* arrayNew = new int[end];
	for (int i = 0; i < end; i++){
		arrayNew[i] = array[i];
	}

	delete[] array;
	array = arrayNew;
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
	*-/

	/*
	 for(int r = 0; r < getNumRows(); r++){
		 for(int c = 0; c < getNumCols(); c++){
			 cout << matrix[r][c] << " ";
	     }
	     cout << endl;
	 }
	*-/

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

	fill(outputVector, 0);

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

int** CSR::transpose(CSR& matrix){
	int tRows = matrix.getNumCols();
	int tCols = matrix.getNumRows();

	int** tMatrix = new int*[tRows];

	 for (int i = 0; i < tRows; i++){
		tMatrix[i] = new int[tCols];
	}

	 for (int j = 0; j < tRows; j++){
	 	int start = matrix.getRowPtr()[j];
	 	int end = matrix.getNumNonZeros();

	 	if (j != (tRows - 1)){
	 		end = matrix.getRowPtr()[j+1];
	 	}
	 	else {
	 		end = matrix.getNumNonZeros();
	 	}

	 	for (int k = start; k < end; k++){
	 		tMatrix[matrix.getColPos()[k]][j] = matrix.getValues()[k];
	 		//cout << values[k] << " (" << k << ") " ;
	 	}
	 }


	 return tMatrix;

}

CSR* CSR::matrixMultiply (CSR& matrixB){
	if (m != matrixB.getNumRows()){
		return NULL;
	}

	CSR* product;

	int productRows = n;
	int productCols = matrixB.getNumCols();

	int productNonZeros = 0;
	int rowHolder = -1;

	int* valuesTemp = new int[productRows*productCols];
	int* rowPtrTemp = new int[productRows];
	int* colPosTemp = new int[productRows*productCols];

	fill(valuesTemp, 0);
	fill(rowPtrTemp, 0);
	fill(colPosTemp, 0);

	int** productMatrix = new int*[productRows];
	for (int i = 0; i < productRows; i++){
		productMatrix[i] = new int[productCols];
	}

	int* storage;

	int** tMatrix = transpose(matrixB);

	/*
	for (int i = 0; i < productRows; i++){
		productMatrix[i] = matrixVectorMultiply(tMatrix[i]);
		for (int j = 0; j < productCols; j++){

			cout << productMatrix[i][j] << " ";

			if (productMatrix[i][j] != 0){

				valuesTemp[productNonZeros] = productMatrix[i][j];
				colPosTemp[productNonZeros] = j;

				if (i != rowHolder){
					rowPtrTemp[i] = productNonZeros;
					rowHolder = i;
				}

				productNonZeros++;
			}
		}
	}
	*-/

	for (int cols = 0; cols < productCols; cols++){
		storage = matrixVectorMultiply(tMatrix[cols]);

		for (int rows = 0; rows < productRows; rows++){
			productMatrix[rows][cols] = storage[rows];
		}
	}


	for (int rows = 0; rows < productRows; rows++){
		for (int cols = 0; cols < productCols; cols++){
			if (productMatrix[rows][cols] != 0){

				valuesTemp[productNonZeros] = productMatrix[rows][cols];
				colPosTemp[productNonZeros] = cols;

				if (rows != rowHolder){
					rowPtrTemp[rows] = productNonZeros;
					rowHolder = rows;
				}

				productNonZeros++;
			}
		}
	}

	product = new CSR (productRows, productCols, productNonZeros);

	truncate(valuesTemp, productNonZeros);
	truncate(rowPtrTemp, productRows);
	truncate(colPosTemp, productNonZeros);

	(*product).setValues(valuesTemp);
	(*product).setRowPtr(rowPtrTemp);
	(*product).setColPos(colPosTemp);


	/*
	for (int nonZeros = 0; nonZeros < productNonZeros; nonZeros++){


		(*product).addValue (valuesTemp[nonZeros]);
		(*product).addColumn (colPosTemp[nonZeros]);
	}

	for (int rows = 0; rows < productRows; rows++){
		(*product).addRow (rowPtrTemp[rows]);
	}
	*-/

	cout << endl;

	for (int rows = 0; rows < productRows; rows++){
		for (int cols = 0; cols < productCols; cols++){
			cout << productMatrix[rows][cols] << " ";
		}
		cout << endl;
		delete[] productMatrix[rows];
	}

	cout << endl;

	delete[] storage;
	delete[] valuesTemp;
	delete[] rowPtrTemp;
	delete[] colPosTemp;

	return product;
}

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
	CSR* A;
	CSR* B;
	int* aVector;
	int numRows, numColumns, numNonZeros;
	int row, col, value;   //read in the first matrix
	cin >> numRows >> numColumns;
	cin >> numNonZeros;
	A = new CSR (numRows, numColumns, numNonZeros);
	for (int i=0; i < numNonZeros; i++) {
		temp = i;

		cin >> row >> col >> value;
		(*A).addValue (value);
		(*A).addRow (row);//needs to be done cleverly in the method
		(*A).addColumn (col);

	}
	(*A).display ();

	cout << "\n copied matrix \n" << endl;

	CSR* C = new CSR (*A); //calling the copy constructor
	(*C).display ();

	//read in the second matrix which is similar to the first into the CSR pointer object B and display; Write code for this

	cout << "\n second matrix \n" << endl;

	cin >> numRows >> numColumns;
	cin >> numNonZeros;
	B = new CSR (numRows, numColumns, numNonZeros);
	for (int i=0; i < numNonZeros; i++) {
		temp = i;

		cin >> row >> col >> value;
		(*B).addValue (value);
		(*B).addRow (row);//needs to be done cleverly in the method
		(*B).addColumn (col);

	}

	(*B).display ( );

	cout << "enter vector size, then vector" << endl;

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

	CSR* resultMatrix = (*C).matrixMultiply (*B);
	(*resultMatrix).display ( );

	// Call the destructors
	delete [ ] aVector;
	delete [ ] resultVector;
	delete A;
	delete B;
	delete C;
	delete resultMatrix;

	return 0;
}
*/
