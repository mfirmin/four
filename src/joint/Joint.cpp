
#include <stdlib.h>
#include <iostream>

#include <vector>

#include "entity/entity.h"
#include "joint/joint.h"
#include "vmath.h"
#include "utils/utils.h"

struct Joint::impl
{

    Vector3f pos;
    Vector3f ang;

    Vector3f currTorque;

    Entity* parent;
    Entity* child;
    
};

Joint::Joint(Entity* e1, Entity* e2, Vector3f ang) 
{
    pimpl = new impl();
    pimpl->parent = e1;
    pimpl->child = e2;
    pimpl->ang = ang;
    pimpl->currTorque = Vector3f(0,0,0);

}

int Joint::init()
{
    return 0;
}

/*
int main(int argc, char** argv)
{

}
*/
