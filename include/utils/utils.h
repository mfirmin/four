#ifndef UTILS_H
#define UTILS_H

#include <math.h>
#include "vmath.h"

namespace utils
{

    void ODE_to_OGL(float* set, const float* from);

    void RFromEulerAngles(float* R, Vector3f angles);

    void setMFromRAndP(float* M, const float* R, Vector3f pos);

}

#endif // UTILS_H
