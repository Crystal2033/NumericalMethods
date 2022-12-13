#include "MatrixInitializer.h"
#include "Colors.h"
typename Matrix* GaussMatrixIniter::generateMatrix(const int xQuantity, const bool isUserMatrix)
{
    Matrix* matrix = new Matrix(xQuantity, xQuantity + 1);
    if (!isUserMatrix) {
        if (xQuantity == 3) {
            create3x4Matrix(matrix);
        }
        else if (xQuantity == 4) {
            create4x5Matrix(matrix);
        }
        else {
            std::cout << red << "Unpredicted value of x quantity." << white << std::endl;
        }
    }
    else{   
        delete matrix;
        return initUserMatrix();
    }

    return matrix;
}

void GaussMatrixIniter::create3x4Matrix(Matrix* matrix)
{
    matrix->matrix[0][0] = (double)Nc;
    matrix->matrix[0][1] = 5.0;
    matrix->matrix[0][2] = 2.0;
    matrix->matrix[0][3] = 1.0;

    matrix->matrix[1][0] = 5.0;
    matrix->matrix[1][1] = (double)Nc;
    matrix->matrix[1][2] = -(double)Ng;
    matrix->matrix[1][3] = (double)Nc;

    matrix->matrix[2][0] = 2.0;
    matrix->matrix[2][1] = -(double)Ng;
    matrix->matrix[2][2] = (double)Nc;
    matrix->matrix[2][3] = -(double)Ng;
    return;
}

void GaussMatrixIniter::create4x5Matrix(Matrix* matrix)
{
    matrix->matrix[0][0] = (double)Nc + 5.0;
    matrix->matrix[0][1] = 0.0;
    matrix->matrix[0][2] = (double)Ng;
    matrix->matrix[0][3] = (double)Ng;
    matrix->matrix[0][4] = 2.0;

    matrix->matrix[1][0] = 3.0;
    matrix->matrix[1][1] = 3.0;
    matrix->matrix[1][2] = 0.0;
    matrix->matrix[1][3] = (double)Ng;
    matrix->matrix[1][4] = 2.0;

    matrix->matrix[2][0] = 2.0;
    matrix->matrix[2][1] = 5.0;
    matrix->matrix[2][2] = 3.0;
    matrix->matrix[2][3] = (double)Nc;
    matrix->matrix[2][4] = 2.0;

    matrix->matrix[3][0] = (double)Nc;
    matrix->matrix[3][1] = (double)(Nc + Ng);
    matrix->matrix[3][2] = (double)Nc;
    matrix->matrix[3][3] = 1.0;
    matrix->matrix[3][4] = (double)Nc;
    return;
}

typename Matrix* SweeperMatrixIniter::generateMatrix(const int xQuantity, const bool isUserMatrix)
{
    Matrix* matrix = new Matrix(xQuantity, xQuantity + 1);
    if (!isUserMatrix) {
        createMatrix(matrix, xQuantity);
    }
    else {
        delete matrix;
        return initUserMatrix();
    }

    return matrix;
}

void SweeperMatrixIniter::createMatrix(Matrix* matrix, const int equationsQuantity)
{
    for (int i = 0; i < equationsQuantity; i++) {
        matrix->matrix[i][matrix->columnsValue - 1] = Nc + Ng * (i + 1); //d
        matrix->matrix[i][i] = Nc * (i+1) * (i+1) + Ng; //b
        if (i == 0) {
            matrix->matrix[i][i + 1] = Ng - Nc * (i + 1); //c
        }
        else if (i == matrix->rowsValue - 1) {
            matrix->matrix[i][i - 1] = (i + 1) * Nc + Ng;; //a
        }
        else {
            matrix->matrix[i][i - 1] = (i + 1) * Nc + Ng; //a
            matrix->matrix[i][i + 1] = Ng - Nc * (i + 1); //c
        }
        
    }
}


typename Matrix* SimpleIterMatrixIniter::generateMatrix(const int xQuantity, const bool isUserMatrix)
{
    Matrix* matrix = new Matrix(xQuantity, xQuantity + 1);
    if (!isUserMatrix) {
        if (xQuantity == 3) {
            create3x4Matrix(matrix);
        }
        else if (xQuantity == 4) {
            create4x5Matrix(matrix);
        }
        else {
            std::cout << red << "Unpredicted value of x quantity." << white << std::endl;
        }
    }
    else {
        delete matrix;
        return initUserMatrix();
    }

    return matrix;
}

