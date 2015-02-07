#ifndef RENDERER_H
#define RENDERER_H 

#include "vmath.h"

class World;

class Renderer
{
    public:

        Renderer();

        int init();

        int addPointLight(Vector3f);
        int addWorldToRender(World*);
        void waitForRender();
        int render();

    private:
        static bool INITIALIZED;

        struct impl;
        impl* pimpl;
};

#endif // RENDERER_H
