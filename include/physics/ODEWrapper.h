#ifndef ODEWRAPPER_H
#define ODEWRAPPER_H

#include "vmath.h"
#include <string>

class ODEWrapper
{
    public:

        ODEWrapper();

        int init();
        int addCube(std::string name, Vector3f pos, float sides, Vector3f vel0, Quaternion<float> ang0, Vector3f ang_vel0, float mass);
        int addBox(std::string name, Vector3f pos, Vector3f sides, Vector3f vel0, Quaternion<float> ang0, Vector3f ang_vel0, float mass);
        int addCylinder(std::string name, Vector3f pos, float rad, float h, Vector3f vel0, Quaternion<float> ang0, Vector3f ang_vel0, float mass);
        int addCapsule(std::string name, Vector3f pos, float rad, float h, Vector3f vel0, Quaternion<float> ang0, Vector3f ang_vel0, float mass);
        int addSphere(std::string name, Vector3f pos, float rad, Vector3f vel0, Quaternion<float> ang0, Vector3f ang_vel0, float mass);
        int addPlane(Vector3f A, Vector3f B);
        int addHingeJoint(std::string name, std::string parent, std::string child, Vector3f pos, Vector3f axis, float ang_min=-180, float ang_max=180);
        Vector3f getBodyPositionFromName(std::string name);
        Quaternion<float> getBodyRotationFromName(std::string name);

        void step(float);


    private:
        static bool INITIALIZED;

        struct impl;
        impl* pimpl;
};

#endif // ODEWRAPPER_H
