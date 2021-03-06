
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


struct Controller::impl {

    std::map<std::string, World*> worlds;
    Socket* s;
    int handleMessage(char*);
};

Controller::Controller() {

    pimpl = new impl();

}


int Controller::init() {

    pimpl->s = new Socket();

    pimpl->s->init();

    return 0;
}

const std::map<std::string, World*>& Controller::getWorlds() {
    return pimpl->worlds;
}

World* Controller::initWorld(char* wname) {
    
    World* world;
    auto it = pimpl->worlds.find(std::string(wname));
    if (it != pimpl->worlds.end()) {
        world = it->second;
    } else {
        world = new World(wname);
        world->init();
        pimpl->worlds.insert(std::pair<std::string, World*>(std::string(wname), world));
    }

    return world;

}

int Controller::handleMessage(char* msg) {


    if (strcmp(msg, "init") == 0) {
        char* wname = recvMessage();
        World* world = this->initWorld(wname);
        std::string state = world->getInitialStateAsJSONString();
        sendMessage(state.c_str());
    } else if (strcmp(msg, "requestFrame") == 0) {
        char* wname = recvMessage();

        auto it = pimpl->worlds.find(wname);
        if (it == pimpl->worlds.end()) {
            std::cout << "Unknown world with name " << wname << std::endl;
            return -1;
        }
        World* world = it->second;

        float STEPSIZE = 0.0001;
        float t = 0; 
        float t_frame = 0;
        float frameTime = 1./30.;
        for (t_frame = 0; t_frame < frameTime; t_frame+=STEPSIZE) 
        {
            world->step(STEPSIZE);
        }

        std::string state = world->getCurrentStateAsJSONString();

        sendMessage(state.c_str());
    } else if (strcmp(msg, "reset") == 0) {
        char* wname = recvMessage();

        auto it = pimpl->worlds.find(wname);
        if (it == pimpl->worlds.end()) {
            std::cout << "Unknown world with name " << wname << std::endl;
            return -1;
        }
        World* world = it->second;
        world->reset();


    }

    delete [] msg;

    return 0;

}

int Controller::sendMessage(const char* msg) {
    int res = pimpl->s->sendMessage(msg, strlen(msg));
    return res;
}

char* Controller::recvMessage() {
    char* msg = pimpl->s->recvMessage();

    return msg;
}

int Controller::go() {

    while(true) {
        this->handleMessage(this->recvMessage());
    }
}

