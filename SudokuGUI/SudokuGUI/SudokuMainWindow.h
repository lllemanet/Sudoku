#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_sudokugui.h"
#include "ui_mysudokugui.h"

class SudokuMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	SudokuMainWindow(QWidget *parent = Q_NULLPTR);

private:
	Ui::MySudokuGUIClass ui;
};
