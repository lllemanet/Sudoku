#pragma once
#include <array>

namespace Sudoku {
	enum class Value {
		ONE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE
	};

	struct Point {
		Value val;
		bool isChangeable;
	};

	class Board {
	public:
		Board();
		Board(const Board& board);
		Board(Board&& board);

		//elem access
		Point& operator()(int row, int col);
		Point& operator()(int ind);

		//numbers don't conflict?
		bool IsConsistent();

	private:
		std::array<Point, 9> vals;
	};
}