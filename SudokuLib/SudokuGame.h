#pragma once
#include <vector>
#include "SudokuBoard.h"
#include "UndoManager.h"

namespace Sudoku {
	struct Move {
		int index;
		Point newValue;
		Point oldValue;
	};

	class Game {
	public:
		Game(const Board& startBoard);
		Game(const Game& game) = default;
		Game(Game&& game) = default;

		Game operator=(const Game& game);

		bool MakeMove(Move move);
		bool Undo();
		bool Redo();
		bool CanUndo();
		bool CanRedo();
		bool IsWon();

		const Board& GetCurBoard();
	private:
		bool IsLegalMove(Move move);

		Board startBoard;
		Board curBoard;
		UndoActManager<Move> undoManager;
	};
}