#ifndef ENTITY_H
#define ENTITY_H

#include "vmath.h"

class Geometry;

class Entity
{
    public:

        Entity(Geometry*, Vector3f p=Vector3f(0,0,0), Vector3f v=Vector3f(0,0,0), Quaternion<float> r=Quaternion<float>().fromEulerAngles(0,0,0), Vector3f w=Vector3f(0,0,0));

        int init();


        // Physical Properties

        Vector3f getPosition();
        void setPosition(Vector3f);
        Vector3f getVelocity();
        void setVelocity(Vector3f);
        Quaternion<float> getRotationAsQuaternion();
        void setRotation(Quaternion<float>);
        Vector3f getOmega();
        void setOmega(Vector3f);
        Geometry* getGeometry();
        void setGeometry(Geometry*);

        void setID(int);
        int getID();


        // Stylistic Properties 
        //

        Vector3f getColor();
        void setColor(Vector3f);

        float getOpacity();
        void setOpacity(float);


    private:

        struct impl;
        impl* pimpl;
};

#endif // ENTITY_H
