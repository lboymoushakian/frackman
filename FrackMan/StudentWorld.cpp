#include "StudentWorld.h"
#include <string>
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
        
        removeDeadGameObjects();
        
         if(m_barrelsleft == 0)
         {
             m_currlevel++;
             return GWSTATUS_FINISHED_LEVEL;
         }
        return GWSTATUS_CONTINUE_GAME;
    }


bool StudentWorld::isTooClose(int x, int y, int amt)
{
    for(list<Actor*>::iterator p = m_actors.begin(); p != m_actors.end(); p++)
    {
        if(((*p)->getX() - x) *((*p)->getX() - x) + ((*p)->getY() - y) * ((*p)->getY() - y) < amt)
            return true;
    }
    return false;
}
 void StudentWorld::cleanUp()
{
    delete m_frackman;
    for(int i = 0; i != 64; i++)
        for(int j = 0; j != 64; j++)
            if(m_dirt[i][j] != nullptr)
                delete m_dirt[i][j];
    
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
