#include "stdafx.h"
#include "SudokuMainWindow.h"
#include "SudokuBoard.h"

SudokuMainWindow::SudokuMainWindow(QWidget *parent)
	: QMainWindow(parent), game{ Sudoku::Board{} }
{
	ui.setupUi(this);
	for (int i = 0; i < buttons.size(); i++) {
		buttons[i] = new PointButton(ui.sqrButtons[i]);
	}
}

void SudokuMainWindow::LoadGame(const Sudoku::Game& game) {
	this->game = game;
	Sudoku::Board board = this->game.GetCurBoard();

	for (int i = 0; i < Sudoku::numOfPoints; i++) {
		buttons[i]->SetPoint(board(i));
	}
}