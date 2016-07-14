#include "block.h"
#include <qdatetime.h>
Block::Block(int leftboundary, bool color)
	:QRect(leftboundary, -40, 110, 80) {
	colorindex = qrand() % 100;
	mycolor = color;
}

QColor Block::color() const {
	return mycolor ? QColor(255, 60 + colorindex, 60 + colorindex) : QColor(60 + colorindex, 60 + colorindex, 255);
}

NormalBlock::NormalBlock(int leftboundary, bool color)
	:Block(leftboundary, color) {}

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

DeadBlock::DeadBlock(int leftboundary, bool color)
	:Block(leftboundary, color) {}

QColor DeadBlock::color() const {
	return QColor(0, 0, 0);
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
