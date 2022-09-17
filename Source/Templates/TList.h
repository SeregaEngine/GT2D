/* TODO
 * - Fix when we use standard types like f32

 * - Remake with doubly linked list for fast PopBack()
 * - Remove() that delete everything
 * - RemoveIf() that delete everything with given function
 */

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
        Item(T& _data, Item* _next) : data(_data), next(_next) {}
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

    Item *m_pFirst, *m_pLast;

public:
    TList() : m_pFirst(nullptr), m_pLast(nullptr) {}
    TList(TList<T>& lst) {
        m_pFirst = lst.m_pFirst;
        m_pLast = lst.m_pLast;
        lst.m_pFirst = nullptr;
        lst.m_pLast = nullptr;
    }
    ~TList() { Clean(); }

    void operator=(TList<T>& lst) {
        // Clean what we had before this assign
        Clean();

        m_pFirst = lst.m_pFirst;
        m_pLast = lst.m_pLast;
        lst.m_pFirst = nullptr;
        lst.m_pLast = nullptr;
    }

    void Push(T& data);
    void PushBack(T& data);

    // Pop only if you checked list with IsEmpty()
    void Pop();
    void PopBack();
    void Clean();

    T& Front() { return m_pFirst->data; }
    T& Back() { return m_pLast->data; }
    b32 IsEmpty() const { return m_pFirst ? false : true; }

    void Mapcar(void (*fun)(T, void*), void* userdata = nullptr); // It's just iterator, not mapcar at all...
    void Mapcar(void (*fun)(T));

    Iterator Begin() { return m_pFirst; }
    Iterator End() { return nullptr; }
};

/* ====== METHODS ====== */
template<class T>
inline void TList<T>::Push(T& data) {
    Item* pTemp = new Item(data, m_pFirst);
    m_pFirst = pTemp;
    if (!m_pLast)
        m_pLast = m_pFirst;
}

template<class T>
inline void TList<T>::PushBack(T& data) {
    Item* pTemp = new Item(data, m_pFirst);
    if (m_pLast)
        m_pLast->next = pTemp;
    m_pLast = pTemp;

    if (!m_pFirst)
        m_pFirst = m_pLast;
}

template<class T>
inline void TList<T>::Pop() {
    if (m_pLast == m_pFirst)
    {
        delete m_pFirst;
        m_pFirst = m_pLast = nullptr;
    }
    else
    {
        Item* pTemp = m_pFirst;
        m_pFirst = m_pFirst->next;
        delete pTemp;
    }
}

template<class T>
inline void TList<T>::PopBack() {
    if (m_pFirst == m_pLast)
    {
        delete m_pLast;
        m_pLast = m_pFirst = nullptr;
    }
    else
    {
        Item* pTemp;
        for (pTemp = m_pFirst; pTemp->next != m_pLast; pTemp = pTemp->next)
            {}

        delete m_pLast;
        pTemp->next = nullptr;
        m_pLast = pTemp;
    }
}

template<class T>
inline void TList<T>::Clean() {
    while (m_pFirst)
    {
        Item* pTemp = m_pFirst;
        m_pFirst = m_pFirst->next;
        delete pTemp;
    }

    m_pFirst = nullptr;
    m_pLast = nullptr;
}

template<class T>
inline void TList<T>::Mapcar(void (*fun)(T, void*), void* userdata) {
    for (Item* pTemp = m_pFirst; pTemp; pTemp = pTemp->next)
        fun(pTemp->data, userdata);
}

template<class T>
inline void TList<T>::Mapcar(void (*fun)(T)) {
    for (Item* pTemp = m_pFirst; pTemp; pTemp = pTemp->next)
        fun(pTemp->data);
}

#endif // LIST_H_