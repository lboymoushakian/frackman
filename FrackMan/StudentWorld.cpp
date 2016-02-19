#include "StudentWorld.h"
#include <string>
using namespace std;

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
// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp
