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
	Self *myself0, *myself1;//�ƶ���
	QList<Block* > obstacle0, obstacle1;//�ϰ�
	enum size{width = 400, height = 800};//�����ڵĿ�͸�
	enum decosize{recwidth = 20, recheight = 80};//װ�γ����εĿ�͸�
	//װ�γ����ε���ʼλ�ã�����λ�ü����
	enum decopos{decotop = 0, decobottom = 800, decospace = 20, decoleft1 = 5, decoright1 = 375, decoleft2 = 405, decoright2 = 775};
	int score0;//��ߵ÷�
	int score1;//�ұߵ÷�
	int time;//��Ϸʱ��
	int speed;
	int myTimeID;//�ƶ����ʱ��
	int systemTimeID;//ϵͳ��ʱ��
	int blockTimeID;//�ϰ����ʱ��
	int endTimeID;
	int endcount;
	QBrush *brush;
	QFont *font;
	QPen *pen;
	QPainter *paint;
	QColor* color;
	Self *endself;//�����������ƶ���
	bool start0, start1;
	bool isend;
	QQueue<QRect> decoration;
	QSet<Qt::Key> key;//�Ѿ����µİ���
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
