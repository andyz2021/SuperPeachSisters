#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_
#include <vector>
#include "GameWorld.h"
#include "Level.h"
#include "Actor.h"
#include <string>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp


class StudentWorld : public GameWorld
{
public:
  StudentWorld(std::string assetPath);
  virtual int init();
  virtual int move();
  virtual void cleanUp();
  void changeLevel();
  void winGame();
  Actor* overlap(int x, int y);
  Actor* overlapPeach(int x, int y);
    
  ~StudentWorld()
    {
        cleanUp();
    }

private:
    std::vector<Actor*> actors;
    Actor* PeachPtr;
    bool levelComplete;
    bool gameComplete;
    
};

#endif // STUDENTWORLD_H_
