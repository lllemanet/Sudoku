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
	sb1(8, 7) = Point::NINE;
	std::cout << sb1.IsConsistent();
	Board sb2{ std::move(sb1) };
	std::cout << sb2.IsConsistent();
	Board sb3 = SolveSudoku(sb2);

	for (int r = 0; r < 9; r++) {
		for (int c = 0; c < 9; c++) {
			std::cout << "\t" << sb3(r, c);
		}
		std::cout << "\n";
	}
	//SudokuBoard sb1{};
}