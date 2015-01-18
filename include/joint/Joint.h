#ifndef JOINT_H
#define JOINT_H

#include "vmath.h"
#include "config.h"

class Geometry;
class Entity;

class Joint
{
    public:

        Joint(
                Entity* parent, 
                Entity* child, 
                Vector3f pos,
                Vector3f angle=Vector3f(0,0,0), 
                Vector3f ang_min=Vector3f(-180,-180,-180),
                Vector3f ang_max = Vector3f(180,180,180),
                Vector3f MAX_TORQUE = Vector3f(Globals::MAX_TORQUE_DEFAULT, Globals::MAX_TORQUE_DEFAULT, Globals::MAX_TORQUE_DEFAULT)
             );

        int init();


        // Physical Properties

        Vector3f getPosition();
        Vector3f getJointAngle();
        Vector3f getCurrTorque();
        Vector3f getTorqueLimit();
        Vector3f getAngleLimitMin();
        Vector3f getAngleLimitMax();

        void setID(int);
        int getID();
        

        void addTorque(Vector3f t);

    private:

        struct impl;
        impl* pimpl;
};

#endif // JOINT_H
