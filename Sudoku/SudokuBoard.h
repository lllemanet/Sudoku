#pragma once
#include <array>

namespace Sudoku {
	//suffix L meand locked (not changeable)
	//ONE is equal 0 because it eases next implementation
	enum Point {
		ONE = 0, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE,
		ONEL = 9, TWOL, THREEL, FOURL, FIVEL, SIXL, SEVENL, EIGHTL, NINEL, EMPTY = 18
	};

	inline bool isChangeable(Point p);

	class Board {
	public:
		Board();
		Board(std::initializer_list<Point> points);
		Board(const Board& board);
		Board(Board&& board);

		Board& operator=(const Board& board);
		Board& operator=(Board&& board);

		//elem access
		Point& operator()(int row, int col);
		Point& operator()(int ind);

		//numbers don't conflict?
		bool IsConsistent();

		std::array<int, 9> rowIndexes(int row);
		std::array<int, 9> colIndexes(int col);
		std::array<int, 9> squareIndexes(int sqrNum);

	private:
		std::array<Point, 81> points;
	};
}