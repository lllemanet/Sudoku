#pragma once
#include <array>

namespace Sudoku {
	constexpr int numOfPoints = 81;

	//suffix L meand locked (not changeable)
	//ONE is equal 0 because it eases next implementation
	enum Point {
		EMPTY = -1,
		ONE = 0, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE,
		ONEL = 9, TWOL, THREEL, FOURL, FIVEL, SIXL, SEVENL, EIGHTL, NINEL
	};

	inline bool IsChangeable(Point p) {
		return p >= Point::EMPTY && p <= Point::NINE;
	}

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

		Point operator()(int sqrrow, int sqrcol, int sqrind) const;
		Point operator()(int row, int col) const ;
		Point operator()(int ind) const;

		//numbers don't conflict?
		bool IsConsistent() const;

		static constexpr int GetIndex(int row, int col);
		static constexpr int GetIndex(int sqrrow, int sqrcol, int sqrind);

	private:
		std::array<Point, 81> points;
	};


	//Utilities
	/*
		Solves sudoku and returns referece for solved board
		Returns empty board if there's no solution
	*/
	Board SolveSudoku(const Board& board);
}