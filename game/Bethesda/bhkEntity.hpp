#pragma once
#include "bhkWorldObject.hpp"

class bhkEntity : public bhkWorldObject {
public:
};
static_assert(sizeof(bhkEntity) == 0x14);