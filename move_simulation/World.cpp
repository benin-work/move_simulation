#include "stdafx.h"
#include "World.h"
#include "Scene.h"
#include "../phys_simulator_lib/ISimulator.h"
#include "PhysObject.h"
#include "GraphSceneObject.h"

namespace move_simulation {

	namespace
	{
		// A factory of IKlass-implementing objects looks thus
		typedef ISimulator* (__cdecl *isimulator_create)();
	}

	World::World()
		: m_simulator(nullptr)
		, m_prev_time(std::chrono::high_resolution_clock::now())
	{
	}

	World::~World()
	{
		if (m_simulator)
			m_simulator->destroy();
	}

	void World::init()
	{
		const TCHAR* library_name =
#ifdef _DEBUG
			TEXT("phys_simulator_lib_d.dll");
#else
			TEXT("phys_simulator_lib.dll");
#endif
		HINSTANCE dll_handle = ::LoadLibrary(library_name);
		if (!dll_handle) {
			logger() << Logger::Error << "Unable to load Simulation DLL!" << std::endl;
			return;
		}

		// Get the function from the DLL
		isimulator_create factory_func = reinterpret_cast<isimulator_create>(
			::GetProcAddress(dll_handle, "create_simulator"));
		if (!factory_func) 
		{
			logger() << Logger::Error << "Unable to load create_simulator from DLL!" << std::endl;
			::FreeLibrary(dll_handle);
			return;
		}

		// Load simulation
		m_simulator = factory_func();
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