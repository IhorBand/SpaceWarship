#pragma once

#include "PoolObject.h"
#include "GameWorld.h"

template<class T>
class WorldEntityPool : public PoolObject<T>
{
public:
    template<class...Args>
    static T* NewEntity(Args&&...);
    static void RegisterObject(GameWorld* world);
    static void SetClassID(size_t id) { T::m_classID = id; }
    static WorldEntity* GetWorldEntityAt(uint32_t index);

    static size_t GetClassID();
};

template<class T>
template<class...Args>
T* WorldEntityPool<T>::NewEntity(Args&&... args)
{
    T* newObject = PoolObject<T>::Add(args...);
    newObject->SetID(newObject->GetGlobalIndex());
    return newObject;
}

template<class T>
void WorldEntityPool<T>::RegisterObject(GameWorld* world)
{
    T::m_classID = world->RegisterEntityClass(WorldEntityPool<T>::GetWorldEntityAt);
    T::Initialize();
}

template<class T>
WorldEntity* WorldEntityPool<T>::GetWorldEntityAt(uint32_t index)
{
    WorldEntity* entity = T::GetObjectAt(index);
    return entity;
}

template<class T>
size_t WorldEntityPool<T>::GetClassID()
{
    return T::m_classID;
}