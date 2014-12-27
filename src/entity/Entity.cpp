
#include <stdlib.h>
#include <iostream>

#include <vector>

#include "entity/entity.h"
#include "math/VECTOR.h"
#include "utils/utils.h"

struct Entity::impl
{

    VECTOR pos;
    VECTOR vel;
    float rot[9];
    VECTOR ang_vel;
    VECTOR color;
    float opacity;

    Geometry* geom;
    
};

Entity::Entity(Geometry* g, VECTOR p, VECTOR v, VECTOR r, VECTOR w) 
{
    pimpl = new impl();
    pimpl->pos = p;
    pimpl->vel = v;
    utils::RFromEulerAngles(pimpl->rot, r);
    pimpl->ang_vel= w;

    pimpl->color = VECTOR(.5,.5,.5);
    pimpl->opacity = 1;

    pimpl->geom = g;
}

int Entity::init()
{
    return 0;
}

VECTOR Entity::getColor()
{
    return pimpl->color;
}

void Entity::setColor(VECTOR c)
{
    pimpl->color = c;
}

float Entity::getOpacity()
{
    return pimpl->opacity;
}

void Entity::setOpacity(float o)
{
    pimpl->opacity = o;
}

Geometry* Entity::getGeometry()
{
    return pimpl->geom;
}

void Entity::setGeometry(Geometry* g)
{
    pimpl->geom = g;
}

VECTOR Entity::getPosition()
{
    return pimpl->pos;

}
void Entity::setPosition(VECTOR pos)
{
    pimpl->pos = pos;
}
VECTOR Entity::getVelocity()
{
    return pimpl->vel;

}
void Entity::setVelocity(VECTOR vel)
{
    pimpl->vel = vel;
}
const float* Entity::getRotation()
{
    /*
    std::cout << pimpl->rot[0] << " " << pimpl->rot[3] << " " << pimpl->rot[6] << std::endl;
    std::cout << pimpl->rot[1] << " " << pimpl->rot[4] << " " << pimpl->rot[7] << std::endl;
    std::cout << pimpl->rot[2] << " " << pimpl->rot[5] << " " << pimpl->rot[8] << std::endl;
    */
    return pimpl->rot;

}
void Entity::setRotation(const float* rot_in)
{
    utils::ODE_to_OGL(pimpl->rot, rot_in);
}
VECTOR Entity::getOmega()
{
    return pimpl->ang_vel;

}
void Entity::setOmega(VECTOR o)
{
    pimpl->ang_vel = o;
}

/*
int main(int argc, char** argv)
{

}
*/
