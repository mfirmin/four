#ifndef SOCKETRENDERER_H
#define SOCKETRENDERER_H 

#include "vmath.h"

class World;

class SocketRenderer 
{
    public:

        SocketRenderer();

        int init();

        int addPointLight(Vector3f, Vector3f c=Vector3f(.1,.1,.1));
        int addWorldToRender(World*);
        void waitForRender();
        int render();

    private:
        static bool INITIALIZED;

        struct impl;
        impl* pimpl;
};

#endif // SOCKETRENDERER_H
