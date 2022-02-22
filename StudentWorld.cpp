#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
#include <iostream> // defines the overloads of the << operator
#include <sstream>  // defines the type std::ostringstream
#include <iomanip>  // defines the manipulator setw
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
    levelComplete = false;
    gameComplete = false;
}

int StudentWorld::overlap(int x, int y, bool bonk, bool onlyBlocks)//detect overlap. Returns 3 if overlaps with a object that can be damaged(For Peach fireballs). Returns 2 if the overlap is with an object that blocks movement, returns 1 if it doesn't block movement, returns 0 otherwise. If bonk is true, the object that is overlapped with will be bonked. If onlyBlocks is true, it only checks for actors that block movement
{
    for(int i = 0;i<actors.size();i++)
    {
        if(onlyBlocks)//only checking for actors that block movement
        {
            if(actors[i]->blockMovement() && actors[i]->isAlive())
            {
                if(actors[i]->getX() >= x && actors[i]->getX() <= x+SPRITE_WIDTH-1 && actors[i]->getY() >= y && actors[i]->getY() <= y+SPRITE_HEIGHT-1)//if the bottom left of the actor overlaps the object calling overlap
                {
                    if(bonk==true)
                    {
                        actors[i]->bonk();
                    }
                    return 2;
                }
                
                if(actors[i]->getX()+SPRITE_WIDTH-1 >= x && actors[i]->getX()+SPRITE_WIDTH-1 <= x+SPRITE_WIDTH-1 && actors[i]->getY()+SPRITE_HEIGHT-1 >= y && actors[i]->getY()+SPRITE_HEIGHT-1 <= y+SPRITE_HEIGHT-1)//if top right overlaps
                {
                    
                    if(bonk==true)
                    {
                        actors[i]->bonk();
                    }
                    return 2;
                }
                if(actors[i]->getX() >= x && actors[i]->getX() <= x+SPRITE_WIDTH-1 && actors[i]->getY()+SPRITE_HEIGHT-1 >= y && actors[i]->getY()+SPRITE_HEIGHT-1 <= y+SPRITE_HEIGHT-1)//if top left overlaps
                {
                    if(bonk==true)
                    {
                        actors[i]->bonk();
                    }
                    return 2;
                }
                if(actors[i]->getX()+SPRITE_WIDTH-1 >= x && actors[i]->getX()+SPRITE_WIDTH-1 <= x+SPRITE_WIDTH-1 && actors[i]->getY() >= y && actors[i]->getY() <= y+SPRITE_HEIGHT-1)//if bottom right overlaps
                {
                    if(bonk==true)
                    {
                        actors[i]->bonk();
                    }
                    return 2;
                }
                 
            }
            
        }
        else//checks for all actors
        {
            if(actors[i]->isAlive())
            {
                if(actors[i]->getX() >= x && actors[i]->getX() <= x+SPRITE_WIDTH-1 && actors[i]->getY() >= y && actors[i]->getY() <= y+SPRITE_HEIGHT-1)//if the bottom left of the actor overlaps the object calling overlap
                {
                    if(bonk==true)
                    {
                        actors[i]->bonk();
                    }
                    if(actors[i]->canBeDamaged() && !onlyBlocks)
                    {
                        if(bonk==false)
                        {
                            damageEnemy(actors[i]);
                        }
                        return 3;
                    }
                    if(actors[i]->blockMovement())
                    {
                        return 2;
                    }
                    return 1;
                }
                
                if(actors[i]->getX()+SPRITE_WIDTH-1 >= x && actors[i]->getX()+SPRITE_WIDTH-1 <= x+SPRITE_WIDTH-1 && actors[i]->getY()+SPRITE_HEIGHT-1 >= y && actors[i]->getY()+SPRITE_HEIGHT-1 <= y+SPRITE_HEIGHT-1)//if top right overlaps
                {
                    
                    if(bonk==true)
                    {
                        actors[i]->bonk();
                    }
                    if(actors[i]->canBeDamaged() && !onlyBlocks)
                    {
                        if(bonk==false)
                        {
                            damageEnemy(actors[i]);
                        }
                        return 3;
                    }
                    if(actors[i]->blockMovement())
                    {
                        return 2;
                    }
                    return 1;
                }
                if(actors[i]->getX() >= x && actors[i]->getX() <= x+SPRITE_WIDTH-1 && actors[i]->getY()+SPRITE_HEIGHT-1 >= y && actors[i]->getY()+SPRITE_HEIGHT-1 <= y+SPRITE_HEIGHT-1)//if top left overlaps
                {
                    if(bonk==true)
                    {
                        actors[i]->bonk();
                    }
                    if(actors[i]->canBeDamaged() && !onlyBlocks)
                    {
                        if(bonk==false)
                        {
                            damageEnemy(actors[i]);
                        }
                        return 3;
                    }
                    if(actors[i]->blockMovement())
                    {
                        return 2;
                    }
                    return 1;
                }
                if(actors[i]->getX()+SPRITE_WIDTH-1 >= x && actors[i]->getX()+SPRITE_WIDTH-1 <= x+SPRITE_WIDTH-1 && actors[i]->getY() >= y && actors[i]->getY() <= y+SPRITE_HEIGHT-1)//if bottom right overlaps
                {
                    if(bonk==true)
                    {
                        actors[i]->bonk();
                    }
                    if(actors[i]->canBeDamaged() && !onlyBlocks)
                    {
                        if(bonk==false)
                        {
                            damageEnemy(actors[i]);
                        }
                        return 3;
                    }
                    if(actors[i]->blockMovement())
                    {
                        return 2;
                    }
                    return 1;
                }
            }

             
        }

    }
    return 0;
}

