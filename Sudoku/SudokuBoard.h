#pragma once
#include <array>

namespace Sudoku {
	//suffix L meand locked (not changeable)
	//ONE is equal 0 because it eases next implementation
	enum Point {
		EMPTY = -1,
		ONE = 0, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE,
		ONEL = 9, TWOL, THREEL, FOURL, FIVEL, SIXL, SEVENL, EIGHTL, NINEL
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
		/* 3*3 sqrmatrix with next indexing inside it:
		   0 1 2
		   3 4 5
		   6 7 8
		*/
		Point& operator()(int sqrrow, int sqrcol, int sqrind);
		Point& operator()(int row, int col);
		Point& operator()(int ind);

		//numbers don't conflict?
		bool IsConsistent();

	private:
		std::array<Point, 81> points;
	};
}