#pragma once 
#include <gl/GL.h>
#include "aabb.hpp"
#include "vec.hpp"
#include "plane.hpp"
#include "rayTrace.hpp"

//Data types
using size_t = std::size_t;
using shortsize_t = uint32_t;
using shortersize_t = uint16_t;

using gametime_t = int32_t;

using blockId_t = uint16_t;
using modelId_t = uint16_t;
using textureId_t = GLuint;

using regionPos_t = int16_t;
using chunkPos_t = int32_t;
using blockPos_t = int32_t;

using BlockAabb = Aabb<blockPos_t>;
using ChunkAabb = Aabb<chunkPos_t>;
using RegionAabb = Aabb<regionPos_t>;

using Vec2f = Vec2<GLfloat>;
using Vec2d = Vec2<GLdouble>;

using Vec3f = Vec3<GLfloat>;
using Vec3d = Vec3<GLdouble>;

using BlockPos = Vec3<blockPos_t>;
using ChunkPos = Vec3<chunkPos_t>;
using RegionPos = Vec2<regionPos_t>;

using Planed = Plane<GLdouble>;
using Planef = Plane<GLfloat>;

using BlockPlane = Plane<blockPos_t>;

using RayTraced = RayTrace<double_t>;
using RayTracef = RayTrace<float_t>;