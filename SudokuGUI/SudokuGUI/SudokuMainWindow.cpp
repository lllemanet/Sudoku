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

//if PointButton was pressed
void SudokuMainWindow::sqrInput(int a) {
	if (waitInButtonIndex != -1) {
		return;	//don't respond to any other point button pressed until handled this one
	}

	if (Sudoku::IsChangeable(game.GetCurBoard()(a))) {
		buttons[a]->SetWaitState(true, true);
		waitInButtonIndex = a;
	}
	else {
		Notify("You cannot change locked squares");
	}

	
}

//handle key pressed (MakeMove). TODO extract to separate method
void SudokuMainWindow::keyPressEvent(QKeyEvent *event) {
	if (waitInButtonIndex != -1 && event->type() == QEvent::KeyPress
			&& (event->key() >= Qt::Key_0 || event->key() <= Qt::Key_9)) {
		Sudoku::Point newPoint = static_cast<Sudoku::Point>(event->key() - Qt::Key_0 - 1);
		Sudoku::Point oldPoint = buttons[waitInButtonIndex]->GetPoint();
		Sudoku::Move move = Sudoku::Move{ waitInButtonIndex, newPoint,  oldPoint};

		if (game.MakeMove(move)) {
			buttons[waitInButtonIndex]->SetWaitState(false);
			buttons[waitInButtonIndex]->SetPoint(newPoint, true);
			Notify("Point was changed successfully");
		}
		else {
			buttons[waitInButtonIndex]->SetWaitState(false, true);
			Notify("Cannot make such move");
		}

		waitInButtonIndex = -1;
	}

	QMainWindow::keyPressEvent(event);
}

void SudokuMainWindow::Notify(QString msg) {
	ui.statusBar->showMessage(msg);
}