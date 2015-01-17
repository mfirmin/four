
#include <stdlib.h>
#include <iostream>

#include "entity/Cylinder.h"

struct Cylinder::impl
{

    float radius;
    float height;
    
};

Cylinder::Cylinder(float r, float h) 
{
    pimpl = new impl();
    pimpl->radius = r;
    pimpl->height = h;
}

int Cylinder::init()
{
    return 0;
}

float Cylinder::getRadius()
{
    return pimpl->radius;

}
float Cylinder::getHeight()
{
    return pimpl->height;

}

void Cylinder::setRadius(float r)
{
    pimpl->radius = r;
}
void Cylinder::setHeight(float h)
{
    pimpl->height = h;
}



/*
int main(int argc, char** argv)
{

}
*/
