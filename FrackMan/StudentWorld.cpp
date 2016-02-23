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
