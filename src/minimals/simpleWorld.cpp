
//#include "ODEConstants.h"

#define dSINGLE

#include <stdlib.h>
#include <iostream>

#include <vector>


#include "world/world.h"
#include "entity/Geometry.h"
#include "entity/Box.h"
#include "entity/Cylinder.h"
#include "entity/Capsule.h"
#include "entity/Sphere.h"
#include "entity/Plane.h"

#include "joint/Joint.h"
#include "joint/HingeJoint.h"
#include "character/Character.h"

#include "vmath.h"
#include "physics/ODEWrapper.h"
#include "entity/Entity.h"
#include "renderer/Renderer.h"


int main(int argc, char** argv)
{

    float STEPSIZE = 0.0001;

    // -- Set up renderer -- //
    Renderer* r = new Renderer();
    r->init();

    // -- Set up world 1 -- //
    World* world = new World();

    world->init();

    r->addPointLight(Vector3f(10,10,10));

    Geometry* g = new Box(Vector3f(1,1,1));

    Entity* e = new Entity(std::string("box1"), g, Vector3f(0,10,0), Vector3f(0,0,0), Quaternion<float>().fromEulerAngles(0,0,0));
    e->setColor(Vector3f(1,.3,.3));
    
    Entity* e2 = new Entity(std::string("box2"), new Box(Vector3f(1,1,1)), Vector3f(1,11,0));
    e2->setColor(Vector3f(0,.8,.2));
    
    Entity* e3 = new Entity(std::string("box3"), new Box(Vector3f(1,1,1)), Vector3f(-1,10,0));
    e3->setColor(Vector3f(0,.4,.6));
    

    world->addEntity(e);
    world->addEntity(e2);
    world->addEntity(e3);

    Joint* j = new HingeJoint(std::string("j1"), e, e2, Vector3f(.5, 10.5, 0));
    Joint* j2 = new HingeJoint(std::string("j2"),e, e3, Vector3f(-.5, 9.5, 0));

    world->addJoint(j);
    world->addJoint(j2);

    Geometry* ground = new Plane(Vector3f(-50, -1, 0), Vector3f(50, -1, 0));
    Entity* groundEntity  = new Entity(std::string("ground"), ground);
    world->addEntity(groundEntity);

    // -- Set up world 2 -- //

    World* w2 = new World();
    w2->init();

    Entity* e4 = new Entity(std::string("cap1"), new Capsule(.5, 1), Vector3f(1,25,0));
    e4->setColor(Vector3f(.8,.8,.2));
    
    w2->addEntity(e4);
    
    Geometry* g2 = new Plane(Vector3f(-50, -1, 0), Vector3f(50, -1, 0));
    Entity* g2e = new Entity(std::string("cap2"), ground);
    
    w2->addEntity(groundEntity);

    World* w3 = new World();
    w3->init();

    Entity* body = new Entity(std::string("body"), new Sphere(.5), Vector3f(0,.5,0));
    Entity* torso = new Entity(std::string("torso"), new Sphere(.4), Vector3f(0,1.4,0));
    Entity* head = new Entity(std::string("head"), new Sphere(.3), Vector3f(.01,2.1, 0));

    Joint* hips = new HingeJoint(std::string("hips"), body, torso, Vector3f(0,1,0));
    Joint* neck = new HingeJoint(std::string("neck"), torso, head, Vector3f(0,1.8,0));

    Character* snowman = new Character(std::string("snowman"));
    snowman->addEntity(body);
    snowman->addEntity(torso);
    snowman->addEntity(head);
    snowman->addJoint(hips);
    snowman->addJoint(neck);
    w3->addCharacter(snowman);

    Geometry* g3 = new Plane(Vector3f(-50, -1, 0), Vector3f(50, -1, 0));
    Entity* g3e = new Entity(std::string("cap2"), ground);
    
    w3->addEntity(groundEntity);



    float t = 0; 
    float t_frame = 0;
    float frameTime = 1./30.;
    /*
    r->addWorldToRender(world);
    r->addWorldToRender(w2);
    */
    r->addWorldToRender(w3);
    while (true) 
    {
        for (t_frame = 0; t_frame < frameTime; t_frame+=STEPSIZE) 
        {
            world->step(STEPSIZE);
            w2->step(STEPSIZE);
            w3->step(STEPSIZE);
        }
        r->waitForRender();
        r->render();
    }
}
