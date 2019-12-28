#include "stdafx.h"
#include "SudokuMainWindow.h"
#include "SudokuBoard.h"

SudokuMainWindow::SudokuMainWindow(Sudoku::Game game, QWidget *parent) 
									: game{ game }, QMainWindow(parent)
{
	ui.setupUi(this);

	//init PointButton array
	for (int i = 0; i < buttons.size(); i++) {
		buttons[i] = new PointButton(ui.sqrButtons[i], i, game.GetCurBoard()(i));
		QObject::connect(buttons[i], SIGNAL(clickedInd(int)), this, SLOT(sqrInput(int)));
	}

	//connect redo/undo actions with slots
	QObject::connect(ui.undoAction, SIGNAL(triggered()), this, SLOT(undo()));
	QObject::connect(ui.redoAction, SIGNAL(triggered()), this, SLOT(redo()));

	UpdateUndoAvailability();
}

void SudokuMainWindow::LoadGame(const Sudoku::Game& game) {
	this->game = game;

	UpdateBoard();
	UpdateUndoAvailability();
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
			buttons[waitInButtonIndex]->SetPoint(newPoint, true); //UpdateBoard();
			Notify("Point was changed successfully");
		}
		else {
			buttons[waitInButtonIndex]->SetWaitState(false, true);
			Notify("Cannot make such move");
		}

		waitInButtonIndex = -1;
	}
	UpdateUndoAvailability();

	QMainWindow::keyPressEvent(event);
}

void SudokuMainWindow::Notify(QString msg) {
	ui.statusBar->showMessage(msg);
}

void SudokuMainWindow::undo() {
	if (game.Undo()) {
		Notify("Successful undo");
		UpdateBoard();
	}
	else {
		Notify("Cannot undo");
	}
	UpdateUndoAvailability();
}

void SudokuMainWindow::redo() {
	if (game.Redo()) {
		UpdateBoard();
		Notify("Successful undo");
	}
	else {
		Notify("Cannot undo");
	}
	UpdateUndoAvailability();
}

void SudokuMainWindow::UpdateBoard() {
	Sudoku::Board board = this->game.GetCurBoard();
	for (int i = 0; i < Sudoku::numOfPoints; i++) {
		buttons[i]->SetPoint(board(i), true);
	}
}

void SudokuMainWindow::UpdateUndoAvailability() {
	ui.undoAction->setEnabled(game.CanUndo() ? true : false);
	ui.redoAction->setEnabled(game.CanRedo() ? true : false);
}