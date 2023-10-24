#pragma once
#include <Utilities.h>

enum {
	eListCount = -3,
	eListEnd = -2,
	eListInvalid = -1,
};

enum KeyboardMenuInputCode;

template <class Node, class Info>
class Visitor
{
	const Node* m_pHead;

	template <class Op>
	UInt32 FreeNodes(Node* node, Op& compareOp) const
	{
		static UInt32 nodeCount = 0;
		static UInt32 numFreed = 0;
		static Node* lastNode = nullptr;
		static bool bRemovedNext = false;

		if (node->Next())
		{
			nodeCount++;
			FreeNodes(node->Next(), compareOp);
			nodeCount--;
		}

		if (compareOp.Accept(node->Info()))
		{
			if (nodeCount) node->Delete();
			else node->DeleteHead(lastNode);
			numFreed++;
			bRemovedNext = true;
		}
		else
		{
			if (bRemovedNext) node->SetNext(lastNode);
			bRemovedNext = false;
			lastNode = node;
		}

		const UInt32 returnCount = numFreed;

		if (!nodeCount)	//reset vars after recursing back to head
		{
			numFreed = 0;
			lastNode = NULL;
			bRemovedNext = false;
		}

		return returnCount;
	}

	class AcceptAll {
	public:
		bool Accept(Info* info) {
			return true;
		}
	};

	class AcceptEqual {
		const Info* m_toMatch;
	public:
		AcceptEqual(const Info* info) : m_toMatch(info) { }
		bool Accept(const Info* info) { return info == m_toMatch; }
	};

	class AcceptStriCmp {
		const char* m_toMatch;
	public:
		AcceptStriCmp(const char* info) : m_toMatch(info) { }
		bool Accept(const char* info) { return m_toMatch && info ? !_stricmp(info, m_toMatch) ? true : false : false; }
	};
public:
	Visitor(const Node* pHead) : m_pHead(pHead) { }

	UInt32 Count() const {
		UInt32 count = 0;
		const Node* pCur = m_pHead;
		while (pCur && pCur->Info() != NULL) {
			++count;
			pCur = pCur->Next();
		}
		return count;
	}

	Info* GetNthInfo(UInt32 n) const {
		UInt32 count = 0;
		const Node* pCur = m_pHead;
		while (pCur && count < n && pCur->Info() != NULL) {
			++count;
			pCur = pCur->Next();
		}
		return (count == n && pCur) ? pCur->Info() : NULL;
	}

	template <class Op>
	void Visit(Op&& op) const {
		const Node* pCur = m_pHead;
		bool bContinue = true;
		while (pCur && pCur->Info() && bContinue) {
			bContinue = op.Accept(pCur->Info());
			if (bContinue) pCur = pCur->Next();
		}
	}

	template <class Op>
	const Node* Find(Op&& op, const Node* prev = NULL) const
	{
		const Node* pCur;
		if (!prev) pCur = m_pHead;
		else pCur = prev->next;
		bool bFound = false;
		while (pCur && !bFound)
		{
			if (pCur->Info())
			{
				bFound = op.Accept(pCur->Info());
				if (!bFound) pCur = pCur->Next();
			}
			else pCur = pCur->Next();
		}
		return pCur;
	}

	Node* FindInfo(const Info* toMatch) { return Find(AcceptEqual(toMatch)); }

	template <class Op>
	UInt32 CountIf(Op&& op) const
	{
		UInt32 count = 0;
		const Node* pCur = m_pHead;
		while (pCur)
		{
			if (pCur->Info() && op.Accept(pCur->Info())) count++;
			pCur = pCur->Next();
		}
		return count;
	}

	const Node* GetLastNode() const
	{
		const Node* pCur = m_pHead;
		while (pCur && pCur->Next()) pCur = pCur->Next();
		return pCur;
	}

	void RemoveAll() const { FreeNodes(const_cast<Node*>(m_pHead), AcceptAll()); }

	template <class Op>
	UInt32 RemoveIf(Op&& op) { return FreeNodes(const_cast<Node*>(m_pHead), op); }

	bool Remove(const Info* toRemove) { return RemoveIf(AcceptEqual(toRemove)) ? true : false; }

	bool RemoveString(const char* toRemove) { return RemoveIf(AcceptStriCmp(toRemove)) ? true : false; }

	void Append(Node* newNode)
	{
		Node* lastNode = const_cast<Node*>(GetLastNode());
		if (lastNode == m_pHead && !m_pHead->Info()) lastNode->DeleteHead(newNode);
		else lastNode->SetNext(newNode);
	}

	template <class Op>
	UInt32 GetIndexOf(Op&& op)
	{
		UInt32 idx = 0;
		const Node* pCur = m_pHead;
		while (pCur && pCur->Info() && !op.Accept(pCur->Info()))
		{
			idx++;
			pCur = pCur->Next();
		}

		if (pCur && pCur->Info()) return idx;
		return -1;
	}
};

struct CoordXY
{
	Float32	x;
	Float32	y;

	CoordXY() : x(0), y(0) {}

	CoordXY(float _x, float _y) : x(_x), y(_y) {}

	inline CoordXY& operator =(const CoordXY& rhs)
	{
		*(Float64*)this = *(Float64*)&rhs;
		return *this;
	}
};
