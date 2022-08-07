#pragma once

#include "ChainedObject.h"

/* Wrapper to allow creation of "Pooled object"
e.g. objects that statically handle the storage of their own instances*/
///////////////////////////////////////////////////////////////////////

template<class T>
class PoolObject
{
public:
    template<class...Args>
    static T* Add(Args&&...);

    uint32_t GetIndex() const { return m_index; }
    uint64_t GetGlobalIndex() const;

    void Remove();

    static uint32_t GetObjectsCount() { return s_pool.Size(); }
    static T* GetNext(T*& item);
    static T* GetObjectAt(uint32_t i);
    static Vector<T>& GetObjects();
    static void RemoveObject(uint32_t i);
    static void Resize(uint32_t size);

protected:
    uint32_t m_index;
    static uint32_t m_classID;

private:
    static Pool<T> s_pool;
};

template<class T>
Pool<T> PoolObject<T>::s_pool(10000);

template<class T>
uint32_t PoolObject<T>::m_classID;

template<class T>
template<class...Args>
T* PoolObject<T>::Add(Args&&... args)
{
    uint32_t index = s_pool.CreateObject(args...);
    T* newObject = &s_pool[index];
    newObject->m_index = index;

    return newObject;
}

template<class T>
void PoolObject<T>::RemoveObject(uint32_t i)
{
    s_pool.Remove(i);
}

template<class T>
void PoolObject<T>::Remove()
{
    RemoveObject(m_index);
}

template<class T>
void PoolObject<T>::Resize(uint32_t size)
{
    s_pool.Resize(size);
}

template<class T>
Vector<T>& PoolObject<T>::GetObjects()
{
    return s_pool.GetObjects();
}

template<class T>
T* PoolObject<T>::GetObjectAt(uint32_t i)
{
    return &(s_pool.GetPoolItemAt(i)->object);
}

// Returns the next object in the chain
template<class T>
T* PoolObject<T>::GetNext(T*& item)
{
    if (item) // If we have a start point
    {
        // Search for the next
        PoolItem<T>& poolItem = *(s_pool.GetPoolItemAt(item->m_index));

        int nextIndex = poolItem.nextObject;
        if (nextIndex != -1)
        {
            item = &(s_pool.GetPoolItemAt(nextIndex)->object);
        }
        else // Does not have next
            item = nullptr;
    }
    else // No start point -> returns the first object
    {
        item = s_pool.GetFirstItem();
    }

    return item;
}

// Returns the global index of the T object
// Global means that this index is unique even considering other PoolObject<T>

template<class T>
uint64_t PoolObject<T>::GetGlobalIndex() const
{
    uint64_t globalID = ((uint64_t)m_classID << 32) | m_index;

    return globalID;
}
