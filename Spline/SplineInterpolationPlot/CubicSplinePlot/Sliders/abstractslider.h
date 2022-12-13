/***************************************************************************
 *                                                                         *
 *   Copyright (C) 14.11.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef ABSTRACTSLIDER_H
#define ABSTRACTSLIDER_H


#include <QBoxLayout>
#include <QWidget>
#include "PatternObserver/Subject.h"


class AbstractSlider : public QWidget, InterfaceSubject
{
    Q_OBJECT
public:
    explicit AbstractSlider(QWidget *parent = nullptr);
    virtual QBoxLayout* createSlider(QBoxLayout& layout, Qt::Orientation sliderOrientation, const int left, const int right, const int curr) = 0;
    void addObserver(InterfaceObserver *observer);
    void removeObserver(InterfaceObserver *observer);
    virtual ~AbstractSlider() = default;
    int getValue() const;
    virtual void setValue(int value);

signals:

protected:
    void notifyObservers() const;
    int value = 0;
    QString getNameByChangeType() const;
    QList<InterfaceObserver*> observers;

};

#endif // ABSTRACTSLIDER_H
