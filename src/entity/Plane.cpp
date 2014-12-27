
#include <stdlib.h>
#include <iostream>

#include <vector>

#include "Plane.h"

struct Plane::impl
{

    VECTOR A;
    VECTOR B;
    
};

Plane::Plane(VECTOR a, VECTOR b) 
{
    pimpl = new impl();
    pimpl->A = a;
    pimpl->B = b;
}

int Plane::init()
{
    return 0;
}

std::vector<VECTOR> Plane::getAsLine()
{
    std::vector<VECTOR> ret = std::vector<VECTOR>();

    ret.push_back(pimpl->A);
    ret.push_back(pimpl->B);

    return ret;
}

VECTOR Plane::getB()
{
    return pimpl->B;

}
VECTOR Plane::getA()
{
    return pimpl->A;
}

void Plane::setA(VECTOR a)
{
    pimpl->A = a;
}

void Plane::setB(VECTOR b)
{
    pimpl->B  = b;
}

/*
int main(int argc, char** argv)
{

}
*/
