#ifndef UTILS_H
#define UTILS_H

#include <math.h>
#include "vmath.h"

namespace utils
{

    void ODE_to_OGL(float* set, const float* from);

    void RFromEulerAngles(float* R, Vector3f angles);

    void setMFromRAndP(float* M, Quaternion<float> R, Vector3f pos);

    float deg2rad(float d); 
    float rad2deg(float r);

}

#endif // UTILS_H
