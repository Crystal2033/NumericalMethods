#pragma once
#include "Matrix.h"
class NormaInterface {
public:
	NormaInterface() = default;
	virtual double countNorm(const Matrix& matrix) const = 0;
	virtual ~NormaInterface() = default;
};

//--------------------------------------------------------
class NormaVectorMaxVal : public NormaInterface {
public:
	NormaVectorMaxVal() = default;
	double countNorm(const Matrix& matrix) const override;
	~NormaVectorMaxVal() = default;
};

class NormaMatrixMaxSumInRows : public NormaInterface {
public:
	NormaMatrixMaxSumInRows() = default;
	double countNorm(const Matrix& matrix) const override;
	~NormaMatrixMaxSumInRows() = default;
};
//--------------------------------------------------------
//--------------------------------------------------------
class NormaVectorSumVals : public NormaInterface {
public:
	NormaVectorSumVals() = default;
	double countNorm(const Matrix& matrix) const override;
	~NormaVectorSumVals() = default;
};

class NormaMatrixMaxSumInCols : public NormaInterface {
public:
	NormaMatrixMaxSumInCols() = default;
	double countNorm(const Matrix& matrix) const override;
	~NormaMatrixMaxSumInCols() = default;
};
//--------------------------------------------------------
//--------------------------------------------------------
class NormaEuclidVector : public NormaInterface {
public:
	NormaEuclidVector() = default;
	double countNorm(const Matrix& matrix) const override;
	~NormaEuclidVector() = default;
};

class NormaEuclidMatrix : public NormaInterface {
public:
	NormaEuclidMatrix() = default;
	double countNorm(const Matrix& matrix) const override;
	~NormaEuclidMatrix() = default;
};
//--------------------------------------------------------
