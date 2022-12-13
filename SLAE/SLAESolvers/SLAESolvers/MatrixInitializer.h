#pragma once
#include "Matrix.h"

class IMatrixInitializer {
public:
	IMatrixInitializer(const int Ng, const int Nc) { this->Nc = Nc; this->Ng = Ng; };
	virtual Matrix* generateMatrix(const int xQuantity, const bool isUserMatrix = false) = 0;
	virtual Matrix* initUserMatrix();
	virtual ~IMatrixInitializer() = default;
protected:
	int Ng;
	int Nc;
};

class GaussMatrixIniter : public IMatrixInitializer {
public:
	GaussMatrixIniter(const int Ng, const int Nc) : IMatrixInitializer(Ng, Nc) {};
	Matrix* generateMatrix(const int xQuantity, const bool isUserMatrix) override;
	~GaussMatrixIniter() = default;
private:
	void create3x4Matrix(Matrix* matrix);
	void create4x5Matrix(Matrix* matrix);
};

class SweeperMatrixIniter : public IMatrixInitializer {
public:
	SweeperMatrixIniter(const int Ng, const int Nc) : IMatrixInitializer(Ng, Nc) {};
	Matrix* generateMatrix(const int xQuantity, const bool isUserMatrix) override;
	~SweeperMatrixIniter() = default;
private:
	void createMatrix(Matrix* matrix, const int equationsQuantity);

};

class SimpleIterMatrixIniter : public IMatrixInitializer {
public:
	SimpleIterMatrixIniter(const int Ng, const int Nc) : IMatrixInitializer(Ng, Nc) {};
	Matrix* generateMatrix(const int xQuantity, const bool isUserMatrix) override;
	~SimpleIterMatrixIniter() = default;
private:
	void create3x4Matrix(Matrix* matrix);
	void create4x5Matrix(Matrix* matrix);
};

class JakobiMatrixIniter : public IMatrixInitializer {
public:
	JakobiMatrixIniter(const int Ng, const int Nc) : IMatrixInitializer(Ng, Nc) {};
	Matrix* generateMatrix(const int xQuantity, const bool isUserMatrix) override;
	~JakobiMatrixIniter() = default;
private:
	void create3x3Matrix(Matrix* matrix);
	void create4x4Matrix(Matrix* matrix);
	Matrix* initUserMatrix() override;
};
