/***************************************************************************
 *                                                                         *
 *   Copyright (C) 14.11.2022 by Kulikov Pavel                             *
 *                                                                         *
 *   https://github.com/Crystal2033                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef OBSERVER_H
#define OBSERVER_H
typedef enum {XEDGE} CHANGE_TYPE;

class InterfaceObserver{
public:
    virtual void updateObserver(int xEdge, const CHANGE_TYPE)= 0;
    virtual ~InterfaceObserver() = default;
};



#endif // OBSERVER_H
