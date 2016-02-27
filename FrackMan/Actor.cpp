#include "Actor.h"
#include "StudentWorld.h"
#include "GameController.h"


// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp
Dirt::Dirt(int x, int y)
:GraphObject(IID_DIRT, x, y, right, .25, 3)
{
    setVisible(true);
}
Protester::Protester(StudentWorld* sw, int x, int y, int image)
:Actor(sw,image, x, y, left,1.0, 0), m_pickedupnugget(false)
{
    setProtester();}

regularProtester::regularProtester(StudentWorld* sw, int x, int y)
:Protester(sw, x, y, IID_PROTESTER), m_restfor15(false), m_restfor15count(0),  m_currtick(0)
{
    setVisible(true);
    int ticksToWaitBetweenMoves = max(0, 3 - getWorld()->m_currlevel/4);
    m_restingticks = ticksToWaitBetweenMoves;
    setHealth(5);
    setSquaresToMove(randInt(8, 60));
}

hardcoreProtester::hardcoreProtester(StudentWorld * sw, int x, int y)
:Protester(sw, x, y, IID_HARD_CORE_PROTESTER), m_currtick(0), m_annoyed(false)
{
    setVisible(true);
    setHealth(20);
    int ticksToWaitBetweenMoves = max(0, 3 - getWorld()->m_currlevel/4);
    m_restingticks = ticksToWaitBetweenMoves;
}

FrackMan::FrackMan(StudentWorld* sw, int x, int y)
:Actor(sw, IID_PLAYER, x, y, right, 1.0, 0), m_score(0), m_water(5), m_sonar(1), m_health(10), m_gold(0)
{
    setVisible(true);}

Boulder::Boulder(StudentWorld* sw, int startX, int startY)
:Actor(sw, IID_BOULDER, startX, startY, down, 1.0, 1), m_count(0)
{
    setVisible(true);
    setBoulder();
    for(int i = startX; i != startX +4; i++)
        for(int j = startY; j != startY+4; j++)
        getWorld()->removeDirt(i, j);
}

Squirt::Squirt(StudentWorld* sw, int x, int y, int travel, Direction dir)
:Actor(sw, IID_WATER_SPURT, x, y, dir, 1.0, 1), m_count(travel)
{setVisible(true);}

OilBarrel::OilBarrel(StudentWorld* world, int startX, int startY)
:ActivatingObject(world, startX, startY, IID_BARREL, SOUND_FOUND_OIL)
{setVisible(false);
}

goldForFrackman::goldForFrackman(StudentWorld* world, int startX, int startY)
:ActivatingObject(world, startX, startY, IID_GOLD, SOUND_GOT_GOODIE)
{setVisible(false);}

goldForProtester::goldForProtester(StudentWorld* world, int startX, int startY)
:ActivatingObject(world, startX, startY, IID_GOLD, SOUND_PROTESTER_FOUND_GOLD)
{
    setVisible(true);
    setTicksToLive(getWorld()->maxInt(100, 300 - 10 * getWorld()->getLevel()));
}

ActivatingObject::ActivatingObject(StudentWorld* world, int startX, int startY, int imageID, int soundToPlay)
:Actor(world, imageID, startX, startY, right, 1.0, 2)
{}

SonarKit::SonarKit(StudentWorld* world, int startX, int startY)
:ActivatingObject(world, startX, startY, IID_SONAR, SOUND_GOT_GOODIE)
{
    setTicksToLive(getWorld()->maxInt(100, 300 - 10 * getWorld()->getLevel()));
    setVisible(true);
}

WaterPool::WaterPool(StudentWorld* world, int startX, int startY)
:ActivatingObject(world, startX, startY, IID_WATER_POOL, SOUND_GOT_GOODIE)
{
    setVisible(true);
    setTicksToLive(getWorld()->maxInt(100, 300 - 10 * getWorld()->getLevel()));
}

int regularProtester::restingTicks()
{
    return getWorld()->maxInt(0, 3-getWorld()->getLevel()/4);
}

