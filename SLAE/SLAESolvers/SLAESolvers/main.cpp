#include <iostream>
#include "Matrix.h"
#include "Methods.h"
#include "Colors.h"
#include "MatrixInitializer.h"
#include "Norm.h"
#include <string>
#include "Exceptions.h"
static const int Ng = 11;
static const int Nc = 12;


void userInput(std::string& str)
{
	while (true)
	{
		std::cin.clear();
		std::getline(std::cin, str);
		if (str.size() == 0)
		{
			std::cout << red << "Your input is blank." << std::endl << blue << "Please, try again." << white << "> " << std::endl;
			continue;
		}
		std::cin.clear();
		break;
	}
}

int userChoice(const int left_edge, const int right_edge = INT_MAX)
{
	std::string choice_str;
	int choice_number;
	while (true)
	{
		choice_str.clear();
		std::cout << blue << "Input a number:" << white << std::endl << "> ";
		userInput(choice_str);
		choice_number = atoi(choice_str.c_str()); //return 0 in bad case. So i don`t need 0 in any case.

		if (choice_number < left_edge || choice_number > right_edge) {
			std::cout << red << "InputValueError: You have to choose value from <" << yellow << left_edge << red << "> to <" << yellow << right_edge
				<< red << ">." << white << std::endl;
			continue;
		}
		break;
	}

	return choice_number;
}



void gaussSolveSLAE() {
//12
//5
//2
//1
//5
//12
//-11
//12
//2
//-11
//12
//-11
	Methods method;
	IMatrixInitializer* matrixIniter = new GaussMatrixIniter(Ng, Nc);
	std::cout << cyan << "You have chosen solving SLAE with Gauss`s method." << white << std::endl;
	std::cout << yellow << "Choose type of matrix:" << white << std::endl;
	std::cout << cyan << "1. Existing 3x4 matrix." << white << std::endl;
	std::cout << cyan << "2. Existing 4x5 matrix." << white << std::endl;
	std::cout << cyan << "3. Make my own." << white << std::endl;

	int choiceNumber = userChoice(1, 3);
	Matrix* matrix = nullptr;
	switch (choiceNumber)
	{
		case 1:
		{
			matrix = matrixIniter->generateMatrix(3, false);
			break;
		}
		case 2:
		{
			matrix = matrixIniter->generateMatrix(4, false);
			break;
		}
		case 3:
		{
			matrix = matrixIniter->generateMatrix(1, true);
			getchar();
			break;
		}
		default: {
			throw InputUserValueException("Unpredictable value.");
		}
	}

	std::cout << cyan << "Solving..." << white << std::endl;
	std::vector<double> answer = method.gaussSolveSLAE(*matrix);
	std::cout << green << "Solved!" << white << std::endl;
	for (int i = 0; i < matrix->getRowsValue(); i++) {
		std::cout << cyan << "X[" << i << "]" << " = " << answer[i] << white << std::endl;
	}
	delete matrix;
	delete matrixIniter;
}

void sweepingSolveSLAE() {

	Methods method;
	IMatrixInitializer* matrixIniter = new SweeperMatrixIniter(Ng, Nc);
	std::cout << cyan << "You have chosen solving SLAE with sweeping method." << white << std::endl;
	std::cout << yellow << "Choose type of matrix:" << white << std::endl;
	std::cout << cyan << "1. Existing 5x6 matrix." << white << std::endl;
	std::cout << cyan << "2. Existing 10x11 matrix." << white << std::endl;
	std::cout << cyan << "3. Set own matrix size." << white << std::endl;
	std::cout << cyan << "4. Make matrix by my own. " << red <<"It must be triple diagonal!" << white << std::endl;

	int choiceNumber = userChoice(1, 4);
	int matrixSize = 0;
	if (choiceNumber == 3) {
		std::cout << yellow <<"Input value of matrix size (from 1 to 100)." << white << std::endl;
		matrixSize = userChoice(1, 100);
	}
	Matrix* matrix = nullptr;
	switch (choiceNumber)
	{
		case 1:
		{
			matrix = matrixIniter->generateMatrix(5, false);
			break;
		}
		case 2:
		{
			matrix = matrixIniter->generateMatrix(10, false);
			break;
		}
		case 3:
		{
			matrix = matrixIniter->generateMatrix(matrixSize, false);
			break;
		}
		case 4:
		{
			matrix = matrixIniter->generateMatrix(1, true);
			getchar();
			break;
		}
		default: {
			throw InputUserValueException("Unpredictable value.");
		}
	}

	std::cout << cyan << "Solving..." << white << std::endl;
	std::vector<double> answer = method.solveSweepingSLAE(*matrix);
	std::cout << green << "Solved!" << white << std::endl;
	for (int i = 0; i < matrix->getRowsValue(); i++) {
		std::cout << cyan << "X[" << i << "]" << " = " << answer[i] << white << std::endl;
	}

	delete matrix;
	delete matrixIniter;
}

void simpleIterationsSolveSLAE() {
	Methods method;
	IMatrixInitializer* matrixIniter = new SimpleIterMatrixIniter(Ng, Nc);

	std::cout << cyan << "You have chosen solving SLAE with simple iterations method." << white << std::endl;
	std::cout << yellow << "Choose type of matrix:" << white << std::endl;
	std::cout << cyan << "1. Existing 3x4 matrix." << white << std::endl;
	std::cout << cyan << "2. Existing 4x5 matrix." << white << std::endl;
	std::cout << cyan << "3. Make my own. " << red <<"It must have diagonal dominance!" << white << std::endl;

	int choiceNumber = userChoice(1, 3);
	Matrix* matrix = nullptr;
	switch (choiceNumber)
	{
		case 1:
		{
			matrix = matrixIniter->generateMatrix(3, false);
			break;
		}
		case 2:
		{
			matrix = matrixIniter->generateMatrix(4, false);
			break;
		}
		case 3:
		{
			matrix = matrixIniter->generateMatrix(1, true);
			getchar();
			break;
		}
		default: {
			throw InputUserValueException("Unpredictable value.");
		}
	}

	std::cout << cyan << "Solving..." << white << std::endl;
	std::vector<double> answer = method.solveSimpleIterationsSLAE(*matrix);
	std::cout << green << "Solved!" << white << std::endl;
	for (int i = 0; i < matrix->getRowsValue(); i++) {
		std::cout << cyan << "X[" << i << "]" << " = " << answer[i] << white << std::endl;
	}
	delete matrix;
	delete matrixIniter;
}

