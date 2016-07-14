#ifndef SIDEBYSIDE_H
#define SIDEBYSIDE_H

#include <QtWidgets>
#include <QPainter> 
#include "Self.h"
#include "block.h"

class SidebySide : public QWidget {
	Q_OBJECT

public:
	SidebySide(QWidget *parent = 0);

protected:
	virtual void paintEvent(QPaintEvent* );
	virtual void keyPressEvent(QKeyEvent* );
	virtual void keyReleaseEvent(QKeyEvent* );
	virtual void timerEvent(QTimerEvent* );

private:
	Self *myself1, *myself2;//移动块
	QList<Block* > obstacle1, obstacle2;//障碍
	enum size{width = 400, height = 800};//主窗口的宽和高
	enum decosize{recwidth = 20, recheight = 80};//装饰长方形的宽和高
	//装饰长方形的起始位置，结束位置及间隔
	enum decopos{decotop = 0, decobottom = 800, decospace = 20, decoleft1 = 5, decoright1 = 375, decoleft2 = 405, decoright2 = 775};
	int pos;//两侧装饰块的起始位置
	int score;//得分
	int time;//游戏时间
	int speed;
	int myTimeID;//移动块计时器
	int systemTimeID;//系统计时器
	int blockTimeID;//障碍块计时器
	QPainter *paint;
	QSet<Qt::Key> key;//已经按下的按键

	void initialize();
	void refresh();
	void refresh_key();
	void generate_new();
};

#endif // SIDEBYSIDE_H
