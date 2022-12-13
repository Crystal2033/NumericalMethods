#include "Interpolation.h"

InterpolationInterface::InterpolationInterface(const std::vector<std::pair<double, double>>& gridFunc){
	this->gridFunction = gridFunc;
}

std::vector<std::pair<double, double>> LagrangeInterpolation::interpolate()
{
	return std::vector<std::pair<double, double>>();
}

double LagrangeInterpolation::interpolate(const double x) const
{
	double result = 0.0;
	for (int i = 0; i < gridFunction.size(); i++) {
		result += (gridFunction[i].second * countMultiplierFraction(x, i));
	}
	return result;
}

LagrangeInterpolation::LagrangeInterpolation(const std::vector<std::pair<double, double>>& gridFunc) : InterpolationInterface(gridFunc)
{}

double LagrangeInterpolation::countMultiplierFraction(const double x, const int currI) const
{
	double multRes = 1.0;
	for (int i = 0; i < gridFunction.size(); i++) {
		if (i == currI) { 
			continue;
		}
		else{
			multRes *= ((x - gridFunction[i].first) /
				(gridFunction[currI].first - gridFunction[i].first));
		}
	}
	return multRes;
}

std::vector<std::pair<double, double>> NewtonInterpolation::interpolate()
{
	return std::vector<std::pair<double, double>>();
}

double NewtonInterpolation::interpolate(const double x) const
{
	double result = 0.0;
	for (int i = 0; i < cuttenPairs.size(); i++) {
		double multiplyValue = cuttenPairs[i][0];
		for (int j = 0; j < i; j++) {
			multiplyValue *= (x - gridFunction[j].first);
		}
		result += multiplyValue;
	}
	return result;
}

NewtonInterpolation::NewtonInterpolation(const std::vector<std::pair<double, double>>& gridFunc) : InterpolationInterface(gridFunc)
{
	cuttenPairs.push_back(std::vector<double>());
	for (int i = 0; i < gridFunction.size(); i++) {
		cuttenPairs[0].push_back(gridFunction[i].second);
	}

	for (int i = 1; i < gridFunction.size(); i++) {
		cuttenPairs.push_back(std::vector<double>());
		for (int j = 0; j < gridFunction.size() - i; j++) {
			double up = (cuttenPairs[i - 1][j + 1] - cuttenPairs[i - 1][j]);
			double down = (gridFunction[j + i].first - gridFunction[j].first);
			cuttenPairs[i].push_back(up / down);
		}
	}
}
