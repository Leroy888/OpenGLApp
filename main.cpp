#include "Mainwindow.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    int num =10;
    auto func = [num]() mutable {
        num += 5;
        return num;
    };
    qDebug()<<"func num:"<<func()<<"  num:"<<num;


    MainWindow w;
    w.show();
    return a.exec();
}
