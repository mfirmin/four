#ifndef ENTITY_H
#define ENTITY_H

#include "vmath.h"
#include <string>

class Geometry;

class Entity
{
    public:

        Entity(std::string name, Geometry*, float m=1, Vector3f p=Vector3f(0,0,0), Vector3f v=Vector3f(0,0,0), Quaternion<float> r=Quaternion<float>().fromEulerAngles(0,0,0), Vector3f w=Vector3f(0,0,0));

        int init();


        // Physical Properties

        // GETTERS //
        Vector3f getPosition();
        Vector3f getVelocity();
        Quaternion<float> getRotationAsQuaternion();
        Vector3f getOmega();
        Geometry* getGeometry();
        float getMass();
        int getID();

        std::string getName();

        // SETTERS //
        void setPosition(Vector3f);
        void setVelocity(Vector3f);
        void setRotation(Quaternion<float>);
        void setOmega(Vector3f);
        void setGeometry(Geometry*);
        void setMass(float);
        void setID(int);

        void setName(std::string);


        // State Info //
        int getInitialStateAsJSONString(char* buffer);
        int getCurrentStateAsJSONString(char* buffer);


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
