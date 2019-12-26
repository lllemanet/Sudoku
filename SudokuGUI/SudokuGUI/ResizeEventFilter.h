#pragma once
#include <QtCore/QObject>

class ResizeEventFilter : public QObject
{
public:
	ResizeEventFilter(QObject *parent = nullptr) : QObject{ parent } { };
	bool eventFilter(QObject *obj, QEvent *event);

	int ratio = 1; //means width = height*ratio
	//QWidget *target = nullptr;
};