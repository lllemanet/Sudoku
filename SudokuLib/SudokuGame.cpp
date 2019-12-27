#pragma once
#include "pch.h"
#include "SudokuGame.h"
#include "SudokuBoard.h"

namespace Sudoku {

	Game::Game(const Board& startBoard) : startBoard(startBoard), curBoard(startBoard) {}

	Game Game::operator=(const Game& game) {
		return Game{ game };
	}

	bool Game::MakeMove(Move move) {
		if (!IsLegalMove(move))
			return false;

		curBoard(move.index) = move.newValue;
		if (!curBoard.IsConsistent()) {
			curBoard(move.index) = move.oldValue;
			return false;
		}

		undoManager.Do(move);

		return true;
	}

	bool Game::Undo() {
		Move undoMove;

		//shortcut solution
		try {
			undoMove = undoManager.Undo();
		}
		catch (invalid_operation) {
			return false;
		}

		curBoard(undoMove.index) = undoMove.oldValue;
		return true;
	}

	bool Game::Redo() {
		Move redoMove;
		try {
			redoMove = undoManager.Redo();
		}
		catch (invalid_operation) {
			return false;
		}
		curBoard(redoMove.index) = redoMove.newValue;
		return true;
	}

	bool Game::IsWon() {
		for (int i = 0; i < numOfPoints; i++) {
			if (curBoard(i) == Point::EMPTY)
				return false;
		}
		return curBoard.IsConsistent();
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