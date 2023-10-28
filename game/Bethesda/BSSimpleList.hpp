#pragma once
#include "MemoryManager.hpp"
#include <forward_list>

/*
template <typename Item> struct TListNode
{
	Item* data;
	TListNode* next;

	TListNode() : data(nullptr), next(nullptr) {}
	TListNode(Item* _data) : data(_data), next(nullptr) {}

	TListNode* RemoveMe()
	{
		if (next)
		{
			TListNode* pNext = next;
			data = next->data;
			next = next->next;
			GameHeapFree(pNext);
			return this;
		}
		data = NULL;
		return nullptr;
	}

};

template <class Item> class TList
{
public:
	typedef TListNode<Item> Node;

	Node	first;


	TList(Item* item = nullptr)
	{
		first.data = item;
		first.next = nullptr;
	}

	Node* GetLastNode() const
	{
		Node* node = Head();
		while (node->next) node = node->next;
		return node;
	}

	Node* GetLastNode(SInt32* outIdx) const
	{
		Node* node = Head();
		if (!node) return nullptr;
		if (outIdx)
		{
			SInt32 index = 0;
			while (node->next)
			{
				node = node->next;
				index++;
			}
			*outIdx = index;
		}
		return node;
	}

	Node* GetNthNode(SInt32 index) const
	{
		if (index < 0) return nullptr;

		Node* node = Head();
		do
		{
			if (!index) return node;
			index--;
		} while ((node = node->next));

		return nullptr;
	}

	Node* Head() const { return const_cast<Node*>(&first); }
	Node* Tail() const { return GetLastNode(); }

	bool Empty() const { return !first.data; }

	class Iterator
	{
		Node* m_curr;

	public:
		Iterator	operator++()
		{
			m_curr = m_curr->next;
			return *this;
		}
		Item*		operator->() const { return m_curr->data; }
		Item*&		operator*() const { return m_curr->data; }
		Iterator&	operator=(const Iterator& rhs)
		{
			m_curr = rhs.m_curr;
			return *this;
		}
		bool		operator!=(const Iterator& rhs) { return m_curr && m_curr->data; }

		Iterator() : m_curr(nullptr) {}
		Iterator(Node* node) : m_curr(node) {}
		Iterator(const TList* _list) : m_curr(const_cast<Node*>(& _list->first)) {}
		Iterator(TList& _list, Item* _item) : m_curr(&_list.first) { Find(_item); }
		Iterator(TList* _list, Item* _item) : m_curr(&_list->first) { Find(_item); }
	};

	Iterator begin() const { return Iterator(this); }
	Iterator end() const { return Iterator(); }

	UInt32 count() const
	{
		if (!first.data) return 0;
		UInt32 count = 0;
		for (const auto iter : *this) count++;
		return count;
	}

	bool contains(Item* item) const
	{
		for (const auto iter : *this) if (iter == item) return true;
		return false;
	}

	Item* GetFirstItem() const { return first.data; }

	Item* GetLastItem() const { return GetLastNode()->data; }

	SInt32 Append(Item* item)
	{
		SInt32 index = eListInvalid;
		if (item)
		{
			Node* node = GetLastNode(&index);
			if (node->data) node->Append(item);
			else node->data = item;
		}
		return index;
	}

	void Insert(Item* item)
	{
		if (item)
		{
			if (first.data) first.Insert(item);
			else first.data = item;
		}
	}

	void CopyFrom(TList& sourceList)
	{
		Node* target = Head(), * source = sourceList.Head();
		RemoveAll();
		if (!source->data) return;
		target->data = source->data;
		while (source = source->next)
			target = target->Append(source->data);
	}

	class AcceptItem
	{
		Item* m_toMatch;
	public:
		AcceptItem(Item* match) : m_toMatch(match) {}
		bool Accept(Item* match) { return m_toMatch == match; }
	};

	class AcceptNth
	{
		SInt32 m_toMatch	= 0;
		SInt32 m_current	= 0;
	public:
		AcceptNth(UInt32 match) : m_toMatch(match) {}
		bool Accept(Item* item)
		{
			if (m_toMatch == m_current) return true;
			m_current++;
			return false;
		}
	};

	class AcceptAll
	{
	public:
		bool Accept(Item* item) { return true; }
	};

	template <class Op> Item* Find(Op&& op) const
	{
		for (const auto iter : *this) if (op.Accept(iter)) return iter;
		return nullptr;
	}

	Item* Find(Item* item) const { return this->Find(AcceptItem(item)); }
	Item* GetNth(SInt32 index) const { return this->Find(AcceptNth(index)); }

	template <class Op> Iterator Find(Op&& op, Iterator& prev) const
	{
		Iterator curIt = prev.End() ? begin() : ++prev;
		while (!curIt.End())
		{
			if (*curIt && op.Accept(*curIt)) break;
			++curIt;
		}
		return curIt;
	}

	template <class Op> UInt32 CountIf(Op&& op) const
	{
		UInt32 count = 0;
		for (const auto iter : this) if (op.Accept(iter)) count++;
		return count;
	}

	UInt32 Count(Item* item) const { return this->CountIf(AcceptItem(item)); }

	template <class Op>	SInt32 GetIndexOf(Op&& op) const
	{
		SInt32 idx = 0;
		for (const auto iter : *this)
		{
			if (op.Accept(iter)) return idx;
			idx++;
		}
		return -1;
	}

	SInt32 GetIndexOfItem(Item* item) const { return this->GetIndexOf(AcceptItem(item)); }

	template <class Op>	UInt32 RemoveIf(Op&& compareOp, Node* node = nullptr) const
	{
		if (!node) node = Head();
		static UInt32 nodeCount = 0, numFreed = 0, lastNumFreed = 0;
		if (node->next)
		{
			nodeCount++;
			this->RemoveIf(compareOp, node->next);
			nodeCount--;
		}
		if (compareOp.Accept(node->data))
		{
			node->RemoveMe();
			numFreed++;
		}
		if (!nodeCount)
		{
			lastNumFreed = numFreed;
			numFreed = 0;
		}
		return lastNumFreed;
	}

	void RemoveAll() const { this->RemoveIf(AcceptAll()); }
	UInt32 RemoveItem(Item* item) const { return this->RemoveIf(AcceptItem(item)); }

	void DeleteAll() const
	{
		Node* nextNode = Head(), * currNode = nextNode->next;
		GameHeapFree(nextNode->data);
		nextNode->data = NULL;
		nextNode->next = NULL;
		while (currNode)
		{
			nextNode = currNode->next;
			currNode->data->~Item();
			GameHeapFree(currNode->data);
			GameHeapFree(currNode);
			currNode = nextNode;
		}
	}

	template <class Op>	UInt32 Replace(Op&& op, Item* replace)
	{
		UInt32 replaced = 0;
		for (auto iter : this) if (op.Accept(iter))
		{
			iter = replace;
			replaced++;
		}
		return replaced;
	}

	UInt32 ReplaceItem(Item* item, Item* replace)
	{
		return this->Replace(AcceptItem(item), replace);
	}

	Item* ReplaceNth(SInt32 index, Item* item)
	{
		Item* replaced = nullptr;
		if (item)
		{
			Node* node;
			if (eListEnd == index)
				node = GetLastNode();
			else
			{
				node = GetNthNode(index);
				if (!node) return nullptr;
			}
			replaced = node->data;
			node->data = item;
		}
		return replaced;
	}

	template <typename F> void ForEach(const F* f)
	{
		for (const auto iter : this) f(iter);
	}

	template <typename F> void ForEach(const F& f)
	{
		for (const auto iter : this) f(iter);
	}
};
static_assert(sizeof(TList<void*>) == 0x8);
static_assert(sizeof(std::forward_list<void*>) == 0x8);
*/

