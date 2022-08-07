#pragma once

#include "WorldEntity.h"
#include "WorldEntityPool.h"

template<class T>
class StandardEntity : public WorldEntity, public WorldEntityPool<T>
{
public:
    StandardEntity();
    StandardEntity(float x, float y, float angle);

    static void Initialize();
};

template<class T>
StandardEntity<T>::StandardEntity() :
    WorldEntity(0.0f, 0.0f, 0.0f)
{
}

template<class T>
StandardEntity<T>::StandardEntity(float x, float y, float angle) :
    WorldEntity(x, y, angle)
{
}

template<class T>
void StandardEntity<T>::Initialize()
{
    T::Initialize();
}
