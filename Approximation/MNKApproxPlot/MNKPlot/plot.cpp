/***************************************************************************
 *                                                                         *
 *   Copyright (C) 17.09.2022 by Kulikov Pavel                                 *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "plot.h"
#include "Approximation/MNKApprox.h"

void Plot::drawPlot() // drawing plot.
{
    for(unsigned i = 0; i < gridFunction.size(); i++){
        painter.setPen(QPen(Qt::red, 5));
        painter.drawPoint(gridFunction[i].x() * scaledCoeffX, gridFunction[i].y() * scaledCoeffY);
    }
    for(unsigned i = 0; i < penAndGraphics.size(); i++){
        *pen = penAndGraphics[i].first;
        for(unsigned j = 0; j < penAndGraphics[i].second.size() - 1; j++){
            drawLine(penAndGraphics[i].second[j], penAndGraphics[i].second[j+1]);
            checkAndSetMax(penAndGraphics[i].second[j], VALUE);
        }
    }
}

double Plot::getMaxArgFromGrid() const
{
    double max = 0;
    for(int i = 0; i < gridFunction.size(); i++){
        if(fabs(gridFunction[i].x()) > max){
            max = fabs(gridFunction[i].x());
        }
    }
    return max + 1.0;
}


void Plot::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.translate(width()/X_AXIS_SHIFT_COEFF, height()/Y_AXIS_SHIFT_COEFF);

    draw2DAxis();
    drawPlot();

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

void Plot::initPoints()
{
    const double step = 0.01;
    const int valueOfIterations = (int)(abs(gridFunction[gridFunction.size()-1].x() - gridFunction[0].x()))/step;
    std::vector<QPointF> linearGraphic;
    int nextGridValue = 0;
    double startXValue =gridFunction[0].x();
    qInfo() << "Linear delta";
    for(int i = 0; i < valueOfIterations; i++){
        linearGraphic.push_back(QPointF(startXValue + step * i,
                                getLinearRes(startXValue + step * i)));
        if(fabs(startXValue + step * i - gridFunction[nextGridValue].x()) < 1e-7){
            qInfo() << fabs(linearGraphic[linearGraphic.size() - 1].y() - gridFunction[nextGridValue].y());
            nextGridValue++;
        }

    }
    penAndGraphics.push_back(std::make_pair(QPen(Qt::green, 1), linearGraphic));

    std::vector<QPointF> parabolicGraphic;
    nextGridValue = 0;
    qInfo() << "Parabolic delta";
    for(int i = 0; i < valueOfIterations; i++){
        parabolicGraphic.push_back(QPointF(startXValue + step * i,
                                getParabolicRes(startXValue + step * i)));
        if(fabs(startXValue + step * i - gridFunction[nextGridValue].x()) < 1e-7){
            qInfo() << fabs(parabolicGraphic[parabolicGraphic.size() - 1].y() - gridFunction[nextGridValue].y());
            nextGridValue++;
        }
    }
    penAndGraphics.push_back(std::make_pair(QPen(Qt::cyan, 1), parabolicGraphic));
    update();
}

double Plot::getParabolicRes(const double x) const
{
    if(linearCoeffs.size() != 2){
        return 0.0;
    }
    return linearCoeffs[0]*x + linearCoeffs[1];
}

double Plot::getLinearRes(const double x) const
{
    if(parabolicCoeffs.size() != 3){
        return 0.0;
    }
    return parabolicCoeffs[0]*pow(x, 2) + parabolicCoeffs[1]*x + parabolicCoeffs[2];
}


void Plot::create(const int xMax) // creating plot
{
    this->xMax = xMax;
}

void Plot::setGridPointsOnPlot(const std::vector<std::pair<double, double>> gridFunc)
{
    for(unsigned i = 0; i < gridFunc.size(); i++){
        gridFunction.append(QPointF(gridFunc[i].first, gridFunc[i].second));
        checkAndSetMax(gridFunction[i], VALUE);
    }

    update();
}

void Plot::addFunction(std::vector<QPointF> function, QPen pen)
{
    penAndGraphics.clear();
    if(!function.empty()){
        penAndGraphics.append(std::make_pair(pen, function));
    }
    update();
}

void Plot::addFunctions(QList<std::pair<QPen, std::vector<QPointF> > > listOfFuncs)
{
    penAndGraphics.clear();
    if(!listOfFuncs.empty()){
        for(int i = 0; i < listOfFuncs.size(); i++){
            penAndGraphics.append(listOfFuncs[i]);
        }
    }
    update();
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
            scaledCoeffX = double(rightOxLineEdge)/double(xMax);
            scaledCoeffY = double(upperOyLineEdge)/double(yMax);
            update();
        }
    }
    else if (type == VALUE){ // type is Y
        if(point.y() > yMax){
            yMax = point.y();
            scaledCoeffX = double(rightOxLineEdge)/double(xMax);
            scaledCoeffY = double(upperOyLineEdge)/double(yMax);
            update();
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



Plot::Plot(QWidget *parent) : QWidget(parent)
{
    setBackGroundColor(QColor(QLatin1String("#314350")));
    pen = new QPen(Qt::white, 2, Qt::PenStyle::SolidLine, Qt::PenCapStyle::RoundCap, Qt::PenJoinStyle::RoundJoin);
    setMinimumSize(350, 350); //fixex min size
    std::vector<std::pair<double, double>> gridFunc;
    const int a = Ng + Nc;
//    gridFunc.push_back(std::make_pair(-2.5*a, 84-Ng));
//    gridFunc.push_back(std::make_pair(-1.5*a, 73-Ng*2));
//    gridFunc.push_back(std::make_pair(-0.5*a, 63-Ng*3));
//    gridFunc.push_back(std::make_pair(0.5*a, 55-Ng*4));
//    gridFunc.push_back(std::make_pair(1.5*a, 47-Ng*5));

    gridFunc.push_back(std::make_pair(-4.0, 2.4));
    gridFunc.push_back(std::make_pair(-3.0, 3.7));
    gridFunc.push_back(std::make_pair(-2.0, 4.0));
    gridFunc.push_back(std::make_pair(-1.0, 3.9));
    gridFunc.push_back(std::make_pair(0.0, 4.8));
    gridFunc.push_back(std::make_pair(1.0, 4.7));
    gridFunc.push_back(std::make_pair(2.0, 4.0));
    gridFunc.push_back(std::make_pair(3.0, 3.1));
    gridFunc.push_back(std::make_pair(4.0, 2.4));
    gridFunc.push_back(std::make_pair(5.0, 1.7));

//    gridFunc.push_back(std::make_pair(1.0, 7.0));
//    gridFunc.push_back(std::make_pair(2.0, 7.0));
//    gridFunc.push_back(std::make_pair(3.0, 6.0));
//    gridFunc.push_back(std::make_pair(4.0, 7.0));
//    gridFunc.push_back(std::make_pair(5.0, 6.0));
//    gridFunc.push_back(std::make_pair(6.0, 5.0));
//    gridFunc.push_back(std::make_pair(7.0, 4.0));
//    gridFunc.push_back(std::make_pair(8.0, 4.0));
//    gridFunc.push_back(std::make_pair(9.0, 4.0));
//    gridFunc.push_back(std::make_pair(10.0, 3.0));
    setGridPointsOnPlot(gridFunc);
    double max = getMaxArgFromGrid();

    create(max);

    MNKApprox approx(gridFunc);
    linearCoeffs = approx.getLinearCoeffsForMNK();
    parabolicCoeffs = approx.getParabolicCoeffsForMNK();
    initPoints();


}

Plot::~Plot()
{
    delete pen;
}

