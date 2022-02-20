#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
#include <iostream> // defines the overloads of the << operator
#include <sstream>  // defines the type std::ostringstream
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

int StudentWorld::overlap(int x, int y, bool bonk)//detect overlap. Returns 2 if the overlap is with an object that blocks movement, returns 1 if it doesn't block movement, returns 0 otherwise
{
    for(int i = 0;i<actors.size();i++)
    {
        if(actors[i]->getX() <= x && actors[i]->getX()+SPRITE_WIDTH-1 >= x && actors[i]->getY() <= y && actors[i]->getY()+SPRITE_HEIGHT-1 >= y)//if the bottom left overlaps any block/pipe
        {
            if(bonk==true)
            {
                actors[i]->bonk();
            }
            if(actors[i]->blockMovement())
            {
                return 2;
            }
            return 1;
        }
        if(actors[i]->getX() <= x+SPRITE_WIDTH-1 && actors[i]->getX()+SPRITE_WIDTH-1 >= x+SPRITE_WIDTH-1 && actors[i]->getY() <= y+SPRITE_HEIGHT-1 && actors[i]->getY()+SPRITE_HEIGHT-1 >= y+SPRITE_HEIGHT-1 )//if top right overlaps
        {
            
            if(bonk==true)
            {
                actors[i]->bonk();
            }
            if(actors[i]->blockMovement())
            {
                return 2;
            }
            return 1;
        }
        if(actors[i]->getX() <= x && actors[i]->getX()+SPRITE_WIDTH-1 >= x && actors[i]->getY() <= y+SPRITE_HEIGHT-1 && actors[i]->getY()+SPRITE_HEIGHT-1 >= y+SPRITE_HEIGHT-1 )//if top left overlaps
        {
            if(bonk==true)
            {
                actors[i]->bonk();
            }
            if(actors[i]->blockMovement())
            {
                return 2;
            }
            return 1;
        }
        if(actors[i]->getX() <= x+SPRITE_WIDTH-1 && actors[i]->getX()+SPRITE_WIDTH-1 >= x+SPRITE_WIDTH-1 && actors[i]->getY() <= y && actors[i]->getY()+SPRITE_HEIGHT-1 >= y)//if bottom right overlaps
        {
            if(bonk==true)
            {
                actors[i]->bonk();
            }
            if(actors[i]->blockMovement())
            {
                return 2;
            }
            return 1;
        }
    }
    return false;
}

bool StudentWorld::overlapPeach(int x, int y)//returns true if the object overlaps with Peach, false otherwise 
{
    
    if(PeachPtr->getX() <= x && PeachPtr->getX()+SPRITE_WIDTH-1 >= x && PeachPtr->getY() <= y && PeachPtr->getY()+SPRITE_HEIGHT-1 >= y)//if the bottom left overlaps any block/pipe
    {
        return true;
    }
    if(PeachPtr->getX() <= x+SPRITE_WIDTH-1 && PeachPtr->getX()+SPRITE_WIDTH-1 >= x+SPRITE_WIDTH-1 && PeachPtr->getY() <= y+SPRITE_HEIGHT-1 && PeachPtr->getY()+SPRITE_HEIGHT-1 >= y+SPRITE_HEIGHT-1 )//if top right overlaps
    {
        return true;
    }
    if(PeachPtr->getX() <= x && PeachPtr->getX()+SPRITE_WIDTH-1 >= x && PeachPtr->getY() <= y+SPRITE_HEIGHT-1 && PeachPtr->getY()+SPRITE_HEIGHT-1 >= y+SPRITE_HEIGHT-1 )//if top left overlaps
    {
        return true;
    }
    if(PeachPtr->getX() <= x+SPRITE_WIDTH-1 && PeachPtr->getX()+SPRITE_WIDTH-1 >= x+SPRITE_WIDTH-1 && PeachPtr->getY() <= y && PeachPtr->getY()+SPRITE_HEIGHT-1 >= y )//if bottom right overlaps
    {
        return true;
    }
    return false;
}


void StudentWorld::addStar(int x, int y)
{
    actors.push_back(new Star(this, x, y));
    //Add new Star
}
void StudentWorld::addMushroom(int x, int y)
{
    actors.push_back(new Mushroom(this, x, y));
    //Add new Mushroom
}
void StudentWorld::addFlower(int x, int y)
{
    actors.push_back(new Flower(this, x, y));
    //Add new Flower
}
int StudentWorld::init()
{
    Level lev(assetPath());
    ostringstream oss;
    oss.fill('0');
    int levelNum = getLevel();
    oss << "level" << setw(2) << levelNum << ".txt";
    string level_file = "level01.txt";
    //string level_file = oss.str();
    Level::LoadResult result = lev.loadLevel(level_file);
    if (result == Level::load_fail_file_not_found)
    {
        return GWSTATUS_LEVEL_ERROR;
    }
    else if (result == Level::load_fail_bad_format)
    {
        return GWSTATUS_LEVEL_ERROR;
    }
    
    for(int i = 0;i<GRID_WIDTH;i++)
    {
        for(int k = 0;k<GRID_HEIGHT;k++)
        {
            Level::GridEntry ge;
            ge = lev.getContentsOf(i, k);
            if(ge==Level::block)
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
        }
        
    }
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    if(PeachPtr->isAlive())
    {
        PeachPtr->doSomething();
    }
    for(int i = 0;i<actors.size();i++)
    {
        if(actors[i]->isAlive())
        {
            actors[i]->doSomething();
        }
    }
    /*
    vector<Actor*>::iterator it;
    for(it = actors.begin();it!=actors.end();)
    {
        if(!(*it)->isAlive())
        {
            it = actors.erase(it);
            delete *it;
        }
        else
        {
            it++;
        }
    }
    */
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::changeLevel()
{
    levelComplete = true;
}

void StudentWorld::winGame()
{
    gameComplete = true;
}


void StudentWorld::cleanUp()
{
    delete PeachPtr;
    vector<Actor*>::iterator it;
    for (it = actors.begin(); it != actors.end(); )// notice: no it++
    {
        it = actors.erase(it);
    }
        
}
