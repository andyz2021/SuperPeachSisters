#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
Actor::Actor(StudentWorld* ptr, int imageID, int startX, int startY, int dir, int depth, double size): GraphObject(imageID, startX, startY, dir, depth, size), StudentWorldPtr(ptr)
{
    alive = true;//each actor has an alive status, and coordinates
    xCoord = startX;
    yCoord = startY;
}

bool Actor::blockMovement()//some Actors block objects
{
    return true;
}
bool Actor::canBeDamaged()//some actors can be damaged
{
    return true;
}
void Actor::die()//some actors can die(flags, goombas, etc)
{
    alive = false;
}
bool Actor::isAlive()//get alive status
{
    return alive;
}

void Actor::bonk()
{
    
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
    hp = 1;//starts with hp of 1, no powers
    flower = false;
    mushroom = false;
    star = false;
    starLength = 0;
    tempImmune = 0;
    time_to_recharge_before_next_fire = 0;
    remaining_jump_distance = 0;
}

bool Peach::blockMovement()//Peach doesn't block movement
{
    return false;
}

void Peach::setPower(int power)
{
    if(power == 1)
    {
        star = true;
    }
    else if(power == 2)
    {
        mushroom = true;
    }
    else if(power == 3)
    {
        flower = true;
    }
}

void Peach::addHp(int health)//if get a mushroom or flower power, increment hp
{
    hp += health;
}
void Peach::doSomething()
{
    if(!isAlive())//if dead, do nothing
    {
        return;
    }
    if(star)//decrement length with star
    {
        starLength--;
    }
    if(tempImmune>0)//decrement temp immunity
    {
        tempImmune--;
    }
    if(time_to_recharge_before_next_fire>0)//decrement cooldown time for fireball
    {
        time_to_recharge_before_next_fire--;
    }
    
    if(getWorld()->overlap(getX(),getY(), true))//if overlapping with something, bonk it
    {

    }
    
    if(remaining_jump_distance>0)//if in a jump
    {
        if(getWorld()->overlap(getX(), getY()+4, true)==2)//if something is above peach, bonk it
        {
            remaining_jump_distance = 0;//set distance to 0 so peach falls
        }
        else
        {
            moveTo(getX(), getY()+4);//go up
            remaining_jump_distance--;
        }
    }
    
    if(remaining_jump_distance == 0 && (getWorld()->overlap(getX(), getY()-4, false)==0))//if nothing below peach
    {
        moveTo(getX(), getY()-4);//fall
    }
    
    int ch;
    if(getWorld() ->getKey(ch))
    {
        if(ch == KEY_PRESS_LEFT)//if go left
        {

            setDirection(180);
            if(getWorld()->overlap(getX()-4, getY(), true)==2)//if something blocking peach
            {

            }
            else
            {
                moveTo(getX()-4, getY());//move left
            }
        }
        else if(ch == KEY_PRESS_RIGHT)//same as left, but going right
        {

             setDirection(0);
            if(getWorld()->overlap(getX()+4, getY(), true)==2)
            {

            }
            else
            {
                moveTo(getX()+4, getY());
            }
        }
        else if(ch == KEY_PRESS_UP)//if up
        {

            if(getWorld()->overlap(getX(), getY()-1, false)==2)//if peach has something under
            {
                if(mushroom)
                {
                    remaining_jump_distance = 12;
                }
                remaining_jump_distance = 8;
                getWorld()->playSound(SOUND_PLAYER_JUMP);
            }
        }
        else if(ch == KEY_PRESS_SPACE)
        {

            if(flower && time_to_recharge_before_next_fire==0)
            {
                getWorld()->playSound(SOUND_PLAYER_FIRE);
                time_to_recharge_before_next_fire = 8;
                if(getDirection()==0)
                {
                    getWorld()->addProjectile(1, getX()+4, getY());
                }
                else if(getDirection()==180)
                {
                    getWorld()->addProjectile(1, getX()-4, getY());
                }
            }
        }

    }
}


void Peach::bonk()
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

void Environment::bonk()
{
    
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
    if(n_goodie!=0 && !wasBonked())
    {
        getWorld()->playSound(SOUND_POWERUP_APPEARS);
        
        if(n_goodie==1)
        {
            getWorld()->addGoodie(1, getX(), getY()+8);
        }
        else if (n_goodie==2)
        {
            getWorld()->addGoodie(2, getX(), getY()+8);
        }
        else if (n_goodie==3)
        {
            getWorld()->addGoodie(3, getX(), getY()+8);
        }
        
    }
    else
    {
        getWorld()->playSound(SOUND_PLAYER_BONK);
    }
    bonked = true;
}
Block::~Block()
{
    
}

Pipe::Pipe(StudentWorld* ptr, int startX, int startY) : Environment(ptr, IID_PIPE, startX, startY, 0, 2, 1.0)
{
    
}

void Pipe::bonk()
{
    getWorld()->playSound(SOUND_PLAYER_BONK);
}

winCondition::winCondition(StudentWorld* ptr, int imageID, int startX, int startY, int dir, int depth, double size) : Actor(ptr, imageID, startX, startY, dir, depth, size)
{
    
}

