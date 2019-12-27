#pragma once

#include <array>
#include <QtWidgets/QMainWindow>
#include <QtGui/QKeyEvent>
//#include "ui_sudokugui.h"
#include "ui_mysudokugui.h"
#include "pointbutton.h"
#include "SudokuGame.h"

class SudokuMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	SudokuMainWindow(QWidget *parent = Q_NULLPTR);

	void LoadGame(const Sudoku::Game& game);

public slots:
	void sqrInput(int);

protected:
	void keyPressEvent(QKeyEvent *event) override;

private:
	void Notify(QString msg);

	
	Ui::MySudokuGUIClass ui;
	Sudoku::Game game;
	std::array<PointButton*, Sudoku::numOfPoints> buttons;
	int waitInButtonIndex = -1;	//-1 measn we don't wait for input. value 0-80 means we wait for input for this square.
};