bool StudentWorld::overlapPeach(int x, int y, bool bonk)//returns true if the object overlaps with Peach, false otherwise. Bonk is used to determine whether the peach object is bonked or not. 
{
    
    if(PeachPtr->getX() <= x && PeachPtr->getX()+SPRITE_WIDTH-1 >= x && PeachPtr->getY() <= y && PeachPtr->getY()+SPRITE_HEIGHT-1 >= y)//if the bottom left overlaps any block/pipe
    {
        if(bonk==true)
        {
            PeachPtr->bonk();
        }
        return true;
    }
    if(PeachPtr->getX() <= x+SPRITE_WIDTH-1 && PeachPtr->getX()+SPRITE_WIDTH-1 >= x+SPRITE_WIDTH-1 && PeachPtr->getY() <= y+SPRITE_HEIGHT-1 && PeachPtr->getY()+SPRITE_HEIGHT-1 >= y+SPRITE_HEIGHT-1 )//if top right overlaps
    {
        if(bonk==true)
        {
            PeachPtr->bonk();
        }
        return true;
    }
    if(PeachPtr->getX() <= x && PeachPtr->getX()+SPRITE_WIDTH-1 >= x && PeachPtr->getY() <= y+SPRITE_HEIGHT-1 && PeachPtr->getY()+SPRITE_HEIGHT-1 >= y+SPRITE_HEIGHT-1 )//if top left overlaps
    {
        if(bonk==true)
        {
            PeachPtr->bonk();
        }
        return true;
    }
    if(PeachPtr->getX() <= x+SPRITE_WIDTH-1 && PeachPtr->getX()+SPRITE_WIDTH-1 >= x+SPRITE_WIDTH-1 && PeachPtr->getY() <= y && PeachPtr->getY()+SPRITE_HEIGHT-1 >= y )//if bottom right overlaps
    {
        if(bonk==true)
        {
            PeachPtr->bonk();
        }
        return true;
    }
    return false;
}

int StudentWorld::getPeachX()
{
    return PeachPtr->getX();
}
    
int StudentWorld::getPeachY()
{
    return PeachPtr->getY();
}
    
bool StudentWorld::extendOverSpace(int x, int y)//Checks if any actors overlap with this coordinate. Returns true if the object would extend over empty space, returns false if it wouldn't. 
{
    for(int i = 0;i<actors.size();i++)
    {
        if(actors[i]->blockMovement())
        {
            if(actors[i]->getX() <= x && actors[i]->getX() + SPRITE_WIDTH - 1 >= x && actors[i]->getY() <= y && actors[i]->getY() + SPRITE_HEIGHT - 1 >= y)//if it overlaps with that specific point
            {
                return false;//it won't fall off
            }
        }
    }
    return true;//it will fall off
}
void StudentWorld::addGoodie(int goodieType, int x, int y)//Adds a type of goodie based on the type. 1 = star, 2 = mushroom, 3 = flower
{
    if(goodieType==1)
    {
        actors.push_back(new Star(this, x, y));
    }
    else if(goodieType==2)
    {
        actors.push_back(new Mushroom(this, x, y));
    }
    else if(goodieType==3)
    {
        actors.push_back(new Flower(this, x, y));
    }
}

void StudentWorld::addProjectile(int type, int x, int y, int dir)//add projectile based on the type. 1 = peach fireball, 2 = piranha fireball, 3 = koopa shell
{
    if(type==1)
    {
        actors.push_back(new PeachFireball(this, x, y, dir));
    }
    else if (type==2)
    {
        actors.push_back(new PiranhaFireball(this, x, y, dir));
    }
    else if (type==3)
    {
        actors.push_back(new Shell(this, x, y, dir));
    }
}

int StudentWorld::randomDir()//generate random direction
{
    if(randInt(0,180)<90)
    {
        return 0;
    }
    else
    {
        return 180;
    }
}

string StudentWorld::determineText(bool star, bool flower, bool mushroom)//Determines the text that goes into the status line
{
    ostringstream os;
    os << "Lives: " << getLives() << "  Level: " << getLevel() << "  Points: " << getScore() << " ";
    if(star)
    {
        os << "StarPower! ";
    }
    if(flower)
    {
        os << "ShootPower! ";
    }
    if(mushroom)
    {
        os << "JumpPower! ";
    }

    string text = os.str();
    return text;
}
    
bool StudentWorld::PeachHasStar()
{
    return PeachPtr->hasStar();
}
    
