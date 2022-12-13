#pragma once
#include<vector>
typedef enum {LINEAR, PARABOLIC} APPROX_TYPE;
class MNKApprox {
private:
	std::vector<std::pair<double, double>> gridFunction;
public:
	MNKApprox(const std::vector<std::pair<double, double>>& gridFunction);
	std::vector<double> getParabolicCoeffsForMNK();
	std::vector<double> getLinearCoeffsForMNK();
    std::vector<double> getCoeffForMNK(const APPROX_TYPE type);
};
