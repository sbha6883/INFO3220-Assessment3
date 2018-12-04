#ifndef MEMENTO_H
#define MEMENTO_H

#include "poolgame.h"

class Memento{
//public:
//    virtual ~Memento();

private:
    Memento(std::vector<Ball*> stateOfBalls)
     :m_state (stateOfBalls)
    {
    }

    std::vector<Ball*> getSavedState()    //return the m_state. This function is private so it can only be called by the friend class PoolGame, which is the originator in memento design pattern.
    {
        return m_state;     //stores a list of balls' information in a Ball vector, which are the balls' deep copies given by the Originator (the poolgame class)

    const std::vector<Ball*> m_state;
    friend class PoolGame; //poolgame.h is our originator
};

#endif // MEMENTO_H
