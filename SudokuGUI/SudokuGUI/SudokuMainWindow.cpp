#include "stdafx.h"
#include "SudokuMainWindow.h"
#include "SudokuBoard.h"

SudokuMainWindow::SudokuMainWindow(QWidget *parent)
	: QMainWindow(parent), game{ Sudoku::Board{} }
{
	ui.setupUi(this);
}

void SudokuMainWindow::LoadGame(const Sudoku::Game& game) {
	this->game = game;
}