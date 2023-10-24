#pragma once

struct TESFile;

class TESPackageData {
public:
	TESPackageData();
	~TESPackageData();
	virtual void	Destroy(bool free);
	virtual void	CopyFrom(TESPackageData* packageData);
	virtual void	Unk_02();
	virtual void	Save(TESFile* modInfo);
	virtual void	Unk_04();
	virtual void	Unk_05();
	virtual void	Unk_06();
	virtual void	Unk_07();
};