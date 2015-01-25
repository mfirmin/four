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
        int addJoint(Joint* j);
        int addPointLight(Vector3f pos);
        const std::vector<Entity*>& getEntities();
        void go(float stepsize);
        void step(float stepsize);

    private:

        struct impl;
        impl* pimpl;
};

#endif // WORLD_H
