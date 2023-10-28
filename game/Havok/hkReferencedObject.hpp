#pragma once

#include "hkBaseObject.hpp"

class hkReferencedObject : public hkBaseObject {
public:
	UInt16 m_memSizeAndFlags;
	UInt16 m_usReferenceCount;
};

ASSERT_SIZE(hkReferencedObject, 0x8);