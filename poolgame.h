#ifndef POOLGAME_H
#define POOLGAME_H


#include <vector>
#include <QPainter>
#include <QSize>

#include "table.h"
#include "ball.h"

#include "changeinpoolgame.h"
#include "memento.h"

/**
 * @brief The PoolGame class runs the pool game, it is in charge of the physics of the pool game as well as
 * drawing the game
 */
class PoolGame
{
public:
    /**
     * @brief PoolGame constructor
     * @param m_table a pointer to a Table object, Poolgame takes ownership of this pointer
     * @param balls a vector of pointers to balls, Poolgame takes ownership of all the contained pointers
     */
    PoolGame(Table * m_table,std::vector<Ball*> balls)
        :m_table(m_table),m_balls(balls)
    {}

    ~PoolGame();

    /**
     * @brief simulate one timestep of the game
     * @param timeStep is the period of time that this timestep is simulating
     */
    void simulateTimeStep(float timeStep);

    /**
     * @brief draws all elements of the game, table and balls in that order
     * @param p is the painter which is used to paint the object
     */
    void draw(QPainter &p);

    /**
     * @brief size
     * @return the size of the game
     */
    QSize size(){return QSize(m_table->width(),m_table->height());}

    /*   void set(std::vector<Ball*> state){
           m_states = state;
       }  */

       Memento* saveToMemento();  // create m_states and pass it to memento when it is called.

       void restoreFromMemento(Memento memento);         //replace the balls (m_balls vector) with ball copies in a given memento object when it is called.


   private:
       /**
        * @brief collide two balls if they are in contact
        * @param b1
        * @param b2
        * @return the change in the pool game after the collision
        */
       ChangeInPoolGame collide(Ball *b1, Ball *b2);


       Table * m_table;
       std::vector<Ball*> m_balls;

       std::vector<Ball*> m_states;     //deep copy of each balls in current m_ball vector, will be passed to memento to be saved as a snapshot of the game.
   };

   #endif // POOLGAME_H