void regularProtester::doSomething()
{
    if(isAlive() == false)
        return;
    if(getHealth() <= 0)
    {setDead();
        GameController::getInstance().playSound(SOUND_PROTESTER_GIVE_UP);
        getWorld()->increaseScore(100);return;}
    {
    if(m_currtick!=m_restingticks)
    {m_currtick++; return;}
    else
        m_currtick = 0;
    }
    
    
    if(m_restfor15count < 15 && m_restfor15 == true)
    {m_restfor15count++; return;}
    else
    {m_restfor15count = 0; m_restfor15 = false;}
    
    
    if(getSquares() == 0)
        setSquaresToMove( randInt(8, 60));
    
    if(closeToFrackman() == true && m_restfor15 == false && isFacingFrackman() == true)
    {
        GameController::getInstance().playSound(SOUND_PROTESTER_YELL);
        getWorld()->m_frackman->decreaseHealth(2);
        m_restfor15 = true;
        return;
    }
    
    if(canSeeFrackman() == true && closeToFrackman() == false && stuffInTheWay() == false)
    {
        setDirectiontoFrackman();
        setSquaresToMove(0);
        return;
    }
    
   
    else{
        setSquaresToMove(getSquares() -1);
        if(getSquares() <= 0)
        {
            int dir = randInt(0, 3);
            if(dir == 0)
            {if(getWorld()->isDirt(getX(), getY() + 1))
                   dir = randInt(1, 3);
            else
                setDirection(up);
                }
            if(dir == 1)
            { if(getWorld()->isDirt(getX(), getY() -1))
                    dir = randInt(2, 3);
                else
                    setDirection(down);
            }
            if(dir == 2)
            { if(getWorld()->isDirt(getX() -1, getY()))
                dir = 3;
            else
                setDirection(left);
            }
            if(dir == 3)
                setDirection(right);

            setSquaresToMove( randInt(8, 60));
        }
    
    }
    
    move();
    
}

void hardcoreProtester::doSomething()
{
    if(!isAlive())
        return;
    if(m_currtick!=m_restingticks)
    {m_currtick++; return;}
    else
        m_currtick = 0;
    
    if(getHealth() <= 0)
    {setDead();
        GameController::getInstance().playSound(SOUND_PROTESTER_GIVE_UP);
        getWorld()->increaseScore(250);
        return;}
    if(m_annoyed == true)
    {
        GameController::getInstance().playSound(SOUND_PROTESTER_ANNOYED);
        m_restingticks= getWorld()->maxInt(50, 100 - getWorld()->m_currlevel * 10);
        
        m_annoyed = false;
    }

    if(getSquares() == 0)
        setSquaresToMove( randInt(8, 60));
    if(closeToFrackman() == true && m_restfor15 == false && isFacingFrackman() == true)
    {
        GameController::getInstance().playSound(SOUND_PROTESTER_YELL);
        getWorld()->m_frackman->decreaseHealth(2);
        m_restfor15 = true;
        return;
    }
    if(canSeeFrackman() == true && closeToFrackman() == false && stuffInTheWay() == false)
    {
        setDirectiontoFrackman();
        setSquaresToMove(0);
        return;
    }
    else{
        setSquaresToMove(getSquares() -1);
        if(getSquares() <= 0)
        {
            int dir = randInt(0, 3);
            if(dir == 0)
            {if(getWorld()->isDirt(getX(), getY() + 1))
                dir = randInt(1, 3);
            else
                setDirection(up);
            }
            if(dir == 1)
            { if(getWorld()->isDirt(getX(), getY() -1))
                dir = randInt(2, 3);
            else
                setDirection(down);
            }
            if(dir == 2)
            { if(getWorld()->isDirt(getX() -1, getY()))
                dir = 3;
            else
                setDirection(left);
            }
            if(dir == 3)
                setDirection(right);
            
            setSquaresToMove( randInt(8, 60));
        }
        
    }

    
    move();
    
    
    
    
}


void Protester::move()
{
    if(getDirection() == up && getY() < 60 && !(getWorld()->isDirt(getX(), getY()+1)))
        moveTo(getX(), getY()+1);
    if(getDirection() == down && getY() > 0  && !(getWorld()->isDirt(getX(), getY()-1)))
        moveTo(getX(), getY()-1);
    if(getDirection() == left && getX() > 0 && !(getWorld()->isDirt(getX()-1, getY())))
        moveTo(getX() -1, getY());
    if(getDirection() == right && getX() < 60 && !(getWorld()->isDirt(getX()+1, getY())))
        moveTo(getX() + 1, getY());
}


void Protester::setDirectiontoFrackman()
{
    if(getWorld()->m_frackman->getY() > getY())
    {
        setDirection(up);
        if(!getWorld()->isDirt(getX(), getY()+1))
        moveTo(getX(), getY()+1);
    }
   else if( getWorld()->m_frackman->getY() < getY())
    {
        setDirection(down);
        if(!getWorld()->isDirt(getX(), getY()-1))
        moveTo(getX(), getY()-1);
        
    }
   else if( getWorld()->m_frackman->getX() < getX())
   {
       setDirection(left);
       if(!getWorld()->isDirt(getX()-1, getY()))
       moveTo(getX()-1, getY());
       
   }
   else if( getWorld()->m_frackman->getX() > getX())
   {
       setDirection(right);
       if(!getWorld()->isDirt(getX()+1, getY()))
       moveTo(getX()+1, getY());
       
   }
   
}

