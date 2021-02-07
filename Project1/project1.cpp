//============================================================================
// Name        : Project1.cpp
// Author      : kill this
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

// Used to store index of values when placed into value/row-index/column array
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
		void truncate(int*& array, int end);
		void fill(int*& array, int filled);
		void display ();
		int* matrixVectorMultiply (int* inputVector);
		int** transpose(CSR& matrix);
		CSR* matrixMultiply (CSR& matrixB);
		~CSR ();
};

// CSR empty constructor
CSR::CSR(){
	n = 0;
	m = 0;
	values = NULL;
	rowPtr = NULL;
	colPos = NULL;
}

// CSR copy-by-alias constructor
CSR::CSR (CSR& matrixB){

	n = matrixB.getNumRows();
	m = matrixB.getNumCols();
	nonZeros = matrixB.nonZeros;

	values = matrixB.getValues();
	rowPtr = matrixB.getRowPtr();
	colPos = matrixB.getColPos();

}

// CSR normal constructor
CSR::CSR (int rows, int cols, int numNonZeros) {
	n = rows;
	m = cols;
	nonZeros = numNonZeros;

	values = new int [nonZeros];
	colPos = new int [nonZeros];
	rowPtr = new int [n];
}

// Getter for the amount of rows in the matrix
int CSR::getNumRows(){
	return n;
}

// Getter for the amount of columns in the matrix
int CSR::getNumCols(){
	return m;
}

// Getter for the amount of non-zero values in the matrix
int CSR::getNumNonZeros(){
	return nonZeros;
}

// Getter for the array of non-zero values in the matrix
int* CSR::getValues(){
	return values;
}

// Getter for the array of index of row within value array
int* CSR::getRowPtr(){
	return rowPtr;
}

// Getter for the array of column positions for values within value array
int* CSR::getColPos(){
	return colPos;
}

// Appends value to the value array
void CSR::addValue(int value){
	values[temp] = value;
}

// Appends value to column array
void CSR::addColumn (int col){
	colPos[temp] = col;
}

// Appends value to the row-index array
void CSR::addRow (int row){

	for (int i = 0; i < getNumRows(); i++){

		// If an inserted value's row-index of the row-index array is empty,
		// set that value to the index of inserted value
		if (i == row && rowPtr[row] == 0 && i != 0){

			rowPtr[row] = temp;
			break;
		}
	}
}

// Sets the value array to an already-existing array
void CSR::setValues (int* valuesArray){
	values = valuesArray;
}

// Sets the row-index array to an already-existing array
void CSR::setRowPtr (int* rowPtrArray){
	rowPtr = rowPtrArray;
}

// Sets the column array to an already-existing array
void CSR::setColPos (int* colPosArray){
	colPos = colPosArray;
}

// Truncates an array to [0:end)
void CSR::truncate (int*& array, int end){
	int* arrayNew = new int[end];
	for (int i = 0; i < end; i++){
		arrayNew[i] = array[i];
	}

	delete[] array;
	array = arrayNew;
}

void CSR::fill (int*& array, int filled){
	int size = sizeof(array) / sizeof(array[0]);
	for (int i = 0; i <= size; i++){
		array[i] = filled;
	}
}

// Displays the matrix in matrix form
// Additionally, displays the value. row-index, and column arrays
void CSR::display (){

	// Fills in the value of the matrix
	for (int j = 0; j < getNumRows(); j++){
		int start = rowPtr[j];
		int end = nonZeros;

		if (j != (getNumRows() - 1)){

			end = rowPtr[j+1];
		}
		else {
			end = nonZeros;
		}

		string line = "";

		for (int k = 0; k < getNumCols(); k++){

			bool found = false;
			for (int l = start; l < end; l++){
				if (k == colPos[l]){
					line.append(to_string(values[l]) + " ");
					found = true;
					break;
				}
			}

			if (!found){
				line.append("0 ");
			}
		}

		cout << line << endl;

	}

	// Prints out row-index array
	cout << "rowPtr: ";
	for (int rows  = 0; rows < getNumRows(); rows++){
		cout << rowPtr[rows] << " ";
	}
	cout << endl;


	// Prints out column array
	cout << "colPos: ";
	for (int cols = 0; cols < nonZeros; cols++){
		cout << colPos[cols] << " ";
	}
	cout << endl;


	// Prints out value array
	cout << "values: ";
	for (int vals = 0; vals < nonZeros; vals++){
			cout << values[vals] << " ";
	}
	cout << endl;
}

// Multiplies the matrix with a vector
int* CSR::matrixVectorMultiply (int* inputVector){
	int* outputVector = new int [n];

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

// Returns a transposed version of the original matrix
// Because matrix-multiplication requires to parse the columns of the second matrix,
// transpose the second matrix to make grabbing these columns easier
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
	 	}
	 }

	 return tMatrix;
}

