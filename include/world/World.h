#ifndef WORLD_H
#define WORLD_H

#include "vmath.h"

class Entity;
class Joint;
class Renderer;

class World
{
    public:

        World(Renderer* r);

        int init();
        int addEntity(Entity* e);
        int addJoint(Joint* j);
        int addPointLight(Vector3f pos);
        void go(float stepsize);
        void step(float stepsize);

    private:

        struct impl;
        impl* pimpl;
};

#endif // WORLD_H
