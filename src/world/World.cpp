
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
#include "entity/Plane.h"

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
    // references to simulation IDs.
    std::vector<int> simIDs;

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
            ent = pimpl->simulator.addBox(e->getPosition(), dynamic_cast<Box*>(e->getGeometry())->getSides(), e->getVelocity(), e->getRotation(), e->getOmega(), 10);
            break;
        case Geometry::Type::CYLINDER:
            ent = pimpl->simulator.addCylinder(e->getPosition(), dynamic_cast<Cylinder*>(e->getGeometry())->getRadius(), dynamic_cast<Cylinder*>(e->getGeometry())->getHeight(), e->getVelocity(), e->getRotation(), e->getOmega(), 10);
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

    pimpl->entities.push_back(e);
    pimpl->simIDs.push_back(ent);;

    return 0;
}

void World::impl::updateEntities()
{

    auto IDit = simIDs.begin();
    for (auto it = entities.begin(); it != entities.end(); it++)
    {
        if ((*it)->getGeometry()->getType() == Geometry::Type::PLANE) { continue; }
        (*it)->setPosition(simulator.getBodyPositionFromID(*IDit));
        (*it)->setRotation(simulator.getBodyRotationFromID(*IDit));
        IDit++;
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

    Entity* e = new Entity(g, Vector3f(0,10,-1), Vector3f(0,0,0), Vector3f(-.7, 0, 0));
    e->setColor(Vector3f(1,.3,.3));

    
    Entity* e3 = new Entity(new Box(Vector3f(2,1,1)), Vector3f(3,15,0));
    e3->setColor(Vector3f(0,.8,.2));
    

    Entity* e2 = new Entity(new Cylinder(.5, 1), Vector3f(0,15,0));
    e2->setColor(Vector3f(0,.4,.7));

    world->addEntity(e);
    world->addEntity(e2);
    world->addEntity(e3);

    Geometry* ground = new Plane(Vector3f(-50, -1, 0), Vector3f(50, -1, 0));
    Entity* groundEntity  = new Entity(ground);

    world->addEntity(groundEntity);

    world->go(STEPSIZE);

}
