
#include <stdlib.h>
#include <iostream>

#include <vector>

#include "entity/entity.h"
#include "joint/joint.h"
#include "joint/hingejoint.h"
#include "vmath.h"
#include "utils/utils.h"

struct HingeJoint::impl 
{
    Vector3f axis;
};

HingeJoint::HingeJoint(Entity* e1, Entity* e2, float ang, Vector3f axis, float ang_min, float ang_max, float maxTorque) : Joint( e1, e2, Vector3f(0,0,ang), Vector3f(0,0,ang_min), Vector3f(0,0,ang_max), Vector3f(0,0,maxTorque))
{

    pimpl = new impl();

    pimpl->axis = axis;


}

    /*

    Vector3f HingeJoint::getPosition() {
        return pimpl->pos;
    }

Vector3f HingeJoint::getHingeJointAngle() {
    return pimpl->ang;
}
Vector3f HingeJoint::getCurrTorque() {
    return pimpl->currTorque;
}
Vector3f HingeJoint::getTorqueLimit() {
    return pimpl->MAX_TORQUE;
}
Vector3f HingeJoint::getAngleLimitMin() {
    return pimpl->ANGLE_LIMIT_MIN;
}
Vector3f HingeJoint::getAngleLimitMax() {
    return pimpl->ANGLE_LIMIT_MAX;
}
void HingeJoint::addTorque(Vector3f t) {
    pimpl->currTorque += t;
}
*/

int HingeJoint::init()
{
    return 0;
}

/*
int main(int argc, char** argv)
{

}
*/
