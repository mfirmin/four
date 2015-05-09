#ifndef WORLD_H
#define WORLD_H

#include "vmath.h"
#include <map>
#include <string>

class Entity;
class Joint;
class Character;

class World
{
    public:

        World(std::string name);

        int init();
        int addEntity(Entity* e);
        int addCharacter(Character* c);
        int addJoint(Joint* j);
        int addPointLight(Vector3f pos);
        std::string getName();
        const std::map<std::string, Entity*>& getEntities();
        void go(float stepsize);
        void step(float stepsize);
        std::string getInitialStateAsJSONString();

    private:

        struct impl;
        impl* pimpl;
};

#endif // WORLD_H
