#pragma once

namespace move_simulation {

	class BaseSceneObject
	{
	public:
		BaseSceneObject();
		explicit BaseSceneObject(const Vector pos, const Vector dir);
		virtual ~BaseSceneObject();

		virtual void draw(HDC hdc) const = 0;

		const Vector& pos() const;
		void set_pos(const Vector new_pos);

		const Vector& dir() const;
		void set_dir(const Vector new_dir);

	private:
		Vector m_pos;
		Vector m_dir;
	};

} // namespace move_simulation