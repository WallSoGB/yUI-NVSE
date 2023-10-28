#pragma once

template <typename T_Data>
class BSSimpleArray {
public:
	virtual ~BSSimpleArray();
	virtual T_Data* Allocate(UInt32 auiCount);
	virtual void* FreeArg(UInt32);
	virtual void* ResizeBuffer(T_Data* apData, UInt32 auiCount);

	T_Data*	pBuffer;
	UInt32	uiSize;
	UInt32	uiAllocSize;

	// this only compiles for pointer types
	T_Data operator[](UInt32 idx) {
		if (idx < uiSize)
			return pBuffer[idx];
		return NULL;
	}

	UInt32 GetSize() { return uiSize; }
	UInt32 GetAllocSize() { return uiAllocSize; }
	bool IsEmpty() { return uiSize == 0; }
	bool IsFull() { return uiSize == uiAllocSize; }

	class Iterator
	{
	protected:
		friend BSSimpleArray;

		T_Data*		pData;
		UInt32		count;

	public:
		bool End() const { return !count; }
		void operator++()
		{
			count--;
			pData++;
		}

		T_Data& operator*() const { return *pData; }
		T_Data& operator->() const { return *pData; }
		bool operator!=(const Iterator& rhs) { return pData != rhs.pData; }

		Iterator() : pData(nullptr), count(0) {}
		Iterator(const BSSimpleArray& source) : pData(source.data), count(source.size) {}
		Iterator(const BSSimpleArray* source) : pData(source->data), count(source->size) {}

	};

	Iterator begin() const { return Iterator(); }
	Iterator end() const { return Iterator(this); }

	void Append(T_Data* item) { ThisCall(0x7CB2E0, this, item); }
};
static_assert(sizeof(BSSimpleArray<void*>) == 0x10);