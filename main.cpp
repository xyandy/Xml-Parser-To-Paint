#include "head.h"
#include "project.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Project w;
	w.show();
	return a.exec();
}
