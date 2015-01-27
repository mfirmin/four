#ifndef CHARACTER_H
#define CHARACTER_H

#include "vmath.h"

#include <string>
class Entity;
class Joint;

class Character
{
    public:

        Character(std::string name);

        int init();

        void addEntity(Entity*);
        void addJoint(Joint*);
        const std::map<std::string, Entity*>& getEntities();
        const std::map<std::string, Joint*>& getJoints();


    private:

        struct impl;
        impl* pimpl;
};

#endif // CHARACTER_H