bool Protester::stuffInTheWay()
{
   if(getX() < getWorld()->m_frackman->getX() && getY() < getWorld()->m_frackman->getY())
   {for(int i = getX(); i != getWorld()->m_frackman->getX(); i++)
       for(int j = getY(); j != getWorld()->m_frackman->getY(); j++)
           if(getWorld()->isDirt(i, j))
               return true;}
       return false;
}
bool Protester::canSeeFrackman()
{
    if(getWorld()->m_frackman->getX() > getX() - 4 && getWorld()->m_frackman->getX() < getX() + 4)
        return true;
    if(getWorld()->m_frackman->getY() > getY() - 4 && getWorld()->m_frackman->getY() < getY() + 4)
        return true;
    return false;
    
}
bool Protester::isFacingFrackman()
{
    if(getDirection() == up)
        if(getWorld()->m_frackman->getY() > getY() && getWorld()->m_frackman->getX() > getX() - 4 && getWorld()->m_frackman->getX() < getX() + 4)
            return true;
    if(getDirection() == down)
        if(getWorld()->m_frackman->getY() < getY() && getWorld()->m_frackman->getX() > getX() - 4 && getWorld()->m_frackman->getX() < getX() + 4)
            return true;
    if(getDirection() == left)
        if(getWorld()->m_frackman->getX() < getX() && getWorld()->m_frackman->getY() > getY() - 4 && getWorld()->m_frackman->getY() < getY() + 4)
            return true;
    if(getDirection() == right)
        if(getWorld()->m_frackman->getX() > getX() && getWorld()->m_frackman->getY() > getY() - 4 && getWorld()->m_frackman->getY() < getY() + 4)
            return true;
    
    return false;
}

bool Protester::closeToFrackman()
{
    if(sqrt((getWorld()->m_frackman->getX() - getX()) *(getWorld()->m_frackman->getX() - getX()) + (getWorld()->m_frackman->getY() - getY()) * (getWorld()->m_frackman->getY() - getY())) < 4)
        return true;
    return false;
}

void OilBarrel::doSomething()
{
    if(!isAlive())
        return;
    
    if(getWorld()->m_frackman->getX() - getX() < 3 &&getWorld()->m_frackman->getX() - getX() > -3 &&
       getWorld()->m_frackman->getY() - getY() < 3 &&getWorld()->m_frackman->getY() - getY() > -3)
    { setDead();
    GameController::getInstance().playSound(SOUND_FOUND_OIL);
        getWorld()->m_frackman->increaseScore(1000);
        getWorld()->decreaseBarrels();}
    if(getWorld()->m_frackman->getX() - getX() < 5 &&getWorld()->m_frackman->getX() - getX() > -5 &&
       getWorld()->m_frackman->getY() - getY() < 5 &&getWorld()->m_frackman->getY() - getY() > -5)
    { setVisible(true); return;}
}

void SonarKit::doSomething()
{
    if(!isAlive())
        return;
    decreaseTicksToLive();
    if(getTicksToLive() <= 0)
        setDead();
    if(getWorld()->m_frackman->getX() - getX() < 3 &&getWorld()->m_frackman->getX() - getX() > -3 &&
       getWorld()->m_frackman->getY() - getY() < 3 &&getWorld()->m_frackman->getY() - getY() > -3)
    {
        setDead();
        GameController::getInstance().playSound(SOUND_GOT_GOODIE);
        getWorld()->m_frackman->increaseScore(75);
        getWorld()->m_frackman->increaseSonar();
        getWorld()->m_frackman->increaseSonar();
    }
}


