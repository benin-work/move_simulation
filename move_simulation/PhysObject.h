#pragma once

namespace move_simulation {

	class PhysObject
	{
	public:
		PhysObject();
		PhysObject(const Vector& pos);
		virtual ~PhysObject();

		const Vector& pos() const;
		void set_pos(const Vector& new_pos);

		double mass() const;
		void set_mass(const double new_mass);

		const Vector& vel() const;
		void set_vel(const Vector& new_vel);

		const Vector& accel() const;
		void set_accel(const Vector& new_accel);

	private:
		Vector m_pos;
		double m_angle;
		double m_mass;
		Vector m_vel;
		Vector m_accel;
	};

} // namespace move_simulation