#include "gamebuilder.h"
#include <QJsonArray>
#include <QVector2D>
#include <QJsonObject>
#include <QJsonValue>
#include <QString>
#include "util.h"

GameBuilder::GameBuilder(AbstractFactory *factory)
    :m_balls(),m_table(nullptr),m_factory(factory)
{

}
GameBuilder::~GameBuilder()
{
    //in normal operation m_table is likely to be nullptr
    //and m_balls is likely to empty
    //this is only not the case if the director terminates the builder mid build
    delete m_table;
    for(Ball * b: m_balls)
    {
        delete b;
    }
}

void GameBuilder::addBall(const QJsonObject &ballJSon)
{
    Ball * ball = m_factory->makeBall(ballJSon);
    if(ball)
        m_balls.push_back(ball);
}

void GameBuilder::buildTable(const QJsonObject &tableJSon)
{
    //since poolgame only has one table we delete the old one
    //this is a noop if m_table is nullptr
    delete m_table;
    m_table = m_factory->makeTable(tableJSon);
}

PoolGame *GameBuilder::getGame()
{
    //create the game and reset the member variables
    PoolGame * result = new PoolGame(m_table,std::move(m_balls));
    m_table = nullptr;
    m_balls.clear();
    return result;
}

void GameBuilder::addBallGroup(const QJsonObject &ballJSon,const QJsonObject &tableJSon)
{

    Ball * ball = m_factory->makeBall(ballJSon);
    QVector2D d = QJsonValueToVector2D(tableJSon["size"]);
    ball->setPosition(d/2);
    float r = ball->radius();

    Ball * clone1 = ball->clone();
    clone1->changePosition(QVector2D(r*1.6,r*1.6));
    Ball * clone2 = ball->clone();
    clone2->changePosition(QVector2D(r*1.6,-r*1.6));
    Ball * clone3 = ball->clone();
    clone3->changePosition(QVector2D(r*3.2,0));
    Ball * clone4 = clone1->clone();
    clone4->changePosition(QVector2D(r*1.6,r*1.6));
    Ball * clone5 = clone2->clone();
    clone5->changePosition(QVector2D(r*1.6,-r*1.6));

    if(ball)
        m_balls.push_back(ball);
        m_balls.push_back(clone1);
        m_balls.push_back(clone2);
        m_balls.push_back(clone3);
        m_balls.push_back(clone4);
        m_balls.push_back(clone5);

}
