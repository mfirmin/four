
#include <stdlib.h>
#include <iostream>

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <fstream>

#include "controller/controller.h"


struct Controller::impl
{


};

Controller::Controller() 
{
    pimpl = new impl();

}


int Controller::init()
{
    return 0;
}

int Controller::setTorques()
{
    return -1;
}
