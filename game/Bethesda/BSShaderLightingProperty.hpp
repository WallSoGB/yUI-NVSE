#pragma once

#include "BSShaderProperty.hpp"
#include "NiTListBase.hpp"

NiSmartPointer(BSShaderLightingProperty);

class BSShaderLightingProperty : public BSShaderProperty {
public:
	BSShaderLightingProperty();
	virtual ~BSShaderLightingProperty();

	virtual void CopyTo2();
	virtual void Unk_31();

	enum EnumxtraFlags {
		EF_IsPlayer = 0x1,
	};

	NiTPointerList<ShadowSceneLight*>			lLightList;
	float										fUnk06C;
	UInt32										uiExtraFlags; // Originally RefID, assigned only to non-player actors. Seems unused.
	bool										bLightListChanged;
	NiTListIterator								kLightIterator;

	CREATE_OBJECT(BSShaderLightingProperty, 0xB71920);

	UInt32				GetActiveLightCount();
	ShadowSceneLight*	GetIlluminatingLight(NiTListIterator& apIter);
	ShadowSceneLight*	GetNextIlluminatingLight(NiTListIterator& apIter);
	void				SortLights(NiBound* apObjBound);
	void				Unk_B71600(NiGeometry* apGeometry);
	void				RemoveLight(ShadowSceneLight* apLight);
};

ASSERT_SIZE(BSShaderLightingProperty, 0x7C);