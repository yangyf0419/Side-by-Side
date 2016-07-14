#include "Self.h"

Self::Self(int left, int right, int bottom, int top, bool color):QRect() {
	leftbound = left;
	rightbound = right;
	bottombound = top;
	topbound = bottom;
	setRect((left + right) / 2 - 40, top - bottom - 100, 80, 40);
	mycolor = color ? QColor(60, 60, 255) : QColor(255, 60, 60);
}

QColor Self::color() const {
	return mycolor;
}

QColor Self::convert() {
	mycolor = mycolor == QColor(60, 60, 255) ? QColor(255, 60, 60) : QColor(60, 60, 255);
	return color();
}

Self Self::operator+=(int distance) {
	this -> moveBottom(this -> bottom() + distance);
	return *this;
}

Self Self::operator-=(int distance) {
	this -> moveTop(this -> top() - distance);
	return *this;
}