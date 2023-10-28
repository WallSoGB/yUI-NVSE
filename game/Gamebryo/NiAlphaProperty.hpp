#pragma once

#include "NiProperty.hpp"

NiSmartPointer(NiAlphaProperty);

class NiAlphaProperty : public NiProperty {
public:
	NiAlphaProperty();
	virtual ~NiAlphaProperty();

	enum AlphaFlags : UInt16 {
		ALPHA_BLEND_MASK = 0x0001,
		SRC_BLEND_MASK = 0x001e,
		SRC_BLEND_POS = 1,
		DEST_BLEND_MASK = 0x01e0,
		DEST_BLEND_POS = 5,
		TEST_ENABLE_MASK = 0x0200,
		TEST_FUNC_MASK = 0x1c00,
		TEST_FUNC_POS = 10,
		ALPHA_NOSORTER_MASK = 0x2000
	};

	enum AlphaFunction
	{
		ALPHA_ONE = 0x0,
		ALPHA_ZERO = 0x1,
		ALPHA_SRCCOLOR = 0x2,
		ALPHA_INVSRCCOLOR = 0x3,
		ALPHA_DESTCOLOR = 0x4,
		ALPHA_INVDESTCOLOR = 0x5,
		ALPHA_SRCALPHA = 0x6,
		ALPHA_INVSRCALPHA = 0x7,
		ALPHA_DESTALPHA = 0x8,
		ALPHA_INVDESTALPHA = 0x9,
		ALPHA_SRCALPHASAT = 0xA,
		ALPHA_MAX_MODES = 0xB,
	};

	enum TestFunction {
		TEST_ALWAYS = 0x0,
		TEST_LESS = 0x1,
		TEST_EQUAL = 0x2,
		TEST_LESSEQUAL = 0x3,
		TEST_GREATER = 0x4,
		TEST_NOTEQUAL = 0x5,
		TEST_GREATEREQUAL = 0x6,
		TEST_NEVER = 0x7,
		TEST_MAX_MODES = 0x8,
	};


	AlphaFlags	m_eFlags;
	UInt8		m_ucAlphaTestRef;

	CREATE_OBJECT(NiAlphaProperty, 0xA5CEB0);

	bool HasAlphaBlend() { return m_eFlags & ALPHA_BLEND_MASK; }
	bool HasAlphaTest() { return m_eFlags & TEST_ENABLE_MASK; }
	bool HasAlphaSorter() { return m_eFlags & ALPHA_NOSORTER_MASK; }

	UInt8 GetAlphaTestRef() {
		return m_ucAlphaTestRef;
	}

	void SetAlphaTestRef(UInt8 ucRef) {
		m_ucAlphaTestRef = ucRef;
	}

	void SetAlphaBlending(bool abBlend) {
		m_eFlags = (AlphaFlags)(abBlend ? m_eFlags | ALPHA_BLEND_MASK : m_eFlags & ~ALPHA_BLEND_MASK);
	}

	void SetAlphaTesting(bool abTest) {
		m_eFlags = (AlphaFlags)(abTest ? m_eFlags | TEST_ENABLE_MASK : m_eFlags & ~TEST_ENABLE_MASK);
	}

	void SetSrcBlendMode(AlphaFunction aeSrcBlend) {
		m_eFlags = (AlphaFlags)(aeSrcBlend ? m_eFlags | SRC_BLEND_MASK : m_eFlags & ~SRC_BLEND_MASK);
		m_eFlags = (AlphaFlags)(aeSrcBlend ? m_eFlags | ALPHA_BLEND_MASK : m_eFlags & ~ALPHA_BLEND_MASK);
	}

	void SetDestBlendMode(AlphaFunction aeDestBlend) {
		m_eFlags = (AlphaFlags)(aeDestBlend ? m_eFlags | DEST_BLEND_MASK : m_eFlags & ~DEST_BLEND_MASK);
		m_eFlags = (AlphaFlags)(aeDestBlend ? m_eFlags | DEST_BLEND_POS : m_eFlags & ~DEST_BLEND_POS);
	}

	void SetTestRef(UInt8 aucRef) {
		m_ucAlphaTestRef = aucRef;
	}

	void SetTestMode(TestFunction aeTestFunc) {
		m_eFlags = (AlphaFlags)(aeTestFunc ? m_eFlags | TEST_FUNC_MASK : m_eFlags & ~TEST_FUNC_MASK);
		m_eFlags = (AlphaFlags)(aeTestFunc ? m_eFlags | TEST_FUNC_POS : m_eFlags & ~TEST_FUNC_POS);
	}
};

ASSERT_SIZE(NiAlphaProperty, 0x01C);