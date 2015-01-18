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
        int addHingeJoint(Entity* e1, Entity* e2, Vector3f axis);
        int addPointLight(Vector3f pos);
        void go(float stepsize);

    private:

        struct impl;
        impl* pimpl;
};

#endif // WORLD_H
