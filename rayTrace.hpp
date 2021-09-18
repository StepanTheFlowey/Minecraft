#pragma once
#include "vec.hpp"
#include "plane.hpp"
#include "math.hpp"

template <typename T> class RayTrace {
  bool hit_ = false;
  Vec3<T> hitPos_;
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
    Vec3<T> A(plane.x, plane.y, plane.z); //Point on the plane
    Vec3<T> N = getNormal(plane);         //Normal to plane

    Vec3<T> CA = A - lineBegin;           //Vector from A to lineBegin
    Vec3<T> CV = lineEnd - lineBegin;     //Vector from lineEnd to lineBegin

    T CN = dotProduct(CA, N);             //Shortest distance between plane and line
    if(CN == 0) {
      return;                             //If distance zero return
    }

    T CM = dotProduct(CV, N);
    T K = CN / CM;
    if(K <= 0.0 || K > 1.0) {
      return;                             //if k = 0 or k > 1 line does not reach plane
    }

    hitPos_ = CV * K;                     //Collision point on plane
    Vec3<T> X = CV * K + lineBegin        //Global collision point
                                          //Check if point located on the plane
      if(X.x > plane.x + plane.vX || X.y > plane.y + plane.vY || X.z > plane.z + plane.vZ) {
        return;
      }
    if(X.x < plane.x || X.y < plane.y || X.z < plane.z) {
      return;
    }
    hit_ = true;
  }
};