void StudentWorld::givePeachPower(int type)//Gives peach a power.
{
    if(type==1)
    {
        PeachPtr->setPower(1);//gives peach star power.
    }
    if(type==2)
    {
        PeachPtr->setPower(2);//give peach mushroom power.
    }
    if(type==3)
    {
        PeachPtr->setPower(3);//give peach flower power 
    }
    
}
    
void StudentWorld::damageEnemy(Actor* enemy)
{
    enemy->getDamaged();
}
    

void StudentWorld::setPeachInvincible()
{
    PeachPtr->setStarLength();
}
int StudentWorld::init()
{
    Level lev(assetPath());
    ostringstream oss;
    oss.fill('0');
    int levelNum = getLevel();
    oss << "level" << setw(2) << levelNum << ".txt";
    string level_file = oss.str();//get name of level
    Level::LoadResult result = lev.loadLevel(level_file);
    if (result == Level::load_fail_file_not_found)
    {
        return GWSTATUS_LEVEL_ERROR;
    }
    else if (result == Level::load_fail_bad_format)//check for bad level loads
    {
        return GWSTATUS_LEVEL_ERROR;
    }
    
    for(int i = 0;i<GRID_WIDTH;i++)
    {
        for(int k = 0;k<GRID_HEIGHT;k++)//iterate through level grid
        {
            Level::GridEntry ge;
            ge = lev.getContentsOf(i, k);
            if(ge==Level::block)//check each individual space in the grid for what type of actor it is
            {
                actors.push_back(new Block(this, i*SPRITE_WIDTH, k*SPRITE_HEIGHT, 0));
            }
            if(ge==Level::star_goodie_block)
            {
                actors.push_back(new Block(this, i*SPRITE_WIDTH, k*SPRITE_HEIGHT, 1));
            }
            if(ge==Level::mushroom_goodie_block)
            {
                actors.push_back(new Block(this, i*SPRITE_WIDTH, k*SPRITE_HEIGHT, 2));
            }
            if(ge==Level::flower_goodie_block)
            {
                actors.push_back(new Block(this, i*SPRITE_WIDTH, k*SPRITE_HEIGHT, 3));
            }
            if(ge==Level::peach)
            {
                PeachPtr = new Peach(this, i*SPRITE_WIDTH, k*SPRITE_HEIGHT);
            }
            if(ge==Level::pipe)
            {
                actors.push_back(new Pipe(this, i*SPRITE_WIDTH, k*SPRITE_HEIGHT));
            }
            if(ge==Level::flag)
            {
                actors.push_back(new Flag(this, i*SPRITE_WIDTH, k*SPRITE_HEIGHT));
            }
            if(ge==Level::mario)
            {
                actors.push_back(new Mario(this, i*SPRITE_WIDTH, k*SPRITE_HEIGHT));
            }
            if(ge==Level::goomba)
            {
                actors.push_back(new Goomba(this, i*SPRITE_WIDTH, k*SPRITE_HEIGHT, randomDir()));
            }
            if(ge==Level::koopa)
            {
                actors.push_back(new Koopa(this, i*SPRITE_WIDTH, k*SPRITE_HEIGHT, randomDir()));
            }
            if(ge==Level::piranha)
            {
                actors.push_back(new Piranha(this, i*SPRITE_WIDTH, k*SPRITE_HEIGHT, randomDir()));
            }
        }
        
    }
    return GWSTATUS_CONTINUE_GAME;//continue the game
}

int StudentWorld::move()
{
    if(PeachPtr->isAlive())
    {
        PeachPtr->doSomething();//if peach is alive, do something
        if(!PeachPtr->isAlive())
        {
            playSound(SOUND_PLAYER_DIE);
            decLives();
            return GWSTATUS_PLAYER_DIED;
        }
    }
    
    for(int i = 0;i<actors.size();i++)
    {
            actors[i]->doSomething();//if actors are alive, do something
            if(!PeachPtr->isAlive())
            {
                playSound(SOUND_PLAYER_DIE);
                decLives();
                return GWSTATUS_PLAYER_DIED;
            }
    }

    
    if(levelComplete)
    {
        playSound(SOUND_FINISHED_LEVEL);
        levelComplete = false;
        return GWSTATUS_FINISHED_LEVEL;
    }
    
    if(gameComplete)
    {
        playSound(SOUND_GAME_OVER);
        return GWSTATUS_PLAYER_WON;
    }
    
    vector<Actor*>::iterator it;
    for(it = actors.begin();it!=actors.end();)
    {
        if(!(*it)->isAlive())
        {
            delete *it;
            it = actors.erase(it);//delete dead actors
        }
        else
        {
            it++;
        }
    }
    
    setGameStatText(determineText(PeachPtr->hasStar(), PeachPtr->hasFlower(), PeachPtr->hasMushroom()));
    
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::changeLevel()//if Peach reaches flag, call this
{
    levelComplete = true;
}

void StudentWorld::winGame()//if Peach reaches mario, call this
{
    gameComplete = true;
}


void StudentWorld::cleanUp()
{
    delete PeachPtr;
    vector<Actor*>::iterator it;
    for (it = actors.begin(); it != actors.end(); )// delete all Actors 
    {
        delete *it;
        it = actors.erase(it);
    }
        
}
