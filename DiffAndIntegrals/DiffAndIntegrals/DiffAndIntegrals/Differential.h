#pragma once
#include <vector>
#include "Colors.h"
class Differential {
public:
	Differential(const std::vector<std::pair<double, double>>& gridFunction);
	double getFirstLeftDiff(const double x);
	double getFirstMidDiff(const double x);
	double getFirstRightDiff(const double x);
	double getSecondDiff(const double x);
	~Differential() = default;
private:
	std::vector<std::pair<double, double>> gridFunction;
};