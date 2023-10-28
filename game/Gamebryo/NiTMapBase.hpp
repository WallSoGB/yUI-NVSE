#pragma once

#include "NiMemObject.hpp"

typedef void* NiTMapIterator;

template <class T_Key, class T_Data> class NiTMapItem : public NiMemObject {
public:
    NiTMapItem* m_pkNext;
    T_Key       m_key;
    T_Data      m_val;
};

template <class Allocator, class T_Key, class T_Data> class NiTMapBase : public NiMemObject {
public:
    typedef NiTMapItem<T_Key, T_Data> Entry;

    struct AntiBloatAllocator : public Allocator {
        UInt32 m_uiCount;
    };

    NiTMapBase(UInt32 uiHashSize = 37) {
        m_uiHashSize = uiHashSize;
        m_kAllocator.m_uiCount = 0;

        UInt32 uiSize = sizeof(NiTMapItem<T_Key, T_Data>*) * m_uiHashSize;
        m_ppkHashTable = (NiTMapItem<T_Key, T_Data>**)NiAlloc(uiSize);
        memset(m_ppkHashTable, 0, m_uiHashSize * sizeof(NiTMapItem<T_Key, T_Data>*));
    };
    virtual                             ~NiTMapBase();
    virtual UInt32                      KeyToHashIndex(T_Key key);
    virtual bool                        IsKeysEqual(T_Key key1, T_Key key2);
    virtual void                        SetValue(NiTMapItem<T_Key, T_Data>* pkItem, T_Key key, T_Data data);
    virtual void                        ClearValue(NiTMapItem<T_Key, T_Data>* pkItem);
    virtual NiTMapItem<T_Key, T_Data>*  NewItem() = 0;
    virtual void                        DeleteItem(NiTMapItem<T_Key, T_Data>* pkItem) = 0;

    UInt32                      m_uiHashSize;
    NiTMapItem<T_Key, T_Data>** m_ppkHashTable;
    AntiBloatAllocator          m_kAllocator;

    UInt32 GetCount() const { return m_kAllocator.m_uiCount; }

    bool GetAt(T_Key key, T_Data& dataOut) {
        UInt32 hashIndex = KeyToHashIndex(key);
        NiTMapItem<T_Key, T_Data>* item = m_ppkHashTable[hashIndex];
        while (item) {
            if (IsKeysEqual(item->m_key, key)) {
                dataOut = item->m_val;
                return true;
            }
            item = item->m_pkNext;
        }
        return false;
    }

    void SetAt(T_Key key, T_Data data) {
        UInt32 hashIndex = KeyToHashIndex(key);
        NiTMapItem<T_Key, T_Data>* item = m_ppkHashTable[hashIndex];
        while (item) {
            if (IsKeysEqual(item->m_key, key)) {
                item->m_val = data;
                return;
            }
            item = item->m_pkNext;
        }
        NiTMapItem<T_Key, T_Data>* nuEntry = NewItem();
        SetValue(nuEntry, key, data);
        nuEntry->m_pkNext = m_ppkHashTable[hashIndex];
        m_ppkHashTable[hashIndex] = nuEntry;
        m_kAllocator.m_uiCount++;
    }

    T_Data* Lookup(T_Key key) {
        T_Data* dataOut = nullptr;
        GetAt(key, *dataOut);
        return dataOut;
    }

    bool Insert(NiTMapItem<T_Key, T_Data>* nuEntry) {
        // game code does not appear to care about ordering of entries in buckets
        UInt32 bucket = nuEntry->m_key % m_uiHashSize;
        NiTMapItem<T_Key, T_Data>* prev = NULL;
        for (NiTMapItem<T_Key, T_Data>* cur = m_ppkHashTable[bucket]; cur; cur = cur->m_pkNext) {
            if (cur->m_key == nuEntry->m_key) {
                return false;
            }
            else if (!cur->m_pkNext) {
                prev = cur;
                break;
            }
        }

        if (prev) {
            prev->m_pkNext = nuEntry;
        }
        else {
            m_ppkHashTable[bucket] = nuEntry;
        }

        m_uiHashSize++;
        return true;
    }

    void RemoveAll() {
        for (UInt32 i = 0; i < m_uiHashSize; i++) {
            while (m_ppkHashTable[i]) {
                NiTMapItem<T_Key, T_Data>* item = m_ppkHashTable[i];
                m_ppkHashTable[i] = m_ppkHashTable[i]->m_pkNext;
                ClearValue(item);
                DeleteItem(item);
            }
        }

        m_kAllocator.m_uiCount = 0;
    }

    NiTMapIterator GetFirstPos() const {
        for (UInt32 i = 0; i < m_uiHashSize; i++) {
            if (m_ppkHashTable[i])
                return m_ppkHashTable[i];
        }
        return 0;
    }

    void GetNext(NiTMapIterator& pos, T_Key& key, T_Data& val) {
        NiTMapItem<T_Key, T_Data>* item = (NiTMapItem<T_Key, T_Data>*) pos;

        key = item->m_key;
        val = item->m_val;

        if (item->m_pkNext) {
            pos = item->m_pkNext;
            return;
        }

        UInt32 i = KeyToHashIndex(item->m_key);
        for (++i; i < m_uiHashSize; i++)
        {
            item = m_ppkHashTable[i];
            if (item)
            {
                pos = item;
                return;
            }
        }

        pos = 0;
    }
};

template<class Allocator, class T_Key, class T_Data>
inline NiTMapBase<Allocator, T_Key, T_Data>::~NiTMapBase() {
    RemoveAll();
    NiFree(m_ppkHashTable);
}

template<class Allocator, class T_Key, class T_Data>
inline UInt32 NiTMapBase<Allocator, T_Key, T_Data>::KeyToHashIndex(T_Key key) {
    return (unsigned int)(((size_t)key) % m_uiHashSize);
}

template<class Allocator, class T_Key, class T_Data>
inline bool NiTMapBase<Allocator, T_Key, T_Data>::IsKeysEqual(T_Key key1, T_Key key2) {
    return key1 == key2;
}

template<class Allocator, class T_Key, class T_Data>
inline void NiTMapBase<Allocator, T_Key, T_Data>::SetValue(NiTMapItem<T_Key, T_Data>* pkItem, T_Key key, T_Data data) {
    pkItem->m_key = key;
    pkItem->m_val = data;
}

template<class Allocator, class T_Key, class T_Data>
inline void NiTMapBase<Allocator, T_Key, T_Data>::ClearValue(NiTMapItem<T_Key, T_Data>* pkItem) {
}
