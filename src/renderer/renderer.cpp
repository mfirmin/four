
#include <stdlib.h>
#include <iostream>

#ifdef __APPLE__
	#include <OpenGL/glu.h>
#else
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

#include <time.h>

#ifdef __APPLE__
#include <sys/time.h>
#endif

#include <GLFW/glfw3.h>

#include <vector>

#include "renderer/renderer.h"
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

struct Renderer::impl
{
    const float frametime = 1./30.;

    std::vector<World*> worlds;

};

bool Renderer::INITIALIZED = false;

Renderer::Renderer() 
{
    pimpl = new impl();

}

int Renderer::getFrameTime() {
    return pimpl->frametime;
}

std::vector<World*>& Renderer::getWorlds() {
    return pimpl->worlds;
}


int Renderer::addWorldToRender(World* w)
{
    pimpl->worlds.push_back(w);
    return 0;
}

GLvoid setMaterialProperties( GLfloat r, GLfloat g, GLfloat b, GLfloat alpha)
{
	GLfloat mat_specular[4] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat mat_ambient_and_diffuse[4] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat mat_shininess[1] = {0.0};
	
	mat_specular[0] = mat_ambient_and_diffuse[0] = r;
	mat_specular[1] = mat_ambient_and_diffuse[1] = g;
	mat_specular[2] = mat_ambient_and_diffuse[2] = b;
	mat_specular[3] = mat_ambient_and_diffuse[3] = alpha;

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_ambient_and_diffuse);
}
