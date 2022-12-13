#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <Sliders/classicslider.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    lay = new QVBoxLayout;
    plot = new Plot();

    sliderLay = new QVBoxLayout;
    deltaSlider = new ClassicSlider();
    deltaSlider->addObserver(plot);

    lay->addWidget(plot, 10);

    deltaSlider->createSlider(*sliderLay, Qt::Orientation::Horizontal, 1, 6, 1);
    createGroupBox(sliderGroupBox, sliderLay, "Delta between points", lay, 1);

    centralWidget()->setLayout(lay);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createGroupBox(QGroupBox *groupBox, QBoxLayout *lay, QString groupName, QBoxLayout *parentGroupBoxLay, const int stretch)
{
    groupBox = new QGroupBox(groupName);
    groupBox->setLayout(lay);
    groupBox->setStyleSheet("QGroupBox:title {"
                            "color: white;"
                            "}"
                            "QGroupBox > *{"
                            "background-color: rgb(48, 107, 103);"
                            "}"
                            "QGroupBox{"
                            "background-color: rgb(48, 107, 103);"
                            "}"
                            ""
                            "");

    parentGroupBoxLay->addWidget(groupBox, stretch);
}

