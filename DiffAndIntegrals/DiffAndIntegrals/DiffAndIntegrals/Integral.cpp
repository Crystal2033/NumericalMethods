#include "Integral.h"

double IntegralBase::RungeRombergConcreete(const double I1, const double I2, const double h1, const double h2, const int p)
{
    return (I1 + (I1 - I2)/(pow((h2 / h1), p) - 1));
}

double IntegralBase::getFuncValue(const double x) const
{
    return (x / (pow(x, 3) + 8));
}

double IntegralRectangle::integrate(const double a, const double b, const double h) const
{
    double result = 0.0;
    unsigned iterations = (b - a) / h;
    for (int i = 0; i < iterations; i++) {
        result += (getFuncValue(a + i * h) * h);
    }
    return result;
}

double IntegralTrapezoid::integrate(const double a, const double b, const double h) const
{
    double result = getFuncValue(a) + getFuncValue(b);
    unsigned iterations = (b - a) / h;
    for (int i = 1; i < iterations; i++) {
        result += (getFuncValue(a + i * h) *2);
    }
    return (h / 2) * result;
}

double IntegralSimpson::integrate(const double a, const double b, const double h) const
{
    double result = getFuncValue(a) + getFuncValue(b);
    unsigned iterations = (b - a) / h;
    for (int i = 1; i < iterations; i += 2) {
        result += (getFuncValue(a + i * h) * 4);
    }
    for (int i = 2; i < iterations-1; i += 2) {
        result += (getFuncValue(a + i * h) * 2);
    }
    return (h / 3) * result;
}
