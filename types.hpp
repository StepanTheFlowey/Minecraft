#pragma once 

//SFML
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

//OpenGL
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glext.h>
#include <gl/wglext.h>

#include "aabb.hpp"
#include "vec.hpp"
#include "plane.hpp"
#include "rayTraceResult.hpp"

//Math defines
#define PI 3.1415926535897932384626433832795
#define DEG_TO_RAD 0.017453292519943295769236907684886

//Bit operation defines
#define bitRead(value, bit) (((value) >> (bit))&0x1)
#define bitSet(value, bit) ((value) |= (1 << (bit)))
#define bitClear(value, bit) ((value) &= ~(1 << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))

#define DEPRECATED [[deprecated("This function is deprecated and is not recommended to use it")]]

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

using SmallPos = Vec3<uint8_t>;
using BlockPos = Vec3<blockPos_t>;
using ChunkPos = Vec3<chunkPos_t>;
using RegionPos = Vec2<regionPos_t>;

using Planed = Plane<GLdouble>;
using Planef = Plane<GLfloat>;

using BlockPlane = Plane<blockPos_t>;

using RayTraceResultd = RayTraceResult<GLdouble>;
using RayTraceResultf = RayTraceResult<GLfloat>;