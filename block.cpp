#include "block.h"
#include <qdatetime.h>
Block::Block(int leftboundary)
	:QRect(leftboundary, -40, 110, 40) {
	colorindex = qrand() % 9;
}

Qt::GlobalColor Block::color() const {
	return colors[colorindex];
}

bool Block::adjust_horizontal(Self* myself) {
	if (!intersects(*myself))
		return 0;
	if (left() > myself -> left())
		myself -> moveRight(left());
	else
		myself -> moveLeft(right());
	return 0;
}

bool Block::adjust_vertical(Self* myself) {
	if (!intersects(*myself))
		return 0;
	if (top() > myself -> top())
		myself -> moveBottom(top());
	else
		myself -> moveTop(bottom());
	return 0;
}

DeadBlock::DeadBlock(int leftboundary)
	:Block(leftboundary) {}

Qt::GlobalColor DeadBlock::color() const {
	return Qt::black;
}

bool DeadBlock::adjust_horizontal(Self* myself) {
	if (intersects(*myself))
		return true;
	return false;
}	
bool DeadBlock::adjust_vertical(Self* myself) {
	if (intersects(*myself))
		return true;
	return false;
}	

const Qt::GlobalColor Block::colors[9] = {
	Qt::green,
	Qt::blue,
	Qt::magenta,
	Qt::yellow,
	Qt::darkRed,
	Qt::darkGreen,
	Qt::darkBlue,
	Qt::darkMagenta,
	Qt::darkYellow
};