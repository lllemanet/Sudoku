#pragma once
#include <QtWidgets/QPushButton>
#include <SudokuBoard.h>

class PointButton{
public:
	PointButton(QPushButton *button);
	PointButton(Sudoku::Point point, QPushButton *button);

	
	void SetPoint(Sudoku::Point p);
private:
	void Update();
	Sudoku::Point point;
	QPushButton *button;
};