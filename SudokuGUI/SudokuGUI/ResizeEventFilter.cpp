#include "stdafx.h"
#include "ResizeEventFilter.h"

bool ResizeEventFilter::eventFilter(QObject *object, QEvent *event) {
	/*if (object != target || */if (event->type() != QEvent::Resize)
		return false;

	QResizeEvent *resEvent = static_cast<QResizeEvent*>(event);
	QWidget *widget = static_cast<QWidget*>(object);
	
	
	widget->setFixedHeight(widget->size().width() / ratio);
	return true;
}