#include "CauchySolver.h"

Euler::Euler(const double a, const double b, const double h, const double y0)
    :CauchySolver(a, b, h, y0)
{}

std::vector<std::pair<double, double>> Euler::solve()
{
    for (unsigned i = 1; i < gridFunc.size(); i++) {
        gridFunc[i].second = gridFunc[i - 1].second +
            h * (getResOfDiffEquation(gridFunc[i - 1].first, gridFunc[i - 1].second));
    }
    return gridFunc;
}

CauchySolver::CauchySolver(const double a, const double b, const double h, const double y0)
{
    this->y0 = y0;
    this->a = a;
    this->b = b;
    this->h = h;

    const unsigned valueOfIterations = (b - a) / h;
    double startXValue;
    for (unsigned i = 0; i < valueOfIterations + 1; i++) {
        if (i == 0) {
            gridFunc.push_back(std::make_pair(a, y0));
        }
        else {
            gridFunc.push_back(std::make_pair(a + i * h, 0.0));
        }
       
    }
}

double CauchySolver::getResOfDiffEquation(const double x, const double y) const
{
    return (std::pow(y, 2) + y*x)/std::pow(x, 2);
}

EulerCauchy::EulerCauchy(const double a, const double b, const double h, const double y0)
    :CauchySolver(a, b, h, y0)
{}

std::vector<std::pair<double, double>> EulerCauchy::solve()
{
    double predictor;
    double corrector;
    for (unsigned i = 1; i < gridFunc.size(); i++) {
        predictor = gridFunc[i - 1].second +
            h * (getResOfDiffEquation(gridFunc[i - 1].first, gridFunc[i - 1].second));
        corrector = gridFunc[i - 1].second + (h / 2.0) * 
            (getResOfDiffEquation(gridFunc[i - 1].first, gridFunc[i - 1].second)
            +getResOfDiffEquation(gridFunc[i].first, predictor));
        gridFunc[i].second = corrector;
    }

    return gridFunc;
}

RungeKutta::RungeKutta(const double a, const double b, const double h, const double y0)
    :CauchySolver(a, b, h, y0)
{}

std::vector<std::pair<double, double>> RungeKutta::solve()
{
    double k1;
    double k2;
    double k3;
    double k4;

    for (unsigned i = 1; i < gridFunc.size(); i++) {
        k1 = h * getResOfDiffEquation(gridFunc[i - 1].first,
                                      gridFunc[i - 1].second);

        k2 = h * getResOfDiffEquation(gridFunc[i - 1].first + h / 2.0,
                                      gridFunc[i - 1].second + 0.5 * k1);

        k3 = h * getResOfDiffEquation(gridFunc[i - 1].first + h / 2.0,
                                      gridFunc[i - 1].second + 0.5 * k2);

        k4 = h * getResOfDiffEquation(gridFunc[i - 1].first + h,
                                      gridFunc[i - 1].second + k3);

        gridFunc[i].second = gridFunc[i - 1].second +
            1.0 / 6.0 * (k1 + 2 * k2 + 2 * k3 + k4);
    }

    return gridFunc;
}

ExactSolution::ExactSolution(const double a, const double b, const double h, const double y0)
    :CauchySolver(a, b, h, y0)
{
    for (unsigned i = 0; i < gridFunc.size(); i++) {
        gridFunc[i].second = getExactValue(gridFunc[i].first);
    }
}

std::vector<std::pair<double, double>> ExactSolution::solve()
{
    return gridFunc;
}

double ExactSolution::getExactValue(const double x) const
{
    return - (x / (std::log(x) - 1));
}
