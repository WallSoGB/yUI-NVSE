#pragma once

#include "BSTCommonMessageQueue.hpp"

template <class T_Data>
class BSTCommonLLMessageQueue : public BSTCommonMessageQueue<T_Data> {
public:
	UInt32 unk08;
	UInt32 unk0C;
	UInt32 unk010;
};