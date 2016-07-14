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

	for (QList<Block* >::iterator i = obstacle0.begin(); i != obstacle0.end(); i++) {
		paint -> setPen(QPen((*i) -> color(), 1));
		paint -> setBrush(QBrush((*i) -> color(), Qt::SolidPattern));
		paint -> drawRect(**i);
	}
	for (QList<Block* >::iterator i = obstacle1.begin(); i != obstacle1.end(); i++) {
		paint -> setPen(QPen((*i) -> color(), 1));
		paint -> setBrush(QBrush((*i) -> color(), Qt::SolidPattern));
		paint -> drawRect(**i);
	}

	paint -> setPen(QPen(myself0 -> color(), 1));
	paint -> setBrush(QBrush(myself0 -> color(), Qt::SolidPattern));
	paint -> drawRect(*myself0);

	paint -> setPen(QPen(myself1 -> color(), 1));
	paint -> setBrush(QBrush(myself1 -> color(), Qt::SolidPattern));
	paint -> drawRect(*myself1);

	paint -> setPen(Qt::black);
	paint -> setBrush(QBrush(Qt::cyan, Qt::SolidPattern));
	paint -> drawRect(0, 0, 800, 20);
	paint -> drawText(QRect(325, 0, 200, 20), tr("TOTAL SCORE: %1").arg(score0 + score1));
	paint -> drawText(QRect(150, 0, 200, 20), tr("SCORE: %1").arg(score0));
	paint -> drawText(QRect(550, 0, 200, 20), tr("SCORE: %1").arg(score1));

};

void SidebySide::keyPressEvent(QKeyEvent *event) {
	key.insert(Qt::Key(event -> key()));
}

void SidebySide::keyReleaseEvent(QKeyEvent *event) {
	key.remove(Qt::Key(event -> key()));
}

void SidebySide::timerEvent(QTimerEvent *event)
{
	if (isend) {
		if (event -> timerId() == endTimeID)
			return end(endself);
		return;
	}
	if (event -> timerId() == systemTimeID)
		refresh();
	if (event -> timerId() == myTimeID)
		refresh_key();
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
	endcount = 0;
	score0 = 0;
	score1 = 0;
	pos = 1;
	time = 0;
	start0 = false;
	start1 = false;
	isend = false;

	systemTimeID = startTimer(15);
	myTimeID = startTimer(3);
	blockTimeID = startTimer(1500);
	endTimeID = 0;
	myself0 = new Self(decoleft1 + recwidth, decoright1, decotop + 20, decobottom, 0);
	myself1 = new Self(decoleft2 + recwidth, decoright2, decotop + 20, decobottom, 1);
}

void SidebySide::refresh() {
	time += 15;
	pos += speed;
	score0 += 5;
	score1 += 5;
	if (speed != 9)
		speed = - 412500 / (time - 200000) + 3;

	for (QList<Block* >::iterator i = obstacle0.begin(); i != obstacle0.end(); i++) {
		(*i) -> moveBottom((*i) -> bottom() + speed);
		if ((*i) -> intersects(*myself0)) {
			if ((*i) -> adjust_vertical(myself0))
				return end(myself0);
		}
	}
	if (myself0 -> bottom() > myself0 -> bottombound - 1)
		return end(myself0);

	for (QList<Block* >::iterator i = obstacle1.begin(); i != obstacle1.end(); i++) {
		(*i) -> moveBottom((*i) -> bottom() + speed);
		if ((*i) -> intersects(*myself1)) {
			if ((*i) -> adjust_vertical(myself1))
				return end(myself1);
		}
	}
	if (myself1 -> bottom() > myself1 -> bottombound - 1)
		return end(myself1);

	myself0 -> moveBottom(myself0 -> bottom() + speed);
	myself1 -> moveBottom(myself1 -> bottom() + speed);

	update();
}

