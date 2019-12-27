#pragma once
#include <QtWidgets/QPushButton>
#include <SudokuBoard.h>

class PointButton : public QObject {
	Q_OBJECT

public:
	PointButton(QPushButton *button, int index = 0, Sudoku::Point point = Sudoku::Point{});

	void SetPoint(Sudoku::Point point, bool update = false);
	Sudoku::Point GetPoint();

	void SetWaitState(bool waitState, bool update = false);
	void SetIndex(int index);

public slots:
	void clicked();

signals:
	void clickedInd(int index);
private:
	void Update();

	int index;
	bool waitState = false;
	Sudoku::Point point;
	QPushButton *button;
};