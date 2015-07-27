
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

#include "renderer/GLFWRenderer.h"
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

struct GLFWRenderer::impl
{

    int initGL();
    int initGLFW();

    float zoom;

    GLFWwindow* window;

    void renderBox(Entity*);
    void renderCylinder(Entity*);
    void renderCapsule(Entity*);
    void renderSphere(Entity*);
    void renderLine(Entity*);

    void setCamera();

    std::vector<World*> worlds;

	_timeval last;

};

bool GLFWRenderer::INITIALIZED = false;


void GLFWRenderer::waitForRender()
{
	long frame = (this->getFrameTime() * 1E9);
    int i = 0;
    _timeval now;

#ifndef __APPLE__
    clock_gettime(CLOCK_REALTIME, &now);
    while ( (now.tv_sec * 1E9 + now.tv_nsec) - (pimpl->last.tv_sec * 1E9 + pimpl->last.tv_nsec) < frame)
    {
        clock_gettime(CLOCK_REALTIME, &now);
    }

    clock_gettime(CLOCK_REALTIME, &(pimpl->last));
#endif
    
#ifdef __APPLE__
    gettimeofday(&now, NULL);
    while ( (now.tv_sec * 1E9 + now.tv_usec * 1E3) - (pimpl->last.tv_sec * 1E9 + pimpl->last.tv_usec * 1E3) < frame)
    {
        gettimeofday(&now, NULL);
        i++;
    }

    gettimeofday(&(pimpl->last), NULL);
#endif

}

GLFWRenderer::GLFWRenderer() : Renderer()
{
    pimpl = new impl();
    pimpl->zoom = 1;

#ifndef __APPLE__
    clock_gettime(CLOCK_REALTIME, &(pimpl->last));
#endif

#ifdef __APPLE__
    gettimeofday(&(pimpl->last), NULL);
#endif

}

int GLFWRenderer::init()
{

    if (pimpl->initGLFW() != 0)
    {
        std::cerr << "Error initializing GLFW (GLFWRenderer.cpp)" << std::endl;
        return -2;
    }
    if (pimpl->initGL() != 0)
    {
        std::cerr << "Error initializing openGL (GLFWRenderer.cpp)" << std::endl;
        return -1;
    }

    return 0;

}

int GLFWRenderer::addPointLight(Vector3f pos, Vector3f color)
{
	GLfloat light_ambient[] = { color.x, color.y, color.z, 1.0 };
	GLfloat light_diffuse[] = { .7, .7, .7, 1.0 };
	GLfloat light_specular[] = { 0, 0, 0, 1.0 };
	GLfloat light_position[] = { pos.x, pos.y, pos.z, 0.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION,0.0);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

    return 0;
}


int GLFWRenderer::impl::initGL()
{
	glEnable(GL_CULL_FACE);

	glCullFace(GL_BACK);
	glEnable(GL_NORMALIZE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(1.0,1.0,1.0,1.0);
	glEnable(GL_DEPTH_TEST);

    return 0;

}

int GLFWRenderer::impl::initGLFW()
{


    if (!INITIALIZED)
    {
        if (!glfwInit())
        {
            std::cout << "Error initializing GLFW in initializeGLFW(), GLFWRenderer.cpp" << std::endl;
            return -1;
        }
        INITIALIZED = true;
    }

    window = glfwCreateWindow(960,720,"Composability",NULL,NULL);

	if (window == NULL)
    {
        std::cout << "Error creating GLFW window in initializeGLFW(), GLFWRenderer.cpp" << std::endl;
		return -2;
    }

    glfwSetWindowPos(window, 400, 100);
    glfwMakeContextCurrent(window);

	return 0;
}

void GLFWRenderer::impl::setCamera()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-2-zoom, 2+zoom, -0.5-.75*zoom, 2.5+.75*zoom, 3, 20);

}

