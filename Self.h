#ifndef SELF_H
#define SELF_H
#include <QRect>
#include <qcolor.h>

class Self:public QRect {

	friend class SidebySide;
	enum{speed = 2};
	int leftbound;
	int rightbound;
	int bottombound;
	int topbound;
	QColor mycolor;
public:
	Self(int, int, int, int, bool);
	QColor color() const;
	QColor convert();
	Self operator+=(int);
	Self operator-=(int);
};
#endif//SELF_H