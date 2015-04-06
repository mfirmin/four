#ifndef RENDERER_H
#define RENDERER_H 

#include "vmath.h"

class World;

class Renderer
{
    public:

        Renderer();

        virtual int addWorldToRender(World*);

        virtual int init() = 0;

        virtual int addPointLight(Vector3f, Vector3f c=Vector3f(.1,.1,.1)) = 0;
        virtual void waitForRender() = 0;
        virtual int render() = 0;


        std::vector<World*>& getWorlds(); 
        int getFrameTime();

    private:
        static bool INITIALIZED;

        struct impl;
        impl* pimpl;
};

// GL Helper fn
void setMaterialProperties( float r, float g, float b, float alpha);

#endif // RENDERER_H
