#ifndef ORIGINATOR_H
#define ORIGINATOR_H

#include "memento.h"

class Originator{

public:
    Originator(){
    }

    void set(std::vector<Ball*> ballState){
        m_ballState = ballState;
    }

    Memento* saveToMemento(){
        return new Memento(m_ballState);
    }

    void restoreFromMemento(Memento memento)
    {
        m_ballState = memento.getSavedState();
    }

private:
    std::vector<Ball*> m_ballState;
};


#endif // ORIGINATOR_H
