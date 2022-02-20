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
    //virtual void bonk(Actor* getBonked);//when an actor gets hit
    StudentWorld* getWorld();
    virtual ~Actor();
  private:
    StudentWorld* StudentWorldPtr;
    int xCoord;
    int yCoord;
    bool alive;
};

class Peach : public Actor
{
  public:
    Peach(StudentWorld* ptr, int startX, int startY);
    virtual void doSomething();
    virtual bool blockMovement();
    virtual void bonk(Actor* getBonked);
    void addHp(int health);
    virtual ~Peach();
  private:
    int power;
    int starLength;
    int tempImmune;
    int time_to_recharge_before_next_fire;
    int remaining_jump_distance;
    int hp;
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


class winCondition : public Actor
{
public:
    winCondition(StudentWorld* ptr, int imageID, int startX, int startY, int dir, int depth, double size);
    virtual void doSomething();
    virtual bool blockMovement();
    virtual bool canBeDamaged();
    virtual void change() = 0;
};

class Flag : public winCondition
{
public:
    Flag(StudentWorld* ptr, int startX, int startY);
    virtual void change();
};

class Mario : public winCondition
{
public:
    Mario(StudentWorld* ptr, int startX, int startY);
    virtual void change();
};
#endif // ACTOR_H_
