#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "vmath.h"

class Geometry
{
    public:

        Geometry();

        int init();

        enum Type { BOX, PLANE, CYLINDER, CAPSULE, SPHERE, N_TYPES };

        virtual Type getType() = 0;

    private:

        struct impl;
        impl* pimpl;
};

#endif // ENTITY_H
