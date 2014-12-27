#ifndef RENDERER_H
#define RENDERER_H 

#include "../math/VECTOR.h"

class Entity;

class Renderer
{
    public:

        Renderer();

        int init();

        int  addPointLight(VECTOR);
        int  render(const std::vector<Entity*>&);

    private:

        struct impl;
        impl* pimpl;
};

#endif // RENDERER_H
