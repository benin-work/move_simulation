#include "stdafx.h"
#include "World.h"
#include "Scene.h"
#include "ISimulator.h"
#include "PhysSimulator.h"

namespace move_simulation {

	World::World()
		: m_simulator(nullptr)
		, m_prev_time(std::chrono::high_resolution_clock::now())
	{
	}

	World::~World()
	{
		if (m_simulator)
			delete m_simulator;
	}

	void World::init()
	{
		// Load simulation
		m_simulator = new PhysSimulator();
	}

	void World::update()
	{
		if (m_simulator == nullptr)
			return;	

		using namespace std::chrono;
		auto now_time = high_resolution_clock::now();
		const double dt = duration_cast<duration<double>>(now_time - m_prev_time).count();
		m_prev_time = now_time;

		for each (const auto& scene in m_scenes)
		{	
			m_simulator->simulate(scene, dt);
		}
	}

	void World::add_scene(const std::shared_ptr<Scene> scene)
	{
		m_scenes.push_back(scene);
	}
	
} // namespace move_simulation