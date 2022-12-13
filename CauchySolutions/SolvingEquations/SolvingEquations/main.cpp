#include<iostream>
#include "Colors.h"
#include "CauchySolver.h"
#include "Norm.h"

void printSolution(const std::vector < std::pair<double, double> >& solutionVector);
double countNorm(const std::vector < std::pair<double, double> >& solutionVector,
	const std::vector < std::pair<double, double> >& exactSolution);
void printNorm(const double normRes);

int main(int argc, char** argv) {
	const double a = 1.0;
	const double b = 2.0;
	const double h = 0.1;
	const double y0 = 1.0;

	CauchySolver* exactSolution = new ExactSolution(a, b, h, y0);
	std::cout << red << "Exact solution is: " << white << std::endl;
	std::cout << red << "------------------------------------" << white << std::endl;
	auto exactVector = exactSolution->solve();
	printSolution(exactVector);
	std::cout << red << "------------------------------------" << white << std::endl;


	CauchySolver* solver = new Euler(a, b, h, y0);
	std::cout << cyan << "Euler solution is: " << white << std::endl;
	std::cout << cyan << "------------------------------------" << white << std::endl;
	auto eulerResVector = solver->solve();
	printSolution(eulerResVector);
	printNorm(countNorm(eulerResVector, exactVector));
	std::cout << cyan << "------------------------------------" << white << std::endl;
	delete solver;

	solver = new EulerCauchy(a, b, h, y0);
	std::cout << cyan << "Euler-Cauchy solution is: " << white << std::endl;
	std::cout << cyan << "------------------------------------" << white << std::endl;
	auto eulerCauchyResVector = solver->solve();
	printSolution(eulerCauchyResVector);
	printNorm(countNorm(eulerCauchyResVector, exactVector));
	std::cout << cyan << "------------------------------------" << white << std::endl;
	delete solver;

	solver = new RungeKutta(a, b, h, y0);
	std::cout << cyan << "Runge-Kutta solution is: " << white << std::endl;
	std::cout << cyan << "------------------------------------" << white << std::endl;
	auto rungeKuttaResVector = solver->solve();
	printSolution(rungeKuttaResVector);
	printNorm(countNorm(rungeKuttaResVector, exactVector));
	std::cout << cyan << "------------------------------------" << white << std::endl;
	delete solver;

	return 0;
}

void printSolution(const std::vector < std::pair<double, double> >& solutionVector) {
	for (unsigned i = 0; i < solutionVector.size(); i++) {
		std::cout << "f(" << blue << solutionVector[i].first << white << ") = " 
			<< green << solutionVector[i].second << white << std::endl;
	}
}

double countNorm(const std::vector < std::pair<double, double> >& solutionVector,
	const std::vector < std::pair<double, double> >& exactSolution) {
	std::vector<double> resultDelta;
	for (unsigned i = 0; i < exactSolution.size(); i++) {
		resultDelta.push_back(std::fabs(exactSolution[i].second -
			solutionVector[i].second));
	}

	Matrix deltaVector(resultDelta);
	NormaInterface* norma = new NormaEuclidVector;
	double result = norma->countNorm(deltaVector);
	delete norma;
	return result;
}

void printNorm(const double normRes) {
	std::cout << std::endl;
	std::cout << yellow << "|| fExact(x) - method(x) || = " << green << normRes << white << std::endl;
	std::cout << std::endl;
}

void solveExact()
{
}
