#pragma once

#include <array>
#include <QtWidgets/QMainWindow>
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
private:
	Ui::MySudokuGUIClass ui;
	Sudoku::Game game;
	std::array<PointButton*, Sudoku::numOfPoints> buttons;
};