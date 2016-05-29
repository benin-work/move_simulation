#include "stdafx.h"
#include "PhysSceneObject.h"

namespace move_simulation {

	PhysSceneObject::PhysSceneObject()
		: m_mass(0)
		, m_vel(0)
		, m_accel(0)
	{
	}

	PhysSceneObject::PhysSceneObject(const Vector pos, const Vector dir)
		: BaseSceneObject(pos, dir)
		, m_mass(0)
		, m_vel(0)
		, m_accel(0)
	{
	}

	PhysSceneObject::~PhysSceneObject()
	{
	}

	double PhysSceneObject::mass() const
	{
		return m_mass;
	}

	void PhysSceneObject::set_mass(const double new_mass)
	{
		m_mass = new_mass;
	}

	const Vector& PhysSceneObject::vel() const
	{
		return m_vel;
	}

	void PhysSceneObject::set_vel(const Vector& new_vel)
	{
		m_vel = new_vel;
	}

	const Vector& PhysSceneObject::accel() const
	{
		return m_accel;
	}

	void PhysSceneObject::set_accel(const Vector& new_accel)
	{
		m_accel = new_accel;
	}

} // namespace move_simulation