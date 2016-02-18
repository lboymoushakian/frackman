#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp
Dirt::Dirt(int x, int y)
:GraphObject(IID_DIRT, x, y, right, .25, 3)
{
    setVisible(true);
}

FrackMan::FrackMan(int x, int y)
:Actor(IID_PLAYER, x, y, right, 1.0, 0)
{}



Actor::Actor(int imageID, int startX, int startY, Direction dir, double size, int depth)
:GraphObject(imageID, startX, startY, dir, size, depth)
{
    
}

//GraphObject(int imageID, int startX, int startY, Direction dir = right, double size = 1.0, unsigned int depth = 0)