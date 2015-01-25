#ifndef JOINT_H
#define JOINT_H

#include "vmath.h"
#include <string>
#include "config.h"

class Geometry;
class Entity;

class Joint
{
    public:

        Joint(
                std::string name,
                Entity* parent, 
                Entity* child, 
                Vector3f pos,
                Vector3f angle=Vector3f(0,0,0), 
                Vector3f ang_min=Vector3f(-180,-180,-180),
                Vector3f ang_max = Vector3f(180,180,180),
                Vector3f MAX_TORQUE = Vector3f(Globals::MAX_TORQUE_DEFAULT, Globals::MAX_TORQUE_DEFAULT, Globals::MAX_TORQUE_DEFAULT)
             );

        int init();

        Entity* getParent();
        Entity* getChild();

        // Physical Properties

        std::string getName();
        void setName(std::string);
        Vector3f getPosition();
        Vector3f getJointAngle();
        Vector3f getCurrTorque();
        Vector3f getTorqueLimit();
        Vector3f getAngleLimitMin();
        Vector3f getAngleLimitMax();

        void setID(int);
        int getID();

        enum Type { HINGE, BALL };

        void addTorque(Vector3f t);

        virtual Type getType() = 0;

    private:

        struct impl;
        impl* pimpl;
};

#endif // JOINT_H
