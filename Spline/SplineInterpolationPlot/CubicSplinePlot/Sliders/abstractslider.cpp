/***************************************************************************
 *                                                                         *
 *   Copyright (C) 14.11.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#include "Sliders/abstractslider.h"

AbstractSlider::AbstractSlider(QWidget *parent)
    : QWidget{parent}
{

}

void AbstractSlider::addObserver(InterfaceObserver *observer)
{
    this->observers.append(observer);
}

void AbstractSlider::removeObserver(InterfaceObserver *observer)
{
    QList<InterfaceObserver*>::ConstIterator it = observers.constBegin();
    for (; it != observers.constEnd(); ++it) {
        if (*it == observer) {
            observers.erase(it);
            return;
        }
    }
}

void AbstractSlider::notifyObservers() const
{
    for (auto obs : observers) {
        obs->updateObserver(value);
    }
}


QString AbstractSlider::getNameByChangeType() const
{
    return "Delta ";
}


int AbstractSlider::getValue() const
{
    return value;
}

void AbstractSlider::setValue(int value)
{
    this->value = value;
    notifyObservers();
}
