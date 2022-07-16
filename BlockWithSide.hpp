#pragma once

#include "Block.hpp"
#include "Side.hpp"

struct BlockWithSide {
  BlockPos pos;
  Side side = Side::Null;
};
