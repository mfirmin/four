#ifndef HINGEJOINT_H
#define HINGEJOINT_H

#include "vmath.h"
#include "config.h"
#include "joint/joint.h"

class Entity;

class HingeJoint : public Joint
{
    public:

        HingeJoint(
                Entity* parent, 
                Entity* child, 
                float angle, 
                Vector3f axis=Vector3f(0,0,1),
                float ang_min = -180,
                float ang_max = 180,
                float MAX_TORQUE = Globals::MAX_TORQUE_DEFAULT
             );

        int init();


        // Physical Properties

        /*
        Vector3f getPosition();
        Vector3f getHingeJointAngle();
        Vector3f getCurrTorque();
        Vector3f getTorqueLimit();
        Vector3f getAngleLimitMin();
        Vector3f getAngleLimitMax();

        void addTorque(Vector3f t);
        */


    private:
        struct impl;
        impl* pimpl;
};

#endif // HINGEJOINT_H
