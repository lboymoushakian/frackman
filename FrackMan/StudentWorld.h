#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <string>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
	StudentWorld(std::string assetDir)
	 : GameWorld(assetDir)
	{
        
	}

	virtual int init()
	{
        for(int i = 0; i != 30; i++)
            for(int j = 0; j != 30; j++)
               m_dirt[i][j] = new Dirt(i,j);
        m_frackman = new FrackMan(30, 60);
        
        
        
        return GWSTATUS_CONTINUE_GAME;
	}

	virtual int move()
	{
		  // This code is here merely to allow the game to build, run, and terminate after you hit enter a few times.
		  // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
        m_frackman->doSomething();
        //decLives();
		return GWSTATUS_CONTINUE_GAME;
	}

	virtual void cleanUp()
	{
	}

private:
    FrackMan* m_frackman;
    Dirt* m_dirt[64][64];
};

#endif // STUDENTWORLD_H_