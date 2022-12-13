#pragma once
#include <vector>
#include <iostream>
#include <math.h>
class Plot;

class CubicSpline {
public:
	CubicSpline(const std::vector<std::pair<double, double>>& gridFunc);
	std::vector<std::vector<double>> getCoefficientsVector() const;
    double getSplineValue(const double x) const;
    void check() const;
private:
	std::vector<std::pair<double, double>> gridFunction;
	std::vector<std::vector<double>> splineCoefficientsMatrix;
	std::vector<double> secondDiffSplineValues;
	std::vector<double> stepsBetweenPoints;
	void countSplinesCoefficients();
	void countSteps();
	void setSecondDiffSplineValues();



};
