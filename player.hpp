#pragma once

#include "main.hpp"
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
public:
  Camera camera;

  //Default constructor
  Player();

  //Default destructor
  ~Player();

  //Assign move direction
  void setMoveDirection(Side side, bool value);

  //Tries to place block
  void placeBlock();

  //Tries to break block
  void breakBlock();

  //Move player by offest
  void move(const Vec3d offset);

  //Updating player
  void update(const Time time);

  //Draws player and block mouse over
  void draw() const;
};