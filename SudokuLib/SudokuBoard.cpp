#pragma once
#include <stdexcept>	//invalid_argument
#include <array>		//array
#include <algorithm>	//fill_n
#include "pch.h"
#include "SudokuBoard.h"

#define OUT

namespace Sudoku {
	Board::Board() {
		std::fill_n(points.begin(), 81, Point::EMPTY);
	}

	Board::Board(std::initializer_list<Point> points) : Board()  {
		if (points.size() < 81) {
			for (unsigned int i = 0; i < points.size(); i++) {
				this->points[i] = *(points.begin() + i);
			}
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

	//access operators make checks (can harm performance) TODO fast access
	Point& Board::operator()(int sqrrow, int sqrcol, int sqrind) {
		if (sqrrow < 0 || sqrrow > 3 ||
				sqrcol < 0 || sqrcol > 3 ||
				sqrind < 0 || sqrind > 8)
			throw std::invalid_argument("sqrrow and sqrcol must be between 0 and 2; \
				sqrind should be between 0 and 8");

		return points[GetIndex(sqrrow, sqrcol, sqrind)];
	}

	Point& Board::operator()(int row, int col) {
		if (row < 0 || row > 8 ||
				col < 0 || col > 8)
			throw std::invalid_argument("row and col should be between 0 and 8");
		return points[GetIndex(row, col)];
	}

	Point& Board::operator()(int ind) {
		if (ind < 0 || ind > 80)
			throw std::invalid_argument("index for board should be non-negative and < 80");
		return points[ind];
	}

	Point Board::operator()(int sqrrow, int sqrcol, int sqrind) const {
		if (sqrrow < 0 || sqrrow > 3
			|| sqrcol < 0 || sqrcol > 3
			|| sqrind < 0 || sqrind > 8) {
			throw std::invalid_argument("sqrrow and sqrcol must be between 0 and 2; sqrind should be between 0 and 8");
		}

		return points[GetIndex(sqrrow, sqrcol, sqrind)];
	}

	Point Board::operator()(int row, int col) const {
		if (row < 0 || row > 8
			|| col < 0 || col > 8) {
			throw std::invalid_argument("row and col should be between 0 and 8");
		}

		return points[GetIndex(row, col)];
	}

	Point Board::operator()(int ind) const{
		if (ind < 0 || ind > 80)
			throw std::invalid_argument("index for board should be non-negative and < 80");

		return points[ind];
	}

	//check if there repeat in any row, col or 3*3 square
	bool Board::IsConsistent() const {
		std::array<int, 9> checkTable{};	//used for each row, col or 3*3 square to check if the're coincidences

		//check rows
		for (int row = 0; row < 9; row++) {
			for (int col = 0; col < 9; col++) {
				int val = operator()(row, col);
				if (val == Point::EMPTY)
					continue;
				else {
					val %= 9;	//get value without lock and empty
					if (++checkTable[val] > 1)
						return false;
				}
			}
			std::fill_n(checkTable.begin(), 9, 0);
		}

		//check columns
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
			std::fill_n(checkTable.begin(), 9, 0);
		}

		//for squares
		for (int sqrrow = 0; sqrrow < 3; sqrrow++) {
			for (int sqrcol = 0; sqrcol < 3; sqrcol++) {
				for (int sqrind = 0; sqrind < 9; sqrind++) {
					int val = operator()(sqrrow, sqrcol, sqrind);
					if (val == Point::EMPTY)
						continue;
					else {
						val %= 9; //get value without lock and empty
						if (++checkTable[val] > 1)
							return false;
					}
				}
				std::fill_n(checkTable.begin(), 9, 0);
			}
		}
		return true;
	}



	/*Sudoku solver*/
	inline int GetNextEmptyIndex(const Board& board, int curInd) {
		for (; curInd < numOfPoints; curInd++) {
			if (board(curInd) == Point::EMPTY)
				return curInd;
		}
		return numOfPoints;
	}

	bool SolveSudokuHelper(OUT Board& resBoard, int curInd);

	Board SolveSudoku(const Board& srcBoard) {
		if (!srcBoard.IsConsistent())
			return Board{};

		Board resBoard{ srcBoard };
		int curInd = GetNextEmptyIndex(resBoard, 0);
		if (curInd == numOfPoints)
			return resBoard;

		if (SolveSudokuHelper(resBoard, curInd))
			return resBoard;
		else
			return Board{}; //fix it
	}

	bool SolveSudokuHelper(OUT Board& resBoard, int curInd) {
		if (curInd == numOfPoints)
			return true;

		for (int tryVal = 0; tryVal < 9; tryVal++) {
			resBoard(curInd) = static_cast<Point>(tryVal); //trying this value

			if (resBoard.IsConsistent()) {
				if (SolveSudokuHelper(resBoard, curInd + 1)) { //try next free
					return true;
				}
				else {
					//empty all elements added after curInd
					for (int i = curInd + 1; i < numOfPoints; i++) {
						if (IsChangeable(resBoard(i)))
							resBoard(i) = Point::EMPTY;
					}
				}
			}
		}
		return false;
	}
}