#include "sidebyside.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	SidebySide* MyMainWindow = new SidebySide;
	MyMainWindow -> show();
	return app.exec();
}
