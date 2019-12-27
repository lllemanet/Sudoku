#include "stdafx.h"
#include "pointbutton.h"
#include "SudokuBoard.h"

PointButton::PointButton(QPushButton *button, int index, Sudoku::Point point)
							: button{ button } , index{ index }, point{ point } {
	QObject::connect(button, SIGNAL(clicked()), this, SLOT(clicked()));
	Update();
}

void PointButton::SetIndex(int index) {
	this->index = index;
}

void PointButton::SetWaitState(bool waitState, bool update) {
	this->waitState = waitState;
	if (update)
		Update();
}

void PointButton::SetPoint(Sudoku::Point point, bool update) {
	this->point = point;
	if (update)
		Update();
}

Sudoku::Point PointButton::GetPoint() {
	return point;
}

void PointButton::clicked() {
	clickedInd(index);
}

void PointButton::Update() {
	QString styleStr = "font-size: 30px;";
	if (waitState) {
		styleStr += "background-color: black;";
	}
	else if (!Sudoku::IsChangeable(point)) {
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
