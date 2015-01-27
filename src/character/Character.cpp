
#include <stdlib.h>
#include <iostream>

#include <vector>
#include <map>
#include <string>

#include "character/character.h"
#include "entity/entity.h"
#include "joint/joint.h"
#include "vmath.h"
#include "utils/utils.h"

class Entity;
class Joint;

struct Character::impl
{

    std::string name;
    std::map<std::string, Entity*> entities;
    std::map<std::string, Joint*> joints;

};

Character::Character(std::string n) 
{
    pimpl = new impl();
    pimpl->name = n;

}

const std::map<std::string, Joint*>& Character::getJoints()
{
    return pimpl->joints;
}
const std::map<std::string, Entity*>& Character::getEntities()
{
    return pimpl->entities;
}
void Character::addJoint(Joint* j)
{
    pimpl->joints.insert(std::pair<std::string, Joint*>(j->getName(), j));
}
void Character::addEntity(Entity* e)
{
    pimpl->entities.insert(std::pair<std::string, Entity*>(e->getName(), e));
}

int Character::init()
{
    return 0;
}


/*
int main(int argc, char** argv)
{

}
*/
