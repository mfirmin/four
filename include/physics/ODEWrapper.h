#ifndef ODEWRAPPER_H
#define ODEWRAPPER_H

#include "vmath.h"

class ODEWrapper
{
    public:

        ODEWrapper();


        int init();
        int addCube(Vector3f pos, float sides, Vector3f vel0, const float* ang0, Vector3f ang_vel0, float mass);
        int addBox(Vector3f pos, Vector3f sides, Vector3f vel0, const float* ang0, Vector3f ang_vel0, float mass);
        int addCylinder(Vector3f pos, float rad, float h, Vector3f vel0, const float* ang0, Vector3f ang_vel0, float mass);
        int addCapsule(Vector3f pos, float rad, float h, Vector3f vel0, const float* ang0, Vector3f ang_vel0, float mass);
        int addPlane(Vector3f A, Vector3f B);
        int addJoint(Vector3f pos, float theta=0, float dTheta=0);
        Vector3f getBodyPositionFromID(int id);
        const float* getBodyRotationFromID(int id);

        void step(float);

    private:

        struct impl;
        impl* pimpl;
};

#endif // ODEWRAPPER_H
