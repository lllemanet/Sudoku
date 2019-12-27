#include "stdafx.h"
#include "SudokuMainWindow.h"
#include "SudokuGame.h"
#include <QtWidgets/QApplication>

//#include "SqrButton.h" //tmp

int main(int argc, char *argv[])
{
	/*TEMP PARSE STRING*/
	std::string str = "501740008000000050098600400040961580050000010016854070005006730070000000900072805";
	Sudoku::Board board{};
	for (int i = 0; i < 81; i++) {
		using namespace Sudoku;
		board(i) = str[i] == '0' ? Point::EMPTY :
			static_cast<Point>(Point::ONEL + (str[i] - '0' - 1));
	}
	/**/

	QApplication a(argc, argv);
	SudokuMainWindow w;
	w.LoadGame(Sudoku::Game{ board });
	w.show();
	return a.exec();
	
	
	
	/*QApplication a(argc, argv);
	QMainWindow *mainWin = new QMainWindow{};
	QWidget *centralWidget = new QWidget(mainWin);
	mainWin->setCentralWidget(centralWidget);

	QGridLayout *gridLayout = new QGridLayout(centralWidget);

	SqrButton *sqrButton = new SqrButton(centralWidget);
	sqrButton->setObjectName(QString::fromUtf8("SqrButton_1"));
	gridLayout->addWidget(sqrButton); 
	mainWin->show();
	return a.exec();*/

}
