#ifndef STAGE3BALL_H
#define STAGE3BALL_H

#include <vector>

#include "ball.h"
#include "changeinpoolgame.h"


class Stage3Ball : public Ball
{
public:
    Stage3Ball(){}
    void setStrength(float strength){m_strength = strength;}
    // Ball interface
public:
    void draw(QPainter &p);

protected:
    float m_strength;
};

/**
 * @brief The CompositeBall class is the composite in the composite design pattern,
 * it stores a vector of children of type Stage2Ball. It can break apart to release these balls.
 */
class CompositeBall : public Stage3Ball
{
public:
    CompositeBall():m_containedMass(0)
    {
        Ball::setRadius(-1);
    }
    virtual ~CompositeBall();

    /**
     * @brief changeVelocity changes the velocity of the ball, if it changes to fast it may break apart
     * @param deltaV the change in velocity
     * @return the change to the poolgame list of balls, if the ball breaks it will be added to the remove list
     * and its children will be added to the add list
     */
    ChangeInPoolGame changeVelocity(const QVector2D &deltaV);

    /**
     * @brief mass get the total mass of the composite ball wich is the sum of its mass and the mass of its children
     * @return
     */
    float mass()const;

    /**
     * @brief draws the composite ball, if draw children is true it will also draw its children
     * @param p
     */
    void draw(QPainter &p);

    /**
     * @brief addBall to the composite
     * @param ball
     */
    void addBall(Ball* ball)
    {
        m_containedBalls.push_back(ball);
        m_containedMass += ball->mass();
    }

    /**
     * @brief setRadius sets the new radius of the ball, adjusting the radius of any children so they are stil contained
     * @param newRadius
     */
    void setRadius(float newRadius);

    Ball* clone();

protected:
    std::vector<Ball*> m_containedBalls;
    float m_containedMass;
    //here we decide whether or not to draw children
    bool drawChildren = true;
};

/**
 * @brief The SimpleStage2Ball class is the leaf in the composite design pattern,
 * all stage 3 balls that aren't composites are leaves
 */
class SimpleStage3Ball : public Stage3Ball
{
public:
    SimpleStage3Ball(){}
    ChangeInPoolGame changeVelocity(const QVector2D &deltaV);

    Ball clone();
};

#endif // STAGE3BALL_H
