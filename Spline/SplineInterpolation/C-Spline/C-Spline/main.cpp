#include<iostream>
#include "Colors.h"
#include "CubicSpline.h"

int main(int argc, char** argv) {
	std::vector<std::pair<double, double>> gridFunction;
	//gridFunction.push_back(std::make_pair(0.0, 2.0));
	//gridFunction.push_back(std::make_pair(1.0, 4.0));
	//gridFunction.push_back(std::make_pair(3.0, 6.0));
	//gridFunction.push_back(std::make_pair(6.0, 7.0));
	//gridFunction.push_back(std::make_pair(10.0, 3.0));
	gridFunction.push_back(std::make_pair(1.0, 1.0));
	gridFunction.push_back(std::make_pair(2.0, 3.0));
	gridFunction.push_back(std::make_pair(3.0, 6.0));
	gridFunction.push_back(std::make_pair(4.0, 9.0));
	gridFunction.push_back(std::make_pair(5.0, 21.0));
	CubicSpline spline(gridFunction);
	double step = 0.1;
	for (int i = 0; i < (gridFunction.size() - 1) * (1.0 / step) + 1; i++) {
		std::cout << spline.getSplineValue(gridFunction[0].first + i * step) << std::endl;
		//std::cout << gridFunction[0].first + i * step << std::endl;
	}
	//spline.getSplineValue(2.0);

	return 0;
}