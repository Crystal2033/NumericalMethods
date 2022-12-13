#include "MNKApprox.h"
#include "MatrixAndSLAE/Methods.h"
#include "MatrixAndSLAE/Matrix.h"
#include <math.h>

MNKApprox::MNKApprox(const std::vector<std::pair<double, double>>& gridFunction)
{
	this->gridFunction = gridFunction;
}

std::vector<double> MNKApprox::getParabolicCoeffsForMNK()
{
    return getCoeffForMNK(PARABOLIC);
}

std::vector<double> MNKApprox::getLinearCoeffsForMNK()
{
    return getCoeffForMNK(LINEAR);
}

std::vector<double> MNKApprox::getCoeffForMNK(const APPROX_TYPE type)
{
    int rowValue = 0;
    int colsValue = 0;
    int globalDegreeForMainMatr = 0;
    int globalDegreeForExtMatr = 0;
    if(type == LINEAR){
        rowValue = 2;
        colsValue = 3;
        globalDegreeForMainMatr = 2;
        globalDegreeForExtMatr = 1;
    }
    else if(type == PARABOLIC){
        rowValue = 3;
        colsValue = 4;
        globalDegreeForMainMatr = 4;
        globalDegreeForExtMatr = 2;
    }
    Matrix coeffsMatrix(rowValue, colsValue);
    int globalDegree = globalDegreeForMainMatr;
    int currDegree;
    for (int i = 0; i < coeffsMatrix.getRowsValue(); i++) {
        currDegree = globalDegree;
        for (int j = 0; j < coeffsMatrix.getRowsValue(); j++) {
            for (unsigned k = 0; k < gridFunction.size(); k++) {
                coeffsMatrix.matrix[i][j] += pow(gridFunction[k].first, currDegree);
            }
            currDegree--;
        }
        globalDegree--;
    }
    globalDegree = globalDegreeForExtMatr;
    for (int i = 0; i < coeffsMatrix.getRowsValue(); i++) {
        for (unsigned k = 0; k < gridFunction.size(); k++) {
            coeffsMatrix.matrix[i][coeffsMatrix.getColsValue() - 1] += (pow(gridFunction[k].first, globalDegree) * gridFunction[k].second);
        }
        globalDegree--;
    }

    Methods method;
    return method.gaussSolveSLAE(coeffsMatrix);
}

