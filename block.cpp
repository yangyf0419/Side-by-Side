#include "block.h"
#include <qdatetime.h>
Block::Block(int leftboundary, bool side)
	:QRect(leftboundary, -40, 110, 80) {
		int tmp = qrand() % 100;
	myside = side;
	mycolor = side ? QColor(255, 60 + tmp, 60 + tmp) : QColor(60 + tmp, 60 + tmp, 255);
}

QColor Block::color() const {
	return mycolor;
}

NormalBlock::NormalBlock(int leftboundary, bool side)
	:Block(leftboundary, side) {}

QColor NormalBlock::color() const {
	return Block::color();
}


bool NormalBlock::adjust_horizontal(Self* myself) {
	if (!intersects(*myself))
		return 0;
	if (left() > myself -> left())
		myself -> moveRight(left() - 1);
	else
		myself -> moveLeft(right() + 1);
	return 0;
}

bool NormalBlock::adjust_vertical(Self* myself) {
	if (!intersects(*myself))
		return 0;
	if (top() > myself -> top())
		myself -> moveBottom(top());
	else
		myself -> moveTop(bottom() + 1);
	return 0;
}

DeadBlock::DeadBlock(int leftboundary, bool side)
	:Block(leftboundary, side) {}

QColor DeadBlock::color() const {
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
