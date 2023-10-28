#include <main.h>
#include <Safewrite.hpp>

#include <SimpleINILibrary.h>

namespace Patch::CharGenMenuSRemoval
{
	bool enable = false;

	void Patch(const bool enable)
	{
		if (enable)
		{
			WriteRelCall(0x753E32, 0x0753E54);
		}
		else
		{
			UndoSafeWrite(0x753E32);
		}
	}

	extern void Init(CSimpleIni& ini)
	{
		if (g_nvseInterface->isEditor) return;
		enable = ini.GetOrCreate("General", "bPatchCharGenMenuSRemoval", 0, "; removes hardcoded 's' added if there are multiple points to assign in CharGen menu");
		Patch(enable);
	}
}
