#include "stdafx.h"
#include "PhysObject.h"

namespace move_simulation {

	PhysObject::PhysObject()
		: m_pos(0)
		, m_angle(0)
		, m_mass(0)
		, m_vel(0)
		, m_accel(0)
	{
	}

	PhysObject::PhysObject(const Vector& pos)
		: m_pos(pos)
		, m_angle(0)
		, m_mass(0)
		, m_vel(0)
		, m_accel(0)
	{
	}

	PhysObject::~PhysObject()
	{
	}

	const Vector& PhysObject::pos() const
	{
		return m_pos;
	}

	void PhysObject::set_pos(const Vector& new_pos)
	{
		m_pos = new_pos;
	}

	double PhysObject::mass() const
	{
		return m_mass;
	}

	void PhysObject::set_mass(const double new_mass)
	{
		m_mass = new_mass;
	}

	const Vector& PhysObject::vel() const
	{
		return m_vel;
	}

	void PhysObject::set_vel(const Vector& new_vel)
	{
		m_vel = new_vel;
	}

	const Vector& PhysObject::accel() const
	{
		return m_accel;
	}

	void PhysObject::set_accel(const Vector& new_accel)
	{
		m_accel = new_accel;
	}

} // namespace move_simulation