void GLFWRenderer::impl::renderCylinder(Entity* e)
{
    glPushMatrix();
    Vector3f pos = e->getPosition();
    Vector3f color = e->getColor();
    Quaternion<float> rot = e->getRotationAsQuaternion();
    float opacity = e->getOpacity();

    setMaterialProperties(color.x, color.y, color.z, opacity);

    float M[16];
    utils::setMFromRAndP(M, rot, pos);

    
    glTranslatef(0,0,-10);
    glMultMatrixf(M);

    float r = dynamic_cast<Cylinder*>(e->getGeometry())->getRadius();
    float h = dynamic_cast<Cylinder*>(e->getGeometry())->getHeight();

    glPushMatrix();
        glTranslatef(0, 0, h/2.);
        gluDisk(gluNewQuadric(), 0, r, 16, 16);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0, 0, -h/2.);
        GLUquadric* back = gluNewQuadric();
        gluQuadricOrientation(back, GLU_INSIDE);
        gluDisk(back, 0, r, 16, 16);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0, 0, -h/2.);
        gluCylinder(gluNewQuadric(), r, r, h, 16, 16);
    glPopMatrix();

    glPopMatrix();

}

void GLFWRenderer::impl::renderCapsule(Entity* e)
{
    glPushMatrix();
    Vector3f pos = e->getPosition();
    Vector3f color = e->getColor();
    Quaternion<float> rot = e->getRotationAsQuaternion();
    float opacity = e->getOpacity();

    setMaterialProperties(color.x, color.y, color.z, opacity);

    float M[16];
    utils::setMFromRAndP(M, rot, pos);

    
    glTranslatef(0,0,-10);
    glMultMatrixf(M);

    float r = dynamic_cast<Capsule*>(e->getGeometry())->getRadius();
    float h = dynamic_cast<Capsule*>(e->getGeometry())->getHeight();

    glPushMatrix();
        glTranslatef(0, 0, h/2.);
        gluSphere(gluNewQuadric(), r, 16, 16);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0, 0, -h/2.);
        gluSphere(gluNewQuadric(), r, 16, 16);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0, 0, -h/2.);
        gluCylinder(gluNewQuadric(), r, r, h, 16, 16);
    glPopMatrix();

    glPopMatrix();

}
void GLFWRenderer::impl::renderSphere(Entity* e)
{
    glPushMatrix();
    Vector3f pos = e->getPosition();
    Vector3f color = e->getColor();
    Quaternion<float> rot = e->getRotationAsQuaternion();
    float opacity = e->getOpacity();

    setMaterialProperties(color.x, color.y, color.z, opacity);

    float M[16];
    utils::setMFromRAndP(M, rot, pos);

    
    glTranslatef(0,0,-10);
    glMultMatrixf(M);

    float r = dynamic_cast<Sphere*>(e->getGeometry())->getRadius();

    glPushMatrix();
        gluSphere(gluNewQuadric(), r, 16, 16);
    glPopMatrix();

    glPopMatrix();

}

