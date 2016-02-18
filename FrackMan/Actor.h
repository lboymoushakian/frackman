#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
class StudentWorld;

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class Actor : public GraphObject
{
public:
    Actor(StudentWorld* sw, int imageID, int startX, int startY, Direction dir = right, double size = 1.0, int depth = 0) ;
    ~Actor(){};
    virtual void doSomething() = 0;
    StudentWorld* getWorld() {return m_sw;};
    
    StudentWorld* m_sw;
    
    
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
};


#endif // ACTOR_H_
