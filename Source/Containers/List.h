#pragma once

#include "Engine/Types.h"

template<class T>
class TList
{
private:
    struct Item
    {
        T data;
        Item* pNext;

        Item() : data(), pNext(nullptr) {}
        Item(const T& _data, Item* _pNext) : data(_data), pNext(_pNext) {}
    };

public:
    struct Iterator
    {
        Item* pItem;

        Iterator() : pItem(nullptr) {}
        Iterator(Item* _pItem) : pItem(_pItem) {}
        ~Iterator() {}

        Iterator operator=(Item* _pItem) { pItem = _pItem; return *this; }
        void operator++() { pItem = pItem->pNext; }
        Iterator operator++(int) { pItem = pItem->pNext; return *this; }

        b32 operator==(Iterator it) { return pItem == it.pItem; }
        b32 operator==(void* ptr) { return pItem == ptr; }
        b32 operator!=(Iterator it) { return pItem != it.pItem; }
        b32 operator!=(void* ptr) { return pItem != ptr; }

        Item* operator->() { return pItem; }
    };

    Item *m_pFirst, *m_pLast;

public:
    TList() : m_pFirst(nullptr), m_pLast(nullptr) {}
    ~TList() { Clean(); }

    static void Move(TList<T>& lstDest, TList<T>& lstSrc);

    void Push(const T& data);
    void PushBack(const T& data);
    void PushBefore(Iterator& beforeIterator, const T& data);

    void Pop();
    void PopBack();
    void Remove(const T& data);
    void Clean();

    T& Front() { return m_pFirst->data; }
    T& Back() { return m_pLast->data; }
    b32 IsEmpty() const { return m_pFirst ? false : true; }
    b32 IsMember(const T& check) const;

    void Foreach(void (*fun)(T&, void*), void* userdata);
    void Foreach(void (*fun)(T&));

    Iterator Begin() { return m_pFirst; }
    Iterator End() { return nullptr; }
    const Iterator CBegin() const { return m_pFirst; }
    const Iterator CEnd() const { return nullptr; }

private:
    // No copy, no assignment. Use references instead
    TList(TList<T>& lst) = delete;
    void operator=(TList<T>& lst) = delete;
};

template<class T>
inline void TList<T>::Move(TList<T>& lstDest, TList<T>& lstSrc)
{
    lstDest.Clean();
    lstDest.m_pFirst = lstSrc.m_pFirst;
    lstDest.m_pLast = lstSrc.m_pLast;

    lstSrc.m_pFirst = nullptr;
    lstSrc.m_pLast = nullptr;
}

template<class T>
inline void TList<T>::Push(const T& data)
{
    Item* pTemp = new Item(data, m_pFirst);
    m_pFirst = pTemp;
    if (!m_pLast)
    {
        m_pLast = m_pFirst;
    }
}

template<class T>
inline void TList<T>::PushBack(const T& data)
{
    Item* pTemp = new Item(data, nullptr);
    if (m_pLast)
    {
        m_pLast->pNext = pTemp;
    }
    m_pLast = pTemp;

    if (!m_pFirst)
    {
        m_pFirst = m_pLast;
    }
}

template<class T>
inline void TList<T>::PushBefore(Iterator& beforeIterator, const T& data)
{
    // Push front if beforeIterator item is our first item
    if (beforeIterator.pItem == m_pFirst)
    {
        Push(data);
        return;
    }

    // Try to find list item before beforeIterator
    Item* pTemp = m_pFirst;
    for ( ; pTemp && pTemp->pNext != beforeIterator.pItem; pTemp = pTemp->pNext)
        {}

    // Push back if we didn't find this item
    if (!pTemp)
    {
        PushBack(data);
        return;
    }

    // Allocate new item
    Item* pNew = new Item(data, beforeIterator.pItem);
    pTemp->pNext = pNew;
}

template<class T>
inline void TList<T>::Pop()
{
    if (!m_pFirst)
    {
        return;
    }

    if (m_pLast == m_pFirst)
    {
        delete m_pFirst;
        m_pFirst = m_pLast = nullptr;
    }
    else
    {
        Item* pTemp = m_pFirst;
        m_pFirst = m_pFirst->pNext;
        delete pTemp;
    }
}

template<class T>
inline void TList<T>::PopBack()
{
    if (!m_pFirst)
    {
        return;
    }

    if (m_pFirst == m_pLast)
    {
        delete m_pLast;
        m_pLast = m_pFirst = nullptr;
    }
    else
    {
        Item* pTemp;
        for (pTemp = m_pFirst; pTemp->pNext != m_pLast; pTemp = pTemp->pNext)
            {}

        delete m_pLast;
        pTemp->pNext = nullptr;
        m_pLast = pTemp;
    }
}

template<class T>
inline void TList<T>::Remove(const T& data)
{
    // If it's our back
    if (m_pLast->data == data)
    {
        PopBack();
        return;
    }

    // Find which item to remove
    Item** ppItem = &m_pFirst;
    for ( ; *ppItem && (*ppItem)->data != data; ppItem = &(*ppItem)->pNext)
        {}

    // If found
    if (*ppItem)
    {
        Item* pRemove = *ppItem;
        *ppItem = pRemove->pNext;
        delete pRemove;
    }
}

template<class T>
inline void TList<T>::Clean()
{
    while (m_pFirst)
    {
        Item* pTemp = m_pFirst;
        m_pFirst = m_pFirst->pNext;
        delete pTemp;
    }

    m_pFirst = nullptr;
    m_pLast = nullptr;
}

template<class T>
inline void TList<T>::Foreach(void (*fun)(T&, void*), void* userdata)
{
    for (Item* pTemp = m_pFirst; pTemp; pTemp = pTemp->pNext)
    {
        fun(pTemp->data, userdata);
    }
}

template<class T>
inline void TList<T>::Foreach(void (*fun)(T&))
{
    for (Item* pTemp = m_pFirst; pTemp; pTemp = pTemp->pNext)
    {
        fun(pTemp->data);
    }
}

template<class T>
inline b32 TList<T>::IsMember(const T& check) const
{
    for (Item* pTemp = m_pFirst; pTemp; pTemp = pTemp->pNext)
    {
        if (pTemp->data == check)
        {
            return true;
        }
    }
    return false;
}
