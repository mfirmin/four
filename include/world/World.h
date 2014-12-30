#ifndef WORLD_H
#define WORLD_H

#include "vmath.h"

class Entity;

class World
{
    public:

        World();

        int init();
        int addEntity(Entity* e);
        int addPointLight(Vector3f pos);
        void go(float stepsize);

    private:

        struct impl;
        impl* pimpl;
};

#endif // WORLD_H
