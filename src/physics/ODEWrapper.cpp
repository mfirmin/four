
//#include "ODEConstants.h"

#define dSINGLE

#include <stdlib.h>
#include <iostream>
#include <ode/ode.h>
#include <cmath>

#include <vector>
#include <string>
#include <map>

#include "physics/ODEWrapper.h"
#include "vmath.h"

struct ODEWrapper::impl
{
    dWorldID world;
    dSpaceID space;
    dJointGroupID contactgroup;
    dJointGroupID jointgroup;

    std::map<std::string, dBodyID> bodies;
//    std::vector<dBodyID> bodies;
//    std::vector<dJointID> joints;
    std::map<std::string, dJointID> joints;

    dBodyID addBody(ODEWrapper*, dGeomID&, Vector3f, Vector3f, Quaternion<float>, Vector3f);

    dBodyID getBodyIDFromName(std::string name) { return bodies.find(name)->second; }

    static void nearCallback(void*, dGeomID, dGeomID);
};

bool ODEWrapper::INITIALIZED = false;

ODEWrapper::ODEWrapper() 
{
    if (!INITIALIZED) 
    {
        dInitODE();
        INITIALIZED = true;
    }
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

    
    dQuaternion q; 
    q[0] = ang.v.x;
    q[1] = ang.v.y;
    q[2] = ang.v.z;
    q[3] = ang.w;
    dBodySetQuaternion(id, q);
    //std::cout << R << std::endl;
    //std::cout << ang.x << " " << ang.y << " " << ang.z << std::endl;

	dBodySetLinearVel(id, vel.x, vel.y, vel.z);
	dBodySetAngularVel(id, w.x,w.y, w.z);

    return id;
}

int ODEWrapper::addCube(std::string name, float mass, Vector3f pos, float sides, Vector3f vel0, Quaternion<float> ang0, Vector3f ang_vel0)
{

    return addBox(name, mass, pos, Vector3f(sides, sides, sides), vel0, ang0, ang_vel0);

}

int ODEWrapper::addBox(std::string name, float mass, Vector3f pos, Vector3f sides, Vector3f vel0, Quaternion<float> ang0, Vector3f ang_vel0)
{
    dMass m;
	dMassSetBoxTotal(&m, mass, sides.x, sides.y, sides.z);

	dGeomID geom = dCreateBox(pimpl->space, sides.x, sides.y, sides.z);
    dBodyID id   = pimpl->addBody(this, geom, pos, vel0, ang0, ang_vel0);

	dBodySetMass(id, &m);

    dGeomSetBody(geom, id);

    pimpl->bodies.insert(std::pair<std::string, dBodyID>(name, id));
    return pimpl->bodies.size()-1;

}

int ODEWrapper::addCylinder(std::string name, float mass, Vector3f pos, float rad, float h, Vector3f vel0, Quaternion<float> ang0, Vector3f ang_vel0)
{
    dMass m;
    dMassSetCylinderTotal(&m, mass, 3, rad, h);
    dGeomID geom = dCreateCylinder(pimpl->space, rad, h);
    dBodyID id = pimpl->addBody(this, geom, pos, vel0, ang0, ang_vel0);
    dBodySetMass(id, &m);
    dGeomSetBody(geom, id);
    pimpl->bodies.insert(std::pair<std::string, dBodyID>(name, id));
    return pimpl->bodies.size()-1;
}

int ODEWrapper::addSphere(std::string name, float mass, Vector3f pos, float rad, Vector3f vel0, Quaternion<float> ang0, Vector3f ang_vel0)
{
    dMass m;
    dMassSetSphere(&m, mass, rad);
    dGeomID geom = dCreateSphere(pimpl->space, rad);
    dBodyID id = pimpl->addBody(this, geom, pos, vel0, ang0, ang_vel0);
    dBodySetMass(id, &m);
    dGeomSetBody(geom, id);
    pimpl->bodies.insert(std::pair<std::string, dBodyID>(name, id));
    return pimpl->bodies.size()-1;
}
int ODEWrapper::addCapsule(std::string name, float mass, Vector3f pos, float rad, float h, Vector3f vel0, Quaternion<float> ang0, Vector3f ang_vel0)
{
    dMass m;
    dMassSetCapsule(&m, mass, 3, rad, h);
    dGeomID geom = dCreateCapsule(pimpl->space, rad, h);
    dBodyID id = pimpl->addBody(this, geom, pos, vel0, ang0, ang_vel0);
    dBodySetMass(id, &m);
    dGeomSetBody(geom, id);
    pimpl->bodies.insert(std::pair<std::string, dBodyID>(name, id));
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

int ODEWrapper::addHingeJoint(std::string name, std::string parent, std::string child, Vector3f pos, Vector3f axis, float ang_min, float ang_max)
{
    dBodyID pBID = pimpl->getBodyIDFromName(parent);
    dBodyID cBID = pimpl->getBodyIDFromName(child);

    dJointID jID = dJointCreateHinge(pimpl->world, pimpl->jointgroup);
    dJointAttach(jID, pBID, cBID);
    dJointSetHingeAnchor(jID, pos.x, pos.y, pos.z);

    dJointSetHingeAxis(jID, axis.x, axis.y, axis.z);
    dJointSetHingeParam(jID, dParamLoStop, ang_min);
    dJointSetHingeParam(jID, dParamHiStop, ang_max);

    pimpl->joints.insert(std::pair<std::string, dJointID>(name, jID));
    return pimpl->joints.size()-1;;
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

    if (dAreConnected(b1, b2)) {
            return;
    }


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

Vector3f ODEWrapper::getBodyPositionFromName(std::string name)
{
    const dReal* pos = dBodyGetPosition(pimpl->getBodyIDFromName(name));
    return Vector3f(pos[0], pos[1], pos[2]);
}

Quaternion<float> ODEWrapper::getBodyRotationFromName(std::string name)
{
	const dReal* R = dGeomGetRotation(dBodyGetFirstGeom(pimpl->getBodyIDFromName(name)));

    dQuaternion q_ode;
    dGeomGetQuaternion(dBodyGetFirstGeom(pimpl->getBodyIDFromName(name)), q_ode);
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
void ODEWrapper::setHingeJointTorque(std::string jointName, float torque) 
{

    dJointID jID = pimpl->joints.find(jointName)->second;
    dJointAddHingeTorque(jID, torque);

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
