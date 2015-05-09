
#include <stdlib.h>
#include <iostream>

#include "vmath.h"

#include "entity/geometry.h"

struct Geometry::impl
{

};

Geometry::Geometry() 
{
    pimpl = new impl();
}

int Geometry::init()
{
    return 0;
}


/*
int main(int argc, char** argv)
{

}
*/
