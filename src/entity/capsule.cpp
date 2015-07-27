
#include <stdlib.h>
#include <iostream>

#include "entity/capsule.h"

struct Capsule::impl
{

    float radius;
    float height;
    
};

Capsule::Capsule(float r, float h) 
{
    pimpl = new impl();
    pimpl->radius = r;
    pimpl->height = h;
}

int Capsule::init()
{
    return 0;
}

int Capsule::getInitialStateAsJSONString(char* buffer) {
    return sprintf(buffer, "\"type\":\"capsule\",\"radius\":%f,\"height\":%f", pimpl->radius, pimpl->height);
}

float Capsule::getRadius()
{
    return pimpl->radius;

}
float Capsule::getHeight()
{
    return pimpl->height;

}

void Capsule::setRadius(float r)
{
    pimpl->radius = r;
}
void Capsule::setHeight(float h)
{
    pimpl->height = h;
}



/*
int main(int argc, char** argv)
{

}
*/
