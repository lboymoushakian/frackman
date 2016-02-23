#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <string>
#include <random>
//using namespace std;


// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp


// Return a random int from min to max, inclusive
int randInt(int min, int max);


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
            for(int j = 0; j != 59; j++)
               m_dirt[i][j] = new Dirt(i,j);
        for(int i = 34; i != 64; i++)
            for (int j = 0; j != 59; j++)
                m_dirt[i][j]= new Dirt(i, j);
        m_frackman = new FrackMan(this, 30, 60);
        
        int B = minInt(m_currlevel / 2 + 2, 6);
        for(int i = 0; i != B; i++)
        {
            m_actors[m_numactors] = new Boulder(this, randInt(0, 60), randInt(20, 56));
            m_numactors++;
            
        }
        
        return GWSTATUS_CONTINUE_GAME;
	}
    
    ~StudentWorld();
	virtual int move()
	{
		  // This code is here merely to allow the game to build, run, and terminate after you hit enter a few times.
		  // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
        m_frackman->doSomething();
        for(int k = 0; k != m_numactors; k++)
            m_actors[k] -> doSomething();
        //decLives();
		return GWSTATUS_CONTINUE_GAME;
	}

    virtual void cleanUp();
    
    bool isDirt(int x, int y);
    void removeDirt(int x, int y) {delete m_dirt[x][y];
        m_dirt[x][y] = nullptr;};
    int minInt(int first, int second);
	
private:

    FrackMan* m_frackman;
    Dirt* m_dirt[64][64] = {nullptr};
    Actor* m_actors[100];
    int m_numactors = 0;
    int m_currlevel = 0;
};

#endif // STUDENTWORLD_H_
