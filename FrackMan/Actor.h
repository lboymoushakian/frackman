#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameConstants.h"
class StudentWorld;

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class Actor : public GraphObject
{
public:
    Actor(StudentWorld* sw, int imageID, int startX, int startY, Direction dir = right, double size = 1.0, int depth = 0) ;
    virtual ~Actor(){};
    virtual void doSomething() = 0;
    bool isAlive() const {return m_alive;};
    void setDead(){m_alive = false;};
    StudentWorld* getWorld() {return m_sw;};
    virtual bool annoyActor(unsigned int amt){return true;};
    bool isBoulder() { return m_boulder;};
    void setBoulder() {m_boulder = true;};
    bool isProtester() {return m_protester;};
    void setProtester() {m_protester = true;};
    virtual void annoy(int amt)=0;
    virtual void setAnnoyed(){};
    
private:
    StudentWorld* m_sw;
    bool m_alive;
    bool m_boulder = false;
    bool m_protester = false;
    
    
};

class ActivatingObject : public Actor
{
public:
    ActivatingObject(StudentWorld* world, int startX, int startY, int imageID,
                                     int soundToPlay);
    
    
    /// Set number of ticks until this object dies
    void setTicksToLive(int ticks){m_tickstolive = ticks;};
    void decreaseTicksToLive() {m_tickstolive--;};
    int getTicksToLive() {return m_tickstolive;};
private:
    int m_tickstolive;
};


class WaterPool : public ActivatingObject
{
public:
    WaterPool(StudentWorld* world, int startX, int startY);
    void doSomething() ;
    ~WaterPool() {setVisible(false);}
    void annoy(int amt) {};
};
class SonarKit : public ActivatingObject
{
public:
    SonarKit(StudentWorld* world, int startX, int startY);
    void doSomething();
    ~SonarKit() {setVisible(false);}
    void annoy(int amt) {};
};
class OilBarrel : public ActivatingObject
{
public:
    OilBarrel(StudentWorld* world, int startX, int startY);
    void doSomething();
    ~OilBarrel() {setVisible(false);};
    void annoy(int amt) {};
    
};

class Dirt : public GraphObject
{
public:
    Dirt(int x, int y);
    ~Dirt() {};

};

class Squirt : public Actor
{
public:
    Squirt(StudentWorld* sw, int x, int y, int travel, Direction dir);
    ~Squirt() {};
    void doSomething() ;
    void annoy(int amt) {};
private:
    int m_count;
};


class Protester : public Actor
{
public:
    Protester(StudentWorld * sw, int x, int y, int image) ;
    virtual ~Protester() {setVisible(false);};
    void pathToExit() {};
    bool closeToFrackman();
    bool isFacingFrackman();
    bool canSeeFrackman();
    bool stuffInTheWay();
    void setDirectiontoFrackman();
    void move();
    void annoy(int amt) {m_health -= amt;};
    void setHealth(int amt) {m_health = amt;};
    int getHealth() {return m_health;};
    void setSquaresToMove(int num) {m_numsquarestomove = num;};
    int getSquares() {return m_numsquarestomove;};
    void setPickedUpNugget() {m_pickedupnugget = true;};
    void setAnnoyed() {m_annoyed = true;};
private:
   int m_health;
    int m_numsquarestomove;
        bool m_pickedupnugget;
    bool m_annoyed;
    
    
};


class regularProtester : public Protester
{
public:
    regularProtester(StudentWorld* sw, int x, int y);
    ~regularProtester() {setVisible(false);};
    int restingTicks();
    void doSomething();
    void setAnnoyed() {m_annoyed = true;};
private:
    int m_restingticks;
    int m_currtick;
    bool m_restfor15;
    int m_restfor15count;
    bool m_annoyed;
    
};

class hardcoreProtester : public Protester
{
public:
    hardcoreProtester(StudentWorld* sw, int x, int y);
    ~hardcoreProtester() {setVisible(false);};
    void doSomething();
    void setAnnoyed() {m_annoyed = true;};
private:
    int m_restingticks;
    int m_currtick;
    bool m_restfor15;
    int m_restfor15count;
    bool m_annoyed;
};
class FrackMan : public Actor
{
public:
    FrackMan(StudentWorld* sw, int x, int y);
    ~FrackMan() {};
    void doSomething();
    void increaseScore(int x) {m_score+= x;};
    void increaseGold() {m_gold++;};
    int getGold() {return m_gold;};
    void increaseSonar() {m_sonar++;};
    int getWater() { return m_water;};
    void decreaseWater() {m_water--;};
    void addWater() {m_water+= 5;};
    void decreaseSonar() {m_sonar--;};
    int getSonar() {return m_sonar;};
    int getHealth() {return m_health;};
    void decreaseHealth(int amt) {m_health -= amt;};
    void annoy(int amt) {};
private:
    int m_health;
    int m_water;
    int m_sonar;
    int m_gold;
    int m_score;
};

class goldForFrackman : public ActivatingObject
{
public:
    goldForFrackman(StudentWorld* world, int startX, int startY);
    void doSomething();
    ~goldForFrackman() {setVisible(false);};
    void annoy(int amt) {};
};

class goldForProtester : public ActivatingObject
{
public:
    goldForProtester(StudentWorld* world, int startX, int startY);
    void doSomething() ;
    ~goldForProtester() {setVisible(false);}
    void annoy(int amt) {};

};
class Boulder : public Actor
{
public:
    Boulder(StudentWorld* sw, int startX, int startY);
    ~Boulder() {setVisible(false);};
    virtual void move() {};
    //virtual bool canActorsPassThroughMe() const;
    void doSomething();
    void annoy(int amt) {};
    bool isDirtUnder(int x, int y);
private:
    bool m_falling;
    
    int m_count = 0;
};

#endif // ACTOR_H_
