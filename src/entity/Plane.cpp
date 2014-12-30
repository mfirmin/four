
#include <stdlib.h>
#include <iostream>

#include "entity/Plane.h"

struct Plane::impl
{

    Vector3f A;
    Vector3f B;
    
};

Plane::Plane(Vector3f a, Vector3f b) 
{
    pimpl = new impl();
    pimpl->A = a;
    pimpl->B = b;
}

int Plane::init()
{
    return 0;
}

std::vector<Vector3f> Plane::getAsLine()
{
    std::vector<Vector3f> ret = std::vector<Vector3f>();

    ret.push_back(pimpl->A);
    ret.push_back(pimpl->B);

    return ret;
}

Vector3f Plane::getB()
{
    return pimpl->B;

}
Vector3f Plane::getA()
{
    return pimpl->A;
}

void Plane::setA(Vector3f a)
{
    pimpl->A = a;
}

void Plane::setB(Vector3f b)
{
    pimpl->B  = b;
}

/*
int main(int argc, char** argv)
{

}
*/
