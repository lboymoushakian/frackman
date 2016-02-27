#include "StudentWorld.h"
#include <string>
#include <cmath>
using namespace std;

int randInt(int min, int max)
{
    if (max < min)
        std::swap(max, min);
    static std::random_device rd;
    static std::mt19937 generator(rd());
    std::uniform_int_distribution<> distro(min, max);
    return distro(generator);
}


GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

StudentWorld::~StudentWorld()
{
    delete m_frackman;
    for(int i = 0; i != 64; i++)
        for(int j = 0; j != 64; j++)
            if(m_dirt[i][j] != nullptr)
                delete m_dirt[i][j];
    
}

void StudentWorld::removeDeadGameObjects()
{
   
    for(list<Actor*>::iterator p = m_actors.begin(); p != m_actors.end(); p++)
    {
        if(!((*p)->isAlive()))
        {
            delete *p;
            p  = m_actors.erase(p);
            }
        
    }
    
}

string StudentWorld::Format(int score, int level, int lives, int health, int squirts, int gold, int sonar, int barrels)
{
    string thescore = to_string(score);
    for(int i = 0; i != 7; i++)
        if(thescore.size() < i)
            thescore = "0" + thescore;
    string thelevel = to_string(level);
    if(thelevel.size() == 1)
        thelevel = " " + thelevel;
    double dhealth = health;
    
    int healthpercent = (dhealth / 10) * 100;
    string thehealth = to_string(healthpercent);

    
    
    string thewater = to_string(squirts);
    if(thewater.size() == 1)
        thewater = " " + thewater;
    string thegold = to_string(gold);
    if(thegold.size() == 1)
        thegold = " " + thegold;
    string thesonar = to_string(sonar);
    if(thesonar.size() == 1)
        thesonar = " " + thesonar;
    string thebarrels = to_string(barrels);
    if(thebarrels.size() == 1)
        thebarrels = " " + thebarrels;
    return "Scr: " + thescore + "  Lvl: " + thelevel + "  Lives: " + to_string(lives) +
    "  Hlth: " + thehealth + " %  Wtr: " + thewater + "  Gld: " + thegold +
    "  Sonar " + thesonar + "  Oil Left: " + thebarrels;
}

void StudentWorld::setDisplayText()
{
    int score = getScore();
    int level = getLevel();
    int lives = getLives();
    int health = m_frackman->getHealth();
    int squirts = m_frackman->getWater();
    int gold = m_frackman->getGold();
    int sonar = m_frackman->getSonar();
    int barrels = m_barrelsleft;
    
    string s = Format(score, level, lives,
                                                      health, squirts, gold, sonar, barrels);
    setGameStatText(s);}

int StudentWorld::move()
    {
        // This code is here merely to allow the game to build, run, and terminate after you hit enter a few times.
        // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
        m_frackman->doSomething();
        for(list<Actor*>::iterator p = m_actors.begin(); p != m_actors.end(); p++)
            (*p)->doSomething();
        
        int G = m_currlevel * 25 + 300;
        if(randInt(0, G) == 1)
        {
            if(randInt(0, 4) == 1)
                m_actors.push_front(new SonarKit(this, 0, 60));
            else
            {
                int x = randInt(0, 60);
                int y = randInt(0, 60);
                while(isDirt4x4(x, y) == false)
                {
                    x = randInt(0, 60);
                    y = randInt(0, 60);
                }
            m_actors.push_front(new WaterPool(this, x, y));
            }
        }
        int ticksbetweenprotesters = maxInt(25, 200 - m_currlevel);
        int targetprotesters = minInt(15, 2 + m_currlevel * 1.5);
        int probabilityOfHardcore = minInt(90, m_currlevel * 10 + 30);
        
        if(m_ticks == 0)
        {
            if(randInt(0, 100) < probabilityOfHardcore)
                m_actors.push_front(new hardcoreProtester(this, 60, 60));
            else
                m_actors.push_front(new regularProtester(this, 60, 60));
            m_lastprotester = 0;
        }
        if(m_lastprotester > ticksbetweenprotesters && m_protesters < targetprotesters)
        {
            if(randInt(0, 100) < probabilityOfHardcore)
                m_actors.push_front(new hardcoreProtester(this, 60, 60));
            else
                m_actors.push_front(new regularProtester(this, 60, 60));
            m_lastprotester = 0;
        }
        
        removeDeadGameObjects();
        
        setDisplayText();
        m_ticks++;
        m_lastprotester++;
        
         if(m_barrelsleft == 0)
         {
             m_currlevel++;
             m_ticks = 0;
             return GWSTATUS_FINISHED_LEVEL;
         }
        if(m_frackman->getHealth()== 0)
        {
            decLives();
        return GWSTATUS_PLAYER_DIED;}
            
        return GWSTATUS_CONTINUE_GAME;
    }


bool StudentWorld::isTooClose(int x, int y, int amt)
{
    for(list<Actor*>::iterator p = m_actors.begin(); p != m_actors.end(); p++)
    {
        if(sqrt(((*p)->getX() - x) *((*p)->getX() - x) + ((*p)->getY() - y) * ((*p)->getY() - y)) < amt)
            return true;
    }
    return false;
}

void StudentWorld::setCloseVisible(int x, int y, int amt)
{
    for(list<Actor*>::iterator p = m_actors.begin(); p != m_actors.end(); p++)
        if(sqrt(((*p)->getX() - x) *((*p)->getX() - x) + ((*p)->getY() - y) * ((*p)->getY() - y)) < amt)
            (*p)->setVisible(true);
}
 void StudentWorld::cleanUp()
{
    delete m_frackman;
    for(int i = 0; i != 64; i++)
        for(int j = 0; j != 64; j++)
            if(m_dirt[i][j] != nullptr)
                delete m_dirt[i][j];
    for(list<Actor*>::iterator p = m_actors.begin(); p != m_actors.end(); p++)
    {delete *p;
         m_actors.erase(p);}
    
}

bool StudentWorld::isDirt(int x, int y)
{
    if(m_dirt[x][y] != nullptr)
        return true;
    return false;
}
bool StudentWorld::isDirt4x4(int x, int y)
{
    for(int i = x; i != x +4; i++)
        for(int j = y; j != y + 4; j++)
            if(isDirt(i, j))
                return false;
    return true;
}

bool StudentWorld::isBoulder(int x, int y)
{
    for(list<Actor*>::iterator p = m_actors.begin(); p != m_actors.end(); p++)
        if((*p)->isBoulder() && (*p)->getX() > x -4 &&(*p)->getX() < x+4  && (*p)->getY() > y-4 && (*p)->getY() < y+4)
            return true;
    return false;
            
}
bool StudentWorld::isClosetoProtester(int x, int y)
{
    for(list<Actor*>::iterator p = m_actors.begin(); p != m_actors.end(); p++)
        if((*p)->isProtester() && (*p)->getX() > x -3 &&(*p)->getX() < x+3  && (*p)->getY() > y-3 && (*p)->getY() < y+3)
        {
            m_protester = *p;
            return true;
        }
    return false;
}

int StudentWorld::minInt(int first, int second)
{
    if(first > second)
        return second;
    return first;
}

int StudentWorld::maxInt(int first, int second)
{
    if(first < second)
        return second;
    return first;
}
// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp
