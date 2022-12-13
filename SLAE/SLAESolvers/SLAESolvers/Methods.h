#pragma once
#include "Matrix.h"
#include "Norm.h"
class Methods {
public:
	std::vector<double> gaussSolveSLAE(const Matrix& extendedMatrix);
	std::vector<double> solveSweepingSLAE(const Matrix& extendedMatrix);
	std::vector<double> solveSimpleIterationsSLAE(const Matrix& extendedMatrix);
	std::pair<std::vector<double>, Matrix> yacobiGetOwnNumbersAndVectors(const Matrix& matrix);
private:
	void setABCDVectorsForSweeping(Matrix& aVec, Matrix& bVec, Matrix& cVec, Matrix& dVec, const Matrix& extendedMatrix) const;
	void setPQSweepCoeffs(Matrix& pVec, Matrix& qVec, const Matrix& aVec, const Matrix& bVec, const Matrix& cVec, const Matrix& dVec) const;
	std::vector<double> getXVectorSweeping(const Matrix& pVec, const Matrix& qVec) const;

	void makeSimpleMatrixTransform(Matrix& matrix) const;
	void initAlphaAndBetaMatrixesInSimpleIters(Matrix& alpha, Matrix& beta, const Matrix& full);
	void setVectorAndMatrixNorm(NormaInterface*& vecNorm, NormaInterface*& matrixNorm, const Matrix& alpha);
	double getEpsiloneSimpleIterations(const double matrixNorm, const double vectorNorm, const std::vector<double>& xOldVector, const std::vector<double>& xNewVector, NormaInterface* const& vecNorm);
	double getEpsDeltaX(const std::vector<double>& xOldVector, const std::vector<double>& xNewVector, NormaInterface* const& vecNorm) const;
	double getEpsCountingNorms(const double matrixNorm, const double vectorNorm, const std::vector<double>& xOldVector, const std::vector<double>& xNewVector, NormaInterface* const& vecNorm) const;

	double getMaxFromUpTriangleMatrix(const Matrix& matrix, int& k, int& m);
	double getPhiValue(const Matrix& matrix, const int k, const int m) const;
	void initJacobRotationMatrix(Matrix& matrix, const int k, const int m, const double phi) const;
};
