/***************************************************************************
 *                                                                         *
 *   Copyright (C) 14.11.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef OBSERVER_H
#define OBSERVER_H

class InterfaceObserver{
public:
    virtual void updateObserver(int xEdge)= 0;
    virtual ~InterfaceObserver() = default;
};



#endif // OBSERVER_H
