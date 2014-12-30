#ifndef RENDERER_H
#define RENDERER_H 

#include "vmath.h"

class Entity;

class Renderer
{
    public:

        Renderer();

        int init();

        int  addPointLight(Vector3f);
        int  render(const std::vector<Entity*>&);

    private:

        struct impl;
        impl* pimpl;
};

#endif // RENDERER_H
