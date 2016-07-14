#include "sidebyside.h"
#include <QDesktopwidget>
#include <QTimer>

SidebySide::SidebySide(QWidget* parent)
	:QWidget(parent) {
		//初始化标题
		setWindowTitle(tr("Side by Side"));
		//居中摆放
		int width = QApplication::desktop()->width();
		int height = QApplication::desktop()->height();
		setGeometry((width-800)/2, (height-800)/2, 400, 800);
		setFixedSize(800, 800);
		myself1 = new Self(decoleft1 + recwidth, decoright1, decotop + 20, decobottom);
		myself2 = new Self(decoleft2 + recwidth, decoright2, decotop + 20, decobottom);
		qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
		initialize();
}

void SidebySide::paintEvent(QPaintEvent* ) {
	paint = new QPainter;
	paint -> begin(this);

	//绘制装饰矩形
	paint -> setBrush(QBrush(Qt::black, Qt::SolidPattern));
	int start = (decotop + pos) % (recheight + decospace) - recheight;
	for (; start <= decobottom; start += (decospace + recheight)) {
		paint -> drawRect(decoleft1, start, recwidth, recheight);
		paint -> drawRect(decoright1, start, recwidth, recheight);
		paint -> drawRect(decoleft2, start, recwidth, recheight);
		paint -> drawRect(decoright2, start, recwidth, recheight);
	}

	for (QList<Block* >::iterator i = obstacle1.begin(); i != obstacle1.end(); i++) {
		paint -> setBrush(QBrush((*i) -> color(), Qt::SolidPattern));
		paint -> drawRect(**i);
	}
	for (QList<Block* >::iterator i = obstacle2.begin(); i != obstacle2.end(); i++) {
		paint -> setBrush(QBrush((*i) -> color(), Qt::SolidPattern));
		paint -> drawRect(**i);
	}

	paint -> setBrush(QBrush(Qt::red, Qt::SolidPattern));
	paint -> drawRect(*myself1);
	paint -> drawRect(*myself2);

	paint -> setBrush(QBrush(Qt::cyan, Qt::SolidPattern));
	paint -> drawRect(0, 0, 800, 20);
	paint -> drawText(QRect(350, 0, 120, 20), tr("score: %1").arg(score));
	paint -> drawText(500, 50, tr("speed: %1").arg(speed));
	paint -> drawText(500, 150, tr("time: %1").arg(time));
};

void SidebySide::keyPressEvent(QKeyEvent *event) {
	key.insert(Qt::Key(event -> key()));
}

void SidebySide::keyReleaseEvent(QKeyEvent *event) {
	key.remove(Qt::Key(event -> key()));
}

void SidebySide::timerEvent(QTimerEvent *event)
{
	if (event -> timerId() == myTimeID) {
		refresh_key();
	}
	else if (event -> timerId() == systemTimeID) {
		refresh();
	}
	else if (event -> timerId() == blockTimeID) {
		killTimer(blockTimeID);
		generate_new();
		blockTimeID = startTimer(4500 / speed);
	}
	else{
		QWidget::timerEvent(event);
	}
}

void SidebySide::initialize() {
	myTimeID = 0;
	systemTimeID = 0;
	speed = 3;
	score = 0;
	pos = 1;
	time = 0;

	systemTimeID = startTimer(15);
	myTimeID = startTimer(3);
	blockTimeID = startTimer(1500);

}

void SidebySide::refresh() {
	time += 15;
	pos += speed;
	for (QList<Block* >::iterator i = obstacle1.begin(); i != obstacle1.end(); i++)
		(*i) -> moveBottom((*i) -> bottom() + speed);
	for (QList<Block* >::iterator i = obstacle2.begin(); i != obstacle2.end(); i++)
		(*i) -> moveBottom((*i) -> bottom() + speed);
	score += 10;
	speed = - 412500 / (time - 200000) + 1;
	if (time > 148000)
		speed = 9;
	myself1 -> moveBottom(myself1 -> bottom() + speed);
	myself2 -> moveBottom(myself2 -> bottom() + speed);
	SidebySide::update();
}

