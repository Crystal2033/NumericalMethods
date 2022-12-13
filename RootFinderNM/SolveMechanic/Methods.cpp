#include "Exceptions.h"
#include "Methods.h"
#include <QDebug>

#pragma region FindRoot base class
FindRootMethod::FindRootMethod(const std::vector<double>& coefficients, const double epsilone)
{
    this->epsilone = epsilone;
    this->coefficients = coefficients;
}
double FindRootMethod::getFuncRes(const double x, const std::vector<double> funcCoeffs) const
{
    double result = 0.0;
    for (int i = 0; i < funcCoeffs.size(); i++) {
        result += funcCoeffs[i] * pow(x, i);
    }
    return result;
}

bool FindRootMethod::isCorrectRangeCondition(const std::pair<double, double>& range) const
{
    return (getFuncRes(range.first, coefficients) * getFuncRes(range.second, coefficients)) < 0.0;
}
#pragma endregion

#pragma region BinarySearch method
double BinarySearchFindRootMethod::findRoot(const std::pair<double, double>& range)
{

    if (!isCorrectRangeCondition(range)) {
        throw BadRangeException("Your range is not compatible with this method. f(a)*f(b) should be < 0.");
    }
    double leftEdge = range.first;
    double rightEdge = range.second;
    while (abs(rightEdge - leftEdge) > 2 * epsilone) {
        std::pair<double, double> newRange = getNewRangeByBinarySearch(leftEdge, rightEdge);
        leftEdge = newRange.first;
        rightEdge = newRange.second;
    }

    return (leftEdge + rightEdge) / 2.0;
}

BinarySearchFindRootMethod::BinarySearchFindRootMethod(const std::vector<double>& coefficients, const double epsilone) : FindRootMethod(coefficients, epsilone)
{
}

std::pair<double, double> BinarySearchFindRootMethod::getNewRangeByBinarySearch(const double leftEdge, const double rightEdge) const
{
    double middleValue = (leftEdge + rightEdge) / 2.0;
    if (getFuncRes(leftEdge, coefficients) * getFuncRes(middleValue, coefficients) < 0) {
        return std::pair<double, double>(leftEdge, middleValue);
    }
    else {
        return std::pair<double, double>(middleValue, rightEdge);
    }
    
}

bool BinarySearchFindRootMethod::isCorrectRangeCondition(const std::pair<double, double>& range) const{
    return (getFuncRes(range.first, coefficients) * getFuncRes(range.second, coefficients)) < 0.0;
}
#pragma endregion


#pragma region Newton method

double NewtonRootMethod::findRoot(const std::pair<double, double>& range)
{
    firstDiffCoeffs = countDiffAndInsertIntoDiffCoeffVector(coefficients);
    secondDiffCoeffs = countDiffAndInsertIntoDiffCoeffVector(firstDiffCoeffs);
    double currXValue;
    
    if (!isCorrectRangeConditions(range, currXValue)) {
        throw BadRangeException("Your range is not compatible with this method."
            " f(a) * f(b) should be < 0 and f(k)*f''(k) should be > 0.");
    }

    double epsiloneK;
    do{
        epsiloneK = getFuncRes(currXValue, coefficients) / getFuncRes(currXValue, firstDiffCoeffs);
        currXValue = currXValue - epsiloneK;
    } while (abs(epsiloneK) > epsilone);

    return currXValue;
}

NewtonRootMethod::NewtonRootMethod(const std::vector<double>& coefficients, const double epsilone) : FindRootMethod(coefficients, epsilone)
{
}

std::vector<double> NewtonRootMethod::countDiffAndInsertIntoDiffCoeffVector(const std::vector<double>& coeffs)
{
    std::vector<double> diffCoeffs;
    for (int i = 1; i < coeffs.size(); i++) {
        diffCoeffs.push_back(i * coeffs[i]);
    }
    return diffCoeffs;
}
bool NewtonRootMethod::isCorrectRangeConditions(const std::pair<double, double>& range, double& startXValue) const
{
    if (!isCorrectRangeCondition(range)) {
        return false;
    }
    if (getFuncRes(range.second, coefficients) * getFuncRes(range.second, secondDiffCoeffs) > 0.0) {
        startXValue = range.second;
        return true;
    }
    if (getFuncRes(range.first, coefficients) * getFuncRes(range.first, secondDiffCoeffs) > 0.0) {
        startXValue = range.first;
        return true;
    }
    double middleValue = (range.first + range.second) / 2.0;
    if (getFuncRes(middleValue, coefficients) * getFuncRes(middleValue, secondDiffCoeffs) > 0.0) {
        startXValue = middleValue;
        return true;
    }
    return false;
}
#pragma endregion


#pragma region Newton method
double IterationsMethod::findRoot(const std::pair<double, double>& range)
{
    if (!isCorrectRangeCondition(range)) {
        throw BadRangeException("Your range is not compatible with this method. f(a)*f(b) should be < 0.");
    }
    double q = std::max(getExplicitDiffResult(range.first), getExplicitDiffResult(range.second));
    double currX = range.second;
    double nextX = range.second;
    do
    {
        currX = nextX;
        double diffResult = getExplicitDiffResult(currX);
        if (diffResult > 1.0) {
            throw BadRangeException("Your range is not compatible with this method. Should be phi'(x) <= q < 1.");
        }
        nextX = getFuncRes(currX, transformedCoeffs);
        
    } while (1/(1-q)*abs(nextX - currX) > epsilone);
    
 

    return nextX;
}
IterationsMethod::IterationsMethod(const std::vector<double>& coefficients, const double epsilone) : FindRootMethod(coefficients, epsilone)
{
    for (int i = 0; i < coefficients.size() - 1; i++) {
        this->transformedCoeffs.push_back(- coefficients[i] * (1 / coefficients[coefficients.size() - 1]));
    }
}

double IterationsMethod::getFuncRes(const double x, const std::vector<double> funcCoeffs) const
{
    return cbrt(FindRootMethod::getFuncRes(x, funcCoeffs));
}

double IterationsMethod::getExplicitDiffResult(const double x)
{
    //return -5.0/(18.0*cbrt(pow((-10.0/12.0)*x-1320.0, 2)));
    return -88.0/(cbrt(pow((132.0*(23.0-2*x)), 2)));
}



#pragma endregion
