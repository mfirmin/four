#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <resolv.h>
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <netdb.h>
#include <streambuf>
#include <unistd.h>

#include <iostream>
#include <time.h>

#ifdef __APPLE__
#include <sys/time.h>
#endif

#include <vector>

#include "socketrenderer/socketrenderer.h"
#include "vmath.h"
#include "entity/entity.h"
#include "entity/box.h"
#include "entity/cylinder.h"
#include "entity/capsule.h"
#include "entity/sphere.h"
#include "entity/plane.h"
#include "entity/geometry.h"
#include "utils/utils.h"
#include "world/world.h"


#ifdef __APPLE__
typedef timeval _timeval;
#endif
#ifndef __APPLE__
typedef timespec _timeval;
#endif

#define MY_PORT		9999
#define MAXBUF		1024

const float frametime = 1./30.;

struct SocketRenderer::impl {

    void renderBox(Entity*);
    void renderCylinder(Entity*);
    void renderCapsule(Entity*);
    void renderSphere(Entity*);
    void renderLine(Entity*);

    std::vector<World*> worlds;

	_timeval last;

};

int SocketRenderer::init()
{   
    int sockfd;
	struct sockaddr_in self;
	char buffer[MAXBUF];

    
	/*---Create streaming socket---*/
    if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
	{
		perror("Socket");
		exit(errno);
	}

	/*---Initialize address/port structure---*/
	bzero(&self, sizeof(self));
	self.sin_family = AF_INET;
	self.sin_port = htons(MY_PORT);
	self.sin_addr.s_addr = INADDR_ANY;

    int yes = 1;
    if (setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int)) == -1) {
        perror("setsockopt");
        exit(1);
    } 

	/*---Assign a port number to the socket---*/
    if ( bind(sockfd, (struct sockaddr*)&self, sizeof(self)) != 0 )
	{
		perror("socket--bind");
		exit(errno);
	}

	/*---Make it a "listening socket"---*/
	if ( listen(sockfd, 20) != 0 )
	{
		perror("socket--listen");
		exit(errno);
	}

    int i = 0;
    int clientfd;
    struct sockaddr_in client_addr;
    int addrlen=(sizeof(client_addr));
    /*

    clientfd = accept(sockfd, (struct sockaddr*)&client_addr, (socklen_t*)&addrlen);
    // just want our client now. only ever listen to one.
    close(sockfd);

    // inet_ntoa obsolete, use inet_ntop!
    printf("%s:%d connected\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));


    sprintf(buffer, "%d", 12);
    send(clientfd, buffer, sizeof(int), 0);
    sprintf(buffer, "%s", "{\"rArm\": 50}");
    send(clientfd, buffer, 12*sizeof(char), 0);
    printf("done sending!");

	close(clientfd);
    */
	return 0;
}

