#pragma once
#include "types.hpp"
#include "world.hpp"
#include "camera.hpp"

class Player {
  uint8_t walkParam_ = 0;                 //Active walk dir 
  double_t walkSpeed_ = 0.005;            //Player walk speed
  Vec3d position_;

  std::shared_ptr<World> worldIn_ = nullptr;                //World in

  float_t colorDeg = 0;
  BlockWithSide blockMouseOver_;
  bool isBlockMouseOver_ = false;
public:
  Camera camera; //Camera object

  //Description
  Player();
  //Description
  ~Player();

  //Disable or enable walking in specific direction
  //TODO: replace this by func(enum or uint8_t walkDir, bool value);
 
  //Description
  void goForward(bool value);
  //Description
  void goBack(bool value);
  //Description
  void goLeft(bool value);
  //Description
  void goRight(bool value);
  //Description
  void goUp(bool value);
  //Description
  void goDown(bool value);
  //Description
  void breakBlock();
  //Description
  void placeBlock();
  //Description
  void setWorldIn(std::shared_ptr<World> worldIn);
  //Description
  void move(double_t x, double_t y, double_t z);
  //Description
  void update(gametime_t timeLeft);
  //Description
  void draw();
};