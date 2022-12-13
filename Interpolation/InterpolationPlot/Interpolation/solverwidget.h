/***************************************************************************
 *                                                                         *
 *   Copyright (C) 14.11.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef SOLVERWIDGET_H
#define SOLVERWIDGET_H

#include <QBoxLayout>
#include <QWidget>
#include <Sliders/abstractslider.h>
#include "plot.h"
#include <QGroupBox>
#include <QLineEdit>
#include <QPushButton>
#include <vector>
#include <QRadioButton>
#include <QCheckBox>
#include "MechanicInterpolation/Interpolation.h"
#define Ng 11.0
#define Nc 12.0
typedef enum {FIRST4, SECOND4, ALL5} GRID_VALUE;
typedef enum {LAGRANGE, NEWTON, ALL, NONE} INTERPOLATION_TYPE;

class SolverWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SolverWidget(QWidget *parent = nullptr);
    ~SolverWidget();

private:
    QBoxLayout* mainLayout;
    QBoxLayout* slidersLay;
    std::vector<std::pair<double, double>> gridFunc;
    GRID_VALUE lagrangeGridValue = ALL5;
    GRID_VALUE newtonGridValue = ALL5;
    INTERPOLATION_TYPE interpolationType = NONE;

    AbstractSlider* xEdgeSlider;
    Plot* plot;
    QGroupBox* sliderGroupBox;
    InterpolationInterface* interpolator;

    void createButtonOnLay(QPushButton*& button, const QString& text, QBoxLayout* parentLay);

    void createGroupBox(QGroupBox *groupBox, QBoxLayout *lay, QString groupName, QBoxLayout* parentGroupBoxLay, const int stretch=0);

    void addPlotOnLay(QBoxLayout* lay);

    void addSliderOnLay(QBoxLayout* parentLay);

    void setBackGroundColor(const QColor& color);

    void setGridPoints();
    void addLagrangeInterpolationPlot();
    void addNewtonInterpolationPlot();
    void addAllInterpolationsOnPlot();
    void clearPlots();


    QHBoxLayout* menuLay;
    void createMenu();
    void createRadioButtons(std::vector<QRadioButton*>& vectorWithRadios, QBoxLayout* lay);
    QVBoxLayout* lagrangeVertLay = nullptr;
    QVBoxLayout* newtonVertLay = nullptr;
    QGroupBox* lagrangeBox = nullptr;
    QGroupBox* newtonBox = nullptr;
    QVBoxLayout* lagrangeRadiosLay = nullptr;
    QVBoxLayout* newtonRadiosLay = nullptr;
    std::vector<QRadioButton*> lagrangeRadios;
    std::vector<QRadioButton*> newtonRadios;
    QCheckBox* lagrangeMode = nullptr;
    QCheckBox* newtonMode = nullptr;

    void setInterpolatingTypeAndDraw();

    std::vector<QPointF> initFunctionPoints(const GRID_VALUE& gvForFunction);

private slots:
    void checkBoxClicked();
    void radioButtonHasChosen();

signals:

};

#endif // SOLVERWIDGET_H
