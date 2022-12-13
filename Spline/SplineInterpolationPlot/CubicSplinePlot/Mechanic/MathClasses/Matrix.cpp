#include "Matrix.h"
#include "Mechanic/Colors.h"
#include "Mechanic/Exceptions/Exceptions.h"
#include <math.h>

Matrix::Matrix()
{
	
}

Matrix::Matrix(const int row, const int column){
	if (row <= 0) {
		throw MatrixErrorException("Bad row value.");
	}
	if (column <= 0) {
		throw MatrixErrorException("Bad column value.");
	}
	rowsValue = row;
	columnsValue = column;
    for (unsigned i = 0; i < rowsValue; i++) {
		matrix.push_back(std::vector<double>{});
        for (unsigned j = 0; j < columnsValue; j++) {
			matrix[i].push_back(0.0);
		}
	}
}

Matrix::Matrix(const Matrix& copyMatrix)
{
	rowsValue = copyMatrix.getRowsValue();
	columnsValue = copyMatrix.getColsValue();
    for (unsigned i = 0; i < rowsValue; i++) {
		matrix.push_back(std::vector<double>{});
        for (unsigned j = 0; j < columnsValue; j++) {
			matrix[i].push_back(copyMatrix.matrix[i][j]);
		}
	}
}

Matrix::Matrix(const std::vector<std::vector<double>> initValues)
{
	if (initValues.size() == 0) {
		throw MatrixErrorException("Bad init values.");
	}
	rowsValue = initValues.size();
	columnsValue = initValues[0].size();
    for (unsigned i = 0; i < rowsValue; i++) {
		matrix.push_back(std::vector<double>{});
        for (unsigned j = 0; j < columnsValue; j++) {
			matrix[i].push_back(initValues[i][j]);
		}
	}
}

Matrix::Matrix(const std::vector<double> initValues)
{
	if (initValues.size() == 0) {
		throw MatrixErrorException("Bad init values.");
	}
	this->addRow(initValues);
}


double Matrix::get(const unsigned row, const unsigned col) const
{
	if (row > rowsValue-1 || row < 0) {
		throw MatrixErrorException("Bad row value.");
	}
	if (col > columnsValue-1 || col < 0) {
		throw MatrixErrorException("Bad column value.");
	}
	return matrix[row][col];
}

void Matrix::set(const unsigned row, const unsigned col, const double value)
{
	if (row < 0 || row > rowsValue - 1) {
		throw MatrixErrorException("Bad row value.");
	}
	if (col < 0 || col > columnsValue - 1) {
		throw MatrixErrorException("Bad column value.");
	}

	matrix[row][col] = value;
}


Matrix Matrix::getIdentity(const int size)
{
	Matrix temp(size, size);
	for (int i = 0; i < size; i++) {
		temp.matrix[i][i] = 1.0;
	}
	return temp;
}

Matrix Matrix::transpose(const Matrix& matrix)
{
	Matrix transposedMatrix(matrix.columnsValue, matrix.rowsValue);
    for (unsigned i = 0; i < matrix.rowsValue; i++) {
        for (unsigned j = 0; j < matrix.columnsValue; j++) {
			transposedMatrix.matrix[j][i] = matrix.matrix[i][j];
		}
	}
	return transposedMatrix;
}

bool Matrix::operator==(const Matrix& m)
{
	if (this->getRowsValue() != m.getRowsValue()) {
		return false;
	}
	if (this->getColsValue() != m.getColsValue()) {
		return false;
	}
    for (unsigned i = 0; i < rowsValue; i++) {
        for (unsigned j = 0; j < columnsValue; j++) {
            if (fabs(matrix[i][j] - m.matrix[i][j]) > EPSILON) {
				return false;
			}
		}
	}
	return true;
}

Matrix& Matrix::operator=(const Matrix& m)
{
	if (this == &m) {
		return *this;
	}

    for (unsigned i = 0; i < rowsValue; i++) {
		matrix[i].clear();
	}
	matrix.clear();
	
    for (unsigned i = 0; i < m.rowsValue; i++) {
		matrix.push_back(std::vector<double>{});
        for (unsigned j = 0; j < m.columnsValue; j++) {
			matrix[i].push_back(m.matrix[i][j]);
		}
	}
	rowsValue = m.rowsValue;
	columnsValue = m.columnsValue;
	return *this;
}

Matrix& Matrix::operator+=(const Matrix& m)
{
	if (this->getRowsValue() != m.getRowsValue()) {
		throw MatrixErrorException("Bad row value.");
	}
	if (this->getColsValue() != m.getColsValue()) {
		throw MatrixErrorException("Bad column value.");
	}
    for (unsigned i = 0; i < rowsValue; i++) {
        for (unsigned j = 0; j < columnsValue; j++) {
			matrix[i][j] += m.matrix[i][j];
		}
	}
	return *this;
}

