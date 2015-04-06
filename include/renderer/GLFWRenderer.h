#ifndef GLFWRENDERER_H
#define GLFWRENDERER_H 

#include "vmath.h"
#include "renderer.h"

class World;

class GLFWRenderer : public Renderer
{
    public:

        GLFWRenderer();

        int init();

        int addPointLight(Vector3f, Vector3f c=Vector3f(.1,.1,.1));
        void waitForRender();
        int render();

    private:
        static bool INITIALIZED;

        struct impl;
        impl* pimpl;
};

#endif // GLFWRENDERER_H
