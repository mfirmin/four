#ifndef CYLINDER_H
#define CYLINDER_H 

#include "vmath.h"
#include "entity/Geometry.h"

class Cylinder : public Geometry
{
    public:

        Cylinder(float r, float h);

        int init();

        void setRadius(float);
        void setHeight(float);

        float getRadius();
        float getHeight();

        Type getType() { return _type; }

    private:

        struct impl;
        impl* pimpl;
        static const Type _type = CYLINDER;
};

#endif // CYLINDER_H 
