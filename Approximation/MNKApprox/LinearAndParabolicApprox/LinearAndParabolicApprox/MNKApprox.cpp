#include "MNKApprox.h"
#include "Methods.h"

MNKApprox::MNKApprox(const std::vector<std::pair<double, double>>& gridFunction)
{
	this->gridFunction = gridFunction;
}

std::vector<double> MNKApprox::getParabolicCoeffsForMNK()
{
	Matrix coeffsMatrix(3, 4);
	int globalDegree = 4;
	int currDegree; 
	for (int i = 0; i < coeffsMatrix.getRowsValue(); i++) {
		currDegree = globalDegree;
		for (int j = 0; j < coeffsMatrix.getRowsValue(); j++) {
			for (int k = 0; k < gridFunction.size(); k++) {
				coeffsMatrix.matrix[i][j] += pow(gridFunction[k].first, currDegree);
			}
			currDegree--;
		}
		globalDegree--;
	}
	globalDegree = 2;
	for (int i = 0; i < coeffsMatrix.getRowsValue(); i++) {
		for (int k = 0; k < gridFunction.size(); k++) {
			coeffsMatrix.matrix[i][coeffsMatrix.getColsValue() - 1] += (pow(gridFunction[k].first, globalDegree) * gridFunction[k].second);
		}
		globalDegree--;
	}

	Methods method;
	return method.gaussSolveSLAE(coeffsMatrix);
}

std::vector<double> MNKApprox::getLinearCoeffsForMNK()
{

	Matrix coeffsMatrix(2, 3);
	int globalDegree = 2;
	int currDegree;
	for (int i = 0; i < coeffsMatrix.getRowsValue(); i++) {
		currDegree = globalDegree;
		for (int j = 0; j < coeffsMatrix.getRowsValue(); j++) {
			for (int k = 0; k < gridFunction.size(); k++) {
				coeffsMatrix.matrix[i][j] += pow(gridFunction[k].first, currDegree);
			}
			currDegree--;
		}
		globalDegree--;
	}
	globalDegree = 1;
	for (int i = 0; i < coeffsMatrix.getRowsValue(); i++) {
		for (int k = 0; k < gridFunction.size(); k++) {
			coeffsMatrix.matrix[i][coeffsMatrix.getColsValue() - 1] += (pow(gridFunction[k].first, globalDegree) * gridFunction[k].second);
		}
		globalDegree--;
	}

	Methods method;
	return method.gaussSolveSLAE(coeffsMatrix);
}
