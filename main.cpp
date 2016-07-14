#include "sidebyside.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	SidebySide* MyMainWindow = new SidebySide;
	MyMainWindow -> show();
	return app.exec();
}

void sort(QQueue<int>& queue) {
	int tmp;
	for (QQueue<int>::iterator i = queue.end() - 1; i != queue.begin(); i--) 
		if (*i < *(i - 1)) {
			tmp = *i;
			*i = *(i - 1);
			*(i - 1) = tmp;
		}
		else
			break;
}


