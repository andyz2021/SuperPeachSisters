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
    virtual void bonk();//when an actor gets hit
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
    virtual void bonk();
    void addHp(int health);
    void setPower(int power);
    virtual ~Peach();
    
  private:
    bool flower;
    bool star;
    bool mushroom;
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
    virtual void bonk();
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
    virtual void bonk();
    
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

class Goodie : public Actor
{
public:
    Goodie(StudentWorld* ptr, int imageID, int startX, int startY, int dir, int depth, double size);
    virtual void doSomething();
    virtual bool blockMovement();
    virtual bool canBeDamaged();
    virtual void addScore() = 0;
    virtual void givePower() = 0;
};

class Flower : public Goodie
{
public:
    Flower(StudentWorld* ptr, int startX, int startY);
    virtual void addScore();
    virtual void givePower();
};

class Mushroom : public Goodie
{
public:
    Mushroom(StudentWorld* ptr, int startX, int startY);
    virtual void addScore();
    virtual void givePower();
};

class Star : public Goodie
{
public:
    Star(StudentWorld* ptr, int startX, int startY);
    virtual void addScore();
    virtual void givePower();
};

class Fireball : public Actor
{
public:
    Fireball(StudentWorld* ptr, int imageID, int startX, int startY, int dir, int depth, double size);
    virtual void doSomething();
    virtual bool blockMovement();
    virtual bool canBeDamaged();
    virtual bool overlap() = 0;
};

class PiranhaFireball : public Fireball
{
public:
    PiranhaFireball(StudentWorld* ptr, int startX, int startY, int dir);
    virtual bool overlap();
};

class PeachFireball : public Fireball
{
public:
    PeachFireball(StudentWorld* ptr, int imageID, int startX, int startY, int dir);
    virtual bool overlap();
};

class Shell : public PeachFireball
{
public:
    Shell(StudentWorld* ptr, int imageID, int startX, int startY, int dir);
};

class Enemies : public Actor
{
public:
    Enemies(StudentWorld* ptr, int imageID, int startX, int startY, int dir, int depth, double size);
    virtual void doSomething();
    virtual bool canBeDamaged();
    virtual bool blockMovement();
    
};
#endif // ACTOR_H_
