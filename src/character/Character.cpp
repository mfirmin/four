
#include <stdlib.h>
#include <iostream>

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <fstream>

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

Entity* readEntity(std::ifstream& ifs) {

    // --- things --- //
    std::string name;
    ifs >> name;

    std::string block;
    Vector3f pos;
    Quaternion<float> rot;
    float mass;

    while (block.compare(";") != 0) {
        if (block.compare("TYPE") == 0) {
            // READ GEOMETRY
            std::cout << "read geometry not yet implemented" << std::endl;
        }
        else if (block.compare("POSITION")) {
            ifs >> pos.x >> pos.y >> pos.z;
        }
        else if (block.compare("ROTATION")) {
            // READ ROT
            float x,y,z;
            ifs >> x >> y >> z;
            rot.fromEulerAngles(x,y,z);
        }
        else if (block.compare("MASS")) {
            // READ MASS
            ifs >> mass;
        }
        else {
            std::cerr << "(Character.cpp.addEntity) Unknown Block " << block << std::endl;
            return NULL;
        }
    }

    Entity* e = new Entity();

    return e;

}

Joint* readJoint(std::ifstream& ifs) {


    // --- things --- //
    std::string name;
    std::string parent;
    std::string child;

    ifs >> name;
    ifs >> parent;
    ifs >> child;

    std::string block;

    while (block.compare(";") != 0) {
        if (block.compare("TYPE") == 0) {
            // READ JOINT TYPE 
            
        }
        else if (block.compare("POSITION")) {
            // READ POS
        }
        else if (block.compare("ROTATION")) {
            // READ ROT
        }
        else if (block.compare("MASS")) {
            // READ MASS
        }
        else {
            std::cerr << "(Character.cpp.addJoint) Unknown Block " << block << std::endl;
            return NULL;
        }
    }


    Joint* j = new Joint();
    return j;

}

int Character::initFromFile(const char* ifname) 
{
    std::ifstream ifs;
    ifs.open(ifname);

    std::cout << "Reading Character File: " << ifname << std::endl;

    if (!ifs)
    {
        std::cerr << "Couldn't open character file " << ifname << " for reading." << std::endl;
        return -1;
    }

    // --- things --- //
    std::string str;
    float fl;
    int i;

    ifs >> str;
    if (str.compare("CHARACTER") != 0) {
        std::cerr << "Expected 'CHARACTER', but got: " << str << std::endl;
        return -2;
    }

    ifs >> pimpl->name;

    ifs >> str;

    if (str.compare("PARTS") != 0) {
        std::cerr << "Expected 'PARTS', but got: " << str << std::endl;
        return -2;
    }
    ifs >> i;

    for (int p = 0; p < i; p++) {
        Entity* e = readEntity(ifs);
        if (e == NULL) {
            return -3;
        }
        this->addEntity(e);
    }
    ifs >> str;

    if (str.compare("JOINTS") != 0) {
        std::cerr << "Expected 'JOINTS', but got: " << str << std::endl;
        return -2;
    }
    ifs >> i;

    for (int p = 0; p < i; p++) {
        Joint* j = readJoint(ifs);
        if (j == NULL) {
            return -3;
        }
        this->addJoint(j);
    }

    std::cout << "Succesfully read Character File: " << ifname << std::endl;

    return 0;

}


/*
int main(int argc, char** argv)
{

}
*/