Matrix& Matrix::operator-=(const Matrix& m)
{
	if (this->getRowsValue() != m.getRowsValue()) {
		throw MatrixErrorException("Bad row value.");
	}
	if (this->getColsValue() != m.getColsValue()) {
		throw MatrixErrorException("Bad column value.");
	}
    for (unsigned i = 0; i < rowsValue; i++) {
        for (unsigned j = 0; j < columnsValue; j++) {
			matrix[i][j] -= m.matrix[i][j];
		}
	}
	return *this;
}

Matrix& Matrix::operator*=(const Matrix& m)
{
	Matrix temp(rowsValue, m.columnsValue);
    for (unsigned i = 0; i < temp.rowsValue; i++) {
        for (unsigned j = 0; j < temp.columnsValue; j++) {
            for (unsigned k = 0; k < columnsValue; k++) {
				temp.matrix[i][j] += (matrix[i][k] * m.matrix[k][j]);
			}
		}
	}
	return (*this = temp);
}

Matrix& Matrix::operator*=(double value)
{
    for (unsigned i = 0; i < rowsValue; i++) {
        for (unsigned j = 0; j < columnsValue; j++) {
			matrix[i][j] *= value;
		}
	}
	return *this;
}

Matrix& Matrix::operator/=(double value)
{
	if (fabs(value - 0) < EPSILON) {
		throw MatrixErrorException("Dividing by 0 error.");
	}
    for (unsigned i = 0; i < rowsValue; i++) {
        for (unsigned j = 0; j < columnsValue; j++) {
			matrix[i][j] /= value;
		}
	}
	return *this;
}

void Matrix::addRow(std::vector<double> row)
{
	if (columnsValue == 0) {
		matrix.push_back(row);
		columnsValue = row.size();
		rowsValue++;
		return;
	}

	if (columnsValue < row.size()) {
        for (unsigned i = 0; i < row.size() - columnsValue; i++) {
			matrix[i].push_back(0.0);
		}
		columnsValue = row.size();
	}
	else if (columnsValue > row.size()) {
        for (unsigned i = 0; i < columnsValue - row.size(); i++) {
			row.push_back(0.0);
		}
	}
	matrix.push_back(row);
	columnsValue = row.size();
	rowsValue++;
}

void Matrix::addCol(std::vector<double> col)
{
	if (rowsValue < col.size()) {
        for (unsigned i = 0; i < col.size() - rowsValue; i++) {
			matrix.push_back(std::vector<double>{});
		}
		rowsValue = col.size();
	}
	else if (rowsValue > col.size()) {
        for (unsigned i = 0; i < rowsValue - col.size(); i++) {
			col.push_back(0.0);
		}
	}

    for (unsigned i = 0; i < col.size(); i++) {
		matrix[i].push_back(col[i]);
	}
	columnsValue++;
}

void Matrix::addRow(const Matrix& from, const int rowIndex)
{
	if (columnsValue < from.columnsValue) {
        for (unsigned i = 0; i < from.columnsValue - columnsValue; i++) {
			matrix[i].push_back(0.0);
		}
		columnsValue = from.columnsValue;
	}


	matrix.push_back(std::vector<double>{});
	rowsValue++;
    for (unsigned i = 0; i < from.columnsValue; i++) {
		matrix[rowsValue - 1][i] = from.matrix[rowIndex][i];
	}
	
}

void Matrix::addCol(const Matrix& from, const int colIndex)
{
	if (rowsValue < from.rowsValue) {
        for (unsigned i = 0; i < from.rowsValue - rowsValue; i++) {
			matrix.push_back(std::vector<double>{});
		}
		rowsValue = from.rowsValue;
	}

    for (unsigned i = 0; i < from.rowsValue; i++) {
		matrix[i].push_back(from.matrix[i][colIndex]);
	}
    for (unsigned i = 0; i < rowsValue - from.rowsValue; i++) {
		matrix[i + from.rowsValue - 1].push_back(0.0);
	}
	columnsValue++;
}



Matrix Matrix::getRow(const int row) const
{
	Matrix temp(1, columnsValue);

    for (unsigned i = 0; i < columnsValue; i++) {
		temp.matrix[0][i] = matrix[row][i];
	}

	return temp;
}

Matrix Matrix::getCol(const int col) const
{
	Matrix temp(rowsValue, 1);

    for (unsigned i = 0; i < rowsValue; i++) {
		temp.matrix[i][0] = matrix[i][col];
	}

	return temp;
}

