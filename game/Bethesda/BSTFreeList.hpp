#pragma once

template <typename T_Data>
class BSTFreeList {
public:
	virtual void Destroy(bool doFree);

	UInt32 unk04;
	UInt32 unk08;
};

template <typename T_Data, UInt32 Size >
class BSTStaticFreeList : public BSTFreeList<T_Data> {
public:
	struct Data {
		T_Data item[Size];
	};

	Data data;
};