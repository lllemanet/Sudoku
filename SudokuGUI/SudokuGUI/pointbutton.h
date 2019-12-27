#pragma once
#include <QtWidgets/QPushButton>
#include <SudokuBoard.h>

class PointButton : public QObject {
	Q_OBJECT

public:
	PointButton(QPushButton *button, int index = 0, Sudoku::Point point = Sudoku::Point{});

	void SetPoint(Sudoku::Point p);
	void SetIndex(int index);

public slots:
	void clicked();

signals:
	void clickedInd(int index);
private:
	void Update();

	int index;
	Sudoku::Point point;
	QPushButton *button;
};