#ifndef CHARACTER_H
#define CHARACTER_H

#include "vmath.h"

#include <string>
#include <iostream>
#include <fstream>

class Entity;
class Joint;
class Controller;

class Character
{
    public:

        Character(std::string name);

        int init();

        void addEntity(Entity*);
        void addJoint(Joint*);
        const std::map<std::string, Entity*>& getEntities();
        const std::map<std::string, Joint*>& getJoints();
        Joint* readJoint(std::ifstream& ifs);

        int initFromFile(const char* ifname);


    private:

        struct impl;
        impl* pimpl;
};

#endif // CHARACTER_H
