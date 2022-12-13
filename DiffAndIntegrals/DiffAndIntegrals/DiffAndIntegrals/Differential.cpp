#include "Differential.h"


Differential::Differential(const std::vector<std::pair<double, double>>& gridFunction)
{
    this->gridFunction = gridFunction;
}

double Differential::getFirstLeftDiff(const double x)
{
    for (unsigned i = 0; i < gridFunction.size(); i++) {
        if (abs(x - gridFunction[i].first) < 1e-7) {
            if (i > 0) {
                return (gridFunction[i].second - gridFunction[i-1].second)/
                    (gridFunction[i].first - gridFunction[i-1].first);
            }
            else {
                std::cout << red << "Something goes wrong." << white << std::endl;
                return 0.0;
            }
        }
    }
}

double Differential::getFirstMidDiff(const double x)
{
    for (unsigned i = 0; i < gridFunction.size(); i++) {
        if (abs(x - gridFunction[i].first) < 1e-7) {
            if (i > 0 && i < gridFunction.size() - 1) {
                return (gridFunction[i+1].second - gridFunction[i - 1].second) /
                    (gridFunction[i + 1].first - gridFunction[i - 1].first);
            }
            else {
                std::cout << red << "Something goes wrong." << white << std::endl;
                return 0.0;
            }
        }
    }
}

double Differential::getFirstRightDiff(const double x)
{
    for (unsigned i = 0; i < gridFunction.size(); i++) {
        if (abs(x - gridFunction[i].first) < 1e-7) {
            if (i < gridFunction.size() - 1) {
                return (gridFunction[i + 1].second - gridFunction[i].second) /
                    (gridFunction[i+1].first - gridFunction[i].first);
            }
            else {
                std::cout << red << "Something goes wrong." << white << std::endl;
                return 0.0;
            }
        }
    }
}

double Differential::getSecondDiff(const double x)
{
    for (unsigned i = 0; i < gridFunction.size(); i++) {
        if (abs(x - gridFunction[i].first) < 1e-7) {
            if (i > 0 && i < gridFunction.size() - 1) {
                return (gridFunction[i + 1].second - 2*gridFunction[i].second + gridFunction[i - 1].second) /
                    (pow(gridFunction[i + 1].first - gridFunction[i].first,2));
            }
            else {
                std::cout << red << "Something goes wrong." << white << std::endl;
                return 0.0;
            }
        }
    }
}
