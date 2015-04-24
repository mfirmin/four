
#include <stdlib.h>
#include <iostream>

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <fstream>

#include "controller/controller.h"
#include "socket/socket.h"


struct Controller::impl 
{

    Socket* s;

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

int Controller::sendTestMessage() {
    char buff[1024];

    int len = sprintf(buff, "{\"hello\":\"world\"}");
    pimpl->s->sendMessage(buff, len);

    return 0;
}

