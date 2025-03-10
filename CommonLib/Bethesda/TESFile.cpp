#include "TESFile.hpp"

// GAME - 0x473250
// GECK - 0x4DE700
uint8_t TESFile::GetCompileIndex() const {
	return ucCompileIndex;
}

uint16_t TESFile::GetSmallCompileIndex() const {
	return usSmallCompileIndex;
}

void TESFile::SetSmallCompileIndex(uint16_t ausIndex) {
	usSmallCompileIndex = ausIndex;
}

// GAME - 0x471C20
// GECK - 0x4DE370
bool TESFile::IsMaster() const {
	return uiFlags.GetBit(MASTER);
}

// GAME - 0x471C50
void TESFile::SetMaster(bool abMaster) {
	uiFlags.SetBit(MASTER, abMaster);
}

// GAME - 0x471CD0
bool TESFile::IsChecked() const {
	return uiFlags.GetBit(CHECKED);
}

// GAME - 0x471D00
void TESFile::SetChecked(bool abChecked) {
	uiFlags.SetBit(CHECKED, abChecked);
}

// GAME - 0x471D60
bool TESFile::IsActive() const {
	return uiFlags.GetBit(ACTIVE);
}

void TESFile::SetActive(bool abActive) {
	uiFlags.SetBit(ACTIVE, abActive);
}

bool TESFile::IsOptimized() const {
	return uiFlags.GetBit(OPTIMIZED);
}

void TESFile::SetOptimized(bool abOptimized) {
	uiFlags.SetBit(OPTIMIZED, abOptimized);
}

bool TESFile::IsLocalized() const {
	return uiFlags.GetBit(LOCALIZED);
}

void TESFile::SetLocalized(bool abDelocalized) {
	uiFlags.SetBit(LOCALIZED, abDelocalized);
}

bool TESFile::IsSmallFile() const {
	return uiFlags.GetBit(SMALL);
}

void TESFile::SetSmallFile(bool abSmallFile) {
	uiFlags.SetBit(SMALL, abSmallFile);
}

bool TESFile::IsOverlay() const {
	return uiFlags.GetBit(OVERLAY);
}

void TESFile::SetOverlay(bool abOverlay) {
	uiFlags.SetBit(OVERLAY, abOverlay);
}