void jacobiBeautifulPrint(const std::pair<std::vector<double>, Matrix>& lambdasAndOwnVectors) {
	std::vector<std::string> valuesStr;
	for (int i = 0; i < lambdasAndOwnVectors.first.size(); i++) {
		std::cout << green << "L[" << i << "] = " << lambdasAndOwnVectors.first[i] << white << std::endl;
		std::cout << cyan <<"vector = " << white <<std::endl;
		for (int j = 0; j < lambdasAndOwnVectors.second.getRowsValue(); j++) {
			double value = lambdasAndOwnVectors.second.get(j, i);
			std::string valueInString = std::to_string(value);
			std::string spaces = "";
			if (value < 0) {
				spaces = "";
			}
			else {
				spaces = " ";
			}

			if (j == 0) {
				std::cout << "/" << spaces;
			}
			else if (j == lambdasAndOwnVectors.second.getRowsValue() - 1) {
				std::cout << "\\" << spaces;
			}
			else {
				std::cout << "|" << spaces;
			}
			std::cout << blue <<valueInString << white;
			if (j == 0) {
				std::cout << " \\" << std::endl;
			}
			else if (j == lambdasAndOwnVectors.second.getRowsValue() - 1) {
				std::cout << " /" << std::endl;
			}
			else {
				std::cout << " |" << std::endl;
			}
		}
		std::cout << std::endl;
		
	}
}

void yacobiRotationsMethod() {
	Methods method;
	IMatrixInitializer* matrixIniter = new JakobiMatrixIniter(Ng, Nc);

	std::cout << cyan << "You have chosen founding own values and it`s vectors." << white << std::endl;
	std::cout << yellow << "Choose type of matrix:" << white << std::endl;
	std::cout << cyan << "1. Existing 3x3 matrix." << white << std::endl;
	std::cout << cyan << "2. Existing 4x4 matrix." << white << std::endl;
	std::cout << cyan << "3. Make my own." << white << std::endl;

	int choiceNumber = userChoice(1, 3);
	Matrix* matrix = nullptr;
	switch (choiceNumber)
	{
		case 1:
		{
			matrix = matrixIniter->generateMatrix(3, false);
			break;
		}
		case 2:
		{
			matrix = matrixIniter->generateMatrix(4, false);
			break;
		}
		case 3:
		{
			matrix = matrixIniter->generateMatrix(1, true);
			getchar();
			break;
		}
		default: {
			throw InputUserValueException("Unpredictable value.");
		}
	}


	std::cout << cyan << "Solving..." << white << std::endl;
	std::pair<std::vector<double>, Matrix> lambdasAndOwnVectors = method.yacobiGetOwnNumbersAndVectors(*matrix);
	std::cout << green << "Solved!" << white << std::endl << std::endl;
	jacobiBeautifulPrint(lambdasAndOwnVectors);
	delete matrix;
	delete matrixIniter;
}



int main(int agrc, char** argv) {
	std::cout << green << "This program can solve SLAE, find own numbers and it`s vectors." << white << std::endl;
	
	
	while (true) {
		std::cout << std::endl;
		std::cout << yellow << "Choose the type of task:" << white << std::endl;
		std::cout << cyan << "1. Gauss SLAE solver." << white << std::endl;
		std::cout << cyan << "2. Sweeping SLAE solver." << white << std::endl;
		std::cout << cyan << "3. Simple iterations SLAE solver." << white << std::endl;
		std::cout << cyan << "4. Finding own values and it`s vectors." << white << std::endl;
		std::cout << azure << "------------------------------------------------------------------" << white << std::endl;
		std::cout << blue << "5. About author." << white << std::endl;
		std::cout << red << "6. Exit." << white << std::endl;
		int userTask;
		userTask = userChoice(1, 6);
		try {
			switch (userTask)
			{
				case 1:
				{
					gaussSolveSLAE();
					break;
				}
				case 2:
				{
					sweepingSolveSLAE();
					break;
				}
				case 3:
				{
					simpleIterationsSolveSLAE();
					break;
				}
				case 4:
				{
					yacobiRotationsMethod();
					break;
				}
				case 5:
				{
					std::cout << red << "Developer is: " << blue << "Kulikov Pavel" << white << std::endl;
					break;
				}
				case 6:
				{
					std::cout << red <<"Thank" << yellow <<" you" << blue<< " for" <<
						purple << " using " << azure << "this " << pink << "program." << green << "=)" << white << std::endl;
					return 0;
				}
				default: {
					std::cout << red << "Unpredictable value" << white << std::endl;
					break;
				}
			}
		}
		catch (MatrixErrorException& err) {
			std::cout << red << err.what() << white << std::endl;
		}
		catch (InputUserValueException& err) {
			std::cout << red << err.what() << white << std::endl;
		}
		catch (NormErrorException& err) {
			std::cout << red << err.what() << white << std::endl;
		}
		catch (...) {
			std::cout << red << "Unpredictable error situation. Programmer is blind." << white << std::endl;
		}

	}
}




