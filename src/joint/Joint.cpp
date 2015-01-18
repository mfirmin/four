
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
    // Specified in Euler axis angles (degrees).
    Vector3f ang;
    Vector3f ANGLE_LIMIT_MIN;
    Vector3f ANGLE_LIMIT_MAX;

    Vector3f MAX_TORQUE;

    Vector3f currTorque;

    Entity* parent;
    Entity* child;
    
};

Joint::Joint(Entity* e1, Entity* e2, Vector3f pos, Vector3f ang, Vector3f ang_min, Vector3f ang_max, Vector3f maxTorque) 
{
    pimpl = new impl();
    pimpl->parent = e1;
    pimpl->child = e2;
    pimpl->pos = pos;
    pimpl->ang = ang;
    pimpl->ANGLE_LIMIT_MIN= ang_min;
    pimpl->ANGLE_LIMIT_MAX= ang_max;
    pimpl->MAX_TORQUE = maxTorque;
    pimpl->currTorque = Vector3f(0,0,0);

}

Vector3f Joint::getPosition() {
    return pimpl->pos;
}

Vector3f Joint::getJointAngle() {
    return pimpl->ang;
}
Vector3f Joint::getCurrTorque() {
    return pimpl->currTorque;
}
Vector3f Joint::getTorqueLimit() {
    return pimpl->MAX_TORQUE;
}
Vector3f Joint::getAngleLimitMin() {
    return pimpl->ANGLE_LIMIT_MIN;
}
Vector3f Joint::getAngleLimitMax() {
    return pimpl->ANGLE_LIMIT_MAX;
}
void Joint::addTorque(Vector3f t) {
    pimpl->currTorque += t;
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
