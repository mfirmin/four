
#include <stdlib.h>
#include <iostream>

#include "entity/box.h"

struct Box::impl
{

    Vector3f sides;
    
};

Box::Box(Vector3f s) 
{
    pimpl = new impl();
    pimpl->sides = s;
}

int Box::init()
{
    return 0;
}

int Box::getInitialStateAsJSONString(char* buffer) {
    return sprintf(buffer, "\"type\":\"box\",\"sides\":[%f,%f,%f]", pimpl->sides.x, pimpl->sides.y, pimpl->sides.z);
}

Vector3f Box::getSides()
{
    return pimpl->sides;

}

void Box::setSides(Vector3f s)
{
    pimpl->sides = s;
}

void Box::setWidth(float w)
{
    pimpl->sides.x = w;
}
void Box::setHeight(float h)
{
    pimpl->sides.y = h;
}
void Box::setDepth(float d)
{
    pimpl->sides.z = d;
}


/*
int main(int argc, char** argv)
{

}
*/
