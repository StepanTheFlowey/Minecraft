#pragma once

#include "types.hpp"
#include "world.hpp"
#include "block.hpp"
#include "camera.hpp"
#include "time.hpp"
#include "side.hpp"

class Player {
  Vec3d position_;
  Side moveDir_ = Side::None;
  double_t moveSpeed_ = 0.005;

  std::shared_ptr<World> worldIn_ = nullptr;

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
  void setMoveDirection(Side);

  //Tries to break block
  void breakBlock();

  //Tries to place block
  void placeBlock();

  //Set world pointer
  void setWorldIn(std::shared_ptr<World>);

  //Move player by offest
  void move(Vec3d);

  //Updating player
  void update(Time);

  //Draws player and block mouse over
  void draw();
};