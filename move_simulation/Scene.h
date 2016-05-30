#pragma once

namespace move_simulation {

	class PhysSceneObject;

	class Scene
	{
	public:
		typedef std::shared_ptr<PhysSceneObject> SceneObjectPtr;
		typedef std::vector<SceneObjectPtr> ObjectsList;

	public:
		Scene();
		~Scene();

		// Set the bounds of the scene.
		// Object will be removed if it left bounds
		void set_bounds(Vector top_left, Vector bottom_down);

		void update(const double dt);
		void draw(HDC hdc);

		void add_object(const SceneObjectPtr new_object);
		void remove_object(const SceneObjectPtr object);

		ObjectsList& objects();

	private:
		void draw_sysinfo(HDC hdc);

	private:
		ObjectsList m_objects;
		Vector m_bound_top_left;
		Vector m_bound_bottom_right;
	};

} //namespace move_simulation
