
#include <stdlib.h>
#include <iostream>

#include "entity/sphere.h"

struct Sphere::impl
{
    float radius;
};

Sphere::Sphere(float r) 
{
    pimpl = new impl();
    pimpl->radius = r;
}

int Sphere::init()
{
    return 0;
}

float Sphere::getRadius()
{
    return pimpl->radius;

}

void Sphere::setRadius(float r)
{
    pimpl->radius = r;
}

/*
int main(int argc, char** argv)
{

}
*/
