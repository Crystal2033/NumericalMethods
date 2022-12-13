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

#include <SolveMechanic/Exceptions.h>


SolverWidget::SolverWidget(QWidget *parent)
    : QWidget{parent}
{
    rootPoint = new QPointF();
    mainLayout = new QVBoxLayout;
    menuLay = new QHBoxLayout;

    addPlotOnLay(mainLayout);

    addSliderOnLay(menuLay);

    createRangeLineEditsOnLay(menuLay);

    mainLayout->addLayout(menuLay);
    createFindRootButtonsOnLay(mainLayout);
    createAnswerLabelOnLay(mainLayout);

    plot->create(xEdgeSlider->getValue());
    this->setLayout(mainLayout);
}

void SolverWidget::addPlotOnLay(QBoxLayout* lay)
{
    plot = new Plot();
    lay->addWidget(plot, 10);
}

void SolverWidget::createRangeLineEditsOnLay(QBoxLayout* parentLay)
{
    rangeHorLay = new QHBoxLayout;
    createLabelAndEdit(aRangeLay, aRangeLineEdit, aRangeLabel, "Left edge");
    createLabelAndEdit(bRangeLay, bRangeLineEdit, bRangeLabel, "Right edge");
    createGroupBox(rangeGroupBox, rangeHorLay, "Range", parentLay, 3);
}

void SolverWidget::addSliderOnLay(QBoxLayout* parentLay)
{
    slidersLay = new QHBoxLayout();

    xEdgeSlider = new ClassicSlider();
    xEdgeSlider->createSlider(*slidersLay, Qt::Horizontal, 5, 100, 20);
    slidersLay->addWidget(xEdgeSlider);
    xEdgeSlider->addObserver(plot);
    createGroupBox(sliderGroupBox, slidersLay, "X changer", parentLay, 8);
}

void SolverWidget::createLabelAndEdit(QVBoxLayout*& lay, QLineEdit*& lineEdit, QLabel*& label, const QString &labelText)
{
    label = new QLabel(labelText);
    label->setStyleSheet("background-color: rgb(48, 107, 103);"
                         "color: white;"
                         "");
    lineEdit = new QLineEdit;
    lineEdit->setFixedHeight(30);

    lineEdit->setStyleSheet("background-color: darkcyan;"
                            "color: white;"
                            "font-size: 16px;"
                            "font-weight: bold;"
                            "");

    label->setBuddy(lineEdit);
    lay = new QVBoxLayout();
    lay->addWidget(label);
    lay->addWidget(lineEdit);
    rangeHorLay->addLayout(lay);
}

void SolverWidget::setBackGroundColor(const QColor& color)
{
    QPalette pal = QPalette();

    pal.setColor(QPalette::Window, color);

    this->setAutoFillBackground(true);
    this->setPalette(pal);
}

void SolverWidget::createAnswerLabelOnLay(QBoxLayout *parentLay)
{
    statusAndAnswerLay = new QHBoxLayout;
    statusMainWindowLabel = new QLabel;
    statusMainWindowLabel->setText("Solve status: ");
    statusMainWindowLabel->setStyleSheet("background-color: rgb(71, 84, 83);"
                                         "font-size: 20px;"
                                         "margin-top: 10px;"
                                         "font-weight: bold;"
                                         "color: white;"
                                         "font-family: \"Times New Roman\", Times, serif;");

    answerLabel = new QLabel;
    answerLabel->setStyleSheet("background-color: rgb(71, 84, 83);"
                               "margin-top: 10px;"
                               "font-size: 20px;"
                               "font-weight: bold;"
                               "font-family: \"Times New Roman\", Times, serif;"
                               "color: grey;");

    updateLabelStatus(NOT_USED, "Waiting for choosing method...");
    statusAndAnswerLay->addWidget(statusMainWindowLabel,0, Qt::AlignLeft);
    statusAndAnswerLay->addWidget(answerLabel,0, Qt::AlignLeft);
    parentLay->addLayout(statusAndAnswerLay);
}

