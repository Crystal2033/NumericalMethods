#include<iostream>
#include "Colors.h"
#include "Interpolation.h"
int main(int argc, char** argv) {
	std::vector<std::pair<double, double>> gridFunc;
	gridFunc.push_back(std::make_pair(0.0, -5.0));
	gridFunc.push_back(std::make_pair(1.0, -6.0));
	gridFunc.push_back(std::make_pair(2.0, 3.0));
	gridFunc.push_back(std::make_pair(3.0, 28.0));
	InterpolationInterface* interpolator = new NewtonInterpolation(gridFunc);
	std::cout << blue << interpolator->interpolate(0.5) << white << std::endl;
	double step = 0.0;
	for (int i = 0; i < (gridFunc.size() - 1) * 10 + 1; i++) {
		std::cout << blue << interpolator->interpolate(step) << white << std::endl;
		step += 0.1;
	}

	InterpolationInterface* interpolator2 = new LagrangeInterpolation(gridFunc);
	std::cout << blue << interpolator2->interpolate(0.5) << white << std::endl;
	double step2 = 0.0;
	for (int i = 0; i < (gridFunc.size() - 1) * 10 + 1; i++) {
		std::cout << green << interpolator2->interpolate(step2) << white << std::endl;
		step2 += 0.1;
	}
	
	return 0;
}