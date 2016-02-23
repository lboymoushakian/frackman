#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameConstants.h"
class StudentWorld;

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class Actor : public GraphObject
{
public:
    Actor(StudentWorld* sw, int imageID, int startX, int startY, Direction dir = right, double size = 1.0, int depth = 0) ;
    ~Actor(){};
    virtual void doSomething() = 0;
    bool isAlive() const {return m_alive;};
    void setDead(){m_alive = false;};
    StudentWorld* getWorld() {return m_sw;};
    virtual bool annoyActor(unsigned int amt){return true;};
    
private:
    StudentWorld* m_sw;
    bool m_alive;
    
    
};

class Dirt : public GraphObject
{
public:
    Dirt(int x, int y);
    ~Dirt() {};

};

class FrackMan : public Actor
{
public:
    FrackMan(StudentWorld* sw, int x, int y);
    ~FrackMan() {};
    void doSomething();
private:
    int m_life;
    int m_water;
    int m_sonar;
    int m_gold;
};


class Boulder : public Actor
{
public:
    Boulder(StudentWorld* world, int startX, int startY);
    virtual void move() {};
    //virtual bool canActorsPassThroughMe() const;
    void doSomething();
    bool isStable() {return m_stable;};
    void setWaiting() {m_stable = false; m_waiting = true;};
    bool isWaiting() {return m_waiting;};
    void setFalling() {m_falling = true;};
    bool isFalling() {return m_falling;};
    bool isDirtUnder(int x, int y);
private:
    bool m_stable;
    bool m_falling;
    bool m_waiting;
    int m_count = 0;
};

#endif // ACTOR_H_
