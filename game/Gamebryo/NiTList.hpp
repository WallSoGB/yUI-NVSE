#pragma once

#include "NiTPointerListBase.hpp"
#include "NiTDefaultAllocator.hpp"

template <typename Item> struct DListNode
{
	DListNode* next;
	DListNode* prev;
	Item* data;

	DListNode* Advance(UInt32 times)
	{
		DListNode* result = this;
		while (result && times)
		{
			times--;
			result = result->next;
		}
		return result;
	}

	DListNode* Regress(UInt32 times)
	{
		DListNode* result = this;
		while (result && times)
		{
			times--;
			result = result->prev;
		}
		return result;
	}

};

template <class Item> class DList
{
public:
	typedef DListNode<Item> Node;

private:
	Node*		first = nullptr;
	Node*		last = nullptr;
	UInt32		count = 0;

public:

	class Iterator
	{
		Node* m_curr;

	public:
		Iterator	operator++()
		{
			m_curr = m_curr->next;
			return *this;
		}
		Item* operator->() const { return m_curr->data; }
		Item*& operator*() const { return m_curr->data; }
		Iterator& operator=(const Iterator& rhs)
		{
			m_curr = rhs.m_curr;
			return *this;
		}
		bool		operator!=(const Iterator& rhs) { return m_curr && m_curr->data; }

		Iterator() : m_curr(nullptr) {}
		Iterator(Node* node) : m_curr(node) {}
		Iterator(DList& _list, Item* _item) : m_curr(&_list.first) { Find(_item); }
		Iterator(DList* _list, Item* _item) : m_curr(&_list->first) { Find(_item); }
	};

	bool Empty() const { return !first; }
	Node* Head() { return first; }
	Node* Tail() { return last; }
	UInt32 Count() const { return count; }

	Iterator begin() const { return Iterator(first); }
	Iterator end() const { return Iterator(); }

	void ExchangeNodeData(Node* node1, Node* node2)
	{
		const auto tmpdata = node1->data;
		node1->data = node2->data;
		node2->data = tmpdata;
	}

	void Append(Item* item) { ThisCall(0x4ED8C0, this, &item); }

	template <typename F> void ForEach(const F& f)
	{
		for (const auto iter : this)
			f(iter);
	}

	Node* Remove(Item* item)
	{
		// return the item before the removed entry, or first if previous is null
		Node* result = nullptr;

		Node* node = Head();
		if (!node) return result;

		if (node->data == item)
		{
			first = node->next;
			if (first) first->prev = nullptr;
			else last = nullptr;

			--count;
			StdCall(0x4A49E0, node);
			node = first;
		}
		else
		{
			node = node->next;
		}

		if (node)
		{
			do if (node->data == item)
			{
				result = node->prev;
				if (node->prev) node->prev->next = node->next;
				if (node->next)	node->next->prev = node->prev;
				else last = node->prev;
				--count;
				StdCall(0x4A49E0, node);
			}
			while ((node = node->next));
		}
		return result ? result : first;
	}

	void Sort(int (*compare)(Item* a, Item* b))
	{
		if (!first) return;
		Node* current = first;
		while (current->next)
		{
			Node* index = current->next;
			while (index)
			{
				if (compare(current->data, index->data) > 0)
				{
					Item* temp = current->data;
					current->data = index->data;
					index->data = temp;
				}
				index = index->next;
			}
			current = current->next;
		}
	}

	Node* GetNthChild(UInt32 n)
	{
		auto node = first;
		while (n--) node = node->next;
		return node;
	}
};
static_assert(sizeof(DList<void*>) == 0xC);
static_assert(sizeof(std::list<void*>) == 0xC);


template <class T_Data> 
class NiTList : public NiTPointerListBase<NiTDefaultAllocator<T_Data>, T_Data> {};
static_assert(sizeof(NiTList<void*>) == 0xC);