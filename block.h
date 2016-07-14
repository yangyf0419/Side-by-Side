#ifndef BLOCK_H
#define BLOCK_H
#include "Self.h"
#include <QRect>
#include <qnamespace.h>

//×©¿éÀà
class Block: public QRect
{
public:
	Block(int);
	virtual Qt::GlobalColor color() const;
	virtual bool adjust_horizontal(Self* );
	virtual bool adjust_vertical(Self* );

private:
	static const Qt::GlobalColor colors[9];
	int colorindex;

};

class DeadBlock: public Block {
public:
	DeadBlock(int);
	virtual Qt::GlobalColor color() const;
	virtual bool adjust_horizontal(Self* );
	virtual bool adjust_vertical(Self* );
};

#endif//BLOCK_H