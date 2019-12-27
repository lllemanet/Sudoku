#include "stdafx.h"
#include "SudokuMainWindow.h"
#include "SudokuBoard.h"

SudokuMainWindow::SudokuMainWindow(QWidget *parent)
	: QMainWindow(parent), game{ Sudoku::Board{} }
{
	ui.setupUi(this);

	for (int i = 0; i < buttons.size(); i++) {
		buttons[i] = new PointButton(ui.sqrButtons[i], i, game.GetCurBoard()(i));
		QObject::connect(buttons[i], SIGNAL(clickedInd(int)), this, SLOT(sqrInput(int)));
	}
}

void SudokuMainWindow::LoadGame(const Sudoku::Game& game) {
	this->game = game;
	Sudoku::Board board = this->game.GetCurBoard();

	for (int i = 0; i < Sudoku::numOfPoints; i++) {
		buttons[i]->SetPoint(board(i), true);
	}
}

void SudokuMainWindow::sqrInput(int a) {
	if (waitInButtonIndex != -1) {
		return;
	}
	buttons[a]->SetWaitState(true, true);
	waitInButtonIndex = a;
}

void SudokuMainWindow::keyPressEvent(QKeyEvent *event) {
	if (waitInButtonIndex != -1 && event->type() == QEvent::KeyPress
			&& (event->key() >= Qt::Key_0 || event->key() <= Qt::Key_9)) {
		


		buttons[waitInButtonIndex]->SetWaitState(false);

		//TODOW check for locked indexes and consistency
		Sudoku::Point newPoint = static_cast<Sudoku::Point>(event->key() - Qt::Key_0 - 1);
		//if (game.MakeMove(Sudoku::Move{ waitInButtonIndex, newPoint, buttons[waitInButtonIndex]->point}))
		buttons[waitInButtonIndex]->SetPoint(newPoint, true);

		waitInButtonIndex = -1;
	}

	QMainWindow::keyPressEvent(event);
}