#include "CubicSpline.h"
#include "Methods.h"

CubicSpline::CubicSpline(const std::vector<std::pair<double, double>>& gridFunc)
{
	this->gridFunction = gridFunc;
	countSplinesCoefficients();
}

std::vector<std::vector<double>> CubicSpline::getCoefficientsVector() const
{
	return splineCoefficientsMatrix;
}

double CubicSpline::getSplineValue(const double x)
{

	unsigned currentRange = 0;
	if (x < gridFunction[0].first) {
		currentRange = 1;
	}
	else if (x > gridFunction[gridFunction.size() - 1].first) {
		currentRange = gridFunction.size() - 1;
	}
	else {
		for (unsigned i = 0; i < gridFunction.size() - 1; i++) {
			if (x >= gridFunction[i].first && x <= gridFunction[i + 1].first) {
				currentRange = i + 1;
				break;
			}
		}
	}
	
	
	double firstSum = secondDiffSplineValues[currentRange - 1] *
		pow((gridFunction[currentRange].first - x), 3) / (6 * stepsBetweenPoints[currentRange - 1]);
	//std::cout << "First sum = " << firstSum << std::endl;
	
	double secondSum = secondDiffSplineValues[currentRange] *
		pow((x - gridFunction[currentRange - 1].first), 3) / (6 * stepsBetweenPoints[currentRange - 1]);
	//std::cout << "Second sum = " << secondSum << std::endl;

	double thirdSum = (gridFunction[currentRange - 1].second/stepsBetweenPoints[currentRange - 1] - 
		secondDiffSplineValues[currentRange-1] * (stepsBetweenPoints[currentRange - 1] / 6.0)) * (gridFunction[currentRange].first - x);
	//std::cout << "Third sum = " << thirdSum << std::endl;

	double fourthSum = (gridFunction[currentRange].second / stepsBetweenPoints[currentRange - 1] -
		secondDiffSplineValues[currentRange] * (stepsBetweenPoints[currentRange - 1] / 6.0)) * (x - gridFunction[currentRange - 1].first);
	//std::cout << "Fourth sum = " << fourthSum << std::endl;

	double result = firstSum + secondSum + thirdSum + fourthSum;
	return result;
}

void CubicSpline::countSplinesCoefficients()
{
	countSteps();
	setSecondDiffSplineValues();
}

void CubicSpline::countSteps()
{
	for (unsigned i = 0; i < gridFunction.size() - 1; i++) {
		stepsBetweenPoints.push_back(gridFunction[i + 1].first - gridFunction[i].first);
	}
}

void CubicSpline::setSecondDiffSplineValues()
{

	if (gridFunction.size() < 2) {
		std::cout << red << "Something is going wrong: getSecondDiffSplineValues: gridFunction.size() < 2" << white << std::endl;
		exit(-1);
	}
	Matrix extendedMatrix(gridFunction.size() - 2, gridFunction.size() - 1);
	unsigned startFormulaPos = 1;

	for (unsigned i = 0; i < extendedMatrix.getRowsValue(); i++) {
		extendedMatrix.matrix[i][extendedMatrix.getColsValue() - 1] =
			(gridFunction[startFormulaPos + 1].second - gridFunction[startFormulaPos].second) / stepsBetweenPoints[startFormulaPos]
			- (gridFunction[startFormulaPos].second - gridFunction[startFormulaPos - 1].second) / stepsBetweenPoints[startFormulaPos-1]; //d
		extendedMatrix.matrix[i][i] = (stepsBetweenPoints[startFormulaPos-1] + stepsBetweenPoints[startFormulaPos]) / 3.0; //b
		if (i == 0) {
			extendedMatrix.matrix[i][i + 1] = stepsBetweenPoints[startFormulaPos] / 6.0; //c
		}
		else if (i == extendedMatrix.getRowsValue() - 1) {
			extendedMatrix.matrix[i][i - 1] = stepsBetweenPoints[startFormulaPos-1] / 6.0; //a
		}
		else {
			extendedMatrix.matrix[i][i - 1] = stepsBetweenPoints[startFormulaPos-1] / 6.0; //a
			extendedMatrix.matrix[i][i + 1] = stepsBetweenPoints[startFormulaPos] / 6.0; //c
		}
		startFormulaPos++;
	}
	Methods method;
	secondDiffSplineValues = method.solveSweepingSLAE(extendedMatrix);
	secondDiffSplineValues.push_back(0.0);
	secondDiffSplineValues.insert(secondDiffSplineValues.begin(), 0.0);
}
