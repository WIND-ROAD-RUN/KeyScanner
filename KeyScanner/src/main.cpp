#include <QMessageBox>
#include <QtWidgets/QApplication>
#include "KeyScanner.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    KeyScanner w;

	if (!KeyScanner::check())
	{
		return 1;
	}

#ifdef NDEBUG
	w.showFullScreen();
#else
	w.show();
#endif
    return a.exec();
}
