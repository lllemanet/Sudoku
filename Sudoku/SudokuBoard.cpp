#pragma once
#include <stdexcept>	//invalid_argument
#include <array>		//array
#include <algorithm>	//fill_n
#include "pch.h"
#include "SudokuBoard.h"

namespace Sudoku {
	inline bool isChangeable(Point p) {
		return p > 0 && p < 10;
	}

	Board::Board() {}

	Board::Board(std::initializer_list<Point> points) {
		if (points.size() < 10) {
			for (unsigned int i = 0; i < points.size(); i++) {
				this->points[i] = *(points.begin() + i);
			}

			//doesn't work: unary '++': '_OutIt' does not define this operator or a 
			//conversion to a type acceptable to the predefined operator Sudoku
			//std::copy(points.begin(), points.end(), this->points);
		}
	}

	Board::Board(const Board& board) {
		this->points = board.points;
	}

	Board::Board(Board&& board) {
		swap(points, board.points);
	}

	Board& Board::operator=(const Board& board) {
		this->points = board.points;
		return *this;
	}

	Board& Board::operator=(Board&& board) {
		swap(points, board.points);
		return *this;
	}

	Point& Board::operator()(int row, int col) {
		if (row < 0 || row > 8 ||
			col < 0 || col > 8)
			throw std::invalid_argument("row and col should be between 0 and 2");
		return points[row * 9 + col];
	}

	Point& Board::operator()(int ind) {
		if (ind < 0 || ind > 80)
			throw std::invalid_argument("index for board should be non-negative and < 80");
		return points[ind];
	}

	//check if there repeat in any row, col or 3*3 square
	bool Board::IsConsistent() {
		std::array<int, 9> checkTable{}; //used for each row, col or 3*3 square to check if there coincidences

		//check rows
		for (int row = 0; row < 9; row++) {
			for (int col = 0; col < 9; col++) {
				int val = operator()(row, col);
				if (val == Point::EMPTY)
					continue;
				else {
					val %= 9; //get value without lock and empty
					if (++checkTable[val] > 1)
						return false;
				}
			}
			std::fill_n(checkTable.begin, 9, 0);
		}

		for (int col = 0; col < 9; col++) {
			for (int row = 0; row < 9; row++) {
				int val = operator()(row, col);
				if (val == Point::EMPTY)
					continue;
				else {
					val %= 9; //get value without lock and empty
					if (++checkTable[val] > 1)
						return false;
				}
			}
			std::fill_n(checkTable.begin, 9, 0);
		}

		//big row is three rows together: 1st 0..2, 2nd 3..5, 3rd 6..8 (same logic for bigcol)
		for (int bigrow = 0; bigrow < 3; bigrow++) {
			for (int bigcol = 0; bigcol < 3; bigcol++) {
				for (int row = bigrow * 3; row < bigrow * 3 + 3; row++) {
					for (int col = bigcol * 3; bigcol < bigcol * 3 + 3; col++) {
						int val = operator()(row, col);
						if (val == Point::EMPTY)
							continue;
						else {
							val %= 9; //get value without lock and empty
							if (++checkTable[val] > 1)
								return false;
						}
					}
				}
				std::fill_n(checkTable.begin, 9, 0);
			}
		}
		return true;
	}
}