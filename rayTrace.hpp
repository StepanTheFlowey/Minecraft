#pragma once
#include "vec.hpp"
#include "plane.hpp"
#include "math.hpp"

struct RayTraceResult {
  BlockPos pos;
  Side side;
  bool hit = false;
  enum class HitType : bool {
    Block,
    Entity
  };
};

template <typename T> class RayTrace {
public:
  RayTrace() {

  }

  RayTraceResult planeLineCollision(Plane<T> plane, Vec3<T> lineBegin, Vec3<T> lineEnd) {
    RayTraceResult result;
    Vec3<T> N = math::getNormal(plane);         //Normal to plane
    
    Vec3<T> CA = plane.A - lineBegin;     //Vector from A to lineBegin
    Vec3<T> CV = lineEnd - lineBegin;     //Vector from lineEnd to lineBegin

    T CN = math::dotProduct(CA, N);             //Distance between plane and line
    if(CN <= 0.0) {
      return result;                             //If distance zero return
    }

    T CM = math::dotProduct(CV, N);
    if(abs(CM) < 0.0001) {
      return result;
    }

    T K = CN / CM;
    if(K < 0.0 || K > 1.0) {
      return result;                       //if k < 0 or k > 1 line does not reach plane
    }

    result.pos = CV * K + lineBegin - plane.A + Vec3<T>(abs(N.y) + abs(N.z), 0.0, 0.0);                     //Collision point on plane
    if(
      result.pos.x < 0 ||
      result.pos.y < 0 ||
      result.pos.z < 0 ||
      result.pos.x > 1 ||
      result.pos.y > 1 ||
      result.pos.z > 1
      ) {
      return result;
    }
    result.hit = true;
    return result;
  }
};