void GLFWRenderer::impl::renderBox(Entity* e)
{

    glPushMatrix();
    Vector3f pos = e->getPosition();
    Vector3f color = e->getColor();
    Quaternion<float> rot = e->getRotationAsQuaternion();
    float opacity = e->getOpacity();

    setMaterialProperties(color.x, color.y, color.z, opacity);

    float M[16];
    utils::setMFromRAndP(M, rot, pos);

    
    glTranslatef(0,0,-10);
    glMultMatrixf(M);


    Vector3f sides = dynamic_cast<Box*>(e->getGeometry())->getSides();

    glBegin(GL_QUADS);

    {
        // Front Face
        glNormal3f(0.0,0.0,-1.0);

        glVertex3f(sides.x/2.0,sides.y/2.0,-sides.z/2.0);
        glVertex3f(sides.x/2.0,-sides.y/2.0,-sides.z/2.0);
        glVertex3f(-sides.x/2.0,-sides.y/2.0,-sides.z/2.0);
        glVertex3f(-sides.x/2.0,sides.y/2.0,-sides.z/2.0);

        // Back Face
        glNormal3f(0.0,0.0,1.0);

        glVertex3f(sides.x/2.0,sides.y/2.0,sides.z/2.0);
        glVertex3f(-sides.x/2.0,sides.y/2.0,sides.z/2.0);
        glVertex3f(-sides.x/2.0,-sides.y/2.0,sides.z/2.0);
        glVertex3f(sides.x/2.0,-sides.y/2.0,sides.z/2.0);

        glNormal3f(1.0,0.0,0.0);

        glVertex3f(sides.x/2.0,-sides.y/2.0,sides.z/2.0);
        glVertex3f(sides.x/2.0,-sides.y/2.0,-sides.z/2.0);
        glVertex3f(sides.x/2.0,sides.y/2.0,-sides.z/2.0);
        glVertex3f(sides.x/2.0,sides.y/2.0,sides.z/2.0);

        glNormal3f(-1.0,0.0,0.0);

        glVertex3f(-sides.x/2.0,-sides.y/2.0,sides.z/2.0);
        glVertex3f(-sides.x/2.0,sides.y/2.0,sides.z/2.0);
        glVertex3f(-sides.x/2.0,sides.y/2.0,-sides.z/2.0);
        glVertex3f(-sides.x/2.0,-sides.y/2.0,-sides.z/2.0);

        glNormal3f(0.0,1.0,0.0);

        glVertex3f(-sides.x/2.0,sides.y/2.0,sides.z/2.0);
        glVertex3f(sides.x/2.0,sides.y/2.0,sides.z/2.0);
        glVertex3f(sides.x/2.0,sides.y/2.0,-sides.z/2.0);
        glVertex3f(-sides.x/2.0,sides.y/2.0,-sides.z/2.0);

        glNormal3f(0.0,-1.0,0.0);

        glVertex3f(-sides.x/2.0,-sides.y/2.0,-sides.z/2.0);
        glVertex3f(sides.x/2.0,-sides.y/2.0,-sides.z/2.0);
        glVertex3f(sides.x/2.0,-sides.y/2.0,sides.z/2.0);
        glVertex3f(-sides.x/2.0,-sides.y/2.0,sides.z/2.0);

    }


    glEnd();


    glPopMatrix();


}

void GLFWRenderer::impl::renderLine(Entity* e)
{

    
    glPushMatrix();

    Vector3f pos = e->getPosition();
    Vector3f color = e->getColor();
    float opacity = e->getOpacity();

    setMaterialProperties(color.x, color.y, color.z, opacity);

    glTranslatef(pos.x, pos.y, pos.z-10);

    std::vector<Vector3f> line = dynamic_cast<Plane*>(e->getGeometry())->getAsLine();


    glBegin(GL_LINE_STRIP);
    {

        for (auto it = line.begin(); it != line.end(); it++)
        {
            glVertex3f(it->x, it->y, it->z);
        }
    }

    glEnd();

    glPopMatrix();



}

int GLFWRenderer::render()
{

    glfwMakeContextCurrent(pimpl->window);

    pimpl->setCamera();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    for (auto wIter = this->getWorlds().begin(); wIter != this->getWorlds().end(); wIter++)
    {
        for (auto it=(*wIter)->getEntities().begin(); it != (*wIter)->getEntities().end(); it++)
        {

            switch ((*it).second->getGeometry()->getType())
            {
                case Geometry::Type::BOX:
                    pimpl->renderBox(it->second);
                    break;
                case Geometry::Type::CYLINDER:
                    pimpl->renderCylinder(it->second);
                    break;
                case Geometry::Type::CAPSULE:
                    pimpl->renderCapsule(it->second);
                    break;
                case Geometry::Type::PLANE:
                    pimpl->renderLine(it->second);
                    break;
                case Geometry::Type::SPHERE:
                    pimpl->renderSphere(it->second);
                    break;
                default:
                    std::cerr << "GLFWRenderer.cpp: Unknown Entity TYPE: " << it->second->getGeometry()->getType() << std::endl;
                    break;
            }
        }

    }

    glFlush();

    glfwSwapBuffers(pimpl->window);


    return 0;
}