void SidebySide::refresh_key() {
	for(QSet<Qt::Key>::iterator i = key.begin(); i != key.end(); i++)
		switch(*i) {
		case Qt::Key_Up: {
			myself1 -> moveTop(myself1 -> top() - myself1 -> speed - 3 * speed / 10);
			for(QList<Block* >::iterator j = obstacle1.begin(); j != obstacle1.end(); j++) {
				if (!(*j) -> intersects(*myself1))
					continue;
				if ((*j) -> adjust_vertical(myself1))
					return end(myself1);
				break;
			}
			break;
						 }

		case Qt::Key_W: {
			myself0 -> moveTop(myself0 -> top() - myself0 -> speed - 3 * speed / 10);
			for(QList<Block* >::iterator j = obstacle0.begin(); j != obstacle0.end(); j++) {
				if (!(*j) -> intersects(*myself0))
					continue;
				if ((*j) -> adjust_vertical(myself0))
					return end(myself0);
				break;
			}
			break;
						}

		case Qt::Key_Down: {
			myself1 -> moveBottom(myself1 -> bottom() + myself1 -> speed);
			for(QList<Block* >::iterator j = obstacle1.begin(); j != obstacle1.end(); j++) {
				if (!(*j) -> intersects(*myself1))
					continue;
				if ((*j) -> adjust_vertical(myself1))
					return end(myself1);
				break;
			}
			break;
						   }

		case Qt::Key_S: {
			myself0 -> moveBottom(myself0 -> bottom() + myself0 -> speed);
			for(QList<Block* >::iterator j = obstacle0.begin(); j != obstacle0.end(); j++) {
				if (!(*j) -> intersects(*myself0))
					continue;
				if ((*j) -> adjust_vertical(myself0))
					return end(myself0);
				break;
			}
			break;
						}
		case Qt::Key_Left: {
			myself1 -> moveLeft(myself1 -> left() - myself1 -> speed);
			for(QList<Block* >::iterator j = obstacle1.begin(); j != obstacle1.end(); j++) {
				if (!(*j) -> intersects(*myself1))
					continue;
				if ((*j) -> adjust_horizontal(myself1))
					return end(myself1);
				break;
			}
			break;
						   }

		case Qt::Key_A: {
			myself0 -> moveLeft(myself0 -> left() - myself0 -> speed);
			for(QList<Block* >::iterator j = obstacle0.begin(); j != obstacle0.end(); j++) {
				if (!(*j) -> intersects(*myself0))
					continue;
				if ((*j) -> adjust_horizontal(myself0))
					return end(myself0);
				break;
			}
			break;
						}

		case Qt::Key_Right: {
			myself1 -> moveRight(myself1 -> right() + myself1 -> speed);
			for(QList<Block* >::iterator j = obstacle1.begin(); j != obstacle1.end(); j++) {
				if (!(*j) -> intersects(*myself1))
					continue;
				if ((*j) -> adjust_horizontal(myself1))
					return end(myself1);
				break;
			}
			break;
							}

		case Qt::Key_D: {
			myself0 -> moveRight(myself0 -> right() + myself0 -> speed);
			for(QList<Block* >::iterator j = obstacle0.begin(); j != obstacle0.end(); j++) {
				if (!(*j) -> intersects(*myself0))
					continue;
				if ((*j) -> adjust_horizontal(myself0))
					return end(myself0);
				break;
			}
			break;
						}
	}
	if (myself0 -> right() > myself0 -> rightbound - 2)
		myself0 -> moveRight(myself0 -> rightbound - 2);
	if (myself1 -> right() > myself1 -> rightbound - 2)
		myself1 -> moveRight(myself1 -> rightbound - 2);
	if (myself0 -> left() < myself0 -> leftbound + 2)
		myself0 -> moveLeft(myself0 -> leftbound + 2);
	if (myself1 -> left() < myself1 -> leftbound + 2)
		myself1 -> moveLeft(myself1 -> leftbound + 2);
	if (myself0 -> top() < myself0 -> topbound + 2)
		myself0 -> moveTop(myself0 -> topbound + 2);
	if (myself1 -> top() < myself1 -> topbound + 2)
		myself1 -> moveTop(myself1 -> topbound + 2);
	if (myself0 -> bottom() > myself0 -> bottombound - 2)
		myself0 -> moveBottom(myself0 -> bottombound - 2);
	if (myself1 -> bottom() > myself1 -> bottombound - 2)
		myself1 -> moveBottom(myself1 -> bottombound - 2);
	update();
}

void SidebySide::generate_new() {
	int tempindex;
	int count = 0;

	//左边框生成新障碍
	tempindex = qrand() % 3;
	qrand() % 10 ? obstacle0.append(new Block(30 + 115 * tempindex, 0)) : obstacle0.append(new DeadBlock(30 + 115 * tempindex, 0));
	for (int i = 0; i < 3; i++) {
		if (count > 0)//一排不超过三个障碍
			break;
		if (tempindex == i) //保证一排至少有一个障碍
			continue;
		if (qrand() % 2) {
			qrand() % 2 ? obstacle0.append(new Block(30 + 115 * i, 0)) : obstacle0.append(new DeadBlock(30 + 115 * i, 0));
			count ++;
		}
	}

	//左边框消去屏幕以下的障碍
	for (QList<Block* >::iterator i = obstacle0.begin(); (*i) -> top() > decobottom; i++) {
		delete *i;
		i = obstacle0.erase(i);
		score0 += 100;
	}

	//右边框生成新障碍
	tempindex = qrand() % 3;
	qrand() % 10 ? obstacle1.append(new Block(430 + 115 * tempindex, 1)) : obstacle1.append(new DeadBlock(430 + 115 * tempindex, 1));
	for (int i = 0; i < 3; i++) {
		if (count > 0)
			break;
		if (tempindex == i)
			continue;
		if (qrand() % 2) {
			qrand() % 2 ? obstacle1.append(new Block(430 + 115 * i, 1)) : obstacle1.append(new DeadBlock(430 + 115 * i, 1));
			count ++;
		}
	}

	//右边框消去屏幕以下的障碍
	for (QList<Block* >::iterator i = obstacle1.begin(); (*i) -> top() > decobottom; i++) {
		delete *i;
		i = obstacle1.erase(i);
		score1 += 100;
	}
}

void SidebySide::end(Self* myself) {
	if (!endcount) {
		isend = true;
		endTimeID = startTimer(500);
		endself = myself;
	}
	if (endcount++ > 9)
		return restart();
	myself -> convert();
	return update();
}

void SidebySide::restart() {
	killTimer(systemTimeID);
	killTimer(blockTimeID);
	killTimer(myTimeID);
	int choice = QMessageBox::warning(this, tr("Game Over!"),
		tr("Do you want to restart?"),
		QMessageBox::Yes | QMessageBox::No);
	if(QMessageBox::No == choice){
		this->close();
	}
	for (QList<Block* >::iterator i = obstacle0.begin(); i != obstacle0.end(); i++)
		delete *i;
	for (QList<Block* >::iterator i = obstacle1.begin(); i != obstacle1.end(); i++)
		delete *i;
	key.clear();
	obstacle0.clear();
	obstacle1.clear();
	delete myself0, myself1;
	initialize();
}