#ifndef CAPSULE_H
#define CAPSULE_H 

#include "vmath.h"
#include "entity/geometry.h"

class Capsule : public Geometry
{
    public:

        Capsule(float r, float h);

        int init();

        int getInitialStateAsJSONString(char*);

        void setRadius(float);
        void setHeight(float);

        float getRadius();
        float getHeight();

        Type getType() { return _type; }

    private:

        struct impl;
        impl* pimpl;
        static const Type _type = CAPSULE;
};

#endif // CAPSULE_H 
