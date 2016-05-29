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
			obj->set_accel(Vector(obj->accel().x, 1000));

			Vector new_vel(
				obj->vel().x + obj->accel().x * dt,
				obj->vel().y + obj->accel().y * dt);
			obj->set_vel(new_vel);

			Vector new_pos(
				obj->pos().x + obj->vel().x * dt,
				obj->pos().y + obj->vel().y * dt);
			obj->set_pos(new_pos);
		}
	}

} // namespace move_simulation