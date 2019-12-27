#include "pch.h"
#include <iostream>
#include <string>
#include "SudokuBoard.h"
#include "SudokuGame.h"
#include "GameTerminal.h"
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

	Game game{ sb2 };
	GameTerminal::PrintBoard(game.GetCurBoard());
	game.MakeMove({ 0, Point::THREE, Point::ONE });
	GameTerminal::PrintBoard(game.GetCurBoard());
	game.Undo();
	GameTerminal::PrintBoard(game.GetCurBoard());
	game.Redo();
	GameTerminal::PrintBoard(game.GetCurBoard());
	std::cout << game.Redo();
	std::system("CLS");

	GameTerminal gameTerminal{ game };
	gameTerminal.Start();
	//SudokuBoard sb1{};
}