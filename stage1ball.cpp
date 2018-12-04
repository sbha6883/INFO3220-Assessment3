#include "stage1ball.h"

Stage1Ball::Stage1Ball()
{

}

void Stage1Ball::draw(QPainter &p)
{
    p.setPen(Qt::black);
    p.setBrush(QBrush(m_colour));
    p.drawEllipse(m_position.toPointF(),m_radius,m_radius);
}

Ball* Stage1Ball::clone(){
    Stage1Ball *b = new Stage1Ball();
    b->setPosition(m_position);
    b->setVelocity(m_velocity);
    b->setRadius(m_radius);
    b->setMass(m_mass);
    b->setColour(m_colour);

    return static_cast<Ball*>(b);
}
