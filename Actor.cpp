#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
Actor::Actor(StudentWorld* ptr, int imageID, int startX, int startY, int dir, int depth, double size): GraphObject(imageID, startX, startY, dir, depth, size), StudentWorldPtr(ptr)
{
    alive = true;//each actor has an alive status, and coordinates
}

void Actor::die()//some actors can die(flags, goombas, etc)
{
    alive = false;
}
bool Actor::isAlive()//get alive status
{
    return alive;
}


void Actor::getDamaged()
{
    
}

StudentWorld* Actor::getWorld()
{
    return StudentWorldPtr;
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

bool Peach::canBeDamaged()
{
    return true;
}

void Peach::setHp(int health)//if get a mushroom or flower power, increment hp
{
    hp = health;
}


void Peach::setPower(int power)//give peach a power. If power is 1, gives peach star. 2: mushroom, 3: flower. 
{
    if(power == 1)
    {
        star = true;
    }
    else if(power == 2)
    {
        mushroom = true;
        setHp(2);
    }
    else if(power == 3)
    {
        flower = true;
        setHp(2);
    }
}

void Peach::doSomething()
{
    if(!isAlive())//if dead, do nothing
    {
        return;
    }
    if(hasStar())//decrement length with star
    {
        starLength--;
    }
    if(starLength<=0)
    {
        star = false;
    }
    if(tempImmune>0)//decrement temp immunity
    {
        tempImmune--;
    }
    if(time_to_recharge_before_next_fire>0)//decrement cooldown time for fireball
    {
        time_to_recharge_before_next_fire--;
    }
    
    if(getWorld()->overlap(getX(),getY(), true, false))//if overlapping with something, bonk it
    {

    }
    
    if(remaining_jump_distance>0)//if in a jump
    {
        if(getWorld()->overlap(getX(), getY()+4, true, false)==2)//if something is above peach, bonk it
        {
            remaining_jump_distance = 0;//set distance to 0 so peach falls
        }
        else
        {
            moveTo(getX(), getY()+4);//go up
            remaining_jump_distance--;
        }
    }
    
    if(remaining_jump_distance == 0 && (getWorld()->overlap(getX(), getY()-4, false, true)!=2))//if nothing below peach
    {
        moveTo(getX(), getY()-4);//fall
    }
    
    int ch;
    if(getWorld() ->getKey(ch))
    {
        if(ch == KEY_PRESS_LEFT)//if go left
        {

            setDirection(180);
            if(getWorld()->overlap(getX()-4, getY(), true, true)==2)//if something blocking peach
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
            if(getWorld()->overlap(getX()+4, getY(), true, true)==2)
            {

            }
            else
            {
                moveTo(getX()+4, getY());
            }
        }
        else if(ch == KEY_PRESS_UP)//if up
        {

            if(getWorld()->overlap(getX(), getY()-1, false, true)==2)//if peach has something under
            {
                if(mushroom)
                {
                    remaining_jump_distance = 12;
                }
                else
                {
                    remaining_jump_distance = 8;//set jump distance
                }
                getWorld()->playSound(SOUND_PLAYER_JUMP);
            }
        }
        else if(ch == KEY_PRESS_SPACE)
        {

            if(flower && time_to_recharge_before_next_fire==0)//if peach can fire
            {
                getWorld()->playSound(SOUND_PLAYER_FIRE);
                time_to_recharge_before_next_fire = 8;
                if(getDirection()==0)
                {
                    getWorld()->addProjectile(1, getX()+4, getY(), getDirection());//create new fireball at position and direction determined by peach
                }
                else if(getDirection()==180)
                {
                    getWorld()->addProjectile(1, getX()-4, getY(), getDirection());
                }
            }
        }

    }
}

bool Peach::hasStar()
{
    return star;
}

bool Peach::hasFlower()
{
    return flower;
}

bool Peach::hasMushroom()
{
    return mushroom;
}




void Peach::bonk()//When Peach gets bonked
{
    if(hasStar() || tempImmune>0)
    {
        return;
    }
    else
    {
        hp--;
        tempImmune = 10;
        if(hasFlower())
        {
            flower = false;
        }
        if(hasMushroom())
        {
            mushroom = false;
        }
        if(hp>0)
        {
            getWorld()->playSound(SOUND_PLAYER_HURT);
        }
        if(hp<=0)
        {
            die();
        }
    }
    
}

void Peach::setStarLength()
{
    starLength = 150;
}

Environment::Environment(StudentWorld* ptr, int imageID, int startX, int startY, int dir, int depth, double size) : Actor(ptr, imageID, startX, startY, dir, depth, size)
{
    
}//Environment constructor


void Environment::doSomething()
{
    return;//blocks and pipes do nothing
}
bool Environment::canBeDamaged()
{
    return false;//can't be damaged
}

bool Environment::blockMovement()
{
    return true;
}

void Environment::bonk()
{
    return;
}

Block::Block(StudentWorld* ptr, int startX, int startY, int goodie) : Environment(ptr, IID_BLOCK, startX, startY, 0, 2, 1.0)
{
    bonked = false;
    n_goodie = goodie;
}//block constructor

bool Block::wasBonked()
{
    return bonked;//determines status of if a block was bonked or not
}
void Block::bonk()
{
    if(n_goodie!=0 && !wasBonked())//if block wasn't bonked yet and has a powerup
    {
        getWorld()->playSound(SOUND_POWERUP_APPEARS);
        
        if(n_goodie==1)
        {
            getWorld()->addGoodie(1, getX(), getY()+8);//create the powerup
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
        getWorld()->playSound(SOUND_PLAYER_BONK);//play bonk sound
    }
    bonked = true;
}


Pipe::Pipe(StudentWorld* ptr, int startX, int startY) : Environment(ptr, IID_PIPE, startX, startY, 0, 2, 1.0)
{
    
}

void Pipe::bonk()//Pipes don't do much
{
    getWorld()->playSound(SOUND_PLAYER_BONK);
}

winCondition::winCondition(StudentWorld* ptr, int imageID, int startX, int startY, int dir, int depth, double size) : Actor(ptr, imageID, startX, startY, dir, depth, size)
{
    
}//winConditions include Flag and Mario

void winCondition::doSomething()
{
    if(!isAlive())//if they aren't alive, immediately return
    {
        return;
    }
    if(getWorld()->overlapPeach(getX(), getY(), false))//if they overlap Peach
    {
        getWorld()->increaseScore(1000);
        die();
        change();
    }
}

bool winCondition::blockMovement()//don't block movement
{
    return false;
}

bool winCondition::canBeDamaged()//can't be damaged
{
    return false;
}

void winCondition::bonk()
{
    return;
}
Flag::Flag(StudentWorld* ptr, int startX, int startY) : winCondition(ptr, IID_FLAG, startX, startY, 0, 1, 1.0)
{
    
}

void Flag::change()//Change to the next level
{
    getWorld()->changeLevel();
}

Mario::Mario(StudentWorld* ptr, int startX, int startY) : winCondition(ptr, IID_MARIO, startX, startY, 0, 1, 1.0)
{
    
}

void Mario::change()//win the game
{
    getWorld()->winGame();
}

Goodie::Goodie(StudentWorld* ptr, int imageID, int startX, int startY, int dir, int depth, double size) : Actor(ptr, imageID, startX, startY, dir, depth, size)
{
    
}//Goodies include Flowers, Mushrooms, and Stars

void Goodie::doSomething()
{
    if(!isAlive())//if they aren't alive, return immediately
    {
        return;
    }
    if(getWorld()->overlapPeach(getX(),getY(), false))//if it overlaps with Peach
    {
        addScore();
        givePower();//give Peach power depending on goodie.
        die();
        getWorld()->playSound(SOUND_PLAYER_POWERUP);
        return;
    }
    if(getWorld()->overlap(getX(), getY()-1, false, true)!=2)//check if something is under goodie
    {
        moveTo(getX(), getY()-2);
    }
    if(getDirection()==0)
    {
        if(getWorld()->overlap(getX()+2, getY(), false, true)==2)//check if something is blocking goodie to left/right
        {
            setDirection(180);//if there is something, switch directions
            return;
        }
        moveTo(getX()+2, getY());//if not, move
    }
    else if(getDirection()==180)
    {
        if(getWorld()->overlap(getX()-2, getY(), false, true)==2)
        {
            setDirection(0);
            return;
        }
        moveTo(getX()-2, getY());
    }
}


bool Goodie::blockMovement()//Goodies don't block movement
{
    return false;
}

bool Goodie::canBeDamaged()//Goodies can't be damaged
{
    return false;
}

void Goodie::bonk()
{
    return;
}


Flower::Flower(StudentWorld* ptr, int startX, int startY) : Goodie(ptr, IID_FLOWER, startX, startY, 0, 1, 1.0)
{
    
}

void Flower::addScore()//Flower score value
{
    getWorld()->increaseScore(50);
}

void Flower::givePower()//Give Peach the flower power
{
    getWorld()->givePeachPower(3);
}

//Mushroom and Star are similar
Mushroom::Mushroom(StudentWorld* ptr, int startX, int startY) : Goodie(ptr, IID_MUSHROOM, startX, startY, 0, 1, 1.0)
{

}


void Mushroom::addScore()//Mushroom score Value
{
    getWorld()->increaseScore(75);
}


void Mushroom::givePower()//Give Peach mushroom
{
    getWorld()->givePeachPower(2);
}

Star::Star(StudentWorld* ptr, int startX, int startY) : Goodie(ptr, IID_STAR, startX, startY, 0, 1, 1.0)
{
    
}

void Star::addScore()//Star score value
{
    getWorld()->increaseScore(100);
}

void Star::givePower()//Give peach star
{
    getWorld()->givePeachPower(1);
    getWorld()->setPeachInvincible();
}

Fireball::Fireball(StudentWorld* ptr, int imageID, int startX, int startY, int dir, int depth, double size) : Actor(ptr, imageID, startX, startY, dir, depth, size)
{
    
}//Fireball class includes Peach Fireball and Piranha Fireball

void Fireball::doSomething()
{
    if(!isAlive())//if they aren't alive, return immediately
    {
        return;
    }
    if(overlap())//If it overlaps with the desired object, return
    {
        die();
        return;
    }
    if(getWorld()->overlap(getX(), getY()-1, false, true)!=2)//if something isn't under the fireball
    {
        moveTo(getX(), getY()-2);
    }
    if(getDirection()==0)//
    {
        if(getWorld()->overlap(getX()+2, getY(), false, true)==2)//If something is blocking
        {
            die();
            return;//die and return
        }
        moveTo(getX()+2, getY());//otherwise move to the left/right
    }
    else if(getDirection()==180)
    {
        if(getWorld()->overlap(getX()-2, getY(), false, true)==2)
        {
            die();
            return;
        }
        moveTo(getX()-2, getY());
    }
}

bool Fireball::canBeDamaged()//Fireballs can't be damaged
{
    return false;
}

bool Fireball::blockMovement()//Don't block movement
{
    return false;
}

void Fireball::bonk()
{
    return;
}

bool Fireball::overlap()//If it overlaps with a enemy that can be damaged, for shells and peach fireballs
{
    if(getWorld()->overlap(getX(), getY(), false, false)==3)
    {
        return true;
    }
    return false;
}

PiranhaFireball::PiranhaFireball(StudentWorld* ptr, int startX, int startY, int dir) : Fireball(ptr, IID_PIRANHA_FIRE, startX, startY, dir, 1, 1)
{
    
}

bool PiranhaFireball::overlap()//If it overlaps with Peach
{
    if(getWorld()->overlapPeach(getX(), getY(), true))
    {
        //Damage Peach
        return true;
    }
    return false;
}

PeachFireball::PeachFireball(StudentWorld* ptr, int startX, int startY, int dir) : Fireball(ptr, IID_PEACH_FIRE, startX, startY, dir, 1, 1)
{
    
}



Shell::Shell(StudentWorld* ptr, int startX, int startY, int dir) : Fireball(ptr, IID_SHELL, startX, startY, dir, 1, 1)
{
    
}//Shells are similar to Peach fireballs

Enemies::Enemies(StudentWorld* ptr, int imageID, int startX, int startY, int dir, int depth, double size) : Actor(ptr, imageID, startX, startY, dir, depth, size)
{
    
}//Enemies include Goombas, Koopas, and Piranhas

void Enemies::doSomething()
{
    if(!isAlive())//if they aren't alive, return immediately
    {
        return;
    }
    if(getWorld()->overlapPeach(getX(), getY(), true))//if the enemy overlaps with Peach
    {
        //BONK PEACH
        return;
    }
    if(getDirection()==0)
    {
        if(getWorld()->overlap(getX()+1, getY(), false, true)==2)//If something is blocking it
        {
            setDirection(180);//Change direction
        }
        else if(getWorld()->extendOverSpace(getX()+SPRITE_WIDTH, getY()-1))//If it would go over the edge(partially or fully)
        {
            setDirection(180);
        }
    }
    else if(getDirection()==180)//Same but for left
    {
        if(getWorld()->overlap(getX()-1, getY(), false, true)==2)
        {
            setDirection(0);
        }
        else if(getWorld()->extendOverSpace(getX()-1, getY()-1))
        {
            setDirection(0);
        }
    }
    
    if(getDirection()==0)//If left direction
    {
        if(getWorld()->overlap(getX()+1, getY(), false, true)==2)//If there's something blocking it
        {
            return;//immediately return
        }
        else
        {
            moveTo(getX()+1, getY());//move
        }
    }
    else if(getDirection()==180)//same for right
    {
        if(getWorld()->overlap(getX()-1, getY(), false, true)==2)
        {
            return;
        }
        else
        {
            moveTo(getX()-1, getY());
        }
    }
}

bool Enemies::blockMovement()//Enemies don't block movement
{
    return false;
}

bool Enemies::canBeDamaged()//Enemies can be damaged
{
    return true;
}

void Enemies::getDamaged()
{
    //std::cout << getX() << std::endl;
    die();
    getWorld()->increaseScore(100);
    afterDeath();

}

void Enemies::bonk()
{
    if(getWorld()->PeachHasStar() && getWorld()->overlapPeach(getX(), getY(), false))
    {
        getWorld()->playSound(SOUND_PLAYER_KICK);
        getDamaged();
    }
        
}

void Enemies::afterDeath()
{
    
}

Goomba::Goomba(StudentWorld* ptr, int startX, int startY, int dir) : Enemies(ptr, IID_GOOMBA, startX, startY, dir, 0, 1)
{
    
}


Koopa::Koopa(StudentWorld* ptr, int startX, int startY, int dir) : Enemies(ptr, IID_KOOPA, startX, startY, dir, 0, 1)
{
    
}

void Koopa::afterDeath()
{
    getWorld()->addProjectile(3, getX(), getY(), getDirection());
}

Piranha::Piranha(StudentWorld* ptr, int startX, int startY, int dir) : Enemies(ptr, IID_PIRANHA, startX, startY, dir, 0, 1)
{
    firing_delay = 0;
}

void Piranha::doSomething()
{
    if(!isAlive())
    {
        return;
    }
    increaseAnimationNumber();
    if(getWorld()->overlapPeach(getX(), getY(), true))//Bonk Peach
    {
        return;
    }
    if(getWorld()->getPeachY() > getY()-(1.5 * SPRITE_HEIGHT) && getWorld()->getPeachY() < getY()+(1.5 * SPRITE_HEIGHT))
    {
        if(getWorld()->getPeachX() < getX())
        {
            setDirection(180);
        }
        else if(getWorld()->getPeachX() > getX())
        {
            setDirection(0);
        }
        
        if(firing_delay>0)
        {
            firing_delay--;
            return;
        }
        
        if(getDirection()==0)
        {
            if(getWorld()->getPeachX() - getX() < 8*SPRITE_WIDTH)
            {
                getWorld()->addProjectile(2, getX(), getY(), getDirection());
                getWorld()->playSound(SOUND_PIRANHA_FIRE);
                firing_delay = 40;
            }
        }
        
        else if(getDirection()==180)
        {
            if(getX() - getWorld()->getPeachX() < 8*SPRITE_WIDTH)
            {
                getWorld()->addProjectile(2, getX(), getY(), getDirection());
                getWorld()->playSound(SOUND_PIRANHA_FIRE);
                firing_delay = 40;
            }
        }
    }
}





