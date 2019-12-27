#include "stdafx.h"
#include "pointbutton.h"
#include "SudokuBoard.h"

PointButton::PointButton(QPushButton *button) : PointButton(Sudoku::Point{}, button) {}

PointButton::PointButton(Sudoku::Point point, QPushButton *button) : button{ button }, point{ point } {
	Update();
}

void PointButton::SetPoint(Sudoku::Point point) {
	this->point = point;
	Update();
}

void PointButton::Update() {
	QString styleStr = "font-size: 30px;";
	if (!Sudoku::IsChangeable(point)) {
		styleStr += "background-color: gray;";
	}
	else {
		styleStr += "background-color: white;";
	}

	button->setStyleSheet(styleStr);
	if (point != Sudoku::Point::EMPTY) {
		button->setText(QString::number((point % 9) + 1));
	}
	else {
		button->setText("");
	}
}
