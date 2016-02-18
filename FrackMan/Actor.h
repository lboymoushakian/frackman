#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class Actor : public GraphObject
{
public:
    Actor(int imageID, int startX, int startY, Direction dir = right, double size = 1.0, int depth = 0) ;
    ~Actor(){};
    virtual void doSomething() = 0;
    
    
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
    FrackMan(int x, int y);
    ~FrackMan() {};
    void doSomething() {};
};


#endif // ACTOR_H_
