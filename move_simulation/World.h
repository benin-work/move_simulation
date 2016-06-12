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

		void run();
		void stop();

	private:
		void update_loop();

	private:
		SceneList m_scenes;
		std::shared_ptr<simulation::ISimulator> m_simulator;

		simulation::TimePoint m_prev_time;

		std::thread m_update_thread;
		std::atomic<bool> m_run_update;
	};

} // namespace move_simulation