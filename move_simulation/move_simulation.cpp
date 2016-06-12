// move_simulation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Scene.h"
#include "SceneWindow.h"
#include "World.h"
#include "graph_objects.h"
#include "../include/ISimulator.h"

using namespace move_simulation;

cmdline::parser g_cmd_parser;
const TCHAR* g_library_name =
#ifdef _DEBUG
	TEXT("phys_simulator_lib_d.dll");
#else
	TEXT("phys_simulator_lib.dll");
#endif

void init_cmd_params(int argc, char *argv[]);
void init_logger();

std::unique_ptr<World> create_world();
std::shared_ptr<Scene> create_scene();

int main(int argc, char *argv[])
{
	// Parse command line arguments
	init_cmd_params(argc, argv);

	// Initialize logging
	init_logger();

	// Initialize World with scene system
	auto main_scene = create_scene();
	auto && world = create_world();
	world->add_scene(main_scene);	

	logger() << Logger::Info << "Create Scene window" << std::endl;
	SceneWindow scene_window;
	scene_window.create();
	scene_window.set_scene(main_scene);
	scene_window.show();

	world->run();

	logger() << Logger::Info << "Enter message loop" << std::endl;
	MSG msg;
	while (1) 
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) 
		{
			if (msg.message == WM_QUIT)
				break;						
			
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			scene_window.draw();
		}
	}

	world->stop();

	return static_cast<int>(msg.wParam);
}

void init_cmd_params(int argc, char *argv[])
{
	std::string default_log_name(argv[0]);
	default_log_name.replace(default_log_name.size() - 4, 4, ".log");
	g_cmd_parser.add<std::string>("log", 'l', "logging to file with filename", false, default_log_name);
	g_cmd_parser.add<int>("bound", 'b', "set scene bound as box([-bound, -bound];[bound, bound])", false, 1000);
	g_cmd_parser.add<size_t>("rand", 'r', "add random objects on start", false);
	
	g_cmd_parser.add("add", 'a', "add objects on scene(use with params -x -y )");
	g_cmd_parser.add<int>("posx", 'x', "object position x", false, 0);
	g_cmd_parser.add<int>("posy", 'y', "object position y", false, 0);
	g_cmd_parser.add<int>("vx", '\0', "object speed vector x", false, 0);
	g_cmd_parser.add<int>("vy", '\0', "object speed vector y", false, 0);
	g_cmd_parser.add<std::string>("type", 't', "object type (ball, box)", false, "ball", cmdline::oneof<std::string>("ball", "box"));
	g_cmd_parser.add<int>("mass", 'm', "object mass", false, 1, cmdline::range(1, 100));

	g_cmd_parser.parse_check(argc, argv);
}

void init_logger()
{
	std::ostream* log_stream = &std::cout;
	bool log_owner = false;
	if (g_cmd_parser.exist("log"))
	{
		const std::string fname = g_cmd_parser.get<std::string>("log");
		std::ostream* new_fstream = new std::ofstream(fname);
		if (new_fstream->fail())
		{
			Logger() << Logger::Error << "Cant create log file " << fname << std::endl;
		}else
		{
			log_stream = new_fstream;
			log_owner = true;
		}
	}
	logger().init(Logger::Info, log_stream, log_owner);
}

std::unique_ptr<World> create_world()
{
	logger() << Logger::Info << "Create World" << std::endl;
	auto world = std::make_unique<World>();

	logger() << Logger::Info << "Loading Simulation DLL" << std::endl;
	

	// Loading simulation library
	HMODULE simulation_lib  = LoadLibrary(g_library_name);
	if (!simulation_lib) {
		logger() << Logger::Error << "Unable to load Simulation DLL!" << std::endl;
		return world;
	}

	FARPROC proc_addr = GetProcAddress(simulation_lib, "create");
	if (!proc_addr)
	{
		logger() << Logger::Error << "Unable to find simulation factory method!" << std::endl;
		return world;
	}
	
	auto factory_func = reinterpret_cast<decltype(&simulation::create)>(proc_addr);
	if (!factory_func)
	{
		logger() << Logger::Error << "Factory method doesnt correspond DLL API!" << std::endl;
		::FreeLibrary(simulation_lib);
		return world;
	}

	std::shared_ptr<ISimulator> simulator(factory_func(), std::mem_fn(&ISimulator::destroy));

	world->init(simulator);

	return world;
}

std::shared_ptr<Scene> create_scene()
{
	logger() << Logger::Info << "Create Scene" << std::endl;
	auto scene = std::make_shared<Scene>();
	
	const int bound = g_cmd_parser.get<int>("bound");
	scene->set_bounds(Vector(-bound, -bound), Vector(bound, bound));

	if (g_cmd_parser.exist("add"))
	{
		const Vector pos(g_cmd_parser.get<int>("posx"), g_cmd_parser.get<int>("posy"));
		std::shared_ptr<GraphSceneObject> object;
		if (g_cmd_parser.get<std::string>("type") == std::string("ball"))
			object = std::make_shared<BallSceneObject>(pos);
		else
			object = std::make_shared<BoxSceneObject>(pos);
		object->set_mass(g_cmd_parser.get<int>("mass"));
		object->set_vel(Vector(g_cmd_parser.get<int>("vx"), g_cmd_parser.get<int>("vy")));
		scene->add_object(object);
	}

	if (g_cmd_parser.exist("rand"))
	{
		// Adding test random objects;
		const size_t obj_count = g_cmd_parser.get<size_t>("rand");
		std::random_device rd;
		std::mt19937 eng(rd());
		std::uniform_int_distribution<> distr(0, bound);

		for (size_t i = 0; i < obj_count; ++i)
		{
			auto rand_mass = distr(eng);
			Vector pos(distr(eng), distr(eng));
			std::shared_ptr<GraphSceneObject> object;
			if (rand_mass % 2)
				object = std::make_shared<BallSceneObject>(pos);
			else
				object = std::make_shared<BoxSceneObject>(pos);

			object->set_vel(Vector(distr(eng) - bound / 2, distr(eng)));
			object->set_mass(1. + 2. * rand_mass / bound);
			scene->add_object(object);
		}
	}

	return scene;
}
