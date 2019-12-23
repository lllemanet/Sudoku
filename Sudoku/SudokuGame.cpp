#pragma once
#include "pch.h"
#include "SudokuGame.h"
#include "SudokuBoard.h"

namespace Sudoku {

	Game::Game(const Board& startBoard) : startBoard(startBoard), curBoard(startBoard) {}

	bool Game::MakeMove(Move move) {
		if (!IsLegalMove(move))
			return false;

		curBoard(move.index) = move.newValue;
		moveHistory.push_back(move); //temp for test
		return true;
	}

	const Board& Game::GetCurBoard() {
		return curBoard;
	}

	bool Game::IsLegalMove(Move move) {
		return	!(move.index < 0 || move.index > 80) &&		//not out of bounds
				IsChangeable(curBoard(move.index)) &&		//destination should be changeable (not locked)
				curBoard(move.index) == move.oldValue;		//oldValue must coincide with point in board
	}
}