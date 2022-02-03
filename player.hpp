#pragma once

#include "types.hpp"
#include "world.hpp"
#include "block.hpp"
#include "camera.hpp"
#include "time.hpp"
#include "side.hpp"

class Player {
  Vec3d position_;
  Side moveDir_ = Side::Null;
  double_t moveSpeed_ = 0.005;
  bool onGround_ = false;

  float_t colorDeg = 0;
  BlockWithSide blockMouseOver_;
  bool isBlockMouseOver_ = false;

  World* worldIn_ = nullptr;
public:
  Camera camera;

  //Default constructor
  Player();

  //Default destructor
  ~Player();

  //Assign move direction
  void setMoveDirection(Side, bool);

  //Tries to place block
  void placeBlock();
  
  //Tries to break block
  void breakBlock();

  //Set world pointer
  void setWorldIn(World* worldInPtr);

  //Move player by offest
  void move(const Vec3d);

  //Updating player
  void update(const Time);

  //Draws player and block mouse over
  void draw() const;
};