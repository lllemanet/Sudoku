#pragma once
#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>

class SqrButton : public QPushButton {
public:
	SqrButton(QWidget *parent);
	
	int heightForWidth(int w) const;

protected:
	virtual void resizeEvent(QResizeEvent *event);
};
