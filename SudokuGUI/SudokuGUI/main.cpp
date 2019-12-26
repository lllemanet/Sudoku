#include "stdafx.h"
#include "SudokuMainWindow.h"
#include <QtWidgets/QApplication>

//#include "SqrButton.h" //tmp

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	SudokuMainWindow w;
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