int Matrix::findRowForSwap(const int zeroRow, const int zeroCol) const
{
    for (unsigned i = zeroRow+1; i < rowsValue; i++) {
		if (fabs(matrix[i][zeroCol] - 0) > EPSILON) {
			return i;
		}
	}
	return -1;
}

void Matrix::swapRows(const int row1, const int row2)
{
	Matrix row1FromMatrix = this->getRow(row1);
    for (unsigned i = 0; i < columnsValue; i++) {
		matrix[row1][i] = matrix[row2][i];
		matrix[row2][i] = row1FromMatrix.matrix[0][i];
	}
}

void Matrix::divideRowOnValue(const int row, const double value)
{
	if (fabs(value - 0) < EPSILON) {
		throw MatrixErrorException("Dividing by 0 error.");
	}
    for (unsigned i = 0; i < columnsValue; i++) {
		matrix[row][i] /= value;
	}
}

void Matrix::divideColOnValue(const int col, const double value)
{
	if (fabs(value - 0) < EPSILON) {
		throw MatrixErrorException("Dividing by 0 error.");
	}
    for (unsigned i = 0; i < rowsValue; i++) {
		matrix[i][col] /= value;
	}
}

void Matrix::addRowToRow(const int from, const int to)
{
    for (unsigned i = 0; i < columnsValue; i++) {
		matrix[to][i] += matrix[from][i];
	}
}

void Matrix::addRowToRow(const Matrix& from, const int to)
{
	if (from.matrix.size() != 1) {
		throw MatrixErrorException("Excpected to see vector: 1xN");
	}

    for (unsigned i = 0; i < columnsValue; i++) {
		matrix[to][i] += from.matrix[0][i];
	}
}


std::ostream& operator<<(std::ostream& os, const Matrix& m)
{
    for (unsigned i = 0; i < m.rowsValue; i++) {
		os << m.matrix[i][0];
        for (unsigned j = 1; j < m.columnsValue; j++) {
			os << " " << m.matrix[i][j];
		}
		os << std::endl;
	}
	return os;
}

std::istream& operator>>(std::istream& is, Matrix& m)
{
	std::cout << cyan << "Input coeffs a before x." << white << std::endl;
    for (unsigned i = 0; i < m.rowsValue; i++) {
        for (unsigned j = 0; j < m.columnsValue; j++) {
			if (j < m.rowsValue) {
				std::cout << azure << "a[" << blue << i + 1 << azure << ", " << blue << j + 1 << azure <<"] = " << cyan;
			}
			else {
				std::cout << azure << "b[" << blue << i + 1 << azure <<  "] = " << cyan;
			}
			is >> m.matrix[i][j];
			std::cout << white << std::endl;
		}
	}
	return is;
}

Matrix operator+(const Matrix& first, const Matrix& second)
{
	Matrix temp(first);
	return (temp += second);
}

Matrix operator-(const Matrix& first, const Matrix& second)
{
	Matrix temp(first);
	return (temp -= second);
}

Matrix operator*(const Matrix& first, const Matrix& second)
{
	Matrix temp(first);
	return (temp *= second);
}

Matrix operator*(const Matrix& m, double value)
{
	Matrix temp(m);
	return (temp *= value);
}

Matrix operator*(double value, const Matrix&m)
{
	return (m * value);
}

Matrix operator/(const Matrix& first, double value)
{
	Matrix temp(first);
	return (temp /= value);
}

Matrix fullEchelonForm(const Matrix& extendedMatrix)
{
	std::vector<double> answerVector;
	answerVector.resize(extendedMatrix.rowsValue);
	Matrix temp(extendedMatrix);

    for (unsigned i = 0; i < temp.rowsValue - 1; i++) {
		double pivot = temp.matrix[i][i];
		if (fabs(pivot - 0.0) < EPSILON) {
			int swapRow = temp.findRowForSwap(i, i);
			if (swapRow == -1) {
				throw MatrixErrorException("Pivot is zero. No solutions.");
			}
			temp.swapRows(i, swapRow);
			pivot = temp.matrix[i][i];
		}
		temp.divideRowOnValue(i, pivot);
        for (unsigned j = i + 1; j < temp.rowsValue; j++) {
			Matrix additionCurRow = temp.getRow(i) * -temp.matrix[j][i];
			temp.addRowToRow(additionCurRow, j);
		}
	}

	temp.divideRowOnValue(temp.rowsValue - 1, temp.matrix[temp.rowsValue - 1][temp.rowsValue - 1]);
	

	for (int i = temp.rowsValue - 1; i > 0; i--) {
		for (int j = i - 1; j >= 0; j--) {
			Matrix additionCurRow = temp.getRow(i) * -temp.matrix[j][i];
			temp.addRowToRow(additionCurRow, j);
		}
	}
	
	return temp;

}
