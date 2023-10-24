#pragma once

template <typename T> class BSSimpleArray 
{
public:
	virtual			~BSSimpleArray();
	virtual T*		Allocate(UInt32);
	virtual void*	FreeArg(UInt32);
	virtual void*	Resize4BytesMemebers(UInt32);

	T*		pData;
	UInt32	uiSize;
	UInt32	uiAllocSize;

	// this only compiles for pointer types
	T operator[](UInt32 idx) { return idx < uiSize ? pData[idx] : NULL; }

	UInt32 GetSize() { return uiSize; }
	UInt32 GetAllocSize() { return uiAllocSize; }
	bool IsEmpty() { return uiSize == 0; }

	class Iterator
	{
	protected:
		friend BSSimpleArray;

		T*			pData;
		UInt32		count;

	public:
		bool End() const { return !count; }
		void operator++()
		{
			count--;
			pData++;
		}

		Item& operator*() const { return *pData; }
		Item& operator->() const { return *pData; }
		bool operator!=(const Iterator& rhs) { return pData != rhs.pData; }

		Iterator() : pData(nullptr), count(0) {}
		Iterator(const BSSimpleArray& source) : pData(source.data), count(source.size) {}
		Iterator(const BSSimpleArray* source) : pData(source->data), count(source->size) {}

	};

	Iterator begin() const { return Iterator(); }
	Iterator end() const { return Iterator(this); }

	void Append(T* item) { ThisCall(0x7CB2E0, this, item); }
};
static_assert(sizeof(BSSimpleArray<void*>) == 0x10);