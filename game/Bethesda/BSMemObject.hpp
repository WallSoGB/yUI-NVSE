#pragma once

#include "MemoryManager.hpp"

class BSMemObject {
public:
	static void*	operator new(size_t stSize);
	static void	 operator delete(void* apMem);
};