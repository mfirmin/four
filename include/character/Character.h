#ifndef CHARACTER_H
#define CHARACTER_H

#include "vmath.h"

#include <string>
class Entity;

class Character
{
    public:

        Character();

        int init();

        void addEntity(std::string name, Entity*);


    private:

        struct impl;
        impl* pimpl;
};

#endif // CHARACTER_H
