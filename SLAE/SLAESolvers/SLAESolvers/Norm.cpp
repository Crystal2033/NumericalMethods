#include "Norm.h"
#include "Exceptions.h"

double NormaVectorMaxVal::countNorm(const Matrix& matrix) const
{
	if (matrix.rowsValue != 1 && matrix.columnsValue != 1) {
		throw NormErrorException("It`s not a vector for norm counting.");
	}
	double maxResult = 0.0;
	if (matrix.rowsValue == 1) {
		for (int i = 0; i < matrix.columnsValue; i++) {
			maxResult = max(maxResult, abs(matrix.matrix[0][i]));
		}
	}
	else if (matrix.columnsValue == 1) {
		for (int i = 0; i < matrix.rowsValue; i++) {
			maxResult = max(maxResult, abs(matrix.matrix[i][0]));
		}
	}
	return maxResult;
}

double NormaMatrixMaxSumInRows::countNorm(const Matrix& matrix) const
{
	double maxResult = 0.0;
	double currResult = 0.0;
	for (int i = 0; i < matrix.rowsValue; i++) {
		maxResult = max(maxResult, currResult);
		currResult = 0.0;
		for (int j = 0; j < matrix.columnsValue; j++) {
			currResult += abs(matrix.matrix[i][j]);
		}
	}
	maxResult = max(maxResult, currResult);
	return maxResult;

}
 
double NormaVectorSumVals::countNorm(const Matrix& matrix) const
{
	if (matrix.rowsValue != 1 && matrix.columnsValue != 1) {
		throw NormErrorException("It`s not a vector for norm counting.");
	}
	double result = 0.0;
	if (matrix.rowsValue == 1) {
		for (int i = 0; i < matrix.columnsValue; i++) {
			result += abs(matrix.matrix[0][i]);
		}
	}
	else if (matrix.columnsValue == 1) {
		for (int i = 0; i < matrix.rowsValue; i++) {
			result += abs(matrix.matrix[i][0]);
		}
	}
	return result;
}

double NormaMatrixMaxSumInCols::countNorm(const Matrix& matrix) const
{
	double maxResult = 0.0;
	double currResult = 0.0;
	for (int i = 0; i < matrix.columnsValue; i++) {
		maxResult = max(maxResult, currResult);
		currResult = 0.0;
		for (int j = 0; j < matrix.rowsValue; j++) {
			currResult += abs(matrix.matrix[j][i]);
		}
	}
	maxResult = max(maxResult, currResult);
	return maxResult;
}

double NormaEuclidVector::countNorm(const Matrix& matrix) const
{
	if (matrix.rowsValue != 1 && matrix.columnsValue != 1) {
		throw NormErrorException("It`s not a vector for norm counting.");
	}
	double result = 0.0;
	if (matrix.rowsValue == 1) {
		for (int i = 0; i < matrix.columnsValue; i++) {
			result += abs(pow(matrix.matrix[0][i], 2));
		}
	}
	else if (matrix.columnsValue == 1) {
		for (int i = 0; i < matrix.rowsValue; i++) {
			result += abs(pow(matrix.matrix[i][0], 2));
		}
	}
	return sqrt(result);
}

double NormaEuclidMatrix::countNorm(const Matrix& matrix) const
{
	double result = 0.0;
	for (int i = 0; i < matrix.rowsValue; i++) {
		for (int j = 0; j < matrix.columnsValue; j++) {
			result += abs(pow(matrix.matrix[i][j], 2));
		}
	}
	return sqrt(result);
}
