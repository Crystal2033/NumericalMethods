#include<iostream>
#include "Differential.h"
#include "Integral.h"
void findDifferentials();
void integrate();

int main(int argc, char** argv) {
	findDifferentials();
	std::cout << purple << "--------------------------------------------------" << white << std::endl;
	integrate();
	std::cout << purple << "--------------------------------------------------" << white << std::endl;
	return 0;
}

void integrate() {
	const double a = -1.0;
	const double b = 1.0;
	const double h1 = 0.5;
	const double h2 = 0.25;
	std::cout << green << "The exact answer:" << red << " I = -0.006294843240543572" << white << std::endl;
	IntegralBase* baseInt = new IntegralRectangle;
	double I1 = baseInt->integrate(a, b, h1);
	double I2 = baseInt->integrate(a, b, h2);
	double rungeConcr = baseInt->RungeRombergConcreete(I1, I2, h1, h2, 1);
	std::cout << cyan << "Rectangle method." << white << std::endl;
	std::cout << yellow << "I1 = " << green << I1 << white << std::endl;
	std::cout << yellow << "I2 = " << green << I2 << white << std::endl;
	std::cout << yellow << "RungeConcreete = " << green << rungeConcr << white << std::endl;
	delete baseInt;

	std::cout << std::endl;
	std::cout << cyan << "Trapezoid method." << white << std::endl;
	baseInt = new IntegralTrapezoid;
	I1 = baseInt->integrate(a, b, h1);
	I2 = baseInt->integrate(a, b, h2);
	rungeConcr = baseInt->RungeRombergConcreete(I1, I2, h1, h2, 2);
	std::cout << yellow << "I1 = " << green << I1 << white << std::endl;
	std::cout << yellow << "I2 = " << green << I2 << white << std::endl;
	std::cout << yellow << "RungeConcreete = " << green << rungeConcr << white << std::endl;
	delete baseInt;

	std::cout << std::endl;
	std::cout << cyan << "Simpson method." << white << std::endl;
	baseInt = new IntegralSimpson;
	I1 = baseInt->integrate(a, b, h1);
	I2 = baseInt->integrate(a, b, h2);
	rungeConcr = baseInt->RungeRombergConcreete(I1, I2, h1, h2, 4);
	std::cout << yellow << "I1 = " << green << I1 << white << std::endl;
	std::cout << yellow << "I2 = " << green << I2 << white << std::endl;
	std::cout << yellow << "RungeConcreete = " << green << rungeConcr << white << std::endl;
	delete baseInt;
}

void findDifferentials() {
	const double x = 0.2;
	std::vector<std::pair<double, double>> gridFunction;
	gridFunction.push_back(std::make_pair(-1.0, -1.4142));
	gridFunction.push_back(std::make_pair(-0.4, -0.55838));
	gridFunction.push_back(std::make_pair(0.2, 0.27870));
	gridFunction.push_back(std::make_pair(0.8, 0.84008));
	gridFunction.push_back(std::make_pair(1.4, 1.4142));
	Differential* diff = new Differential(gridFunction);
	std::cout << cyan << "First differential." << white << std::endl;
	std::cout << yellow << "Left f'(" << x << ") = " << green <<
		diff->getFirstLeftDiff(x) << white << std::endl;
	std::cout << yellow << "Middle f'(" << x << ") = " << green <<
		diff->getFirstMidDiff(x) << white << std::endl;
	std::cout << yellow << "Right f'(" << x << ") = " << green <<
		diff->getFirstRightDiff(x) << white << std::endl;
	std::cout << std::endl;
	std::cout << cyan << "Second differential." << white << std::endl;
	std::cout << yellow << "f''(" << x << ") = " << green <<
		diff->getSecondDiff(x) << white << std::endl;
}