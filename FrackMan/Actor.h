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
    virtual ~Actor(){};
    virtual void doSomething() = 0;
    bool isAlive() const {return m_alive;};
    void setDead(){m_alive = false;};
    StudentWorld* getWorld() {return m_sw;};
    virtual bool annoyActor(unsigned int amt){return true;};
    
private:
    StudentWorld* m_sw;
    bool m_alive;
    
    
};

class ActivatingObject : public Actor
{
public:
    ActivatingObject(StudentWorld* world, int startX, int startY, int imageID,
                                     int soundToPlay);
    //virtual void move();
    
    /// Set number of ticks until this object dies
    //void setTicksToLive(){};
};

class OilBarrel : public ActivatingObject
{
public:
    OilBarrel(StudentWorld* world, int startX, int startY);
    void doSomething();
    ~OilBarrel() {setVisible(false);};
    
};

class Dirt : public GraphObject
{
public:
    Dirt(int x, int y);
    ~Dirt() {};

};

class Squirt : public Actor
{
public:
    Squirt(StudentWorld* sw, int x, int y, int travel, Direction dir);
    ~Squirt() {};
    void doSomething() ;
private:
    int m_count;
};

class FrackMan : public Actor
{
public:
    FrackMan(StudentWorld* sw, int x, int y);
    ~FrackMan() {};
    void doSomething();
    void increaseScore(int x) {m_score+= x;};
private:
    int m_life;
    int m_water;
    int m_sonar;
    int m_gold;
    int m_score;
};


class Boulder : public Actor
{
public:
    Boulder(StudentWorld* sw, int startX, int startY);
    virtual void move() {};
    //virtual bool canActorsPassThroughMe() const;
    void doSomething();
    
    bool isDirtUnder(int x, int y);
private:
    bool m_falling;
    
    int m_count = 0;
};

#endif // ACTOR_H_
