#include "pch.h"
#include "SudokuBoard.h"
#include "SudokuGame.h"
#include <iostream>
using namespace Sudoku;

void PrintBoard(Board board);

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

	Game game{ sb2 };
	PrintBoard(game.GetCurBoard());
	game.MakeMove({ 0, Point::THREE, Point::ONE });
	PrintBoard(game.GetCurBoard());
	game.Undo();
	PrintBoard(game.GetCurBoard());
	game.Redo();
	PrintBoard(game.GetCurBoard());
	//SudokuBoard sb1{};
}

void PrintBoard(Board board) {
	for (int r = 0; r < 9; r++) {
		for (int c = 0; c < 9; c++) {
			std::cout << "\t" << board(r, c);
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}