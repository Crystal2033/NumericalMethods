/***************************************************************************
 *                                                                         *
 *   Copyright (C) 17.09.2022 by Kulikov Pavel                                 *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "mainwindow.h"
#include <ui_mainwindow.h>

void MainWindow::showDeveloperInfo(){
    QMessageBox::about(this, "Developer Info",
"<H2> <U>Developer</U>: </H2>"
"<H3> Kulikov Pavel. FIIT M80-311B-20. </H3>"
"<h2> &nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;x^3&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;x</h2>"
"<h2>y = &nbsp;----- + --- + 11*12</h2>"
"<h2> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;10&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;12 </h2>");
}


void MainWindow::createToolBar(){
    toolBar = this->addToolBar("Main toolbar");
    QAction* getDevInfo = toolBar->addAction(QIcon(":/pictures/devIcon.png"), "Developer Info");
    connect(getDevInfo, SIGNAL(triggered()), SLOT(showDeveloperInfo()));
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    createToolBar();

    mainLayout = new QVBoxLayout();

    this->setWindowTitle("Graphic`s plot");
    this->setWindowIcon(QIcon(":/pictures/PlotIcon.png"));
    this->centralWidget()->setLayout(mainLayout);

    solverWidget = new SolverWidget();
    mainLayout->addWidget(solverWidget);

}

MainWindow::~MainWindow(){
    delete ui;
}

