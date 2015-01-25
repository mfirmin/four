#ifndef ODEWRAPPER_H
#define ODEWRAPPER_H

#include "vmath.h"

class ODEWrapper
{
    public:

        ODEWrapper();

        int init();
        int addCube(Vector3f pos, float sides, Vector3f vel0, Quaternion<float> ang0, Vector3f ang_vel0, float mass);
        int addBox(Vector3f pos, Vector3f sides, Vector3f vel0, Quaternion<float> ang0, Vector3f ang_vel0, float mass);
        int addCylinder(Vector3f pos, float rad, float h, Vector3f vel0, Quaternion<float> ang0, Vector3f ang_vel0, float mass);
        int addCapsule(Vector3f pos, float rad, float h, Vector3f vel0, Quaternion<float> ang0, Vector3f ang_vel0, float mass);
        int addSphere(Vector3f pos, float rad, Vector3f vel0, Quaternion<float> ang0, Vector3f ang_vel0, float mass);
        int addPlane(Vector3f A, Vector3f B);
        int addHingeJoint(int parent, int child, Vector3f pos, Vector3f axis, float ang_min=-180, float ang_max=180);
        Vector3f getBodyPositionFromID(int id);
        Quaternion<float> getBodyRotationFromID(int id);

        void step(float);


    private:
        static bool INITIALIZED;

        struct impl;
        impl* pimpl;
};

#endif // ODEWRAPPER_H
