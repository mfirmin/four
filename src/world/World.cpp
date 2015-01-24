
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
    std::vector<Entity*> entities;
    std::vector<Joint*> joints;

    ODEWrapper simulator;

    Renderer renderer;

    void updateEntities();

    void waitForRender(_timeval&);

    float frameTime;

    const float framerate = 1./30.;

    // Last render;

};

World::World() 
{
    pimpl = new impl();
}

int World::init()
{

    pimpl->simulator = ODEWrapper();
    pimpl->simulator.init();
    pimpl->renderer = Renderer();
    pimpl->frameTime = 0;

    pimpl->renderer.init();

    return 0;


}

int World::addPointLight(Vector3f pos)
{
    if (pimpl->renderer.addPointLight(pos) != 0)
    {
        std::cerr << "Error adding point light (world.cpp)" << std::endl;
        return -1;
    }
    return 0;

}

int World::addEntity(Entity* e)
{

    int ent = -1;
    switch(e->getGeometry()->getType())
    {
        case Geometry::Type::BOX:
            ent = pimpl->simulator.addBox(e->getPosition(), dynamic_cast<Box*>(e->getGeometry())->getSides(), e->getVelocity(), e->getRotationAsQuaternion(), e->getOmega(), 10);
            break;
        case Geometry::Type::SPHERE:
            ent = pimpl->simulator.addSphere(e->getPosition(), dynamic_cast<Sphere*>(e->getGeometry())->getRadius(), e->getVelocity(), e->getRotationAsQuaternion(), e->getOmega(), 10);
            break;
        case Geometry::Type::CYLINDER:
            ent = pimpl->simulator.addCylinder(e->getPosition(), dynamic_cast<Cylinder*>(e->getGeometry())->getRadius(), dynamic_cast<Cylinder*>(e->getGeometry())->getHeight(), e->getVelocity(), e->getRotationAsQuaternion(), e->getOmega(), 10);
            break;
        case Geometry::Type::CAPSULE:
            ent = pimpl->simulator.addCapsule(e->getPosition(), dynamic_cast<Capsule*>(e->getGeometry())->getRadius(), dynamic_cast<Capsule*>(e->getGeometry())->getHeight(), e->getVelocity(), e->getRotationAsQuaternion(), e->getOmega(), 10);
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

    e->setID(pimpl->entities.size());
    pimpl->entities.push_back(e);

    return 0;
}

int World::addJoint(Joint* j)
{

    switch(j->getType()) {
        case Joint::Type::HINGE:
            pimpl->simulator.addHingeJoint(j->getParent()->getID(), j->getChild()->getID(), j->getPosition(), dynamic_cast<HingeJoint*>(j)->getAxis());
            j->setID(pimpl->joints.size());
            pimpl->joints.push_back(j);
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
        if ((*it)->getGeometry()->getType() == Geometry::Type::PLANE) { continue; }
        (*it)->setPosition(simulator.getBodyPositionFromID((*it)->getID()));
        (*it)->setRotation(simulator.getBodyRotationFromID((*it)->getID()));
    }

}

void World::impl::waitForRender(_timeval& last)
{
	long frame = (framerate * 1E9);
    int i = 0;
    _timeval now;
#ifndef __APPLE__
    clock_gettime(CLOCK_REALTIME, &now);
    while ( (now.tv_sec * 1E9 + now.tv_nsec) - (last.tv_sec * 1E9 + last.tv_nsec) < frame)
    {
        clock_gettime(CLOCK_REALTIME, &now);
    }

    clock_gettime(CLOCK_REALTIME, &last);
#endif
    
#ifdef __APPLE__
    gettimeofday(&now, NULL);
    while ( (now.tv_sec * 1E9 + now.tv_usec * 1E3) - (last.tv_sec * 1E9 + last.tv_usec * 1E3) < frame)
    {
        gettimeofday(&now, NULL);
        i++;
    }

    gettimeofday(&last, NULL);
#endif

}

void World::go(float stepsize)
{
#ifndef __APPLE__
	timespec last;
    clock_gettime(CLOCK_REALTIME, &last);
#endif

#ifdef __APPLE__
    timeval last;
    gettimeofday(&last, NULL);
#endif
    while (true)
    {
        pimpl->simulator.step(stepsize);

        pimpl->updateEntities();
        pimpl->frameTime+= stepsize;


        if (pimpl->frameTime > pimpl->framerate)
        {
            pimpl->waitForRender(last);
            pimpl->renderer.render(pimpl->entities);
            pimpl->frameTime = 0;
        }
    }
}

int main(int argc, char** argv)
{

    float STEPSIZE = 0.0001;

    World* world = new World();

    world->init();

    world->addPointLight(Vector3f(10,10,10));

    Geometry* g = new Box(Vector3f(1,1,1));

    Entity* e = new Entity(g, Vector3f(0,10,0), Vector3f(0,0,0), Quaternion<float>().fromEulerAngles(0,0,0));
    e->setColor(Vector3f(1,.3,.3));
    
    Entity* e2 = new Entity(new Box(Vector3f(1,1,1)), Vector3f(1,11,0));
    e2->setColor(Vector3f(0,.8,.2));
    
    Entity* e3 = new Entity(new Box(Vector3f(1,1,1)), Vector3f(-1,10,0));
    e3->setColor(Vector3f(0,.4,.6));


    /*
    Entity* e3 = new Entity(new Cylinder(.5, 1), Vector3f(0,15,0));
    e3->setColor(Vector3f(0,.4,.7));

    
    Entity* e4 = new Entity(new Capsule(.5, 1), Vector3f(1,25,0));
    e4->setColor(Vector3f(.8,.8,.2));

    Entity* e5 = new Entity(new Sphere(.5), Vector3f(1.2,18,0));
    e5->setColor(Vector3f(.5,.5,.5));
    
    */
    world->addEntity(e);
    world->addEntity(e2);
    world->addEntity(e3);

    Joint* j = new HingeJoint(e, e2, Vector3f(.5, 10.5, 0));
    Joint* j2 = new HingeJoint(e, e3, Vector3f(-.5, 9.5, 0));

    world->addJoint(j);
    world->addJoint(j2);
    /*
    world->addEntity(e3);
    world->addEntity(e4);
    world->addEntity(e5);
    */

    Geometry* ground = new Plane(Vector3f(-50, -1, 0), Vector3f(50, -1, 0));
    Entity* groundEntity  = new Entity(ground);

    world->addEntity(groundEntity);

    world->go(STEPSIZE);

}
