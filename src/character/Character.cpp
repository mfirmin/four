
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
#include "joint/hingejoint.h"
#include "vmath.h"
#include "utils/utils.h"
#include "entity/cylinder.h"
#include "entity/capsule.h"
#include "entity/box.h"
#include "entity/sphere.h"

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
    Vector3f vel;
    Quaternion<float> rot;
    float mass;
    Geometry* g;

    do {
        ifs >> block;
        if (block.compare("TYPE") == 0) {
            // READ GEOMETRY
            std::string type;
            ifs >> type;
            std::cout << "Type: " << type << std::endl;
            if (type.compare("SPHERE") == 0) {
                float r;
                ifs >> r;
                g = new Sphere(r);
            }
            else if (type.compare("BOX") == 0) {
                Vector3f sides;
                ifs >> sides.x >> sides.y >> sides.z;
                g = new Box(sides);
            }
            else if (type.compare("CAPSULE") == 0) {
                float h, r_top, r_bottom;
                ifs >> h >> r_bottom >> r_top;
                g = new Capsule((r_bottom+r_top)/2., h);
            }
            else if (type.compare("CYLINDER") == 0) {
                float h, r_top, r_bottom;
                ifs >> h >> r_bottom >> r_top;
                g = new Cylinder((r_bottom+r_top)/2., h);
            }
            else {
                std::cerr << "Unknown Geometry " << type << std::endl;
            }
        }
        else if (block.compare("POSITION") == 0) {
            ifs >> pos.x >> pos.y >> pos.z;
            std::cout << "position: " << pos << std::endl;
        }
        else if (block.compare("ROTATION") == 0) {
            // READ ROT
            float x,y,z;
            ifs >> x >> y >> z;
            rot = rot.fromEulerAngles(x,y,z);

            std::cout << "rotation: " << rot << std::endl;
        }
        else if (block.compare("VELOCITY") == 0) {
            ifs >> vel.x >> vel.y >> vel.z;
            std::cout << "velocity: " << vel << std::endl;
        }
        else if (block.compare("MASS") == 0) {
            // READ MASS
            ifs >> mass;
            std::cout << "mass: " << mass << std::endl;
        }

    } while (block.compare(";") != 0);

    std::cout << "pushing entity..." << std::endl;
    Entity* e = new Entity(name, g, mass, pos, vel, rot);

    return e;

}

Joint* Character::readJoint(std::ifstream& ifs) {


    // --- things --- //
    std::string name;
    std::string parent;
    std::string child;

    ifs >> name;
    ifs >> parent;
    ifs >> child;

    std::string type;
    std::string block;
    Vector3f pos;
    Vector3f angle;
    Vector3f angle_max;
    Vector3f angle_min;
    Vector3f axis = Vector3f(0,0,1);

    Joint* j;

    std::cout << "Reading joint " << name << std::endl;
    do {
        ifs >> block;
        if (block.compare("TYPE") == 0) {
            // READ JOINT TYPE 
            ifs >> type;
            std::cout << "type: " << type << std::endl;
        }
        else if (block.compare("POSITION") == 0) {
            ifs >> pos.x >> pos.y >> pos.z;
            std::cout << "pos: " << pos << std::endl;
        }
        else if (block.compare("ANGLE") == 0) {
            ifs >> angle.x >> angle.y >> angle.z;
            angle.x = utils::deg2rad(angle.x);
            angle.y = utils::deg2rad(angle.y);
            angle.z = utils::deg2rad(angle.z);
            std::cout << "angle: " << angle << std::endl;
        }
        else if (block.compare("AXIS") == 0) {
            ifs >> axis.x >> axis.y >> axis.z;
            std::cout << "axis: " << axis << std::endl;
        }
        else if (block.compare("ANGLE_MAX") == 0) {
            ifs >> angle_max.x >> angle_max.y >> angle_max.z;
            angle_max.x = utils::deg2rad(angle_max.x);
            angle_max.y = utils::deg2rad(angle_max.y);
            angle_max.z = utils::deg2rad(angle_max.z);
            std::cout << "angle_max: " << angle_max << std::endl;
        }
        else if (block.compare("ANGLE_MIN") == 0) {
            ifs >> angle_min.x >> angle_min.y >> angle_min.z;
            angle_min.x = utils::deg2rad(angle_min.x);
            angle_min.y = utils::deg2rad(angle_min.y);
            angle_min.z = utils::deg2rad(angle_min.z);
            std::cout << "angle_min: " << angle_min << std::endl;
        }

    } while (block.compare(";") != 0); 


    if (type.compare("HINGE") == 0) {
        j = new HingeJoint(name, this->pimpl->entities.find(parent)->second, this->pimpl->entities.find(child)->second, pos, axis, angle.z, angle_min.z, angle_max.z);

    }

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
        std::cout << "Reading entity..." << std::endl;
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
        std::cout << "Reading joint..." << std::endl;
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
