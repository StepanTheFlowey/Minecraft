#pragma once
#include "vec.hpp"
#include "plane.hpp"
#include "math.hpp"

template <typename T> class RayTrace {
public:
  RayTrace() {

  }

  constexpr bool getHit() {
    return hit_;
  }

  constexpr Vec3<T> getHitPosition() {
    return hitPos_;
  }

  void planeLineCollision(Plane<T> plane, Vec3<T> lineBegin, Vec3<T> lineEnd) {
    hit_ = false;
    Vec3<T> N = getNormal(plane);         //Normal to plane
    
    Vec3<T> CA = plane.A - lineBegin;     //Vector from A to lineBegin
    Vec3<T> CV = lineEnd - lineBegin;     //Vector from lineEnd to lineBegin

    T CN = dotProduct(CA, N);             //Distance between plane and line
    if(CN <= 0.0) {
      return;                             //If distance zero return
    }

    T CM = dotProduct(CV, N);
    if(abs(CM) < 0.0001) {
      return;
    }

    T K = CN / CM;
    if(K < 0.0 || K > 1.0) {
      return;                             //if k < 0 or k > 1 line does not reach plane
    }

    hitPos_ = CV * K + lineBegin - plane.A + Vec3<T>(abs(N.y) + abs(N.z), 0.0, 0.0);                     //Collision point on plane
    if(
      hitPos_.x < 0 ||
      hitPos_.y < 0 ||
      hitPos_.z < 0 ||
      hitPos_.x > 1 ||
      hitPos_.y > 1 ||
      hitPos_.z > 1
      ) {
      return;
    }
    hit_ = true;
  }
};

struct RayTraceResult {
  bool hit_ = false;
  enum class HitType:bool {
    Block,
    Entity
  };
  BlockPos hitPos_;
};