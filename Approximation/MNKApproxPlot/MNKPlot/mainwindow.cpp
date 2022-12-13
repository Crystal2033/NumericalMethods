#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mainLay = new QVBoxLayout;
    plot = new Plot();
    mainLay->addWidget(plot);
    this->centralWidget()->setLayout(mainLay);
}

MainWindow::~MainWindow()
{
    delete ui;
}

