
//#include "ODEConstants.h"

#define dSINGLE

#include <stdlib.h>
#include <iostream>
#include <ode/ode.h>
#include <cmath>

#include <vector>

#include "physics/ODEWrapper.h"
#include "vmath.h"

struct ODEWrapper::impl
{
    dWorldID world;
    dSpaceID space;
    dJointGroupID contactgroup;
    dJointGroupID jointgroup;

    std::vector<dBodyID> bodies;
    std::vector<dJointID> joints;

    dBodyID addBody(ODEWrapper*, dGeomID&, Vector3f, Vector3f, Quaternion<float>, Vector3f);

    dBodyID getBodyIDFromID(int i) { return bodies.at(i); }

    static void nearCallback(void*, dGeomID, dGeomID);
};

ODEWrapper::ODEWrapper() 
{
	dInitODE();
    pimpl = new impl();
}

int ODEWrapper::init() 
{

	pimpl->world = dWorldCreate();
	pimpl->space = dSimpleSpaceCreate(0);
	pimpl->contactgroup = dJointGroupCreate(0);
	pimpl->jointgroup = dJointGroupCreate(0);

	dWorldSetGravity(pimpl->world, 0, -9.81, 0);

	dWorldSetERP(pimpl->world, 0.5);
	dWorldSetCFM(pimpl->world, 1e-5);

	dWorldSetContactMaxCorrectingVel(pimpl->world, 0.3);

	dWorldSetContactSurfaceLayer(pimpl->world, 0.001);

	dWorldSetAutoDisableFlag(pimpl->world, 0);

    return 0;

}

dBodyID ODEWrapper::impl::addBody(ODEWrapper*, dGeomID&, Vector3f pos, Vector3f vel, Quaternion<float> ang, Vector3f w)
{
    dBodyID id = dBodyCreate(world);
    dBodySetPosition(id, pos.x, pos.y, pos.z);

	dMatrix3 R;
	dRFromEulerAngles(R, 0, 0, 0);


    /*
    std::cout << ang[0] << " " << ang[3] << " " << ang[6] << std::endl;
    std::cout << ang[1] << " " << ang[4] << " " << ang[7] << std::endl;
    std::cout << ang[2] << " " << ang[5] << " " << ang[8] << std::endl;
    */

    /*
    std::cout << R[0] << " " << R[4] << " " << R[8] << std::endl;
    std::cout << R[1] << " " << R[5] << " " << R[9] << std::endl;
    std::cout << R[2] << " " << R[6] << " " << R[10] << std::endl;
    */

    
	dBodySetRotation(id, R);
    //std::cout << R << std::endl;
    //std::cout << ang.x << " " << ang.y << " " << ang.z << std::endl;

	dBodySetLinearVel(id, vel.x, vel.y, vel.z);
	dBodySetAngularVel(id, w.x,w.y, w.z);

    return id;
}

int ODEWrapper::addCube(Vector3f pos, float sides, Vector3f vel0, Quaternion<float> ang0, Vector3f ang_vel0, float mass)
{

    return addBox(pos, Vector3f(sides, sides, sides), vel0, ang0, ang_vel0, mass);

}

int ODEWrapper::addBox(Vector3f pos, Vector3f sides, Vector3f vel0, Quaternion<float> ang0, Vector3f ang_vel0, float mass)
{
    dMass m;
	dMassSetBoxTotal(&m, mass, sides.x, sides.y, sides.z);

	dGeomID geom = dCreateBox(pimpl->space, sides.x, sides.y, sides.z);
    dBodyID id   = pimpl->addBody(this, geom, pos, vel0, ang0, ang_vel0);

	dBodySetMass(id, &m);

    dGeomSetBody(geom, id);

    pimpl->bodies.push_back(id);
    return pimpl->bodies.size()-1;

}

int ODEWrapper::addCylinder(Vector3f pos, float rad, float h, Vector3f vel0, Quaternion<float> ang0, Vector3f ang_vel0, float mass)
{
    dMass m;
    dMassSetCylinderTotal(&m, mass, 3, rad, h);
    dGeomID geom = dCreateCylinder(pimpl->space, rad, h);
    dBodyID id = pimpl->addBody(this, geom, pos, vel0, ang0, ang_vel0);
    dBodySetMass(id, &m);
    dGeomSetBody(geom, id);
    pimpl->bodies.push_back(id);
    return pimpl->bodies.size()-1;
}

