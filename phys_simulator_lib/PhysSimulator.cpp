#include "stdafx.h"
#include "PhysSimulator.h"
#include "../include/PhysObject.h"


namespace phys_simulator_lib {

	const double g_accel = -981;

	PhysSimulator::PhysSimulator()
	{
	}

	PhysSimulator::~PhysSimulator()
	{
	}

	void PhysSimulator::destroy()
	{
		delete this;
	}

	void PhysSimulator::simulate(const ObjectsList& objects, const double dt)
	{
		for each (const auto& obj in objects)
		{
			obj->set_accel(simulation::Vector(obj->accel().x(), g_accel));

			obj->set_vel(obj->vel() + obj->accel() * dt);
			obj->set_pos(obj->pos() + obj->vel() * dt);
		}
	}

	simulation::ISimulator* create()
	{
		return new PhysSimulator();
	}
} // namespace phys_simulator_lib