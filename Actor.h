#ifndef ACTOR_H_
#define ACTOR_H_
#include "GraphObject.h"

class StudentWorld;
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class Actor : public GraphObject
{
  public:
    Actor(StudentWorld* ptr, int imageID, int startX, int startY, int dir, int depth, double size);//Constructor
    virtual void doSomething() = 0;//doSomething function
    virtual bool blockMovement() = 0;//Can actors block movement
    virtual bool canBeDamaged() = 0;//Can actors be damaged
    void die();//Set alive status to false
    bool isAlive();//check alive status
    virtual void bonk() = 0;//when an actor gets hit
    virtual void getDamaged();//for when a enemy gets hit with a fireball 
    StudentWorld* getWorld();//get the pointer to the StudentWorld
  private:
    StudentWorld* StudentWorldPtr;
    bool alive;

};

class Peach : public Actor
{
  public:
    Peach(StudentWorld* ptr, int startX, int startY);
    virtual void doSomething();
    virtual bool blockMovement();
    virtual bool canBeDamaged();
    virtual void bonk();
    void setStarLength();
    void setPower(int power);//Give Peach power
    virtual bool hasFlower();
    virtual bool hasStar();
    virtual bool hasMushroom();

    
    
  private:
    void setHp(int health);//set Peach's hp
    int starLength;//length of invincibility from star
    int tempImmune;//length of invincibility after getting hit
    int time_to_recharge_before_next_fire;//length between shooting fireballs
    int remaining_jump_distance;//ticks left of jumping
    int hp;
    bool flower;//all powers
    bool star;
    bool mushroom;
    
};



class Environment : public Actor
{
public:
    Environment(StudentWorld* ptr, int imageID, int startX, int startY, int dir, int depth, double size);
    virtual void doSomething();
    virtual void bonk();
    virtual bool canBeDamaged();
    virtual bool blockMovement();
};

class Block : public Environment
{
  public:
    Block(StudentWorld* ptr, int startX, int startY, int goodie);
    virtual void bonk();
  private:
    bool wasBonked();//check if block was bonked
    int n_goodie;//stores what type of goodie is in the block 
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
    virtual void bonk();
    virtual void change() = 0;//Whether the flag or mario changes level or wins the game
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
    virtual void bonk();
    virtual void addScore() = 0;//how much each goodie is worth
    virtual void givePower() = 0;//give the power to peach
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
    virtual void bonk();
    virtual bool overlap();//What the fireball overlaps with
};

class PiranhaFireball : public Fireball
{
public:
    PiranhaFireball(StudentWorld* ptr, int startX, int startY, int dir);
    virtual bool overlap();//If it overlaps with peach
};

class PeachFireball : public Fireball
{
public:
    PeachFireball(StudentWorld* ptr, int startX, int startY, int dir);
};

class Shell : public Fireball
{
public:
    Shell(StudentWorld* ptr, int startX, int startY, int dir);
};

class Enemies : public Actor
{
public:
    Enemies(StudentWorld* ptr, int imageID, int startX, int startY, int dir, int depth, double size);
    virtual void doSomething();
    virtual bool canBeDamaged();
    virtual bool blockMovement();
    virtual void bonk();
    virtual void getDamaged();
    virtual void afterDeath();
    
};

class Goomba : public Enemies
{
public:
    Goomba(StudentWorld* ptr, int startX, int startY, int dir);
    
};

class Koopa : public Enemies
{
public:
    Koopa(StudentWorld* ptr, int startX, int startY, int dir);
    virtual void afterDeath();
    
};

class Piranha : public Enemies
{
public:
    Piranha(StudentWorld* ptr, int startX, int startY, int dir);
    virtual void doSomething();
private:
    int firing_delay;
};
#endif // ACTOR_H_
