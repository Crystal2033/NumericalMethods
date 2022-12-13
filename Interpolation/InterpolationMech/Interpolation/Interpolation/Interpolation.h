#pragma once
#include<vector>
class InterpolationInterface {
public:
	InterpolationInterface(const std::vector<std::pair<double, double>>& gridFunc);
	virtual std::vector<std::pair<double, double>> interpolate() = 0;
	virtual double interpolate(const double x) const = 0;
	virtual ~InterpolationInterface() = default;

protected:
	std::vector<std::pair<double, double>> gridFunction;


};

class LagrangeInterpolation final : public InterpolationInterface {
public:
	std::vector<std::pair<double, double>> interpolate() override;
	double interpolate(const double x) const override;
	LagrangeInterpolation(const std::vector<std::pair<double, double>>& gridFunc);
	~LagrangeInterpolation() = default;

private:
	double countMultiplierFraction(const double x, const int currI) const;

};

class NewtonInterpolation final : public InterpolationInterface {
public:
	std::vector<std::pair<double, double>> interpolate() override;
	double interpolate(const double x) const override;
	NewtonInterpolation(const std::vector<std::pair<double, double>>& gridFunc);
	~NewtonInterpolation() = default;
private:
	std::vector<std::vector<double>> cuttenPairs;

};