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
Boulder::Boulder(StudentWorld* sw, int startX, int startY)
:Actor(sw, IID_BOULDER, startX, startY, down, 1.0, 1), m_count(0)
{
    setVisible(true);
    for(int i = startX; i != startX +4; i++)
        for(int j = startY; j != startY+4; j++)
        getWorld()->removeDirt(i, j);
}

Squirt::Squirt(StudentWorld* sw, int x, int y, int travel, Direction dir)
:Actor(sw, IID_WATER_SPURT, x, y, dir, 1.0, 1), m_count(travel)
{setVisible(true);}

OilBarrel::OilBarrel(StudentWorld* world, int startX, int startY)
:ActivatingObject(world, startX, startY, IID_BARREL, SOUND_FOUND_OIL)
{setVisible(false);}
ActivatingObject::ActivatingObject(StudentWorld* world, int startX, int startY, int imageID, int soundToPlay)
:Actor(world, imageID, startX, startY, right, 1.0, 2)
{}


 void Squirt::doSomething()
{
   if(m_count == 0)
       setDead();
    if(m_count > 0 &&getDirection() == right && !getWorld()->isDirt(getX()+1, getY()))
        moveTo(getX()+1, getY());
    else if(m_count > 0 &&getDirection() == left)
        moveTo(getX()-1, getY());
    else if(m_count > 0 &&getDirection() == up)
        moveTo(getX(), getY()+1);
    else if(m_count > 0 &&getDirection() == down)
        moveTo(getX(), getY()-1);
    else
        setDead();
    m_count--;
}


Actor::Actor(StudentWorld* sw, int imageID, int startX, int startY, Direction dir, double size, int depth)
:GraphObject(imageID, startX, startY, dir, size, depth), m_sw(sw)
{
    setVisible(true);
    m_alive = true;
}

void Boulder::doSomething()
{
    if(isAlive() == false)
        return;
    if(isDirtUnder(getX(), getY())==true)
        return;
     if(isDirtUnder(getX(), getY())==false)
         m_count++;
    if(m_count >-1 )
    {
        if(getY() -1 >=0 /*&& isDirtUnder(getX(), getY()) == false*/)
        moveTo(getX(), getY() -1);
    }
        
    
}

bool Boulder::isDirtUnder(int x, int y)
{
    for(; x != x+ 4; x++)
        if(getWorld()->isDirt(x, y-1))
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
            
            case KEY_PRESS_TAB:
                //gold
                break;
            case 'Z':
            case 'z':
                //sonar
                break;
            case KEY_PRESS_SPACE:
              if(getDirection() == right)  //m_actors.push_front(new Boulder(this, x, y))
                   getWorld()->m_actors.push_front(new Squirt(getWorld(), getX()+3, getY(), 4, getDirection()));
                if(getDirection() == left)
                    getWorld()->m_actors.push_front(new Squirt(getWorld(), getX()-3, getY(), 4, getDirection()));
                if(getDirection() == up)
                    getWorld()->m_actors.push_front(new Squirt(getWorld(), getX(), getY()+3, 4, getDirection()));
                if(getDirection() == down)
                    getWorld()->m_actors.push_front(new Squirt(getWorld(), getX(), getY()-3, 4, getDirection()));
                
                                                                          
                break;
                
                // etc…
        }
    }
}
          
