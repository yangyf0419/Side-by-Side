#include "Self.h"

Self::Self(int left, int right, int bottom, int top):QRect() {
		leftbound = left;
		rightbound = right;
		bottombound = top;
		topbound = bottom;
		setRect((left + right) / 2 - 40, top - bottom - 100, 80, 40);
}
