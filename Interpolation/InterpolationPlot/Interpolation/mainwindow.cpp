#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    mainLay = new QVBoxLayout();
    solverWidget = new SolverWidget();
    mainLay->addWidget(solverWidget);

    this->centralWidget()->setLayout(mainLay);

}

MainWindow::~MainWindow()
{
    delete ui;
}

