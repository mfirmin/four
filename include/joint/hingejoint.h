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
                std::string name,
                Entity* parent, 
                Entity* child, 
                Vector3f pos,
                Vector3f axis=Vector3f(0,0,1),
                float angle = 0, 
                float ang_min = -180,
                float ang_max = 180,
                float MAX_TORQUE = Globals::MAX_TORQUE_DEFAULT
             );

        int init();

        Vector3f getAxis();

        Type getType() { return _type; }

        // Physical Properties

    private:
        struct impl;
        impl* pimpl;
        static const Type _type = HINGE;
};

#endif // HINGEJOINT_H
