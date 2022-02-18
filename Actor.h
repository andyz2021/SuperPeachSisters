#ifndef ACTOR_H_
#define ACTOR_H_
#include <vector>
#include "GraphObject.h"

class StudentWorld;
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class Actor : public GraphObject
{
  public:
    Actor(StudentWorld* ptr, int imageID, int startX, int startY, int dir, int depth, double size);
    virtual void doSomething() = 0;
    virtual bool blockMovement();
    virtual bool canBeDamaged();
    void die();
    bool isAlive();
    void setHp(int health);
    //virtual void bonk(Actor* getBonked);//when an actor gets hit
    StudentWorld* getWorld();
    Actor* overlap(int x, int y);
    virtual ~Actor();
  private:
    StudentWorld* StudentWorldPtr;
    int xCoord;
    int yCoord;
    int hp;
};

class Peach : public Actor
{
  public:
    Peach(StudentWorld* ptr, int startX, int startY);
    virtual void doSomething();
    virtual void bonk(Actor* getBonked);
    virtual ~Peach();
  private:
    int power;
    int starLength;
    int tempImmune;
    int time_to_recharge_before_next_fire;
};

class Environment : public Actor
{
public:
    Environment(StudentWorld* ptr, int imageID, int startX, int startY, int dir, int depth, double size);
    virtual void doSomething();
    virtual bool canBeDamaged();
};

class Block : public Environment
{
  public:
    Block(StudentWorld* ptr, int startX, int startY, int goodie);
    bool wasBonked();
    virtual void bonk();
    virtual ~Block();
  private:
    int n_goodie;
    bool bonked;
};


class Pipe : public Environment
{
  public:
    Pipe(StudentWorld* ptr, int startX, int startY);
    
};


#endif // ACTOR_H_
