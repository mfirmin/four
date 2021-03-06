#ifndef CONTROLLER_H
#define CONTROLLER_H

/*
 * Controller.h
 * Author: Michael Firmin (mcfirmin @ gmail.com)
 * Date: 22 Apr 2015
 * 
 * Description: controls the simulation, receives/sends commands to the server through a Socket.
 *
 */

#include "vmath.h"

#include <string>
#include <iostream>
#include <fstream>

class World;


class Controller
{
    public:

        Controller();

        int init();

        World* initWorld(char* name);

        const std::map<std::string, World*>& getWorlds();

        char* recvMessage();
        int sendMessage(const char* buffer);

        int handleMessage(char* msg);

        // start the main loop
        int go();

    private:

        struct impl;
        impl* pimpl;
};

#endif // CONTROLLER_H
