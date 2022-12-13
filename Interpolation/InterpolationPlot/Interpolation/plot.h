/***************************************************************************
 *                                                                         *
 *   Copyright (C) 17.09.2022 by Kulikov Pavel                                 *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef PLOT_H
#define PLOT_H

#include <QObject>
#include <QWidget>
#include <QList>
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QPoint>
#include <QDebug>
#include <QtMath>
#include <QLabel>
#include "PatternObserver/Observer.h"

#define ARROW_OFFSET 20
#define X_AXIS_SHIFT_COEFF 2 // translate(width/X_AXIS_SHIFT_COEFF); shift the center of axis
#define Y_AXIS_SHIFT_COEFF 2 // translate(height/Y_AXIS_SHIFT_COEFF); shift the center of axis



typedef enum {ARGUMENT, VALUE} TYPE_OF_VAR;
class Plot : public QWidget, public InterfaceObserver
{
    Q_OBJECT
private:
    QList<QPointF> pointsFirstHalf;
    QPainter painter;
    QPen* pen = nullptr;
    QList<QPointF> gridFunction;
    QList<std::pair<QPen, std::vector<QPointF>>> penAndGraphics;
    int rightOxLineEdge = 0; // the right edge of Ox line (need for drawAxis)
    int leftOxLineEdge = 0;
    int upperOyLineEdge = 0;
    int downOyLineEdge = 0;

    int xMax = 0, xMin = 0, yMax = 0;;
    double scaledCoeffX = 0.0; //this coeff need for scaling between plot on widget and real data points from fucntion. Visualizing coefficient
    double scaledCoeffY = 0.0;

    void paintEvent(QPaintEvent* event) override;
    void drawLine(const QPointF& firstPoint, const QPointF& secondPoint);
    void initPoints();
    double getFunctionRes(const int x) const;
    void draw2DAxis();
    void drawOxOyLines();
    void drawPlotArrows();
    void checkAndSetMax(const QPointF& point, const TYPE_OF_VAR type);
    void resizeEvent(QResizeEvent* event) override;

    void drawPlot();

    void clearLists();

    void addNumbersOnAxis();

    void addNumberOnAxis(const double xScalePosition);
    bool isSpecialPoint(const int x);

    void setBackGroundColor(const QColor& color);

public:
    explicit Plot(QWidget *parent = nullptr);
    void create(const int xRange);

    void setGridPointsOnPlot(const std::vector<std::pair<double, double>> gridFunc);
    void addFunction(std::vector<QPointF> function, QPen pen);
    void addFunctions(QList<std::pair<QPen, std::vector<QPointF>>> listOfFuncs);
    ~Plot();

signals:

public:
    void updateObserver(int xEdge, const CHANGE_TYPE changeType) ;
};


#endif // PLOT_H