void WaterPool::doSomething()
{
    if(!isAlive())
        return;
    decreaseTicksToLive();
    if(getTicksToLive() <= 0)
        setDead();
    if(getWorld()->m_frackman->getX() - getX() < 3 &&getWorld()->m_frackman->getX() - getX() > -3 &&
       getWorld()->m_frackman->getY() - getY() < 3 &&getWorld()->m_frackman->getY() - getY() > -3)
    {
        setDead();
        GameController::getInstance().playSound(SOUND_GOT_GOODIE);
        getWorld()->m_frackman->increaseScore(100);
        getWorld()->m_frackman->addWater();
    }
}
 void Squirt::doSomething()
{
   if(m_count == 0)
       setDead();
   
    if(getWorld()->isClosetoProtester(getX(), getY()))
       {
           getWorld()->m_protester->annoy(2);
           getWorld()->m_protester->setAnnoyed();
           setDead();
       }
    if(m_count > 0 &&getDirection() == right && !getWorld()->isDirt(getX()+1, getY()))
        moveTo(getX()+1, getY());
    else if(m_count > 0 &&getDirection() == left && !getWorld()->isDirt(getX()-1, getY()))
        moveTo(getX()-1, getY());
    else if(m_count > 0 &&getDirection() == up && !getWorld()->isDirt(getX(), getY()-1))
        moveTo(getX(), getY()+1);
    else if(m_count > 0 &&getDirection() == down && !getWorld()->isDirt(getX(), getY()+1))
        moveTo(getX(), getY()-1);
    else
        setDead();
    m_count--;
}

void goldForFrackman::doSomething()
{
    if(!isAlive())
        return;
   
    if(getWorld()->m_frackman->getX() - getX() < 3 &&getWorld()->m_frackman->getX() - getX() > -3 &&
       getWorld()->m_frackman->getY() - getY() < 3 &&getWorld()->m_frackman->getY() - getY() > -3)
    {
        setDead();
        GameController::getInstance().playSound(SOUND_GOT_GOODIE);
        getWorld()->m_frackman->increaseScore(10);
        getWorld()->m_frackman->increaseGold();
        
    }
    if(getWorld()->m_frackman->getX() - getX() < 4 &&getWorld()->m_frackman->getX() - getX() > -4 &&
       getWorld()->m_frackman->getY() - getY() < 4 &&getWorld()->m_frackman->getY() - getY() > -4)
    {
        setVisible(true);
        return;
    }
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

void goldForProtester::doSomething()
{
    if(!isAlive())
        return;
    decreaseTicksToLive();
    if(getTicksToLive() <= 0)
        setDead();
    if(getWorld()->isClosetoProtester(getX(), getY()))
    { setDead();
        GameController::getInstance().playSound(SOUND_PROTESTER_FOUND_GOLD);
        getWorld()->increaseScore(25);
    }
    
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
                    if(getX()-1 >= 0 && !getWorld()->isBoulder(getX()-1, getY()))
                        moveTo(getX()-1, getY());
                break;
            case KEY_PRESS_RIGHT:
                if(getDirection() != right)
                    setDirection(right);
                else
                    if(getX() +1 < 61 && !getWorld()->isBoulder(getX() + 1, getY()))
                        moveTo(getX() + 1, getY());
                break;
            case KEY_PRESS_UP:
                if(getDirection() != up)
                    setDirection(up);
                else
                    if(getY()+1 < 61 && !getWorld()->isBoulder(getX(), getY() + 1))
                        moveTo(getX(), getY()+1);
                break;
            case KEY_PRESS_DOWN:
                if(getDirection() != down)
                    setDirection(down);
                else
                    if(getY()-1>=0 && !getWorld()->isBoulder(getX(), getY()-1))
                        moveTo(getX(), getY()-1);
                break;
                
            case KEY_PRESS_ESCAPE:
                setDead();
                break;
            
            case KEY_PRESS_TAB:
                getWorld()->m_actors.push_front(new goldForProtester(getWorld(), getX(), getY()));
                break;
            case 'Z':
            case 'z':
               
                if(getWorld()->m_frackman->getSonar() > 0)
                {
                    getWorld()->setCloseVisible(getX(), getY(), 12);
                    getWorld()->m_frackman->decreaseSonar();
                }
                break;
            case KEY_PRESS_SPACE:
              if(getWorld()->m_frackman->getWater() != 0)
              {
                if(getDirection() == right) 
                   getWorld()->m_actors.push_front(new Squirt(getWorld(), getX()+3, getY(), 4, getDirection()));
                if(getDirection() == left)
                    getWorld()->m_actors.push_front(new Squirt(getWorld(), getX()-3, getY(), 4, getDirection()));
                if(getDirection() == up)
                    getWorld()->m_actors.push_front(new Squirt(getWorld(), getX(), getY()+3, 4, getDirection()));
                if(getDirection() == down)
                    getWorld()->m_actors.push_front(new Squirt(getWorld(), getX(), getY()-3, 4, getDirection()));
                  getWorld()->m_frackman->decreaseWater();
              }
                
                                                                          
                break;
                
                // etc…
        }
    }
}
          
