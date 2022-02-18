#ifndef ACTOR_H_
#define ACTOR_H_
#include <vector>
#include "GraphObject.h"

class StudentWorld;
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class Actor : public GraphObject
{
  public:
    Actor(StudentWorld* ptr, int imageID, int startX, int startY, int dir, int depth, double size);//initialize Actor
    
    virtual void doSomething() = 0;//doSomething for each actor
    
    virtual bool blockMovement();//return whether this actor blocks movement
    
    virtual bool canBeDamaged();//return whether this actor can be damaged 
    
    void die();//actor dies
    
    bool isAlive();//check if actor is alive
    
    
    //virtual void bonk() = 0;//when an actor gets bonked
    
    StudentWorld* getWorld();//returns the StudentWorld ptr
    
    Actor* overlap(int x, int y);//check if two actors overlap
    
    virtual ~Actor();//destruct Actor
  private:
    StudentWorld* StudentWorldPtr;
    int xCoord;
    int yCoord;
    bool alive;

};

class Peach : public Actor
{
  public:
    Peach(StudentWorld* ptr, int startX, int startY);//Peach constructor
    
    virtual void doSomething();
    
    virtual void bonk(Actor* gotBonked);//Peach bonks another object
    
    virtual ~Peach();
  private:
    int power;
    int starLength;
    int tempImmune;
    int time_to_recharge_before_next_fire;
    int hp;
};

class Environment : public Actor
{
  public:
    Environment(StudentWorld* ptr, int imageID, int startX, int startY, int dir, int depth, double size);
    virtual void doSomething();
    
    virtual bool canBeDamaged();
    
    virtual void bonk();
    
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
