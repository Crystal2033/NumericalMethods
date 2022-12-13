#pragma once
#include <iostream>
#include <vector>

#define EPSILON 1e-10
class Matrix
{
	friend class Methods;

	friend class GaussMatrixIniter;
	friend class SweeperMatrixIniter;
	friend class SimpleIterMatrixIniter;
	friend class JakobiMatrixIniter;

	friend class NormaVectorMaxVal;
	friend class NormaMatrixMaxSumInRows;
	friend class NormaVectorSumVals;
	friend class NormaMatrixMaxSumInCols;
	friend class NormaEuclidVector;
	friend class NormaEuclidMatrix;
public:
	Matrix();
	Matrix(const int row, const int column);
	Matrix(const Matrix& copyMatrix);
	Matrix(const std::vector<std::vector<double>> initValues);
	Matrix(const std::vector<double> initValues);
	~Matrix() = default;
	int getRowsValue() const { return rowsValue; }
	int getColsValue() const { return columnsValue; }
	double get(const int row, const int col) const; 

	friend Matrix fullEchelonForm(const Matrix& extendedMatrix);

	static Matrix getIdentity(const int size);
	static Matrix transpose(const Matrix& matrix);
	bool operator==(const Matrix&);
	Matrix& operator=(const Matrix&);
	Matrix& operator+=(const Matrix&);
	Matrix& operator-=(const Matrix&);
	Matrix& operator*=(const Matrix&);
	Matrix& operator*=(double);
	Matrix& operator/=(double);
	void addRow(std::vector<double> row);
	void addCol(std::vector<double> row);
	void addRow(const Matrix& from, const int rowIndex);
	void addCol(const Matrix& from, const int colIndex);
	Matrix getRow(const int row) const;
	Matrix getCol(const int col) const;

	friend std::ostream& operator<<(std::ostream&, const Matrix&);
	friend std::istream& operator>>(std::istream&, Matrix&);
	
private:
	void divideRowOnValue(const int row, const double value);
	void divideColOnValue(const int col, const double value);
	void addRowToRow(const int from, const int to);
	void addRowToRow(const Matrix& from, const int to);
	int rowsValue = 0;
	int columnsValue = 0;
	std::vector<std::vector<double>> matrix;

};


Matrix operator+(const Matrix&, const Matrix&);
Matrix operator-(const Matrix&, const Matrix&);
Matrix operator*(const Matrix&, const Matrix&);
Matrix operator*(const Matrix&, double);
Matrix operator*(double, const Matrix&);
Matrix operator/(const Matrix&, double);