void SimpleIterMatrixIniter::create3x4Matrix(Matrix* matrix)
{
    matrix->matrix[0][0] = (double)Nc + 10.0;
    matrix->matrix[0][1] = (double)Ng;
    matrix->matrix[0][2] = 1.0;
    matrix->matrix[0][3] = (double)Ng;

    matrix->matrix[1][0] = (double)Ng;
    matrix->matrix[1][1] = (double)Nc + 10.0;
    matrix->matrix[1][2] = 3.0;
    matrix->matrix[1][3] = (double)Nc + 10.0;

    matrix->matrix[2][0] = 1.0;
    matrix->matrix[2][1] = 3.0;
    matrix->matrix[2][2] = (double)Ng + 4.0;
    matrix->matrix[2][3] = 0.0;
}

void SimpleIterMatrixIniter::create4x5Matrix(Matrix* matrix)
{
    matrix->matrix[0][0] = (double)Nc + 10.0;
    matrix->matrix[0][1] = (double)Ng;
    matrix->matrix[0][2] = 1.0;
    matrix->matrix[0][3] = 1.0;
    matrix->matrix[0][4] = (double)Ng;

    matrix->matrix[1][0] = (double)Ng;
    matrix->matrix[1][1] = (double)Nc + 10.0;
    matrix->matrix[1][2] = 2.0;
    matrix->matrix[1][3] = 2.0;
    matrix->matrix[1][4] = (double)Nc + 10.0;

    matrix->matrix[2][0] = 1.0;
    matrix->matrix[2][1] = 2.0;
    matrix->matrix[2][2] = (double)Ng + 4.0;
    matrix->matrix[2][3] = 1.0;
    matrix->matrix[2][4] = 0.0;

    matrix->matrix[3][0] = 1.0;
    matrix->matrix[3][1] = 1.0;
    matrix->matrix[3][2] = 1.0;
    matrix->matrix[3][3] = (double)(Ng + Nc);
    matrix->matrix[3][4] = 1.0;
}

typename Matrix* JakobiMatrixIniter::generateMatrix(const int xQuantity, const bool isUserMatrix)
{
    Matrix* matrix = new Matrix(xQuantity, xQuantity);
    if (!isUserMatrix) {
        if (xQuantity == 3) {
            create3x3Matrix(matrix);
        }
        else if (xQuantity == 4) {
            create4x4Matrix(matrix);
        }
        else {
            std::cout << red << "Unpredicted value of x quantity." << white << std::endl;
        }
    }
    else
    {
        delete matrix;
        return initUserMatrix();
    }
    return matrix;
}

void JakobiMatrixIniter::create3x3Matrix(Matrix* matrix)
{
    matrix->matrix[0][0] = (double)Nc + 10.0;
    matrix->matrix[0][1] = (double)Ng;
    matrix->matrix[0][2] = 1.0;

    matrix->matrix[1][0] = (double)Ng;
    matrix->matrix[1][1] = (double)Nc + 10.0;
    matrix->matrix[1][2] = 3.0;

    matrix->matrix[2][0] = 1.0;
    matrix->matrix[2][1] = 3.0;
    matrix->matrix[2][2] = (double)Ng + 4.0;
}

void JakobiMatrixIniter::create4x4Matrix(Matrix* matrix)
{
    matrix->matrix[0][0] = (double)Nc + 10.0;
    matrix->matrix[0][1] = (double)Ng;
    matrix->matrix[0][2] = 1.0;
    matrix->matrix[0][3] = 1.0;

    matrix->matrix[1][0] = (double)Ng;
    matrix->matrix[1][1] = (double)Nc + 10.0;
    matrix->matrix[1][2] = 2.0;
    matrix->matrix[1][3] = 2.0;

    matrix->matrix[2][0] = 1.0;
    matrix->matrix[2][1] = 2.0;
    matrix->matrix[2][2] = (double)Ng + 4.0;
    matrix->matrix[2][3] = 1.0;

    matrix->matrix[3][0] = 1.0;
    matrix->matrix[3][1] = 1.0;
    matrix->matrix[3][2] = 1.0;
    matrix->matrix[3][3] = (double)(Ng + Nc);
}

Matrix* JakobiMatrixIniter::initUserMatrix()
{
    int rows;
    std::cout << cyan << "Input value of equations: " << white;
    std::cin >> rows;
    std::cout << std::endl;
    int columns = rows;
    Matrix* matrix = new Matrix(rows, columns);
    std::cin >> *matrix;

    return matrix;
}

Matrix* IMatrixInitializer::initUserMatrix()
{
    int rows;
    std::cout << cyan << "Input value of equations: " << white;
    std::cin >> rows;
    std::cout << std::endl;
    int columns = rows + 1;
    Matrix* matrix = new Matrix(rows, columns);
    std::cin >> *matrix;

    return matrix;
}
