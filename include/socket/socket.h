#ifndef SOCKET_H
#define SOCKET_H 

/*
 * Socket.h
 * Author: Michael Firmin (mcfirmin @ gmail.com)
 * Date: 22 Apr 2015
 * 
 * Description: initializes a socket to talk with the python server.
 * Used by Controller.h to set world states, send frame info, etc.
 *
 *
 *
 */

#include "vmath.h"

#define MY_PORT		9999
#define MAXBUF	    2048	
#define MAX_CONNECTIONS 5 

class Socket 
{

    public:

        Socket();

        int init();

        int sendMessage(const char* buffer, int length);
        char* recvMessage();

    private:
        static bool INITIALIZED;

        struct impl;
        impl* pimpl;
};

#endif // SOCKET_H
