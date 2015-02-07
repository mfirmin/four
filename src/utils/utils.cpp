
#include <iostream>

#include "utils/utils.h"

namespace utils
{
    void ODE_to_OGL(float* set, const float* from)
    {


        set[0] = from[0]; set[1] = from[4]; set[2] = from[8]; 
        set[3] = from[1]; set[4] = from[5]; set[5] = from[9];
        set[6] = from[2]; set[7] = from[6]; set[8] = from[10];

        /*
    std::cout << from[0] << " " << from[4] << " " << from[8] << std::endl;
    std::cout << from[1] << " " << from[5] << " " << from[9] << std::endl;
    std::cout << from[2] << " " << from[6] << " " << from[10] << std::endl;
    std::cout << "\n\n";
    */

    }

    void RFromEulerAngles(float* R, Vector3f angles)
    {

        float cosa = cos(angles.x), cosb = cos(angles.y), cosc = cos(angles.z);
        float sina = sin(angles.x), sinb = sin(angles.y), sinc = sin(angles.z);

        R[0] = cosc*cosb*cosa - sinc*sina;   R[3] = cosc*cosb*sina + sinc*cosa;    R[6] = -cosc*sinb;
        R[1] = -sinc*cosb*cosa - cosc*sina;  R[4] = -sinc*cosb*sina + cosc*cosa;   R[7] = sinc*sinb;
        R[2] = sinb*cosa;                    R[5] = sinb*sina;                     R[8] = cosb;

        /*
    std::cout << R[0] << " " << R[3] << " " << R[6] << std::endl;
    std::cout << R[1] << " " << R[4] << " " << R[7] << std::endl;
    std::cout << R[2] << " " << R[5] << " " << R[8] << std::endl;
    */

    }

    void setMFromRAndP(float* M, Quaternion<float> q, Vector3f pos) 
    {
        q.normalize();
        float R[9];
        R[0] = 1 - 2*q.v.y*q.v.y - 2*q.v.z*q.v.z; R[3] = 2*q.v.x*q.v.y - 2*q.v.z*q.w;     R[6] = 2*q.v.x*q.v.z + 2*q.v.y*q.w;
        R[1] = 2*q.v.x*q.v.y + 2*q.v.z*q.w;     R[4] = 1 - 2*q.v.x*q.v.x - 2*q.v.z*q.v.z; R[7] = 2*q.v.y*q.v.z - 2*q.v.x*q.w;
        R[2] = 2*q.v.x*q.v.z - 2*q.v.y*q.w;     R[5] = 2*q.v.y*q.v.z + 2*q.v.x*q.w;     R[8] = 1 - 2*q.v.x*q.v.x - 2*q.v.y*q.v.y;

        M[0] = R[0]; M[4] = R[3]; M[8] =  R[6];  M[12] = pos.x;
        M[1] = R[1]; M[5] = R[4]; M[9] =  R[7];  M[13] = pos.y;
        M[2] = R[2]; M[6] = R[5]; M[10] = R[8];  M[14] = pos.z;
        M[3] = 0;    M[7] = 0;    M[11] = 0;     M[15] = 1;
    }

    float deg2rad(float d) { return d*3.14159/180.; }
    float rad2deg(float r) { return r*180./3.14159; }

}
