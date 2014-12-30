#ifndef BOX_H
#define BOX_H 

#include "vmath.h"
#include "entity/Geometry.h"

class Box : public Geometry
{
    public:

        Box(Vector3f sides);

        int init();


        Vector3f getSides();

        void setSides(Vector3f);
        void setWidth(float);
        void setHeight(float);
        void setDepth(float);

        Type getType() { return _type; }

    private:

        struct impl;
        impl* pimpl;
        static const Type _type = BOX;
};

#endif // ENTITY_H
