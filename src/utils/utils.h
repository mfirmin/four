#ifndef UTILS_H
#define UTILS_H

#include <math.h>
#include "../math/VECTOR.h"

namespace utils
{

    void ODE_to_OGL(float* set, const float* from);

    void RFromEulerAngles(float* R, VECTOR angles);

    void setMFromRAndP(float* M, const float* R, VECTOR pos);

}

#endif // UTILS_H
