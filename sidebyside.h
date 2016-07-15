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
	~SidebySide();

protected:
	virtual void paintEvent(QPaintEvent* );
	virtual void keyPressEvent(QKeyEvent* );
	virtual void keyReleaseEvent(QKeyEvent* );
	virtual void timerEvent(QTimerEvent* );

private:
	Self *myself0, *myself1;//移动块
	QList<Block* > obstacle0, obstacle1;//障碍
	enum size{width = 400, height = 800};//主窗口的宽和高
	enum decosize{recwidth = 20, recheight = 80};//装饰长方形的宽和高
	//装饰长方形的起始位置，结束位置及间隔
	enum decopos{decotop = 0, decobottom = 800, decospace = 20, decoleft1 = 5, decoright1 = 375, decoleft2 = 405, decoright2 = 775};
	int score0;//左边得分
	int score1;//右边得分
	int time;//游戏时间
	int speed;
	int myTimeID;//移动块计时器
	int systemTimeID;//系统计时器
	int blockTimeID;//障碍块计时器
	int endTimeID;
	int endcount;
	QBrush *brush;
	QFont *font;
	QPen *pen;
	QPainter *paint;
	QColor* color;
	Self *endself;//触发死亡的移动块
	bool start0, start1;
	bool isend;
	QQueue<QRect> decoration;
	QSet<Qt::Key> key;//已经按下的按键
	QQueue<int> high_score;

	void initialize();
	void refresh();
	void refresh_key();
	void generate_new();
	void end(Self* );
	void restart();
	void store();
};

void sort(QQueue<int>& ); //in main.cpp

#endif // SIDEBYSIDE_H
