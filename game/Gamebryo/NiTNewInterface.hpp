#pragma once

#include "NiMemory.hpp"

template <class T_Data>
class NiTNewInterface {
public:
    // 0x869840
    static T_Data* Allocate(UInt32 uiNumElements) {
        return new T_Data[uiNumElements];
    };

    // 0x8696C0
    static void Deallocate(T_Data* pArray) {
        delete[] pArray;
    };
};