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
                actors.push_back(new Block(this, i*SPRITE_WIDTH, k*SPRITE_HEIGHT, IID_STAR));
            }
            if(ge==Level::mushroom_goodie_block)
            {
                actors.push_back(new Block(this, i*SPRITE_WIDTH, k*SPRITE_HEIGHT, IID_MUSHROOM));
            }
            if(ge==Level::flower_goodie_block)
            {
                actors.push_back(new Block(this, i*SPRITE_WIDTH, k*SPRITE_HEIGHT, IID_FLOWER));
            }
            if(ge==Level::peach)
            {
                PeachPtr = new Peach(this, i*SPRITE_WIDTH, k*SPRITE_HEIGHT);
            }
            if(ge==Level::pipe)
            {
                actors.push_back(new Pipe(this, i*SPRITE_WIDTH, k*SPRITE_HEIGHT));
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
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    delete PeachPtr;
    vector<Actor*>::iterator it;
    for (it = actors.begin(); it != actors.end(); ) // notice: no it++
        it = actors.erase(it);
}
