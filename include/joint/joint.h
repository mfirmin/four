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
        Vector3f getPosition();
        Vector3f getJointAngle();
        Vector3f getCurrTorque();
        Vector3f getTorqueLimit();
        Vector3f getAngleLimitMin();
        Vector3f getAngleLimitMax();
        void setCurrTorque(Vector3f);
        void resetCurrTorque();
        void setName(std::string);

        void setAngle(Vector3f);

        void setID(int);
        int getID();

        void addTorque(Vector3f t);

        enum Type { HINGE, BALL };
        virtual Type getType() = 0;

    private:

        struct impl;
        impl* pimpl;
};

#endif // JOINT_H
