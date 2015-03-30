#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "vmath.h"

#include <string>
#include <iostream>
#include <fstream>


class Controller
{
    public:

        Controller();

        int init();
        int setTorques();

    private:

        struct impl;
        impl* pimpl;
};

#endif // CONTROLLER_H
