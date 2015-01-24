
#include <stdlib.h>
#include <iostream>

#include <vector>
#include <map>
#include <string>

#include "character/character.h"
#include "vmath.h"
#include "utils/utils.h"

class Entity;
class Joint;

struct Character::impl
{

    std::map<std::string, Entity*> entities;
    std::map<std::string, Joint*> joints;

};

Character::Character() 
{
    pimpl = new impl();
}

void Character::addEntity(std::string name, Entity* e)
{
    pimpl->entities.insert(std::pair<std::string, Entity*>(name, e));
   
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
