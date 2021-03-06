
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
#include "entity/geometry.h"
#include "entity/box.h"
#include "entity/cylinder.h"
#include "entity/capsule.h"
#include "entity/sphere.h"
#include "entity/plane.h"

#include "joint/joint.h"
#include "joint/hingejoint.h"

#include "vmath.h"
#include "physics/odewrapper.h"
#include "entity/entity.h"
#include "character/character.h"
#include "renderer/renderer.h"


#ifdef __APPLE__
typedef timeval _timeval;
#endif
#ifndef __APPLE__
typedef timespec _timeval;
#endif

struct E_state {
    Vector3f pos;
    Vector3f vel;
    Quaternion<float> rot;
    Vector3f ang_vel;
};

struct J_state {
    Vector3f ang;
};

struct State {

    std::map<std::string, E_state> entities;
    std::map<std::string, J_state> joints;

};

struct World::impl
{

    // Entity objects.
 //   std::vector<Entity*> entities;
//    std::vector<Joint*> joints;

    std::string name;

    std::map<std::string, Entity*> entities;
    std::map<std::string, Joint*> joints;

    ODEWrapper simulator;

    void updateEntities();
    void updateJoints();
    void setSimulationTorques();

    std::vector<State> stateList;
};

World::World(std::string name) 
{
    pimpl = new impl();

    pimpl->name = name;
}

int World::init() {

    pimpl->simulator = ODEWrapper();
    pimpl->simulator.init();

    return 0;
}

std::string World::getName() {
    return pimpl->name;
}

std::string World::getInitialStateAsJSONString() {
    int MAXBUF = 4096;
    char buffer[MAXBUF];
    int len = 0;

    len += sprintf(buffer, "{\"entities\":{");

    char* bptr;
    if (pimpl->entities.size() == 0) {
        std::cerr << "Need at least one entity to initialize a world..." << std::endl;
        return std::string("-1");
    }
    for (auto it = pimpl->entities.begin(); it != pimpl->entities.end(); it++) {
        Entity* e = it->second;
        bptr = &(buffer[len]);
        len += e->getInitialStateAsJSONString(bptr);
    }

    len = len-1;
    bptr = &(buffer[len]);
    len += sprintf(bptr, "}}");
    return std::string(buffer);
}

