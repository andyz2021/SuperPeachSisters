#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
Actor::Actor(StudentWorld* ptr, int imageID, int startX, int startY, int dir, int depth, double size): GraphObject(imageID, startX, startY, dir, depth, size), StudentWorldPtr(ptr)
{
    hp = 1;
    xCoord = startX;
    yCoord = startY;
}

bool Actor::blockMovement()
{
    return true;
}
bool Actor::canBeDamaged()
{
    return true;
}
void Actor::die()
{
    hp = 0;
}
void Actor::setHp(int health)
{
    hp = health;
}
bool Actor::isAlive()
{
    if(hp>0)
    {
        return true;
    }
    return false;
}
Actor* Actor::overlap(int x, int y)
{
    std::vector<Actor*> allActors = getWorld() -> getActors();
    for(int i = 0;i<allActors.size();i++)
    {
        if(allActors[i]->blockMovement() && allActors[i]->getX() <= x && allActors[i]->getX()+SPRITE_WIDTH-1 >= x && allActors[i]->getY() <= y && allActors[i]->getY()+SPRITE_HEIGHT-1 >= y)//if the bottom left overlaps any block/pipe
        {
            return allActors[i];
        }
        if(allActors[i]->blockMovement() && allActors[i]->getX() <= x+SPRITE_WIDTH-1 && allActors[i]->getX()+SPRITE_WIDTH-1 >= x+SPRITE_WIDTH-1 && allActors[i]->getY() <= y+SPRITE_HEIGHT-1 && allActors[i]->getY()+SPRITE_HEIGHT-1 >= y+SPRITE_HEIGHT-1 )//if top right overlaps
        {
            return allActors[i];
        }
    }
    return nullptr;
}
StudentWorld* Actor::getWorld()
{
    return StudentWorldPtr;
}

Actor::~Actor()
{
    
}

Peach::Peach(StudentWorld* ptr, int startX, int startY) : Actor(ptr, IID_PEACH, startX, startY, 0, 0, 1.0)
{
    setHp(1);
    power = 0;
}
void Peach::doSomething()
{
    if(!isAlive())
    {
        return;
    }
    if(power==IID_STAR)
    {
        starLength--;
    }
    if(tempImmune>0)
    {
        tempImmune--;
    }
    if(time_to_recharge_before_next_fire>0)
    {
        time_to_recharge_before_next_fire--;
    }
    int ch;
    if(getWorld() ->getKey(ch))
    {
        if(ch == KEY_PRESS_LEFT)
        {
           // if(something is blocking) FILL IN LATER
            setDirection(180);
            if(overlap(getX()-4, getY())!=nullptr)
            {
                bonk(overlap(getX()-4, getY()));
            }
            else
            {
                moveTo(getX()-4, getY());
            }
        }
        else if(ch == KEY_PRESS_RIGHT)
        {
            // if(something is blocking) FILL IN LATER
             setDirection(0);
            if(overlap(getX()+4, getY())!=nullptr)
            {
                bonk(overlap(getX()+4, getY()));
            }
            else
            {
                moveTo(getX()+4, getY());
            }
        }
    }
}


void Peach::bonk(Actor* getBonked)
{

}
Peach::~Peach()
{
    
}

Environment::Environment(StudentWorld* ptr, int imageID, int startX, int startY, int dir, int depth, double size) : Actor(ptr, imageID, startX, startY, dir, depth, size)
{
    
}


void Environment::doSomething()
{
    return;
}
bool Environment::canBeDamaged()
{
    return false;
}

Block::Block(StudentWorld* ptr, int startX, int startY, int goodie) : Environment(ptr, IID_BLOCK, startX, startY, 0, 2, 1.0)
{
    bonked = false;
    n_goodie = goodie;
}

bool Block::wasBonked()
{
    return bonked;
}
void Block::bonk()
{
    bonked = true;
}
Block::~Block()
{
    
}

Pipe::Pipe(StudentWorld* ptr, int startX, int startY) : Environment(ptr, IID_PIPE, startX, startY, 0, 2, 1.0)
{
    
}
