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
{
    setVisible(true);
}

void FrackMan::doSomething()
{
    int ch;
    for(int i = getX(); i != getX()+4; i++)
        for(int j = getY(); j != getY() + 4; j++)
        {
            if(m_sw->m_dirt[i][j] != nullptr &&getX()>=0 && getY()>=0 &&getX()<61 && getY()<61)
            {delete m_sw->m_dirt[i][j];
               m_sw-> m_dirt[i][j] = nullptr;}
        }
    if (getWorld()->getKey(ch) == true)
    {
        // user hit a key this tick!
        switch (ch)
        {
            case KEY_PRESS_LEFT:
                if(getDirection() != left)
                    setDirection(left);
                else
                    if(getX()-1 >= 0)
                    moveTo(getX()-1, getY());
                break;
            case KEY_PRESS_RIGHT:
               if(getDirection() != right)
                   setDirection(right);
                else
                    if(getX() +1 < 61)
                    moveTo(getX() + 1, getY());
                break;
            case KEY_PRESS_UP:
                if(getDirection() != up)
                    setDirection(up);
                else
                    if(getY()+1 < 61)
                    moveTo(getX(), getY()+1);
                break;
            case KEY_PRESS_DOWN:
                if(getDirection() != down)
                    setDirection(down);
                else
                    if(getY()-1>=0)
                    moveTo(getX(), getY()-1);
            
                // etc…
        }
    }
}

//GraphObject(int imageID, int startX, int startY, Direction dir = right, double size = 1.0, unsigned int depth = 0)