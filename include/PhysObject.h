#pragma once
#include "types.h"

namespace simulation {

	class PhysObject
	{
	public:
		PhysObject()
			: m_pos(0)
			, m_angle(0)
			, m_mass(1)
			, m_vel(0)
			, m_accel(0)
		{}

		PhysObject(const Vector& pos) 
			: m_pos(pos)
			, m_angle(0)
			, m_mass(1)
			, m_vel(0)
			, m_accel(0)
		{}

		virtual ~PhysObject() {};

		const Vector& pos() const
		{
			return m_pos;
		}

		void set_pos(const Vector& new_pos)
		{
			m_pos = new_pos;
		}

		double mass() const
		{
			return m_mass;
		}

		void set_mass(const double new_mass)
		{
			m_mass = new_mass;
		}

		const Vector& vel() const
		{
			return m_vel;
		}

		void set_vel(const Vector& new_vel)
		{
			m_vel = new_vel;
		}

		const Vector& accel() const
		{
			return m_accel;
		}

		void set_accel(const Vector& new_accel)
		{
			m_accel = new_accel;
		}

	private:
		Vector m_pos;
		double m_angle;
		double m_mass;
		Vector m_vel;
		Vector m_accel;
	};

} // namespace simulation