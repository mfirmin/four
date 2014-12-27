#ifndef PLANE_H
#define PLANE_H 

#include <vector>
#include "../math/VECTOR.h"
#include "Geometry.h"

class Plane : public Geometry
{
    public:

        Plane(VECTOR a, VECTOR b);

        int init();

        VECTOR getA();
        VECTOR getB();

        std::vector<VECTOR> getAsLine();

        void setA(VECTOR);
        void setB(VECTOR);

        Type getType() { return _type; }

    private:

        struct impl;
        impl* pimpl;
        static const Type _type = PLANE;
};

#endif // PLANE_H
