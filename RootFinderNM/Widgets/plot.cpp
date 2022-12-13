/***************************************************************************
 *                                                                         *
 *   Copyright (C) 17.09.2022 by Kulikov Pavel                                 *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "plot.h"
#include "Widgets/solverwidget.h"

void Plot::drawPlot() // drawing plot.
{
    for(int i = 0; i < pointsFirstHalf.size() - 1; i++){ //we can do this because these lists have the same value of points
        drawLine(pointsFirstHalf[i], pointsFirstHalf[i+1]);
    }
}

void Plot::clearLists(){
    pointsFirstHalf.clear();
    pointsSecondHalf.clear();
}

void Plot::drawRootPoint()
{
    QPen newPen(Qt::red, 4);
    painter.setPen(newPen);
    painter.drawPoint(QPointF(rootPoint->x() * scaledCoeffX, rootPoint->y() * scaledCoeffY));
}

void Plot::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.translate(width()/X_AXIS_SHIFT_COEFF, height()/Y_AXIS_SHIFT_COEFF);

    draw2DAxis();
    drawPlot();

    if(rootPoint){
        drawRootPoint();
    }


    painter.end();
}

void Plot::drawLine(const QPointF &firstPoint, const QPointF &secondPoint) // method draws line between firstPoint and secondPoint points
{

    if(abs(firstPoint.y()) == INFINITY || abs(secondPoint.y()) == INFINITY){ //diff == oo

        int xPosition = 0;
        if(abs(firstPoint.y()) == INFINITY){
             xPosition = firstPoint.x() * scaledCoeffX;
            painter.drawText(xPosition + 5, 20, QString::number(firstPoint.x())); //yMax string point
        }
        else{
            xPosition = secondPoint.x() * scaledCoeffX;
            painter.drawText(xPosition + 5, 20, QString::number(secondPoint.x())); //yMax string point
        }

        painter.setPen(QPen(Qt::red, 1, Qt::PenStyle::DashLine));
        painter.drawLine(xPosition, upperOyLineEdge - ARROW_OFFSET, xPosition, downOyLineEdge);
        painter.setPen(QPen(Qt::black, 1));
        painter.drawLine(xPosition, -5, xPosition, 5);

        return;
    }
    painter.setPen(*pen);
    painter.drawLine(firstPoint.x() * scaledCoeffX, firstPoint.y() * scaledCoeffY, secondPoint.x() *scaledCoeffX, secondPoint.y() *scaledCoeffY);
}


void Plot::create(const int xMax) // creating plot
{
    clearLists();
    this->xMax = xMax;
    initPoints();
}

void Plot::initPoints() // appending function`s points in list
{
    yMax = 0;
    for (int x = -xMax; x <= xMax; x++){

        double y = getFunctionRes(x);
        QPointF point = QPointF(x, y); // its negative because in Qt Ox -> right direction, Oy -> down direction
        checkAndSetMax(point, VALUE);

        pointsFirstHalf.append(point);
    }
    scaledCoeffX = double(rightOxLineEdge)/double(xMax);
    scaledCoeffY = double(upperOyLineEdge)/double(yMax);
    update();
}

double Plot::getFunctionRes(const int x) const // drawing function
{
    return pow(x, 3)/10 + x/Ng + Nc*Ng;
    //return pow(x, 3)/(Nc*Ng) + 2*x - Nc - Ng;
}

void Plot::draw2DAxis()
{
    painter.setPen(QPen(Qt::white, 1));
    drawOxOyLines();
    drawPlotArrows();
    addNumbersOnAxis();

}

void Plot::setBackGroundColor(const QColor& color)
{
    QPalette pal = QPalette();

    pal.setColor(QPalette::Window, color);

    this->setAutoFillBackground(true);
    this->setPalette(pal);
}

void Plot::drawOxOyLines() // this method draws Ox and Oy lines
{
    painter.drawLine(leftOxLineEdge, 0, rightOxLineEdge + ARROW_OFFSET, 0);
    painter.drawLine(0, downOyLineEdge, 0, upperOyLineEdge - ARROW_OFFSET);
}

void Plot::addNumbersOnAxis()
{
    painter.drawText(-QString::number(yMax).size()*8, upperOyLineEdge, QString::number(yMax)); //yMax string point
    painter.drawLine(-5, upperOyLineEdge, 5, upperOyLineEdge); //mini-line yMax on axis

    double xScalePosition = -1.0f;
    for(int i = 0; i < 9; i++){
        if(i == 4){ // we don`t need to insert zero again.
            painter.drawText(-12, 20, "0");
            xScalePosition+=0.25f;
            continue;
        }
        addNumberOnAxis(xScalePosition);
        xScalePosition+=0.25f;
    }

}

void Plot::addNumberOnAxis(const double xScalePosition)
{
    painter.drawText(xScalePosition*rightOxLineEdge, 20, QString::number(xScalePosition*xMax)); //-xMax/2 string point
    painter.drawLine(xScalePosition*rightOxLineEdge, -5, xScalePosition*rightOxLineEdge, 5); //mini-line -xMax/2 on axis
}

void Plot::drawPlotArrows() // this method draws arrows at the end of the Ox and Oy lines
{
    painter.drawLine(rightOxLineEdge + ARROW_OFFSET, 0, rightOxLineEdge + ARROW_OFFSET/2, -3); //drawing OX arrow
    painter.drawLine(rightOxLineEdge + ARROW_OFFSET, 0, rightOxLineEdge + ARROW_OFFSET/2,  3); //drawing OX arrow
    painter.drawText(rightOxLineEdge + ARROW_OFFSET - 5, 10, "x"); //X LABEL

    painter.drawLine(0, upperOyLineEdge - ARROW_OFFSET,  3, upperOyLineEdge - ARROW_OFFSET/2); //drawing OY arrow
    painter.drawLine(0, upperOyLineEdge - ARROW_OFFSET, -3, upperOyLineEdge - ARROW_OFFSET/2); //drawing OY arrow
    painter.drawText(-10, upperOyLineEdge - ARROW_OFFSET + 5, "y"); // Y LABEL
}

void Plot::checkAndSetMax(const QPointF &point, const TYPE_OF_VAR type)
{
    if (type == ARGUMENT){ // type is X
        if(point.x() > xMax){
            xMax = point.x();
        }
    }
    else if (type == VALUE){ // type is Y
        if(point.y() > yMax){
            yMax = point.y();
        }
    }
}

void Plot::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    rightOxLineEdge = 9*(width() - width()/X_AXIS_SHIFT_COEFF)/10;// should remain 10% before the width window
    leftOxLineEdge = -rightOxLineEdge;
    upperOyLineEdge = -9*(height() - height()/Y_AXIS_SHIFT_COEFF)/10; //should remain 10% before the height window
    downOyLineEdge = -upperOyLineEdge;

    scaledCoeffX = double(rightOxLineEdge)/double(xMax);
    scaledCoeffY = double(upperOyLineEdge)/double(yMax);
}

void Plot::setPointOnPlot(const QPointF *point)
{
    if(rootPoint == nullptr){
        rootPoint = new QPointF;
    }

    if(point == nullptr){
        delete rootPoint;
        rootPoint = nullptr;
        update();
        return;
    }

    *rootPoint = *point;

    update();
}


Plot::Plot(QWidget *parent) : QWidget(parent)
{
    setBackGroundColor(QColor(QLatin1String("#314350")));
    pen = new QPen(Qt::white, 2, Qt::PenStyle::SolidLine, Qt::PenCapStyle::RoundCap, Qt::PenJoinStyle::RoundJoin);
    setMinimumSize(350, 350); //fixex min size
}

Plot::~Plot()
{
    clearLists();
    delete pen;
}

void Plot::updateObserver(int xEdge, const CHANGE_TYPE changeType)
{
    Q_UNUSED(changeType);
    create(xEdge);
}
