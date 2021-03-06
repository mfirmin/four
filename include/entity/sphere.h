#ifndef SPHERE_H
#define SPHERE_H 

#include "vmath.h"
#include "entity/geometry.h"

class Sphere : public Geometry
{
    public:

        Sphere(float radius);

        int init();

        int getInitialStateAsJSONString(char*);

        float getRadius();

        void setRadius(float);

        Type getType() { return _type; }

    private:

        struct impl;
        impl* pimpl;
        static const Type _type = SPHERE;
};

#endif // SPHERE_H