// Multiplies 2 two CSR matrices together, returning
// the product matrix as a CSR object
CSR* CSR::matrixMultiply (CSR& matrixB){

	// if columns of first matrix not equal to rows of second matrix,
	// return nothing
	if (m != matrixB.getNumRows()){
		return NULL;
	}

	CSR* product;

	int productRows = getNumRows();
	int productCols = matrixB.getNumCols();

	int productNonZeros = 0;

	// Used to see if a value is the first value of its row
	int rowHolder = -1;

	// Because we do not know the size of these arrays,
	// create "temporary" arrays of the maximum size possible
	int* valuesTemp = new int[productRows*productCols];
	int* rowPtrTemp = new int[productRows];
	int* colPosTemp = new int[productRows*productCols];

	int** productMatrix = new int*[productRows];
	for (int i = 0; i < productRows; i++){
		productMatrix[i] = new int[productCols];
	}

	// Stores the matrix created by multiplying Matrix #1 to column of Matrix #2
	int* storage;

	// Holds the transposed version of Matrix #2
	int** tMatrix = transpose(matrixB);

	// Multiplies Matrix 1 and Matrix 2 together,
	// Stores product in the product matrix
	for (int cols = 0; cols < productCols; cols++){
		storage = matrixVectorMultiply(tMatrix[cols]);

		for (int rows = 0; rows < productRows; rows++){
			productMatrix[rows][cols] = storage[rows];
		}
	}

	// Parses product matrix to create value/row-index/column arrays
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

	// Creates CSR object of the product matrix
	product = new CSR (productRows, productCols, productNonZeros);

	// Because size of each array is known,
	// truncate each array to fit to size
	truncate(valuesTemp, productNonZeros);
	truncate(rowPtrTemp, productRows);
	truncate(colPosTemp, productNonZeros);

	// Sets the values to the CSR product to the value/row-index/column arrays
	(*product).setValues(valuesTemp);
	(*product).setRowPtr(rowPtrTemp);
	(*product).setColPos(colPosTemp);


	// Cleaning up memory
	for (int rows = 0; rows < productRows; rows++){
		delete[] productMatrix[rows];
	}

	for (int rows = 0; rows < matrixB.getNumCols(); rows++){
		delete[] tMatrix[rows];
	}


	delete[] storage;
	delete[] valuesTemp;
	delete[] rowPtrTemp;
	delete[] colPosTemp;

	return product;
}

// Destructor
CSR::~CSR ( ) {
	if (values != NULL)
		delete [ ] values;
	if (rowPtr != NULL)
		delete [ ] rowPtr;
	if (colPos != NULL)
		delete [ ] colPos;
	n = 0;
	m = 0;
	nonZeros = 0;
}

int main ( ) {
	CSR* A;
	CSR* B;
	int* aVector;
	int numRows, numColumns, numNonZeros;
	int row, col, value;

	// Creates Matrix A
	cin >> numRows >> numColumns;
	cin >> numNonZeros;
	A = new CSR (numRows, numColumns, numNonZeros);
	for (int i=0; i < numNonZeros; i++) {
		temp = i;

		cin >> row >> col >> value;
		(*A).addValue (value);
		(*A).addRow (row);
		(*A).addColumn (col);

	}

	cout << "Matrix A" << endl;
	(*A).display ();

	// Copies Matrix A to create Matrix C
	cout << "Matrix C" << endl;
	CSR* C = new CSR (*A);
	(*C).display ();

	// Creates Matrix B
	cin >> numRows >> numColumns;
	cin >> numNonZeros;

	B = new CSR (numRows, numColumns, numNonZeros);
	for (int i=0; i < numNonZeros; i++) {
		temp = i;

		cin >> row >> col >> value;
		(*B).addValue (value);
		(*B).addRow (row);
		(*B).addColumn (col);

	}

	cout << "Matrix B" << endl;
	(*B).display ( );

	cout << flush;
	//read in the vector
	cin >> numColumns;
	aVector = new int [numColumns];
	for (int i=0; i < numColumns; i++){
		cin >> aVector[i];
		//cout << "inserted: " << aVector[i] << endl;

	}
	cout << flush;

	cout << "Vector" << endl;
	for (int i=0; i < numColumns; i++){
		cout << aVector[i] << " ";
	}
	cout << endl;

	// Matrix-Vector Multiplication
	int* resultVector = (*A).matrixVectorMultiply (aVector);

	cout << "A * Vector" << endl;
	for (int i=0; i < (*A).getNumRows ( ); i++){
		cout << resultVector [i] << " ";
	}
	cout << endl;

	//Matrix-Matrix Multiplication
	cout << "A * B" << endl;
	CSR* resultMatrix = (*C).matrixMultiply (*B);
	(*resultMatrix).display ( );

	// Call the destructors
	delete [] aVector;
	delete [] resultVector;
	delete A;
	delete B;
	delete C;
	delete resultMatrix;

	return 0;
}
