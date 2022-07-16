#pragma once

#include "main.hpp"
#include "Camera.hpp"
#include "Block.hpp"
#include "Time.hpp"
#include "Side.hpp"
#include "BlockWithSide.hpp"

class Player {
public:

  Camera camera;

  //Default constructor
  Player() = default;

  //Default destructor
  ~Player() = default;

  //Assign move direction
  void walk(const Side side, const bool value);

  //Tries to place block
  void placeBlock();

  //Tries to break block
  void breakBlock();

  //Move player by offest
  void move(const Vec3d& offset);

  //Updating player
  void update(const Time& time);

  //Draws player and block mouse over
  void draw() const;
protected:

  Vec3d position_;
  Vec3d velocity_;
  float_t moveSpeed_ = 0.005F;
  float_t jumpHeight = 1.1F;
  float_t colorDeg = 0;

  BlockWithSide blockMouseOver_;
  Side moveDir_ = Side::Null;
  bool isBlockMouseOver_ = false;
  bool onGround_ = false;
};
