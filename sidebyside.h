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
	Self *myself1, *myself2;//�ƶ���
	QList<Block* > obstacle1, obstacle2;//�ϰ�
	enum size{width = 400, height = 800};//�����ڵĿ�͸�
	enum decosize{recwidth = 20, recheight = 80};//װ�γ����εĿ�͸�
	//װ�γ����ε���ʼλ�ã�����λ�ü����
	enum decopos{decotop = 0, decobottom = 800, decospace = 20, decoleft1 = 5, decoright1 = 375, decoleft2 = 405, decoright2 = 775};
	int pos;//����װ�ο����ʼλ��
	int score;//�÷�
	int time;//��Ϸʱ��
	int speed;
	int myTimeID;//�ƶ����ʱ��
	int systemTimeID;//ϵͳ��ʱ��
	int blockTimeID;//�ϰ����ʱ��
	QPainter *paint;
	QSet<Qt::Key> key;//�Ѿ����µİ���

	void initialize();
	void refresh();
	void refresh_key();
	void generate_new();
};

#endif // SIDEBYSIDE_H
