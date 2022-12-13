#pragma once
#include <vector>

class FindRootMethod {
public:
	FindRootMethod() = default;
	FindRootMethod(const std::vector<double>& coefficients, const double epsilone);
	virtual double findRoot(const std::pair<double, double>& range) = 0;
	virtual ~FindRootMethod() = default;
protected:
	std::vector<double> coefficients;
	double epsilone;

	virtual double getFuncRes(const double x, const std::vector<double> funcCoeffs) const;
	bool isCorrectRangeCondition(const std::pair<double, double>& range) const;
};

class BinarySearchFindRootMethod final : public FindRootMethod {
public:
	double findRoot(const std::pair<double, double>& range)override;
	BinarySearchFindRootMethod(const std::vector<double>& coefficients, const double epsilone);
	~BinarySearchFindRootMethod() = default;
private:

	std::pair<double, double> getNewRangeByBinarySearch(const double leftEdge, const double rightEdge) const;
	bool isCorrectRangeCondition(const std::pair<double, double>& range) const;
	
};

class NewtonRootMethod final : public FindRootMethod {
public:
	double findRoot(const std::pair<double, double>& range) override;
	NewtonRootMethod(const std::vector<double>& coefficients, const double epsilone);
	~NewtonRootMethod() = default;
private:
	std::vector<double> firstDiffCoeffs;
	std::vector<double> secondDiffCoeffs;
	
	std::vector<double> countDiffAndInsertIntoDiffCoeffVector(const std::vector<double>& coeffs);
	bool isCorrectRangeConditions(const std::pair<double, double>& range, double& startXValue) const;
	
};

class IterationsMethod final : public FindRootMethod {
public:
	double findRoot(const std::pair<double, double>& range) override;
	IterationsMethod(const std::vector<double>& coefficients, const double epsilone);
	~IterationsMethod() = default;
private:

	std::vector<double> transformedCoeffs;
	double getFuncRes(const double x, const std::vector<double> funcCoeffs) const override;
	double getExplicitDiffResult(const double x);

};
