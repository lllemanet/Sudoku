#pragma once
#include <vector>
#include "SudokuBoard.h"

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

		bool MakeMove(Move move);
		bool Undo();
		bool Redo();
		bool IsWon();

		const Board& GetCurBoard();
	private:
		bool IsLegalMove(Move move);

		Board startBoard;
		Board curBoard;
		std::vector<Move> moveHistory;
		int curMoveInd = 0;					//to know what is last move is
		int maxMoves = 0;					//to trace how many redo's are possible
	};
}