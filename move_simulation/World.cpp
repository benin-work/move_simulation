#include "stdafx.h"
#include "../include/ISimulator.h"
#include "../include/PhysObject.h"
#include "World.h"
#include "Scene.h"
#include "GraphSceneObject.h"

namespace move_simulation {

	using namespace simulation;

	World::World()
		: m_simulator(nullptr)
		, m_prev_time(std::chrono::high_resolution_clock::now())
		, m_run_update(false)
		, m_update_thread()
	{
	}

	World::~World()
	{
		stop();
		if (m_update_thread.joinable())
			m_update_thread.join();
	}

	void World::init(std::shared_ptr<simulation::ISimulator> simulator)
	{
		m_simulator = simulator;
	}

	void World::update_loop()
	{
		using namespace std::chrono;
		while (m_run_update)
		{
			auto now_time = high_resolution_clock::now();
			const double dt = duration_cast<duration<double>>(now_time - m_prev_time).count();
			m_prev_time = now_time;

			for (const auto& scene : m_scenes)
			{
				// Collect objects for simulation
				auto && physobj_list = ISimulator::ObjectsList(scene->objects().begin(), scene->objects().end());
				
				m_simulator->simulate(physobj_list, dt);
			}
		}
	}

	void World::run()
	{
		if (m_simulator == nullptr)
		{
			logger() << Logger::Error << "Cant run world simulation, simulator is apsent!" << std::endl;
			return;
		}

		if (m_update_thread.joinable())
		{
			stop();
			m_update_thread.join();
		}

		logger() << Logger::Info << "Start world simulation" << std::endl;
		m_run_update = true;
		m_update_thread = std::thread(&World::update_loop, this);
	}

	void World::stop()
	{
		logger() << Logger::Info << "Stop world simulation" << std::endl;
		m_run_update = false;
	}

	void World::add_scene(const std::shared_ptr<Scene> scene)
	{
		m_scenes.push_back(scene);
	}

	
} // namespace move_simulation