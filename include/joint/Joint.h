#ifndef JOINT_H
#define JOINT_H

#include "vmath.h"

class Geometry;
class Entity;

class Joint
{
    public:

        Joint(Entity* parent, Entity* child, Vector3f angle);

        int init();


        // Physical Properties

        Vector3f getPosition();
        Vector3f getJointAngle();

    private:

        struct impl;
        impl* pimpl;
};

#endif // JOINT_H
