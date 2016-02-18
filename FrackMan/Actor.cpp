#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp
Dirt::Dirt(int x, int y)
:GraphObject(IID_DIRT, x, y, right, .25, 3)
{
    setVisible(true);
}

FrackMan::FrackMan(StudentWorld* sw, int x, int y)
:Actor(sw, IID_PLAYER, x, y, right, 1.0, 0)
{
    setVisible(true);}



Actor::Actor(StudentWorld* sw, int imageID, int startX, int startY, Direction dir, double size, int depth)
:GraphObject(imageID, startX, startY, dir, size, depth), m_sw(sw)
{}

void FrackMan::doSomething()
{
    int ch;
    if (getWorld()->getKey(ch) == true)
    {
        // user hit a key this tick!
        switch (ch)
        {
            case KEY_PRESS_LEFT:
                if(getDirection() != left)
                    setDirection(left);
                else
                moveTo(getX()-1, getY());
                break;
            case KEY_PRESS_RIGHT:
               if(getDirection() != right)
                   setDirection(right);
                else
                    moveTo(getX() + 1, getY());
                break;
            case KEY_PRESS_UP:
                if(getDirection() != up)
                    setDirection(up);
                else
                    moveTo(getX(), getY()+1);
                break;
            case KEY_PRESS_DOWN:
                if(getDirection() != down)
                    setDirection(down);
                else
                    moveTo(getX(), getY()-1);
            
                // etc…
        }
    }
}

//GraphObject(int imageID, int startX, int startY, Direction dir = right, double size = 1.0, unsigned int depth = 0)