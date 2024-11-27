#include "Mainwindow.h"
#include "ui_Mainwindow.h"
#include "OpenGLWidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    OpenGLWidget* pOpenGLWidget = new OpenGLWidget();
    this->setCentralWidget(pOpenGLWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}