void SidebySide::refresh_key() {
	for(QSet<Qt::Key>::iterator i = key.begin(); i != key.end(); i++)
		switch(*i) {
		case Qt::Key_Up: myself2 -> moveTop(myself2 -> top() - myself2 -> speed - 3 * speed / 10); break;
		case Qt::Key_W: myself1 -> moveTop(myself1 -> top() - myself1 -> speed - 3 * speed / 10); break;
		case Qt::Key_Down: myself2 -> moveBottom(myself2 -> bottom() + myself2 -> speed); break;
		case Qt::Key_S: myself1 -> moveBottom(myself1 -> bottom() + myself1 -> speed); break;
		case Qt::Key_Left: myself2 -> moveLeft(myself2 -> left() - myself2 -> speed); break;
		case Qt::Key_A: myself1 -> moveLeft(myself1 -> left() - myself1 -> speed); break;
		case Qt::Key_Right: myself2 -> moveRight(myself2 -> right() + myself2 -> speed); break;
		case Qt::Key_D: myself1 -> moveRight(myself1 -> right() + myself1 -> speed); break;
	}
	if (myself1 -> right() > myself1 -> rightbound)
		myself1 -> moveRight(myself1 -> rightbound);
	if (myself2 -> right() > myself2 -> rightbound)
		myself2 -> moveRight(myself2 -> rightbound);
	if (myself1 -> left() < myself1 -> leftbound)
		myself1 -> moveLeft(myself1 -> leftbound);
	if (myself2 -> left() < myself2 -> leftbound)
		myself2 -> moveLeft(myself2 -> leftbound);
	if (myself1 -> top() < myself1 -> topbound)
		myself1 -> moveTop(myself1 -> topbound);
	if (myself2 -> top() < myself2 -> topbound)
		myself2 -> moveTop(myself2 -> topbound);
	if (myself1 -> bottom() > myself1 -> bottombound)
		myself1 -> moveBottom(myself1 -> bottombound);
	if (myself2 -> bottom() > myself2 -> bottombound)
		myself2 -> moveBottom(myself2 -> bottombound);
	update();
}

void SidebySide::generate_new() {
	int tempindex;
	int count = 0;

	//左边框生成新障碍
	tempindex = qrand() % 3;
	qrand() % 10 ? obstacle1.append(new Block(30 + 115 * tempindex)) : obstacle1.append(new DeadBlock(30 + 115 * tempindex));
	for (int i = 0; i < 3; i++) {
		if (count > 0)//一排不超过三个障碍
			break;
		if (tempindex == i) //保证一排至少有一个障碍
			continue;
		if (qrand() % 2) {
			qrand() % 2 ? obstacle1.append(new Block(30 + 115 * i)) : obstacle1.append(new DeadBlock(30 + 115 * i));
			count ++;
		}
	}

	//左边框消去屏幕以下的障碍
	for (QList<Block* >::iterator i = obstacle1.begin(); (*i) -> top() > decobottom; i++) {
		delete *i;
		i = obstacle1.erase(i);
	}

	//右边框生成新障碍
	tempindex = qrand() % 3;
	qrand() % 10 ? obstacle2.append(new Block(430 + 115 * tempindex)) : obstacle2.append(new DeadBlock(430 + 115 * tempindex));
	for (int i = 0; i < 3; i++) {
		if (count > 0)
			break;
		if (tempindex == i)
			continue;
		if (qrand() % 2) {
			qrand() % 2 ? obstacle2.append(new Block(430 + 115 * i)) : obstacle2.append(new DeadBlock(430 + 115 * i));
			count ++;
		}
	}

	//右边框消去屏幕以下的障碍
	for (QList<Block* >::iterator i = obstacle2.begin(); (*i) -> top() > decobottom; i++) {
		delete *i;
		i = obstacle2.erase(i);
	}
}