#pragma once

#include "BipedAnim.hpp"
#include "QueuedFile.hpp"

class Actor;
class NiRefObject;

class QueuedHelmet : public QueuedFile {
public:
	QueuedHelmet();
	~QueuedHelmet();

	BipedAnim* anim;
	NiRefObject* list2C[20];
	NiRefObject* list7C[20];
	NiRefObject* listCC[20];
	Actor* actor;
	char unk120;
	int unk124;
};

ASSERT_SIZE(QueuedHelmet, 0x128);
/*
// 38
class QueuedHelmet : public QueuedFile
{
public:
QueuedHelmet();
~QueuedHelmet();

QueuedCharacter		* queuedCharacter;		// 18
QueuedChildren		* queuedChildren;		// 1C
void				* unk20;				// 20
QueuedModel			* queuedModel;			// 24
BSFaceGenModel		* faceGenModel;			// 28
NiNode				* niNode;				// 2C
Character			* character;			// 30
UInt32				unk34;					// 34
};
*/