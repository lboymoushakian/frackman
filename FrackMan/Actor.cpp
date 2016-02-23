#include "Actor.h"
#include "StudentWorld.h"
#include "GameController.h"


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
Boulder::Boulder(StudentWorld* world, int startX, int startY)
:Actor(world, IID_BOULDER, startX, startY, down, 1.0, 1), m_stable(true)
{
    setVisible(true);
    for(int i = startX; i != startX +4; i++)
        for(int j = startY; j != startY+4; j++)
        getWorld()->removeDirt(i, j);
}


Actor::Actor(StudentWorld* sw, int imageID, int startX, int startY, Direction dir, double size, int depth)
:GraphObject(imageID, startX, startY, dir, size, depth), m_sw(sw)
{
    setVisible(true);
}

void Boulder::doSomething()
{
    if(isAlive() == false)
        return;
    if(isStable() && isDirtUnder(getX(), getY()))
           return;
    else if(isStable() && !isDirtUnder(getX(), getY()))
            setWaiting();
    if(isWaiting() && m_count < 30)
    {  m_count++; return;}
    if (isWaiting() &&m_count >=30)
        setFalling();
    if(isFalling() )
    {
        if(getY() -1 >=0 && !isDirtUnder(getX(), getY()))
        moveTo(getX(), getY() -1);
    }
        
    
}

bool Boulder::isDirtUnder(int x, int y)
{
    for(int i = getX(); i != getX() + 4; i++)
        if(getWorld()->isDirt(i, getY()))
            return true;
    return false;
    
}

void FrackMan::doSomething()
{
    int ch;
    for(int i = getX(); i != getX()+4; i++)
        for(int j = getY(); j != getY() + 4; j++)
        {
            if(getWorld()->isDirt(i, j) &&getX()>=0 && getY()>=0 &&getX()<61 && getY()<61)
            {GameController::getInstance().playSound(SOUND_DIG);
                getWorld()->removeDirt(i, j);}
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
                break;
                
            case KEY_PRESS_ESCAPE:
                setDead();
                break;
            case KEY_PRESS_SPACE:
                //squirt
                break;
            case KEY_PRESS_TAB:
                //gold
                break;
            case 'Z':
            case 'z':
                //sonar
                break;
                
                // etc…
        }
    }
}
          
