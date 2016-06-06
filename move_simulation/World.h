#pragma once

namespace simulation
{
	class ISimulator;
}

namespace move_simulation {

	class Scene;	
	
	class World
	{
	public:
		typedef std::vector<std::shared_ptr<Scene>> SceneList;

	public:
		World();
		~World();

		void add_scene(const std::shared_ptr<Scene> scene);
		void init(std::shared_ptr<simulation::ISimulator> simulator);
		
		void update();

	private:
		SceneList m_scenes;
		std::shared_ptr<simulation::ISimulator> m_simulator;

		simulation::TimePoint m_prev_time;
	};

} // namespace move_simulation