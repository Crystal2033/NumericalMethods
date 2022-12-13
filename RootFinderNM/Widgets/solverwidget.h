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
#include <SolveMechanic/Methods.h>
#include "plot.h"
#include <QGroupBox>
#include <QLineEdit>
#include <QPushButton>
#include <vector>
#define Ng 11.0
#define Nc 12.0

typedef enum {SUCCESS, BAD_RANGE, NOT_USED, COUNTING} SolveStatus;


class SolverWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SolverWidget(QWidget *parent = nullptr);
    ~SolverWidget();

private:
    const double epsilone = 1e-6;
    const std::vector<double> coefficients {Nc*Ng, 1/Nc, 0.0, 1/10.0};
    QPointF * rootPoint = nullptr;
    QBoxLayout* mainLayout;
    QBoxLayout* slidersLay;

    QHBoxLayout* menuLay;
    AbstractSlider* xEdgeSlider;
    Plot* plot;
    QGroupBox* sliderGroupBox;
    FindRootMethod* findRootMethod = nullptr;

    QHBoxLayout* rangeHorLay;
    QVBoxLayout* aRangeLay;
    QVBoxLayout* bRangeLay;

    QGroupBox* rangeGroupBox;
    QLabel* aRangeLabel;
    QLabel* bRangeLabel;

    QLineEdit* aRangeLineEdit = nullptr;
    QLineEdit* bRangeLineEdit = nullptr;

    QGroupBox* buttonsBox;
    QHBoxLayout* buttonsLay;
    QPushButton* binarySearchButton;
    QPushButton* newtonButton;
    QPushButton* iterationsButton;
    QPushButton* cleanPointButton;

    QHBoxLayout* statusAndAnswerLay;
    QLabel* statusMainWindowLabel;
    QLabel* answerLabel;

    void createFindRootButtonsOnLay(QBoxLayout* parentLay);

    void createButtonOnLay(QPushButton*& button, const QString& text, QBoxLayout* parentLay);

    void createGroupBox(QGroupBox *groupBox, QBoxLayout *lay, QString groupName, QBoxLayout* parentGroupBoxLay, const int stretch=0);

    void addPlotOnLay(QBoxLayout* lay);

    void createRangeLineEditsOnLay(QBoxLayout* parentLay);

    void addSliderOnLay(QBoxLayout* parentLay);

    void createLabelAndEdit(QVBoxLayout*& lay, QLineEdit*& lineEdit, QLabel*& label, const QString& labelText);

    void setBackGroundColor(const QColor& color);

    void createAnswerLabelOnLay(QBoxLayout* parentLay);
    void updateLabelStatus(const SolveStatus& status, const QString& text="");

    std::pair<double, double>* getRangeFromLineEditsOrError();

    void setRootPoint(double root);

private slots:
    void onMethodButtonClicked();

signals:

};

#endif // SOLVERWIDGET_H
