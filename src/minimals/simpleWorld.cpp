
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

    /*

    Entity* body = new Entity(std::string("body"), new Sphere(.5), Vector3f(0,.5,0));
    Entity* torso = new Entity(std::string("torso"), new Sphere(.4), Vector3f(0,1.4,0));
    Entity* head = new Entity(std::string("head"), new Sphere(.3), Vector3f(0,2.1, 0));

    Joint* hips = new HingeJoint(std::string("hips"), body, torso, Vector3f(0,1,0), Vector3f(0,0,1), 0, -.1, .1);
    Joint* neck = new HingeJoint(std::string("neck"), torso, head, Vector3f(0,1.8,0), Vector3f(0,0,1), 0, -1, 1);

    Character* snowman = new Character(std::string("snowman"));
    snowman->addEntity(body);
    snowman->addEntity(torso);
    snowman->addEntity(head);
    snowman->addJoint(hips);
    snowman->addJoint(neck);
    w->addCharacter(snowman);
    */

    Geometry* g = new Plane(Vector3f(-50, 0, 0), Vector3f(50, 0, 0));
    Entity* ge = new Entity(std::string("ground"), g);
    
    world->addEntity(ge);

    Character* human = new Character(std::string("h"));
    //human->initFromFile("inputs/characters/human.char");
    human->initFromFile("inputs/characters/test.char");

    world->addCharacter(human);


    float t = 0; 
    float t_frame = 0;
    float frameTime = 1./30.;

    r->addWorldToRender(world);
    int i = 0;
    while (i < 1) 
    {
        for (t_frame = 0; t_frame < frameTime; t_frame+=STEPSIZE) 
        {
            world->step(STEPSIZE);
        }
        r->waitForRender();
        r->render();
//        i++;
    }
    while (true) {}
}
