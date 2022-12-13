/***************************************************************************
 *                                                                         *
 *   Copyright (C) 14.11.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef SUBJECT_H
#define SUBJECT_H
#include <QList>
#include "Observer.h"

class InterfaceSubject
{
public:
    virtual ~InterfaceSubject() = default;
    virtual void addObserver(InterfaceObserver* observer) = 0;
    virtual void removeObserver(InterfaceObserver* observer) = 0;
    virtual void notifyObservers() const = 0;
};

#endif // SUBJECT_H
