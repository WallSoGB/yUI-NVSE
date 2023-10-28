#pragma once
#include "bhkSerializable.hpp"

class bhkMigrationWorld;

class bhkWorldObject : public bhkSerializable {
public:
	bhkWorldObject();
	virtual ~bhkWorldObject();

	virtual void	Unk_49();								// 49
	virtual void	ForceAdd(void*);						// 50
	virtual NiNode* CreateDisplayGeometry(NiNode* apNode);	// 51
	virtual void	DestroyDisplayGeometry();				// 52

	UInt32 uiBodyFlags;
};
static_assert(sizeof(bhkWorldObject) == 0x14);