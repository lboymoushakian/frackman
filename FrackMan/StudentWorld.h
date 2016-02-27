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
        m_barrelsleft = B;
        for(int i = 0; i != B; i++)
        {
            int x = randInt(0, 60);
            int y = randInt(20, 56);
            while(isTooClose(x, y, 6) ||( x > 30 && x < 34))
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
            while(isTooClose(x, y, 6))
            {
                x = randInt(0, 60);
                y = randInt(0, 56);
            }
            m_actors.push_front(new OilBarrel(this, x, y));
        }
        
        int G = maxInt(5-m_currlevel / 2, 2);
        for(int i = 0; i != G; i++)
        {
            int x = randInt(0, 60);
            int y = randInt(0, 56);
            while(isTooClose(x, y, 6))
            {
                x = randInt(0, 60);
                y = randInt(0, 56);
            }
            m_actors.push_front(new goldForFrackman(this, x, y));
        }
        
        return GWSTATUS_CONTINUE_GAME;
	}
    
    ~StudentWorld();
    virtual int move();
    virtual void cleanUp();
    void removeDeadGameObjects();
    void setDisplayText();
    
    bool isDirt(int x, int y);
    void removeDirt(int x, int y) {delete m_dirt[x][y];
        m_dirt[x][y] = nullptr;};
    int minInt(int first, int second);
    int maxInt(int first, int second);
    bool isTooClose(int x, int y, int amt);
    void decreaseBarrels() {m_barrelsleft--;};
    bool isDirt4x4(int x, int y);
    void setCloseVisible(int x, int y, int amt);
    string Format(int score, int level, int lives, int health, int squirts,int gold, int sonar, int barrels);
    bool isBoulder(int x, int y);
    bool isClosetoProtester(int x, int y);
    
	


    FrackMan* m_frackman;
    Dirt* m_dirt[64][64] = {nullptr};
    list<Actor*> m_actors;
    int m_barrelsleft;
    int m_protesters = 0;
    int m_currlevel = 0;
    int m_ticks = 0;
    int m_lastprotester;
    Actor* m_protester;
};

#endif // STUDENTWORLD_H_
