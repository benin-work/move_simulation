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
	{
	}

	World::~World()
	{
	}

	void World::init(std::shared_ptr<simulation::ISimulator> simulator)
	{
		m_simulator = simulator;
	}

	void World::update()
	{
		if (m_simulator == nullptr)
			return;	

		using namespace std::chrono;
		auto now_time = high_resolution_clock::now();
		const double dt = duration_cast<duration<double>>(now_time - m_prev_time).count();
		m_prev_time = now_time;

		for(const auto& scene: m_scenes)
		{	
			scene->update(dt);
			auto && physobj_list = ISimulator::ObjectsList(scene->objects().begin(), scene->objects().end());
			m_simulator->simulate(physobj_list, dt);
		}
	}

	void World::add_scene(const std::shared_ptr<Scene> scene)
	{
		m_scenes.push_back(scene);
	}

	
} // namespace move_simulation