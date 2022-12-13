/***************************************************************************
 *                                                                         *
 *   Copyright (C) 14.11.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "solverwidget.h"

#include <Sliders/classicslider.h>

#include <QMessageBox>


SolverWidget::SolverWidget(QWidget *parent)
    : QWidget{parent}
{
    mainLayout = new QVBoxLayout;
    menuLay = new QHBoxLayout;

    addPlotOnLay(mainLayout);
    createMenu();

    mainLayout->addLayout(menuLay);

    plot->create(2);
    setGridPoints();
    setInterpolatingTypeAndDraw();
    this->setLayout(mainLayout);
}

void SolverWidget::addPlotOnLay(QBoxLayout* lay)
{
    plot = new Plot();
    lay->addWidget(plot, 10);
}


void SolverWidget::setBackGroundColor(const QColor& color)
{
    QPalette pal = QPalette();

    pal.setColor(QPalette::Window, color);

    this->setAutoFillBackground(true);
    this->setPalette(pal);
}

void SolverWidget::setGridPoints()
{
    gridFunc.clear();
    gridFunc.push_back(std::make_pair(-2.0, Nc));
    gridFunc.push_back(std::make_pair(-1.0, Ng));
    gridFunc.push_back(std::make_pair(0.0, -1.0));
    gridFunc.push_back(std::make_pair(1.0, Nc));
    gridFunc.push_back(std::make_pair(2.0, Ng));
    plot->setGridPointsOnPlot(gridFunc);
}

void SolverWidget::addLagrangeInterpolationPlot()
{
    interpolator = new LagrangeInterpolation(gridFunc);
    auto function = initFunctionPoints(lagrangeGridValue);
    plot->addFunction(function, QPen(Qt::cyan, 2));
    delete interpolator;
}

void SolverWidget::addNewtonInterpolationPlot()
{
    interpolator = new NewtonInterpolation(gridFunc);
    auto function = initFunctionPoints(newtonGridValue);
    plot->addFunction(function, QPen(Qt::green, 2));
    delete interpolator;
}

void SolverWidget::addAllInterpolationsOnPlot()
{
    QList<std::pair<QPen, std::vector<QPointF>>> listOfFuncs;

    interpolator = new LagrangeInterpolation(gridFunc);
    auto function = initFunctionPoints(lagrangeGridValue);
    delete interpolator;
    listOfFuncs.append(std::make_pair(QPen(Qt::cyan, 2), function));

    function.clear();
    interpolator = new NewtonInterpolation(gridFunc);
    function = initFunctionPoints(newtonGridValue);
    listOfFuncs.append(std::make_pair(QPen(Qt::green, 2), function));
    delete interpolator;

    plot->addFunctions(listOfFuncs);
}

void SolverWidget::clearPlots()
{
    plot->addFunction(std::vector<QPointF>(), QPen());
}

void SolverWidget::createMenu()
{
    lagrangeVertLay = new QVBoxLayout;
    lagrangeMode = new QCheckBox("Lagrange interpolation");
    connect(lagrangeMode, &QCheckBox::clicked, this, &SolverWidget::checkBoxClicked);
    lagrangeMode->setStyleSheet("QCheckBox{"
                                "color:white;"
                                "font-size: 15px;"
                                "font-weight: bold;"
                                "}"
                                "");
    lagrangeVertLay->addWidget(lagrangeMode);
    lagrangeRadiosLay = new QVBoxLayout;
    createRadioButtons(lagrangeRadios, lagrangeRadiosLay);
    createGroupBox(lagrangeBox, lagrangeRadiosLay, "Mode", lagrangeVertLay);
    menuLay->addLayout(lagrangeVertLay);

    newtonVertLay = new QVBoxLayout;
    newtonMode = new QCheckBox("Newton interpolation");
    connect(newtonMode, &QCheckBox::clicked, this, &SolverWidget::checkBoxClicked);
    newtonMode->setStyleSheet("QCheckBox{"
                                "color:white;"
                                "font-size: 15px;"
                                "font-weight: bold;"
                                "}"
                                "");
    newtonVertLay->addWidget(newtonMode);
    newtonRadiosLay = new QVBoxLayout;
    createRadioButtons(newtonRadios, newtonRadiosLay);
    createGroupBox(newtonBox, newtonRadiosLay, "Mode", newtonVertLay);
    menuLay->addLayout(newtonVertLay);

}

void SolverWidget::createRadioButtons(std::vector<QRadioButton*> &vectorWithRadios, QBoxLayout* lay)
{

    QRadioButton* radio1 = new QRadioButton("0-1-2-3");
    QRadioButton* radio2 = new QRadioButton("1-2-3-4");
    QRadioButton* radio3 = new QRadioButton("0-1-2-3-4");
    radio3->setChecked(true);
    vectorWithRadios.push_back(radio1);
    vectorWithRadios.push_back(radio2);
    vectorWithRadios.push_back(radio3);

    for(unsigned i = 0; i < vectorWithRadios.size(); i++){
        lay->addWidget(vectorWithRadios[i]);
        vectorWithRadios[i]->setStyleSheet("color:white;"
                                           "font-size: 15px;"
                                           "font-weight: bold;"
                                           ""
                                           "");
        connect(vectorWithRadios[i], &QRadioButton::clicked, this, &SolverWidget::radioButtonHasChosen);
    }
}

void SolverWidget::setInterpolatingTypeAndDraw()
{
    switch (interpolationType) {
    case LAGRANGE:
        addLagrangeInterpolationPlot();
        break;
    case NEWTON:
        addNewtonInterpolationPlot();
        break;
    case ALL:
        addAllInterpolationsOnPlot();
        break;
    case NONE:
        clearPlots();
        break;
    default:
        break;
    }
}

std::vector<QPointF> SolverWidget::initFunctionPoints(const GRID_VALUE& gvForFunc)
{
    std::vector<QPointF> function;
    double startVal = 0.0;
    unsigned iteratorEndVal = 0;
    double step = fabs(gridFunc[1].first - gridFunc[0].first);
    double delta = 0.1;
        switch (gvForFunc) {
            case FIRST4:
                startVal = gridFunc[0].first;
                iteratorEndVal = (gridFunc.size() - 2) * step/delta + 1;
                break;

            case SECOND4:
                startVal = gridFunc[1].first;
                iteratorEndVal = (gridFunc.size() - 2) * step/delta + 1;
                break;

            case ALL5:
                startVal = gridFunc[0].first;
                iteratorEndVal = (gridFunc.size() - 1) * step/delta + 1;
                break;

            default:
                exit(-1);
                break;
        }

    for (unsigned i = 0; i < iteratorEndVal; i++) {
        function.push_back(QPointF(startVal, interpolator->interpolate(startVal)));
        startVal += delta;
    }
    return function;
}

void SolverWidget::checkBoxClicked()
{
    if(lagrangeMode->isChecked() && newtonMode->isChecked()){
        interpolationType = ALL;
    }
    else if(lagrangeMode->isChecked()){
        interpolationType = LAGRANGE;
    }
    else if(newtonMode->isChecked()){
        interpolationType = NEWTON;
    }
    else{
        interpolationType = NONE;
    }
    setInterpolatingTypeAndDraw();
}

void SolverWidget::radioButtonHasChosen()
{
    for(unsigned i = 0; i < lagrangeRadios.size(); i++){
        if(lagrangeRadios[i]->isChecked()){
            lagrangeGridValue = (GRID_VALUE)i;
            break;
        }
    }

    for(unsigned i = 0; i < newtonRadios.size(); i++){
        if(newtonRadios[i]->isChecked()){
            newtonGridValue = (GRID_VALUE)i;
            break;
        }
    }
    setInterpolatingTypeAndDraw();

}


void SolverWidget::createGroupBox(QGroupBox *groupBox, QBoxLayout *lay, QString groupName, QBoxLayout* parentGroupBoxLay, const int stretch)
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

SolverWidget::~SolverWidget()
{

}


