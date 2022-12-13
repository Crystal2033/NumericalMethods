#include "Methods.h"
#define M_PI_4 0.785398163397448309616

std::vector<double> Methods::gaussSolveSLAE(const Matrix& extendedMatrix)
{
	std::vector<double> xVector;
	Matrix temp = fullEchelonForm(extendedMatrix);
    for (unsigned int i = 0; i < extendedMatrix.rowsValue; i++) {
		xVector.push_back(temp.matrix[i][temp.columnsValue - 1]);
	}
	return xVector;
}

std::vector<double> Methods::solveSweepingSLAE(const Matrix& extendedMatrix)
{
	const int valueOfRows = extendedMatrix.rowsValue;
	Matrix aVec(1, valueOfRows);
	Matrix bVec(1, valueOfRows);
	Matrix cVec(1, valueOfRows);
	Matrix dVec(1, valueOfRows);

	setABCDVectorsForSweeping(aVec, bVec, cVec, dVec, extendedMatrix);
	
	Matrix pSweepCoeffs(1, valueOfRows);
	Matrix qSweepCoeffs(1, valueOfRows);

	setPQSweepCoeffs(pSweepCoeffs, qSweepCoeffs, aVec, bVec, cVec, dVec);


	return getXVectorSweeping(pSweepCoeffs, qSweepCoeffs);
}




void Methods::setABCDVectorsForSweeping(Matrix& aVec, Matrix& bVec, Matrix& cVec, Matrix& dVec, const Matrix& extendedMatrix) const
{
    for (unsigned int i = 0; i < extendedMatrix.rowsValue; i++) {
		dVec.matrix[0][i] = extendedMatrix.matrix[i][extendedMatrix.columnsValue - 1];
		bVec.matrix[0][i] = extendedMatrix.matrix[i][i];
		if (i == 0) {
			aVec.matrix[0][i] = 0.0;
			cVec.matrix[0][i] = extendedMatrix.matrix[i][i + 1];
		}
		else if (i == extendedMatrix.rowsValue - 1) {
			aVec.matrix[0][i] = extendedMatrix.matrix[i][i - 1];
			cVec.matrix[0][i] = 0.0;
		}
		else {
			aVec.matrix[0][i] = extendedMatrix.matrix[i][i - 1];
			cVec.matrix[0][i] = extendedMatrix.matrix[i][i + 1];
		}
	}
}

void Methods::setPQSweepCoeffs(Matrix& pVec, Matrix& qVec,  const Matrix& aVec, const Matrix& bVec, const Matrix& cVec, const Matrix& dVec) const
{
	const int colsValue = pVec.columnsValue;
	for (int i = 0; i < colsValue; i++) {
		double denominator = bVec.matrix[0][i] + ((i == 0) ? 0.0 : aVec.matrix[0][i] * pVec.matrix[0][i - 1]);
		pVec.matrix[0][i] = -cVec.matrix[0][i] / denominator;
		qVec.matrix[0][i] = (dVec.matrix[0][i] - ((i == 0) ? 0.0 : aVec.matrix[0][i] * qVec.matrix[0][i - 1])) / denominator;
	}
}

std::vector<double> Methods::getXVectorSweeping(const Matrix& pVec, const Matrix& qVec) const
{
	std::vector<double> xVector;
	
	const int colsValue = pVec.columnsValue;
	xVector.resize(colsValue);

	for (int i = colsValue - 1; i >= 0; i--) {
		xVector[i] = qVec.matrix[0][i] + ((i == colsValue - 1) ? 0.0 : pVec.matrix[0][i] * xVector[i + 1]);
	}
	return xVector;
}