std::string World::getCurrentStateAsJSONString() {
    int MAXBUF = 4096;
    char buffer[MAXBUF];
    int len = 0;


    len += sprintf(buffer, "{\"name\":\"%s\",\"entities\":{", pimpl->name.c_str());

    char* bptr;
    if (pimpl->entities.size() == 0) {
        std::cerr << "Need at least one entity to send a world..." << std::endl;
        return std::string("-1");
    }
    for (auto it = pimpl->entities.begin(); it != pimpl->entities.end(); it++) {
        Entity* e = it->second;
        bptr = &(buffer[len]);
        len += e->getCurrentStateAsJSONString(bptr);
    }

    len = len-1; // get rid of ','
    bptr = &(buffer[len]);
    len += sprintf(bptr, "},\"joints\":{");

    for (auto it = pimpl->joints.begin(); it != pimpl->joints.end(); it++) {
        Joint* j = it->second;
        bptr = &(buffer[len]);
        len += j->getCurrentStateAsJSONString(bptr);
    }

    len = len-1;
    bptr = &(buffer[len]);
    len += sprintf(bptr, "}}");
    return std::string(buffer);
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
            ent = pimpl->simulator.addBox(e->getName(),e->getMass(), e->getPosition(), dynamic_cast<Box*>(e->getGeometry())->getSides(), e->getVelocity(), e->getRotationAsQuaternion(), e->getOmega());
            break;
        case Geometry::Type::SPHERE:
            ent = pimpl->simulator.addSphere(e->getName(), e->getMass(), e->getPosition(), dynamic_cast<Sphere*>(e->getGeometry())->getRadius(), e->getVelocity(), e->getRotationAsQuaternion(), e->getOmega());
            break;
        case Geometry::Type::CYLINDER:
            ent = pimpl->simulator.addCylinder(e->getName(), e->getMass(),e->getPosition(), dynamic_cast<Cylinder*>(e->getGeometry())->getRadius(), dynamic_cast<Cylinder*>(e->getGeometry())->getHeight(), e->getVelocity(), e->getRotationAsQuaternion(), e->getOmega());
            break;
        case Geometry::Type::CAPSULE:
            ent = pimpl->simulator.addCapsule(e->getName(), e->getMass(), e->getPosition(), dynamic_cast<Capsule*>(e->getGeometry())->getRadius(), dynamic_cast<Capsule*>(e->getGeometry())->getHeight(), e->getVelocity(), e->getRotationAsQuaternion(), e->getOmega());
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

int World::addJoint(Joint* j) {

    switch(j->getType()) {
        case Joint::Type::HINGE:
            pimpl->simulator.addHingeJoint(j->getName(), j->getParent()->getName(), j->getChild()->getName(), j->getPosition(), dynamic_cast<HingeJoint*>(j)->getAxis(), j->getAngleLimitMin().z, j->getAngleLimitMax().z);
            pimpl->joints.insert(std::pair<std::string, Joint*>(j->getName(), j));
            break;
        case Joint::Type::BALL:
            std::cerr << "Ball Joints not yet implemented" << std::endl;
            break;
    }
    return 0;
}

void World::impl::updateEntities() {

    for (auto it = entities.begin(); it != entities.end(); it++) {

        if ((*it).second->getGeometry()->getType() == Geometry::Type::PLANE) { continue; }

        (*it).second->setPosition(simulator.getBodyPositionFromName((*it).second->getName()));
        (*it).second->setRotation(simulator.getBodyRotationFromName((*it).second->getName()));
    }

}

void World::impl::updateJoints() {

    for (auto it = joints.begin(); it != joints.end(); it++) {
        (*it).second->setAngle(simulator.getJointAngleFromName((*it).second->getName()));
        (*it).second->setOmega(simulator.getJointOmegaFromName((*it).second->getName()));
    }
}


const std::map<std::string, Entity*>& World::getEntities() {
    return pimpl->entities;

}

void World::impl::setSimulationTorques() {

    for (auto it = joints.begin(); it != joints.end(); it++) {

        Vector3f torque = it->second->getCurrTorque();
        Vector3f maxTorque = it->second->getTorqueLimit();
        if (torque.x > maxTorque.x) { torque.x = maxTorque.x; }
        else if (torque.x < -maxTorque.x) { torque.x = -maxTorque.x; }
        if (torque.y > maxTorque.y) { torque.y = maxTorque.y; }
        else if (torque.y < -maxTorque.y) { torque.y = -maxTorque.y; }
        if (torque.z > maxTorque.z) { torque.z = maxTorque.z; }
        else if (torque.z < -maxTorque.z) { torque.z = -maxTorque.z; }

        Joint* j = joints.find(it->second->getName())->second;
        switch(j->getType()) 
        {
            case Joint::Type::HINGE:
                simulator.setHingeJointTorque(it->second->getName(), torque.z);
                break;
            case Joint::Type::BALL:
                std::cerr << "Ball joints not yet implemented" << std::endl;
                break;
        }

        it->second->resetCurrTorque();

    }

}

void World::step(float stepsize)
{
    pimpl->setSimulationTorques();

    pimpl->simulator.step(stepsize);

    pimpl->updateEntities();
    pimpl->updateJoints();
    //pimpl->frameTime+= stepsize;

}

int World::reset() {
    return this->loadState(0);
}


int World::loadState(int which) {
    if (pimpl->stateList.size() <= which) {
        std::cerr << "Cannot load state " << which << " for world " << pimpl->name << "." << std::endl;
        return -1;
    }

    State* s = &(pimpl->stateList.at(which));

    for (auto it = s->entities.begin(); it != s->entities.end(); it++) {

        std::string name = it->first;
        Entity* set = pimpl->entities.find(name)->second;
        set->setPosition(it->second.pos);
        set->setVelocity(it->second.vel);
        set->setRotation(it->second.rot);
        set->setOmega(it->second.ang_vel);

        pimpl->simulator.updateEntity(name, set->getPosition(), set->getVelocity(), set->getRotationAsQuaternion(), set->getOmega());

    }
    // is this automatically determined based on the part?
    /*
    for (auto it = s->joints.begin(); it != s->joints.end(); it++) {

        std::string name = it->first;
        Joint* set = pimpl->joints.find(name)->second;
        set->setAngle(it->second.ang);

    }
    */

    return 0;

}


void World::saveState() {
    State state;
    for (auto it = pimpl->entities.begin(); it != pimpl->entities.end(); it++) {
        E_state e;
        e.pos = it->second->getPosition();
        e.rot = it->second->getRotationAsQuaternion();
        e.vel = it->second->getVelocity();
        e.ang_vel = it->second->getOmega();
        state.entities.insert(std::pair<std::string, E_state>(it->second->getName(), e));
    }
    for (auto it = pimpl->joints.begin(); it != pimpl->joints.end(); it++) {
        J_state j;
        j.ang = it->second->getJointAngle();
        state.joints.insert(std::pair<std::string, J_state>(it->second->getName(), j));
    }
    pimpl->stateList.push_back(state);
}

void World::go(float stepsize)
{
    this->saveState();
    while (true)
    {
        pimpl->simulator.step(stepsize);
        pimpl->updateEntities();
    }
}