int ODEWrapper::addSphere(Vector3f pos, float rad, Vector3f vel0, Quaternion<float> ang0, Vector3f ang_vel0, float mass)
{
    dMass m;
    dMassSetSphere(&m, mass, rad);
    dGeomID geom = dCreateSphere(pimpl->space, rad);
    dBodyID id = pimpl->addBody(this, geom, pos, vel0, ang0, ang_vel0);
    dBodySetMass(id, &m);
    dGeomSetBody(geom, id);
    pimpl->bodies.push_back(id);
    return pimpl->bodies.size()-1;
}
int ODEWrapper::addCapsule(Vector3f pos, float rad, float h, Vector3f vel0, Quaternion<float> ang0, Vector3f ang_vel0, float mass)
{
    dMass m;
    dMassSetCapsule(&m, mass, 3, rad, h);
    dGeomID geom = dCreateCapsule(pimpl->space, rad, h);
    dBodyID id = pimpl->addBody(this, geom, pos, vel0, ang0, ang_vel0);
    dBodySetMass(id, &m);
    dGeomSetBody(geom, id);
    pimpl->bodies.push_back(id);
    return pimpl->bodies.size()-1;
}

int ODEWrapper::addPlane(Vector3f a, Vector3f b)
{
    dReal dx = b.x - a.x, dy = b.y - a.y; 
    dReal norm = sqrt(dx*dx + dy*dy);
    dReal d = dy/norm * a.x - dx/norm * a.y;

    // Planes have geometry but no body
    dGeomID geom = dCreatePlane(pimpl->space, -dy/norm, dx/norm, 0, -d);
    return 0;          
}

int addJoint(Vector3f pos, float theta=0, float dTheta=0)
{
    std::cout << "not yet implemented" << std::endl;
    return -1;

}

struct nearCallback_data 
{

    dWorldID world;
    dJointGroupID contactgroup;

};

void nearCallback(void *data, dGeomID o1, dGeomID o2)
{
	int i;
	dBodyID b1 = dGeomGetBody(o1);
	dBodyID b2 = dGeomGetBody(o2);


    //if (dBodyGetWorld(b1) != dBodyGetWorld(b2)) { return; }

    dWorldID world = ((nearCallback_data*)(data))->world;
    dJointGroupID contactgroup = ((nearCallback_data*)(data))->contactgroup;

//    std::cout << dBodyGetWorld(b2) << "   " << world << std::endl;



    int MAX_CONTACTS = 6;
	dContact contact[MAX_CONTACTS];


	for (i = 0; i < MAX_CONTACTS; i++)
	{

		dReal mu = dInfinity;

		contact[i].surface.mode = dContactBounce;
		contact[i].surface.mu = mu;
		contact[i].surface.bounce = 0.0;
		contact[i].surface.bounce_vel = .000001;
//		contact[i].surface.soft_cfm = 0.00; // Was at 0.01, but weird ground penetration issues.
	}
	if (int numc = dCollide(o1, o2, MAX_CONTACTS, &contact[0].geom, sizeof(dContact)))
	{
		for (i = 0; i < numc; i++)
		{
			dJointID c = dJointCreateContact(world, contactgroup, contact + i);
			dJointAttach(c, b1, b2);
		}
	}
}

Vector3f ODEWrapper::getBodyPositionFromID(int id)
{
    const dReal* pos = dBodyGetPosition(pimpl->getBodyIDFromID(id));
    return Vector3f(pos[0], pos[1], pos[2]);
}

// TODO: finish me!
Quaternion<float> ODEWrapper::getBodyRotationFromID(int id)
{
	const dReal* R = dGeomGetRotation(dBodyGetFirstGeom(pimpl->getBodyIDFromID(id)));

    dQuaternion q_ode;
    dGeomGetQuaternion(dBodyGetFirstGeom(pimpl->getBodyIDFromID(id)), q_ode);
    Quaternion<float> q = Quaternion<float>(q_ode[0], q_ode[1], q_ode[2], q_ode[3]);

    return q;
}

void ODEWrapper::step(float timestep) 
{
    nearCallback_data* ncd = new nearCallback_data();
    ncd->world = pimpl->world;
    ncd->contactgroup= pimpl->contactgroup;

    dSpaceCollide(pimpl->space, (void*)(ncd), &(nearCallback));
    dWorldQuickStep(pimpl->world, timestep);
    dJointGroupEmpty(pimpl->contactgroup);
}

/*

int main(int argc, char** argv)
{


    ODEWrapper* phys = new ODEWrapper();
    phys->init();

    int box1 = phys->addCube(Vector3f(0,10,0), 1, Vector3f(0,0,0), 0, 0, 10);
    phys->addCube(Vector3f(0,15,0), 1, Vector3f(0,0,0), 0, 0, 10);


    while (true)
    {
        phys->step(0.0001);
        float pos = phys->getBodyPositionFromID(box1).y;

        std::cout << pos << std::endl;
        if (pos < -5)
            break;
    }



    std::cout << "yay" << std::endl;
}
*/
