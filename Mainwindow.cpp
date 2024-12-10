#include "Mainwindow.h"
#include "ui_Mainwindow.h"
#include "OpenGLWidget.h"
#include <QImage>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    OpenGLWidget* pOpenGLWidget = new OpenGLWidget();
    ui->verticalLayout->addWidget(pOpenGLWidget);

    QImage img(":/Res/images/face.jpeg");
    if(img.isNull())
    {
        qDebug()<<"read img failed";
        return;
    }
    ui->label->setPixmap(QPixmap::fromImage(img));
}

MainWindow::~MainWindow()
{
    delete ui;
}
