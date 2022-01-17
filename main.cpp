#include "tienda.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Tienda w;
    w.show();
    return a.exec();
}
