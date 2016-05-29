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

		void draw(HDC hdc);

		void add_object(const SceneObjectPtr new_object);

		ObjectsList& objects();

	private:
		ObjectsList m_objects;

	};

} //namespace move_simulation
