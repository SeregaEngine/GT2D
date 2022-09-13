#ifndef LIST_H_
#define LIST_H_

/* ====== INCLUDES ====== */
#include "Types.h"

/* ====== STRUCTURES ====== */
template<class T>
class TList
{
private:
    struct Item
    {
        T data;
        Item* next;

        Item() : data(), next(nullptr) {}
        Item(T _data, Item* _next) : data(_data), next(_next) {}
        ~Item() {}
    };

public:
    struct Iterator
    {
        Item* item;

        Iterator() : item(nullptr) {}
        Iterator(Item* _item) : item(_item) {}
        ~Iterator() {}

        Iterator operator=(Item* _item) { item = _item; return *this; }
        void operator++() { item = item->next; }
        Iterator operator++(int) { item = item->next; return *this; }

        b32 operator!=(Iterator it) { return item != it.item; }
        b32 operator!=(void* ptr) { return item != ptr; }

        Item* operator->() { return item; }
    };

    Item* m_pFirst;

public:
    TList() : m_pFirst(nullptr) {}
    ~TList() { Clean(); }

    void Push(T data);
    void Clean();
    void Mapcar(void (*fun)(T, void*), void* userdata = nullptr);

    Iterator Begin() { return m_pFirst; }
    Iterator End() { return nullptr; }
};

/* ====== METHODS ====== */
template<class T>
inline void TList<T>::Push(T data)
{
    Item* pTemp = new Item(data, m_pFirst);
    m_pFirst = pTemp;
}

template<class T>
inline void TList<T>::Clean()
{
    Item* pTemp;
    while (m_pFirst)
    {
        pTemp = m_pFirst;
        m_pFirst = m_pFirst->next;
        delete pTemp;
    }
    m_pFirst = nullptr;
}

template<class T>
inline void TList<T>::Mapcar(void (*fun)(T, void*), void* userdata)
{
    for (Item* pTemp = m_pFirst; pTemp; pTemp = pTemp->next)
        fun(pTemp->data, userdata);
}

#endif LIST_H_