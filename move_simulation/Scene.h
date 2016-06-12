#pragma once

namespace move_simulation {

	using namespace simulation;

	class GraphSceneObject;

	class Scene
	{
	public:
		typedef GraphSceneObject SceneObject;
		typedef std::shared_ptr<GraphSceneObject> SceneObjectPtr;
		typedef std::vector<SceneObjectPtr> ObjectsList;

	public:
		Scene();
		~Scene();

		// Set the bounds of the scene.
		// Object will be removed if it left bounds
		void set_bounds(Vector top_left, Vector bottom_down);

		void draw(HDC hdc);

		void add_object(const SceneObjectPtr new_object);
		void remove_object(const SceneObjectPtr object);

		ObjectsList& objects();

	private:
		ObjectsList m_objects;
		Vector m_bound_top_left;
		Vector m_bound_bottom_right;
	};

} //namespace move_simulation
