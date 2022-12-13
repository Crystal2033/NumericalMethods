#pragma once
#include "Matrix.h"
class Methods {
public:
	std::vector<double> gaussSolveSLAE(const Matrix& extendedMatrix);
	std::vector<double> solveSweepingSLAE(const Matrix& extendedMatrix);
	
private:
	void setABCDVectorsForSweeping(Matrix& aVec, Matrix& bVec, Matrix& cVec, Matrix& dVec, const Matrix& extendedMatrix) const;
	void setPQSweepCoeffs(Matrix& pVec, Matrix& qVec, const Matrix& aVec, const Matrix& bVec, const Matrix& cVec, const Matrix& dVec) const;
	std::vector<double> getXVectorSweeping(const Matrix& pVec, const Matrix& qVec) const;
};
