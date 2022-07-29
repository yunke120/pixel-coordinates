#include <QApplication>
#include "mygraphicsview.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyGraphicsView w;
    w.show();
    return a.exec();
}
