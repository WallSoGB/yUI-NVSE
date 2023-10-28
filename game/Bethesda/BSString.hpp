#pragma once

// Technically it should be a template but I'm lazy
// 0x8
class BSStringT
{
public:
	BSStringT();
	~BSStringT();

	char*		pString;
	UInt16		usLen;
	UInt16		usMaxLen;

	bool		Set(const char* src);
	bool		Includes(const char* toFind) const;
	bool		Replace(const char* toReplace, const char* replaceWith); // replaces instance of toReplace with replaceWith
	bool		Append(const char* toAppend);
	double		Compare(const BSStringT& compareTo, bool caseSensitive = false);

	UInt32		GetLength();

	const char* CStr();
};
static_assert(sizeof(BSStringT) == 0x8);

typedef BSStringT String;


/*
class String
{
public:
	String();
	~String();

	char*		m_data;
	UInt16		m_dataLen;
	UInt16		m_bufLen;

	void		Init(UInt32 bufSize);
	bool		Set(const char* src);
	bool		Includes(const char* toFind) const;
	bool		Replace(const char* toReplace, const char* replaceWith); // replaces instance of toReplace with replaceWith
	bool		Append(const char* toAppend);
	double		Compare(const String& compareTo, bool caseSensitive = false);

	const char* CStr() const;

	void		AppendChar(char toAppend);
	void		InsertChar(char toInsert, UInt32 index);
	void		EraseAt(UInt32 index);
	void		EraseAfter(UInt32 index);
	int			EraseWord(UInt32 index);
	void		EraseNextWord(UInt32 index);
	void		RemoveLastChar();
};
static_assert(sizeof(String) == 0x8);
*/