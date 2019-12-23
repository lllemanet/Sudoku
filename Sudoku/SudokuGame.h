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
		Game(const Game& game);
		Game(Game&& game);

		bool MakeMove(Move move);
		bool Do();
		bool Redo();
		bool isWon();

		const Board& GetBoard();
	private:
		bool isLegalMove(Move move);

		Board startBoard;
		Board curBoard;
		std::vector<Move> moveHistory;
		int maxMoves; //to trace how many redo's are possible
	};
}