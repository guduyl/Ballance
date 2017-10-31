
#include "ballance.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Ballance w;
	w.show();

	return a.exec();
}
