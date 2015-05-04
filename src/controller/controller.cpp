
#include <stdlib.h>
#include <iostream>

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <fstream>

#include "controller/controller.h"
#include "socket/socket.h"
#include "world/world.h"


struct Controller::impl 
{

    std::map<std::string, World*> worlds;
    Socket* s;
    int handleMessage(char*);
};

Controller::Controller() 
{

    pimpl = new impl();

}


int Controller::init()
{

    pimpl->s = new Socket();

    pimpl->s->init();

    return 0;
}

const std::map<std::string, World*>& Controller::getWorlds()
{
    return pimpl->worlds;
}

int Controller::initWorld(char* wname) {

    World* world = new World("sampleWorld");
    world->init();

    pimpl->worlds.insert(std::pair<std::string, World*>(std::string(wname), world));

    printf("%s", pimpl->worlds.find(std::string(wname))->second->getName().c_str());

    return 0;

}

int Controller::handleMessage(char* msg) {


    if (strcmp(msg, "init") == 0) {
        char* wname = recvMessage();
        this->initWorld(wname);
    }


    delete [] msg;

    return 0;

}

char* Controller::recvMessage() {
    char* msg = pimpl->s->recvMessage();

    return msg;
}

