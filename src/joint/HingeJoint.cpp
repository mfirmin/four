
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

HingeJoint::HingeJoint(Entity* e1, Entity* e2, Vector3f pos, Vector3f axis, float ang, float ang_min, float ang_max, float maxTorque) : Joint( e1, e2, pos, Vector3f(0,0,ang), Vector3f(0,0,ang_min), Vector3f(0,0,ang_max), Vector3f(0,0,maxTorque))
{

    pimpl = new impl();

    pimpl->axis = axis;


}

Vector3f HingeJoint::getAxis()
{
    return pimpl->axis;
}

int HingeJoint::init()
{
    return 0;
}

/*
int main(int argc, char** argv)
{

}
*/
