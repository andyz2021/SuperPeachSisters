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
  void addGoodie(int goodieType, int x, int y);
  void addProjectile(int type, int x, int y, int dir);
  int overlap(int x, int y, bool bonk, bool onlyBlocks);
  bool extendOverSpace(int x, int y);
  int randomDir();
  bool overlapPeach(int x, int y, bool bonk);
  bool PeachHasStar();
  void setPeachInvincible();
  void givePeachPower(int type);
  void damageEnemy(Actor* enemy);
  std::string determineText(bool star, bool flower, bool mushroom);
  int getPeachX();
  int getPeachY();

    
  ~StudentWorld()
    {
        cleanUp();
    }

private:
    std::vector<Actor*> actors;
    Peach* PeachPtr;
    bool levelComplete;
    bool gameComplete;
    
};

#endif // STUDENTWORLD_H_
