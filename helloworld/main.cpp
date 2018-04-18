#include "mydialog.h"
#include <QApplication>

//build apt need install libgl1-mesa-dev
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyDialog w;
    w.show();

    return a.exec();
}
