#ifndef SELF_H
#define SELF_H
#include <QRect>

class Self:public QRect {

	friend class SidebySide;
	enum{speed = 2};
	int leftbound;
	int rightbound;
	int bottombound;
	int topbound;
public:
	Self(int, int, int, int);
};
#endif//SELF_H