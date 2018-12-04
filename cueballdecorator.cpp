#include "cueballdecorator.h"
CueBallDecorator::CueBallDecorator(Ball *b, Dialog *parent)
    :BallDecorator(b),clicked(false),m_parent(parent)
{
    //connect dialog signals to cueball slots so that this class is notified when the mouse is used
    connect(m_parent,&Dialog::mousePressed,this,&CueBallDecorator::mousePressed);
    connect(m_parent,&Dialog::mouseMoved,this,&CueBallDecorator::mouseMoved);
    connect(m_parent,&Dialog::mouseReleased,this,&CueBallDecorator::mouseReleased);
}

void CueBallDecorator::draw(QPainter &p)
{
    m_ball->draw(p);
    if(clicked)
        p.drawLine(mousePos.toPointF(),m_ball->position().toPointF());
}

void CueBallDecorator::mousePressed(QMouseEvent *event)
{
    if(velocity().lengthSquared()<0.001 && (QVector2D(event->pos())-position()).length() < radius())
    {
        clicked = true;
        m_parent->saveState();

        mousePos = QVector2D(event->pos());
    }
}

void CueBallDecorator::mouseMoved(QMouseEvent *event)
{
    if(clicked)
    {
        mousePos = QVector2D(event->pos());
    }

}

void CueBallDecorator::mouseReleased(QMouseEvent *event)
{
    if(clicked)
    {
        clicked = false;
        setVelocity(4*(m_ball->position()-QVector2D(event->pos())));

    }
}

Ball* CueBallDecorator::clone(){
    Ball* b = m_ball->clone();
    CueBallDecorator *c = new CueBallDecorator(b,m_parent);
    return static_cast<Ball*>(c);
}