void winCondition::doSomething()
{
    if(!isAlive())
    {
        return;
    }
    if(getWorld()->overlapPeach(getX(), getY(), false))
    {
        getWorld()->increaseScore(1000);
        die();
        change();
    }
}

bool winCondition::blockMovement()
{
    return false;
}

bool winCondition::canBeDamaged()
{
    return false;
}

Flag::Flag(StudentWorld* ptr, int startX, int startY) : winCondition(ptr, IID_FLAG, startX, startY, 0, 1, 1.0)
{
    
}

void Flag::change()
{
    getWorld()->changeLevel();
}

Mario::Mario(StudentWorld* ptr, int startX, int startY) : winCondition(ptr, IID_MARIO, startX, startY, 0, 1, 1.0)
{
    
}

void Mario::change()
{
    getWorld()->winGame();
}

Goodie::Goodie(StudentWorld* ptr, int imageID, int startX, int startY, int dir, int depth, double size) : Actor(ptr, imageID, startX, startY, dir, depth, size)
{
    
}

void Goodie::doSomething()
{
    if(getWorld()->overlapPeach(getX(),getY(), false))
    {
        addScore();
        givePower();
        //Give Peach object jump power DO LATER
        //Set Peach's hp to 2
        die();
        getWorld()->playSound(SOUND_PLAYER_POWERUP);
        return;
    }
    if(getWorld()->overlap(getX(), getY()-1, false)!=2)
    {
        moveTo(getX(), getY()-2);
    }
    if(getDirection()==0)
    {
        if(getWorld()->overlap(getX()+2, getY(), false)==2)
        {
            setDirection(180);
            return;
        }
        moveTo(getX()+2, getY());
    }
    else if(getDirection()==180)
    {
        if(getWorld()->overlap(getX()-2, getY(), false)==2)
        {
            setDirection(0);
            return;
        }
        moveTo(getX()-2, getY());
    }
}


bool Goodie::blockMovement()
{
    return false;
}

bool Goodie::canBeDamaged()
{
    return false;
}


Flower::Flower(StudentWorld* ptr, int startX, int startY) : Goodie(ptr, IID_FLOWER, startX, startY, 0, 1, 1.0)
{
    
}

void Flower::addScore()
{
    getWorld()->increaseScore(50);
}

void Flower::givePower()
{
    //setPower(1);
}

Mushroom::Mushroom(StudentWorld* ptr, int startX, int startY) : Goodie(ptr, IID_MUSHROOM, startX, startY, 0, 1, 1.0)
{

}


void Mushroom::addScore()
{
    getWorld()->increaseScore(75);
}


void Mushroom::givePower()
{
    //setPower(2);
}

Star::Star(StudentWorld* ptr, int startX, int startY) : Goodie(ptr, IID_STAR, startX, startY, 0, 1, 1.0)
{
    
}

void Star::addScore()
{
    getWorld()->increaseScore(100);
}

void Star::givePower()
{
    //setPower(3);
}

Fireball::Fireball(StudentWorld* ptr, int imageID, int startX, int startY, int dir, int depth, double size) : Actor(ptr, imageID, startX, startY, dir, depth, size)
{
    
}

void Fireball::doSomething()
{
    if(overlap())
    {
        die();
        return;
    }
    if(getWorld()->overlap(getX(), getY()-1, false)!=2)
    {
        moveTo(getX(), getY()-2);
    }
    if(getDirection()==0)
    {
        if(getWorld()->overlap(getX()+2, getY(), false)==2)
        {
            die();
            return;
        }
        moveTo(getX()+2, getY());
    }
    else if(getDirection()==180)
    {
        if(getWorld()->overlap(getX()-2, getY(), false)==2)
        {
            die();
            return;
        }
        moveTo(getX()-2, getY());
    }
}

bool Fireball::canBeDamaged()
{
    return false;
}

bool Fireball::blockMovement()
{
    return false;
}

PiranhaFireball::PiranhaFireball(StudentWorld* ptr, int startX, int startY, int dir) : Fireball(ptr, IID_PIRANHA_FIRE, startX, startY, dir, 1, 1)
{
    
}

bool PiranhaFireball::overlap()
{
    if(getWorld()->overlapPeach(getX(), getY(), true))
    {
        //Damage Peach
        return true;
    }
    return false;
}

PeachFireball::PeachFireball(StudentWorld* ptr, int imageID, int startX, int startY, int dir) : Fireball(ptr, imageID, startX, startY, dir, 1, 1)
{
    
}

bool PeachFireball::overlap()
{
    if(getWorld()->overlap(getX(), getY(), true)==3)
    {
        //Damage the object
        return true;
    }
    return false;
}

Shell::Shell(StudentWorld* ptr, int imageID, int startX, int startY, int dir) : PeachFireball(ptr, imageID, startX, startY, dir)
{
    
}

Enemies::Enemies(StudentWorld* ptr, int imageID, int startX, int startY, int dir, int depth, double size) : Actor(ptr, imageID, startX, startY, dir, depth, size)
{
    
}

void Enemies::doSomething()
{
    if(!isAlive())
    {
        return;
    }
    //Update Piranha Sprite
    if(getWorld()->overlapPeach(getX(), getY(), true))
    {
        return;
    }
    
}

bool Enemies::blockMovement()
{
    return false;
}

bool Enemies::canBeDamaged()
{
    return true;
}


