#include "stdafx.h"
#include "PhysSimulator.h"
#include "Scene.h"
#include "PhysSceneObject.h"

namespace move_simulation {

	PhysSimulator::PhysSimulator()
	{
	}

	PhysSimulator::~PhysSimulator()
	{
	}

	void PhysSimulator::simulate(const std::shared_ptr<Scene> scene, const double dt)
	{
		for each (const auto& obj in scene->objects())
		{
			obj->set_accel(Vector(obj->accel().x(), -981));

			obj->set_vel(obj->vel() + obj->accel() * dt);
			obj->set_pos(obj->pos() + obj->vel() * dt);
		}
	}

} // namespace move_simulation