void SolverWidget::updateLabelStatus(const SolveStatus &status, const QString& outPutText)
{
    switch (status) {
        case SUCCESS:
            answerLabel->setText("X= " + outPutText);
            answerLabel->setStyleSheet("background-color: rgb(71, 84, 83);"
                                       "margin-top: 10px;"
                                       "font-size: 20px;"
                                       "font-weight: bold;"
                                       "font-family: Arial, Helvetica, sans-serif;"
                                       "color: green;");
            break;
        case BAD_RANGE:
            answerLabel->setText("Error: " + outPutText);
            answerLabel->setStyleSheet("background-color: rgb(71, 84, 83);"
                                       "margin-top: 10px;"
                                       "font-size: 15px;"
                                       "font-weight: bold;"
                                       "font-family: Arial, Helvetica, sans-serif;"
                                       "color: #C41766;");
            break;
        case NOT_USED:
            answerLabel->setText(outPutText);
            answerLabel->setStyleSheet("background-color: rgb(71, 84, 83);"
                                       "margin-top: 10px;"
                                       "font-size: 20px;"
                                       "font-weight: bold;"
                                       "font-family: Arial, Helvetica, sans-serif;"
                                       "color: grey;");
            break;
        case COUNTING:
            answerLabel->setText(outPutText);
            answerLabel->setStyleSheet("background-color: rgb(71, 84, 83);"
                                       "margin-top: 10px;"
                                       "font-size: 20px;"
                                       "font-weight: bold;"
                                       "font-family: Arial, Helvetica, sans-serif;"
                                       "color: cyan;");
            break;
    default:
        break;
    }
}

std::pair<double, double>* SolverWidget::getRangeFromLineEditsOrError()
{
    if(aRangeLineEdit->text().isEmpty()){
        QMessageBox::critical(this, "Range value error", "You have to insert left edge value for finding root.");
        return nullptr;
    }
    else if(bRangeLineEdit->text().isEmpty()){
        QMessageBox::critical(this, "Range value error", "You have to insert right edge value for finding root.");
        return nullptr;
    }

    bool isOk = false;
    aRangeLineEdit->text().toDouble(&isOk);

    if(!isOk){
        QMessageBox::critical(this, "Range value error", "Your left range has to be a number. Example: 10.23");
        return nullptr;
    }

    isOk = false;
    bRangeLineEdit->text().toDouble(&isOk);
    if(!isOk){
        QMessageBox::critical(this, "Range value error", "Your right range has to be a number. Example: 10.23");
        return nullptr;
    }

    std::pair<double, double> * rangePair = new std::pair<double, double>;
    rangePair->first = aRangeLineEdit->text().toDouble();
    rangePair->second = bRangeLineEdit->text().toDouble();
    return rangePair;
}

void SolverWidget::setRootPoint(double root)
{
    rootPoint->setX(root);
    rootPoint->setY(0);
}

void SolverWidget::onMethodButtonClicked()
{
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender()); // retrieve the button you have clicked
    QString buttonText = buttonSender->text(); // retrive the text from the button clicked
    if(buttonText == "Binary search"){
        findRootMethod = new BinarySearchFindRootMethod(coefficients, epsilone);
    }
    else if(buttonText == "Newton`s tangent"){
        findRootMethod = new NewtonRootMethod(coefficients, epsilone);
    }
    else if(buttonText == "Iterations method"){
        findRootMethod = new IterationsMethod(coefficients, epsilone);
    }
    else if(buttonText == "Clean root on plot"){
        plot->setPointOnPlot(nullptr);
        updateLabelStatus(NOT_USED, "Waiting for choosing method...");
        return;
    }
    else{
        qInfo() << buttonText << " is unknown button. Please add configuration into onMethodButtonClicked().";
        this->close();
    }

    std::pair<double, double>* range = getRangeFromLineEditsOrError();
    double root = 0.0;
    if(range){
        try {
                updateLabelStatus(COUNTING, "Counting...");
                root = findRootMethod->findRoot(*range);
                updateLabelStatus(SUCCESS, QString::number(root));
                setRootPoint(root);
                plot->setPointOnPlot(rootPoint);
            }
            catch (BadRangeException& exc) {
               updateLabelStatus(BAD_RANGE, exc.what());
            }
    }
    delete findRootMethod;
    delete range;
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
    delete rootPoint;
}

void SolverWidget::createFindRootButtonsOnLay(QBoxLayout *parentLay)
{
    buttonsLay = new QHBoxLayout;
    createButtonOnLay(binarySearchButton, "Binary search", buttonsLay);
    createButtonOnLay(newtonButton, "Newton`s tangent", buttonsLay);
    createButtonOnLay(iterationsButton, "Iterations method", buttonsLay);
    createButtonOnLay(cleanPointButton, "Clean root on plot", buttonsLay);
    createGroupBox(buttonsBox, buttonsLay, "Methods", parentLay);

}

void SolverWidget::createButtonOnLay(QPushButton *&button, const QString &text, QBoxLayout* parentLay)
{
    button = new QPushButton(text);
    button->setFixedHeight(40);
    button->setStyleSheet("QPushButton{"
                          "background-color: #2286AE;"
                          "color:white;"
                          "font-size: 15px;"
                          "font-weight: bold;"
                          ""
                          "}"
                          "QPushButton:hover{"
                          "background-color:#234D5E;"
                          ""
                          "}"
                          "");
    connect(button, &QPushButton::clicked, this, &SolverWidget::onMethodButtonClicked);

    parentLay->addWidget(button);
}
