#ifndef BLOCK_H
#define BLOCK_H
#include "Self.h"
#include <QRect>
#include <qnamespace.h>

//ש����
class Block: public QRect {
public:
	Block(int, bool);
	virtual QColor color() const;
	virtual bool adjust_horizontal(Self* ) = 0;
	virtual bool adjust_vertical(Self* ) = 0;

private:
	bool mycolor;//false��Ӧ��ɫϵ��true��Ӧ��ɫϵ
	int colorindex;
};

class NormalBlock: public Block {
public:
	NormalBlock(int, bool);
	virtual QColor color() const;
	virtual bool adjust_horizontal(Self* );
	virtual bool adjust_vertical(Self* );
};


class DeadBlock: public Block {
public:
	DeadBlock(int, bool);
	virtual QColor color() const;
	virtual bool adjust_horizontal(Self* );
	virtual bool adjust_vertical(Self* );
};

#endif//BLOCK_H