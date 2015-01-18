
#include <stdlib.h>
#include <iostream>

#include <vector>

#include "entity/entity.h"
#include "vmath.h"
#include "utils/utils.h"

struct Entity::impl
{

    Vector3f pos;
    Vector3f vel;
    Quaternion<float> rot;
    Vector3f ang_vel;
    Vector3f color;
    float opacity;

    Geometry* geom;
    
};

Entity::Entity(Geometry* g, Vector3f p, Vector3f v, Quaternion<float> r, Vector3f w) 
{
    pimpl = new impl();
    pimpl->pos = p;
    pimpl->vel = v;
    pimpl->rot = r;
    std::cout << r.v.x << ", " << r.v.y << ", " << r.v.z << ", " << r.w << std::endl;
    pimpl->ang_vel= w;

    pimpl->color = Vector3f(.5,.5,.5);
    pimpl->opacity = 1;

    pimpl->geom = g;
}

int Entity::init()
{
    return 0;
}

Vector3f Entity::getColor()
{
    return pimpl->color;
}

void Entity::setColor(Vector3f c)
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

Vector3f Entity::getPosition()
{
    return pimpl->pos;

}
void Entity::setPosition(Vector3f pos)
{
    pimpl->pos = pos;
}
Vector3f Entity::getVelocity()
{
    return pimpl->vel;

}
void Entity::setVelocity(Vector3f vel)
{
    pimpl->vel = vel;
}
Quaternion<float> Entity::getRotationAsQuaternion()
{
    return pimpl->rot;

}
void Entity::setRotation(Quaternion<float> q)
{
    pimpl->rot = q;
}
Vector3f Entity::getOmega()
{
    return pimpl->ang_vel;

}
void Entity::setOmega(Vector3f o)
{
    pimpl->ang_vel = o;
}

/*
int main(int argc, char** argv)
{

}
*/
