#ifndef PLANE_H
#define PLANE_H 

#include <vector>
#include "vmath.h"
#include "entity/geometry.h"

class Plane : public Geometry
{
    public:

        Plane(Vector3f a, Vector3f b);

        int init();

        Vector3f getA();
        Vector3f getB();

        std::vector<Vector3f> getAsLine();

        void setA(Vector3f);
        void setB(Vector3f);

        Type getType() { return _type; }

    private:

        struct impl;
        impl* pimpl;
        static const Type _type = PLANE;
};

#endif // PLANE_H
