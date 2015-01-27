
//#include "ODEConstants.h"

#define dSINGLE

#include <stdlib.h>
#include <iostream>

#include <vector>

#include <time.h>

#ifdef __APPLE__
#include <sys/time.h>
#endif

#include "world/world.h"
#include "entity/Geometry.h"
#include "entity/Box.h"
#include "entity/Cylinder.h"
#include "entity/Capsule.h"
#include "entity/Sphere.h"
#include "entity/Plane.h"

#include "joint/Joint.h"
#include "joint/HingeJoint.h"

#include "vmath.h"
#include "physics/ODEWrapper.h"
#include "entity/Entity.h"
#include "character/Character.h"
#include "renderer/Renderer.h"


#ifdef __APPLE__
typedef timeval _timeval;
#endif
#ifndef __APPLE__
typedef timespec _timeval;
#endif

struct World::impl
{

    // Entity objects.
 //   std::vector<Entity*> entities;
//    std::vector<Joint*> joints;

    std::map<std::string, Entity*> entities;
    std::map<std::string, Joint*> joints;

    ODEWrapper simulator;

    void updateEntities();


};

World::World() 
{
    pimpl = new impl();
}

int World::init()
{

    pimpl->simulator = ODEWrapper();
    pimpl->simulator.init();


    return 0;


}

int World::addCharacter(Character* c) 
{
    for (auto it = c->getEntities().begin(); it != c->getEntities().end(); it++)
    {
        this->addEntity(it->second);
    }
    for (auto it = c->getJoints().begin(); it != c->getJoints().end(); it++)
    {
        this->addJoint(it->second);
    }
    return 0;
}

int World::addEntity(Entity* e)
{

    int ent = -1;
    switch(e->getGeometry()->getType())
    {
        case Geometry::Type::BOX:
            ent = pimpl->simulator.addBox(e->getName(),e->getPosition(), dynamic_cast<Box*>(e->getGeometry())->getSides(), e->getVelocity(), e->getRotationAsQuaternion(), e->getOmega(), 10);
            break;
        case Geometry::Type::SPHERE:
            ent = pimpl->simulator.addSphere(e->getName(), e->getPosition(), dynamic_cast<Sphere*>(e->getGeometry())->getRadius(), e->getVelocity(), e->getRotationAsQuaternion(), e->getOmega(), 10);
            break;
        case Geometry::Type::CYLINDER:
            ent = pimpl->simulator.addCylinder(e->getName(), e->getPosition(), dynamic_cast<Cylinder*>(e->getGeometry())->getRadius(), dynamic_cast<Cylinder*>(e->getGeometry())->getHeight(), e->getVelocity(), e->getRotationAsQuaternion(), e->getOmega(), 10);
            break;
        case Geometry::Type::CAPSULE:
            ent = pimpl->simulator.addCapsule(e->getName(), e->getPosition(), dynamic_cast<Capsule*>(e->getGeometry())->getRadius(), dynamic_cast<Capsule*>(e->getGeometry())->getHeight(), e->getVelocity(), e->getRotationAsQuaternion(), e->getOmega(), 10);
            break;
        case Geometry::Type::PLANE:
            ent = pimpl->simulator.addPlane(dynamic_cast<Plane*>(e->getGeometry())->getA(), dynamic_cast<Plane*>(e->getGeometry())->getB());
            break;
        default:
            break;
    }


    if (ent < 0)
    { 
        std::cerr << "Error encountered trying to add entity to simulator (World.addEntity)" << std::endl;
        return -1;
    }

    pimpl->entities.insert(std::pair<std::string, Entity*>(e->getName(), e));

    return 0;
}

int World::addJoint(Joint* j)
{

    switch(j->getType()) {
        case Joint::Type::HINGE:
            pimpl->simulator.addHingeJoint(j->getName(), j->getParent()->getName(), j->getChild()->getName(), j->getPosition(), dynamic_cast<HingeJoint*>(j)->getAxis());
            pimpl->joints.insert(std::pair<std::string, Joint*>(j->getName(), j));
            break;
        case Joint::Type::BALL:
            std::cerr << "Ball Joints not yet implemented" << std::endl;
            break;
    }
    return 0;
}

void World::impl::updateEntities()
{

    for (auto it = entities.begin(); it != entities.end(); it++)
    {
        if ((*it).second->getGeometry()->getType() == Geometry::Type::PLANE) { continue; }
        (*it).second->setPosition(simulator.getBodyPositionFromName((*it).second->getName()));
        (*it).second->setRotation(simulator.getBodyRotationFromName((*it).second->getName()));
    }

}


const std::map<std::string, Entity*>& World::getEntities()
{
    return pimpl->entities;

}

void World::step(float stepsize)
{
    pimpl->simulator.step(stepsize);

    pimpl->updateEntities();
    //pimpl->frameTime+= stepsize;

}

void World::go(float stepsize)
{
    while (true)
    {
        pimpl->simulator.step(stepsize);

        pimpl->updateEntities();
    }
}

