#ifndef ODEWRAPPER_H
#define ODEWRAPPER_H

#include "math/VECTOR.h"

class ODEWrapper
{
    public:

        ODEWrapper();


        int init();
        int addCube(VECTOR pos, float sides, VECTOR vel0, const float* ang0, VECTOR ang_vel0, float mass);
        int addBox(VECTOR pos, VECTOR sides, VECTOR vel0, const float* ang0, VECTOR ang_vel0, float mass);
        int addPlane(VECTOR A, VECTOR B);
        int addJoint(VECTOR pos, float theta=0, float dTheta=0);
        VECTOR getBodyPositionFromID(int id);
        const float* getBodyRotationFromID(int id);

        void step(float);

    private:

        struct impl;
        impl* pimpl;
};

#endif // ODEWRAPPER_H
