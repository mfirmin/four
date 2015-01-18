#ifndef WORLD_H
#define WORLD_H

#include "vmath.h"

class Entity;
class Joint;

class World
{
    public:

        World();

        int init();
        int addEntity(Entity* e);
        Joint* addHingeJoint(Entity* e1, Entity* e2, Vector3f pos, Vector3f axis=Vector3f(0,0,1));
        int addPointLight(Vector3f pos);
        void go(float stepsize);

    private:

        struct impl;
        impl* pimpl;
};

#endif // WORLD_H
