#include "stage2ball.h"
#include <cmath>

void Stage2Ball::draw(QPainter &p)
{
    p.setPen(Qt::black);
    p.setBrush(QBrush(m_colour));
    p.drawEllipse(m_position.toPointF(),m_radius,m_radius);
}

CompositeBall::~CompositeBall()
{
    for(Ball * b: m_containedBalls)
    {
        delete b;
    }
}

ChangeInPoolGame CompositeBall::changeVelocity(const QVector2D &deltaV)
{
    float energyOfCollision = mass()*deltaV.lengthSquared();
    if(energyOfCollision>m_strength)
    {
        float energyPerBall = energyOfCollision/m_containedBalls.size();
        QVector2D pointOfCollision((-deltaV.normalized())*m_radius);
        //for each component ball
        for(Ball * b: m_containedBalls)
        {
            b->setVelocity(m_velocity + sqrt(energyPerBall/b->mass())*(b->position()-pointOfCollision).normalized());
            b->setPosition(m_position+b->position());
        }
        ChangeInPoolGame change({this},std::move(m_containedBalls));
        m_containedBalls.clear();
        return change;
    }
    m_velocity += deltaV;
    return ChangeInPoolGame();
}

float CompositeBall::mass()const
{
    return m_mass+m_containedMass;
}

void CompositeBall::draw(QPainter &p)
{
    Stage2Ball::draw(p);

    if(drawChildren)
    {
        //recursively draw children, translating the painter
        //so that the children are drawn realative to the parent
        p.translate(m_position.toPointF());
        for(Ball * b: m_containedBalls)
        {
            b->draw(p);
        }
        p.translate(-m_position.toPointF());
    }

}

void CompositeBall::setRadius(float newRadius)
{
    if(m_radius==-1)
        m_radius = newRadius;
    else
    {
        float ratio = newRadius/radius();
        m_radius = newRadius;
        //recursively decrease the radius of children
        for(Ball * b: m_containedBalls)
        {
            b->setRadius(b->radius()*ratio);
            b->setPosition(b->position()*ratio);
        }
    }
}

ChangeInPoolGame SimpleStage2Ball::changeVelocity(const QVector2D &deltaV)
{
    if(mass()*deltaV.lengthSquared()>m_strength)
        return ChangeInPoolGame({this});
    m_velocity += deltaV;
    return ChangeInPoolGame();
}

Ball* SimpleStage2Ball::clone(){
    SimpleStage2Ball *b = new SimpleStage2Ball();

    b->setPosition(m_position);
    b->setVelocity(m_velocity);
    b->setRadius(m_radius);
    b->setMass(m_mass);
    b->setColour(m_colour);
    b->setStrength(m_strength);
    return static_cast<Ball*>(b);
}

Ball* CompositeBall::clone(){
    CompositeBall *c = new CompositeBall();
    for(Ball* b:m_containedBalls){
        c->addBall(b->clone());
    }
    c->setPosition(m_position);
    c->setVelocity(m_velocity);
    c->setRadius(m_radius);
    c->setMass(m_mass);
    c->setColour(m_colour);
    c->setStrength(m_strength);

    return static_cast<Ball*>(c);
}
