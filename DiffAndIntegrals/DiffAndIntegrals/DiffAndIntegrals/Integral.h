#pragma once
#include <math.h>
class IntegralBase {
public:
	IntegralBase() = default;
	double RungeRombergConcreete(const double I1, const double I2, const double h1, const double h2, const int p);
	virtual ~IntegralBase() = default;
	virtual double integrate(const double a, const double b, const double h) const = 0;
protected:
	double getFuncValue(const double x) const;
};

class IntegralRectangle : public IntegralBase {
public:
	IntegralRectangle() = default;
	~IntegralRectangle() = default;
	double integrate(const double a, const double b, const double h) const override;
};

class IntegralTrapezoid : public IntegralBase {
public:
	IntegralTrapezoid() = default;
	~IntegralTrapezoid() = default;
	double integrate(const double a, const double b, const double h) const override;
};

class IntegralSimpson : public IntegralBase {
public:
	IntegralSimpson() = default;
	~IntegralSimpson() = default;
	double integrate(const double a, const double b, const double h) const override;
};