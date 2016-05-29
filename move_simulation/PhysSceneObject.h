#pragma once
#include "BaseSceneObject.h"

namespace move_simulation {

	class PhysSceneObject : public BaseSceneObject
	{
	public:
		PhysSceneObject();
		explicit PhysSceneObject(const Vector pos, const Vector dir);
		virtual ~PhysSceneObject();

		double mass() const;
		void set_mass(const double new_mass);

		const Vector& vel() const;
		void set_vel(const Vector& new_vel);

		const Vector& accel() const;
		void set_accel(const Vector& new_accel);

	private:
		double m_mass;
		Vector m_vel;
		Vector m_accel;
	};

} // namespace move_simulation