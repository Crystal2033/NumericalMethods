#pragma once
#include<vector>
#include "Matrix.h"
class MNKApprox {
private:
	std::vector<std::pair<double, double>> gridFunction;
public:
	MNKApprox(const std::vector<std::pair<double, double>>& gridFunction);
	std::vector<double> getParabolicCoeffsForMNK();
	std::vector<double> getLinearCoeffsForMNK();
};