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
            m_actors.erase(p);
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
        removeDeadGameObjects();
        
         
        return GWSTATUS_CONTINUE_GAME;
    }


bool StudentWorld::isTooClose(int x, int y)
{
    for(list<Actor*>::iterator p = m_actors.begin(); p != m_actors.end(); p++)
    {
        if(((*p)->getX() - x) *((*p)->getX() - x) + ((*p)->getY() - y) * ((*p)->getY() - y) < 7)
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

int StudentWorld::minInt(int first, int second)
{
    if(first > second)
        return second;
    return first;
}
// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp
