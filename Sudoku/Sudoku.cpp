#include "pch.h"
#include "SudokuBoard.h"
#include <iostream>
using namespace Sudoku;

int main()
{
	Board sb1{};
	sb1(0) = Point::ONE;
	sb1(0, 1) = Point::TWO;
	sb1(2, 2, 8) = Point::EIGHTL;
	sb1(2, 2, 7) = Point::EIGHTL;
	std::cout << sb1.IsConsistent();
	//SudokuBoard sb1{};
}