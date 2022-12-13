#include<iostream>
#include "Colors.h"
#include "Matrix.h"
#include "Methods.h"
#include "MNKApprox.h"

int main(int argc, char** argv) {
	std::vector<std::pair<double, double>> gridFunc;
	gridFunc.push_back(std::make_pair(-2.0, 3.0));
	gridFunc.push_back(std::make_pair(-1.0, 4.0));
	gridFunc.push_back(std::make_pair(0.0, 2.0));
	gridFunc.push_back(std::make_pair(1.0, 1.0));
	gridFunc.push_back(std::make_pair(2.0, 1.0));

	
	MNKApprox approxer(gridFunc);
	std::vector<double>abcCoeffs = approxer.getParabolicCoeffsForMNK();

	std::cout << green << "Hello world" << white << std::endl;
	return 0;
}