template <class T_Data> class BSSimpleList 
{
public:

	enum {
		eListCount = -3,
		eListEnd = -2,
		eListInvalid = -1,
	};

	BSSimpleList() : m_item(0), m_pkNext(0) { }
	~BSSimpleList() { 
		while (m_pkNext) {
			auto pNewNext = m_pkNext->m_pkNext;
			m_pkNext->m_pkNext = nullptr;
			if (m_pkNext)
				m_pkNext->~BSSimpleList();
			m_pkNext = pNewNext;
		}
		m_item = 0;
	}

	T_Data					m_item;
	BSSimpleList<T_Data>*	m_pkNext;

	__forceinline T_Data				GetItem() const { return m_item; }
	__forceinline BSSimpleList<T_Data>*	GetNext() const { return m_pkNext; }
	__forceinline bool					IsEmpty() { return !m_pkNext && !m_item; }

	class Iterator
	{
		BSSimpleList<T_Data>* m_curr;

	public:
		Iterator	operator++()
		{
			m_curr = m_curr->GetNext();
			return *this;
		}
		T_Data		operator->() const { return m_curr->GetItem(); }
		T_Data&		operator*() const { return m_curr->GetItem(); }
		Iterator&	operator=(const Iterator& rhs)
		{
			m_curr = rhs.m_curr;
			return *this;
		}
		bool		operator!=(const Iterator& rhs) { return m_curr && m_curr->data; }

		Iterator() : m_curr(nullptr) {}
		Iterator(BSSimpleList<T_Data>* node) : m_curr(node) {}
		Iterator(BSSimpleList<T_Data>& node) : m_curr(node) {}
//		Iterator(const TList* _list) : m_curr(const_cast<Node*>(& _list->first)) {}
//		Iterator(TList& _list, Item* _item) : m_curr(&_list.first) { Find(_item); }
//		Iterator(TList* _list, Item* _item) : m_curr(&_list->first) { Find(_item); }
	};

	Iterator begin() const { return Iterator(this); }
	Iterator end() const { return Iterator(); }

	UInt32 count() const
	{
		if (IsEmpty()) return 0;
		UInt32 count = 0;
		for (const auto iter : this) count++;
		return count;
	}

	bool contains(const T_Data& am_item) const
	{
		for (const auto iter : this) if (iter == am_item) return true;
		return false;
	}

	BSSimpleList<T_Data>* GetLastNode() const
	{
		auto node = Head();
		while (node->m_pkNext) node = node->m_pkNext;
		return node;
	}

	BSSimpleList<T_Data>* GetNthNode(SInt32 index) const
	{
		if (index < 0) return nullptr;

		auto node = Head();

		do
		{
			if (!index) return node;
			index--;
			node = node->m_pkNext;
		} while (node);

		return nullptr;
	}

	std::forward_list<T_Data> GetAsSTD() { return reinterpret_cast<std::forward_list<T_Data>>(*this); }

	BSSimpleList<T_Data>* RemoveMe()
	{
		if (m_pkNext)
		{
			BSSimpleList<T_Data>* pkNext = m_pkNext;
			m_item = m_pkNext->m_item;
			m_pkNext = m_pkNext->m_pkNext;
			GameHeapFree(pkNext);
			return this;
		}
		m_item = NULL;
		return nullptr;
	}

	BSSimpleList<T_Data>* RemoveNext()
	{
		BSSimpleList<T_Data>* pkNext = m_pkNext;
		m_pkNext = m_pkNext->m_pkNext;
		GameHeapFree(pkNext);
		return m_pkNext;
	}

	BSSimpleList<T_Data>* Append(T_Data am_item)
	{
		const auto newNode = static_cast<BSSimpleList<T_Data>*>(GameHeapAlloc(sizeof(BSSimpleList<T_Data>)));
		newNode->m_item = am_item;
		newNode->m_pkNext = m_pkNext;
		m_pkNext = newNode;
		return newNode;
	}

	BSSimpleList<T_Data>* Insert(T_Data am_item)
	{
		const auto newNode = static_cast<BSSimpleList<T_Data>*>(GameHeapAlloc(sizeof(BSSimpleList<T_Data>)));
		newNode->m_item = m_item;
		m_item = am_item;
		newNode->m_pkNext = m_pkNext;
		m_pkNext = newNode;
		return newNode;
	}

	SInt32 AddAt(T_Data am_item, const SInt32 index)
	{
		if (!index)
		{
			if (m_item) Insert(am_item);
			else m_item = am_item;
		}
		else if (eListEnd == index)
		{
			if (auto node = GetLastNode(&index); node && node->m_item) node->Append(am_item);
			else node->m_item = am_item;
		}
		else
		{
			auto node = GetNthNode(index);
			if (!node) return eListInvalid;
			node->Insert(am_item);
		}
		return index;
	}

	T_Data RemoveNth(SInt32 idx)
	{
		T_Data removed = NULL;
		if (idx <= 0)
		{
			removed = m_item;
			RemoveMe();
		}
		else
		{
			auto node = Head();
			while (node->m_pkNext && --idx)
				node = node->m_pkNext;
			if (!idx)
			{
				removed = node->m_pkNext->m_item;
				node->RemoveNext();
			}
		}
		return removed;
	};

	BSSimpleList<T_Data>* Head() { return this; }
	BSSimpleList<T_Data>* Tail() { return GetLastNode(); }
};
static_assert(sizeof(BSSimpleList<void*>) == 0x8);
//template <class T> using BSSimpleList = TList<T>;