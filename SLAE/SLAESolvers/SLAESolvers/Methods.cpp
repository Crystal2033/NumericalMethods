#include "Methods.h"
#include "Norm.h"
#define M_PI_4 0.785398163397448309616

std::vector<double> Methods::gaussSolveSLAE(const Matrix& extendedMatrix)
{
	std::vector<double> xVector;
	Matrix temp = fullEchelonForm(extendedMatrix);
	for (int i = 0; i < extendedMatrix.rowsValue; i++) {
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
	for (int i = 0; i < extendedMatrix.rowsValue; i++) {
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


std::vector<double> Methods::solveSimpleIterationsSLAE(const Matrix& extendedMatrix)
{
	Matrix temp(extendedMatrix);
	const double epsilone = 1e-10;

	makeSimpleMatrixTransform(temp);
	Matrix alpha;
	Matrix beta;
	initAlphaAndBetaMatrixesInSimpleIters(alpha, beta, temp);
	NormaInterface* vectorNorm = nullptr;
	NormaInterface* matrixNorm = nullptr;

	setVectorAndMatrixNorm(vectorNorm, matrixNorm, alpha);
	double matrixNormValue = matrixNorm->countNorm(alpha);
	double vectorNormValue = vectorNorm->countNorm(beta);


	std::vector<double> xVector;
	xVector.resize(extendedMatrix.rowsValue);
	for (int i = 0; i < beta.rowsValue; i++) {
		xVector[i] = beta.matrix[i][0];
	}
	std::vector<double> xVectorPrev;
	do
	{
		xVectorPrev = xVector;
		for (int i = 0; i < alpha.rowsValue; i++) {
			xVector[i] = 0.0;
			for (int j = 0; j < alpha.columnsValue; j++) {
				xVector[i] += alpha.matrix[i][j] * xVectorPrev[j];
			}
			xVector[i] += beta.matrix[i][0];
		}

	} while (getEpsiloneSimpleIterations(matrixNormValue, vectorNormValue, xVectorPrev, xVector, vectorNorm) > epsilone);

	delete vectorNorm;
	delete matrixNorm;
	return xVector;
}



double Methods::getEpsiloneSimpleIterations(const double matrixNorm, const double vectorNorm, const std::vector<double>& xOldVector, const std::vector<double>& xNewVector, NormaInterface* const& vecNorm)
{
	if (matrixNorm < 1.0) {
		return getEpsCountingNorms(matrixNorm, vectorNorm, xOldVector, xNewVector, vecNorm);
	}
	return getEpsDeltaX(xOldVector, xNewVector, vecNorm);
}

double Methods::getEpsDeltaX(const std::vector<double>& xOldVector, const std::vector<double>& xNewVector, NormaInterface* const& vecNorm) const
{
	Matrix xOld(xOldVector);
	Matrix xNew(xNewVector);
	Matrix deltaX = xNew - xOld;
	return vecNorm->countNorm(deltaX);

}

double Methods::getEpsCountingNorms(const double matrixNorm, const double vectorNorm, const std::vector<double>& xOldVector, const std::vector<double>& xNewVector, NormaInterface* const& vecNorm) const
{
	return matrixNorm / (1 - matrixNorm) * getEpsDeltaX(xOldVector, xNewVector, vecNorm);
}



void Methods::makeSimpleMatrixTransform(Matrix& matrix) const
{
	for (int i = 0; i < matrix.rowsValue; i++) {
		matrix.divideRowOnValue(i, matrix.matrix[i][i]);
		matrix.matrix[i][i] = 0.0;
	}
	for (int i = 0; i < matrix.rowsValue; i++) {
		for (int j = 0; j < matrix.columnsValue - 1; j++) {
			if (i != j) {
				matrix.matrix[i][j] = -matrix.matrix[i][j];
			}
		}
	}
}

void Methods::initAlphaAndBetaMatrixesInSimpleIters(Matrix& alpha, Matrix& beta, const Matrix& full)
{
	for (int i = 0; i < full.rowsValue; i++) {
		alpha.addCol(full, i);
	}

	beta.addCol(full, full.columnsValue - 1);
}

void Methods::setVectorAndMatrixNorm(NormaInterface*& vecNorm, NormaInterface*& matrixNorm, const Matrix& alpha)
{
	std::vector<double> resultsOfNorms;
	NormaInterface* normaMaxInRows = new NormaMatrixMaxSumInRows;
	NormaInterface* normaMaxInCols = new NormaMatrixMaxSumInCols;
	NormaInterface* normaEuclid = new NormaEuclidMatrix;

	resultsOfNorms.push_back(normaMaxInRows->countNorm(alpha));

	resultsOfNorms.push_back(normaMaxInCols->countNorm(alpha));

	resultsOfNorms.push_back(normaEuclid->countNorm(alpha));

	int minIndex = 0;
	for (int i = 0; i < 2; i++) {
		if (resultsOfNorms[minIndex] > resultsOfNorms[i + 1]) {
			minIndex = i + 1;
		}
	}

	//std::cout << resultsOfNorms[minIndex] << " " << minIndex << std::endl;

	switch (minIndex)
	{
	case 0: {
		delete normaMaxInCols;
		delete normaEuclid;
		matrixNorm = normaMaxInRows;
		vecNorm = new NormaVectorMaxVal;
		return;
	}
	case 1: {
		delete normaMaxInRows;
		delete normaEuclid;
		matrixNorm = normaMaxInCols;
		vecNorm = new NormaVectorSumVals;
		return;
	}
	case 2: {
		delete normaMaxInCols;
		delete normaMaxInRows;
		matrixNorm = normaEuclid;
		vecNorm = new NormaEuclidVector;
		return;
	}
	}
}


std::pair<std::vector<double>, Matrix> Methods::yacobiGetOwnNumbersAndVectors(const Matrix& matrix){
	const double epsilone = 1e-10;
	Matrix matrixCopy(matrix);
	double maxValue = 0.0;
	Matrix transposedYacodRotationMatrix(matrix.rowsValue, matrix.rowsValue);
	Matrix matrixAfterTransform(matrix);
	std::vector<Matrix> allJacobRotateMatrixes;

	while (true) {
		int kPos, mPos;
		Matrix yacobRotationMatrix = Matrix::getIdentity(matrix.rowsValue);
		maxValue = getMaxFromUpTriangleMatrix(matrixAfterTransform, kPos, mPos);
		if (fabs(maxValue) > epsilone) {
			double phi = getPhiValue(matrixAfterTransform, kPos, mPos);
			initJacobRotationMatrix(yacobRotationMatrix, kPos, mPos, phi);
			allJacobRotateMatrixes.push_back(yacobRotationMatrix);

			transposedYacodRotationMatrix = Matrix::transpose(yacobRotationMatrix);

			matrixAfterTransform = transposedYacodRotationMatrix * matrixAfterTransform * yacobRotationMatrix;
		}
		else {
			break;
		}
	}

	std::vector<double> lambdas;
	for (int i = 0; i < matrix.rowsValue; i++) {
		lambdas.push_back(matrixAfterTransform.matrix[i][i]);
	}

	Matrix ownVectors(matrix.rowsValue, matrix.rowsValue);
	ownVectors = allJacobRotateMatrixes[0];
	for (int i = 1; i < allJacobRotateMatrixes.size(); i++) {
		ownVectors *= allJacobRotateMatrixes[i];
	}

	for (int i = 0; i < ownVectors.rowsValue; i++) {
		ownVectors.divideColOnValue(i, ownVectors.matrix[i][i]);
	}

	return std::make_pair(lambdas, ownVectors);
}

double Methods::getMaxFromUpTriangleMatrix(const Matrix& matrix, int& k, int& m)
{
	double maxValue = 0.0;
	for (int i = 0; i < matrix.rowsValue - 1; i++) {
		for (int j = i + 1; j < matrix.columnsValue; j++) {
			if (fabs(maxValue) < fabs(matrix.matrix[i][j])) {
				maxValue = matrix.matrix[i][j];
				k = i; m = j;
			}	
		}
	}
	return maxValue;
}

double Methods::getPhiValue(const Matrix& matrix, const int k, const int m) const
{
	double denominator = matrix.matrix[k][k] - matrix.matrix[m][m];
	double phi = 0.0;
	if (fabs(denominator) < 1e-5) {
		if (matrix.matrix[k][m] < 0) {
			phi = -M_PI_4;
		}
		else {
			phi = M_PI_4;
		}
	}
	else {
		phi = 0.5 * atan((2.0 * matrix.matrix[k][m]) / denominator);
	}
	return phi;
}

void Methods::initJacobRotationMatrix(Matrix& matrix, const int k, const int m, const double phi) const
{
	matrix.matrix[k][k] = cos(phi);
	matrix.matrix[k][m] = -sin(phi);
	matrix.matrix[m][k] = sin(phi);
	matrix.matrix[m][m] = cos(phi);
}


