#include "bhkEntity.hpp"
#include "BSSimpleList.hpp"

class hkVector4;
class hkQuaternion;
class hkTransform;
class hkDiagonal;

class bhkRigidBody : public bhkEntity
{
public:
	virtual hkVector4*	  GetPosition(hkVector4* outTransltn);
	virtual hkQuaternion*   GetRotation(hkQuaternion* outRot);
	virtual void			SetPosition(hkVector4* position);
	virtual void			SetRotation(hkQuaternion* rotation);
	virtual bool			SetMotionType(UInt32 motionType);
	virtual void			SetPositionAndRotation(hkVector4* position, hkQuaternion* rotation);
	virtual hkVector4*	  GetCenterOfMassLoc(hkVector4* outCoM);
	virtual hkVector4*	  GetCenterOfMass(hkVector4* outCoM);
	virtual hkTransform*	GetTransform(hkTransform* outTrnsfrm);
	virtual void			GetShapeSpaceDiagonal(hkDiagonal* resPtr);
	virtual void			Unk_3F(UInt8 arg);

	BSSimpleList<UInt32> Actions;
};
static_assert(sizeof(bhkRigidBody) == 0x1C);