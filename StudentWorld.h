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
  ~StudentWorld()
    {
        cleanUp();
    }
  std::vector<Actor*> getActors()
  {
        return actors;
  }

private:
    std::vector<Actor*> actors;
    Actor* PeachPtr;
    bool levelComplete;
    bool gameComplete;
    
};

#endif // STUDENTWORLD_H_
