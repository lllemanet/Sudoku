#pragma once
#include "SudokuGame.h"
using namespace Sudoku;

class GameTerminal {
public:
	GameTerminal(Game& game);

	void Start();

	static void PrintBoard(const Board&);
private:
	int GetMenuItem();
	Move GetMove();

	Game game;
};