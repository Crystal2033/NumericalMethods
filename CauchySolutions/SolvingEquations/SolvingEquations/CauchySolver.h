#pragma once
#include <vector>
#include <cmath>
#include <iostream>
class CauchySolver {
public:
	CauchySolver(const double a, const double b, const double h, const double y0);
	virtual std::vector<std::pair<double, double>> solve() = 0;
	virtual ~CauchySolver() = default;
protected:
	double y0;
	double a;
	double b;
	double h;
	std::vector<std::pair<double, double>> gridFunc;
	double getResOfDiffEquation(const double x, const double y) const;
};

class Euler : public CauchySolver {
public:
	Euler(const double a, const double b, const double h, const double y0);
	std::vector<std::pair<double, double>> solve() override;
	~Euler() = default;
};

class EulerCauchy : public CauchySolver {
public:
	EulerCauchy(const double a, const double b, const double h, const double y0);
	std::vector<std::pair<double, double>> solve() override;
	~EulerCauchy() = default;
};

class RungeKutta : public CauchySolver {
public:
	RungeKutta(const double a, const double b, const double h, const double y0);
	std::vector<std::pair<double, double>> solve() override;
	~RungeKutta() = default;
};

class ExactSolution : public CauchySolver {
public:
	ExactSolution(const double a, const double b, const double h, const double y0);
	std::vector<std::pair<double, double>> solve() override;
	~ExactSolution() = default;
private:
	double getExactValue(const double x) const;
};