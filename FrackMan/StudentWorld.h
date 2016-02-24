#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <string>
#include <random>
#include <cmath>
#include <list>
using namespace std;


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
            int x = randInt(0, 60);
            int y = randInt(20, 56);
            while(isTooClose(x, y))
            {
                x = randInt(0, 60);
                y = randInt(20, 56);
            }
             m_actors.push_front(new Boulder(this, x, y));
        }
        
        int L = minInt(2 + m_currlevel, 20);
        for(int i = 0; i != L; i++)
        {
            int x = randInt(0, 60);
            int y = randInt(0, 56);
            while(isTooClose(x, y))
            {
                x = randInt(0, 60);
                y = randInt(0, 56);
            }
            m_actors.push_front(new OilBarrel(this, x, y));
        }
        
        
        return GWSTATUS_CONTINUE_GAME;
	}
    
    ~StudentWorld();
    virtual int move();
    virtual void cleanUp();
    void removeDeadGameObjects();
    
    bool isDirt(int x, int y);
    void removeDirt(int x, int y) {delete m_dirt[x][y];
        m_dirt[x][y] = nullptr;};
    int minInt(int first, int second);
    bool isTooClose(int x, int y);
	


    FrackMan* m_frackman;
    Dirt* m_dirt[64][64] = {nullptr};
    list<Actor*> m_actors;
   
    int m_currlevel = 0;
};

#endif // STUDENTWORLD_H_
