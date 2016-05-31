// move_simulation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Scene.h"
#include "SceneWindow.h"
#include "World.h"
#include "graph_objects.h"

using namespace move_simulation;

cmdline::parser g_cmd_parser;

void init_cmd_params(int argc, char *argv[]);
void init_logger();

std::shared_ptr<World> create_world();
std::shared_ptr<Scene> create_scene();

int main(int argc, char *argv[])
{
	// Parse command line arguments
	init_cmd_params(argc, argv);

	// Initialize logging
	init_logger();

	// Initialize World with scene system
	auto main_scene = create_scene();
	auto world = create_world();
	world->add_scene(main_scene);	

	logger() << Logger::Info << "Create Scene window" << std::endl;
	SceneWindow scene_window;
	scene_window.create();
	scene_window.set_scene(main_scene);
	scene_window.show();

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
			world->update();
			scene_window.draw();
		}
	}

	return static_cast<int>(msg.wParam);
}

void init_cmd_params(int argc, char *argv[])
{
	std::string default_log_name(argv[0]);
	default_log_name.replace(default_log_name.size() - 4, 4, ".log");
	g_cmd_parser.add<std::string>("log", 'l', "logging to file with filename", false, default_log_name);

	g_cmd_parser.parse_check(argc, argv);
}

void init_logger()
{
	std::ostream* log_stream = &std::cout;
	bool log_owner = false;
	if (g_cmd_parser.exist("log"))
	{
		const std::string fname = g_cmd_parser.get<std::string>("log");
		log_stream = new std::ofstream(fname);
		log_owner = true;
	}
	logger().init(Logger::Info, log_stream, log_owner);
}

std::shared_ptr<World> create_world()
{
	logger() << Logger::Info << "Create World" << std::endl;
	auto world = std::make_shared<World>();
	world->init();
	
	return world;
}

std::shared_ptr<Scene> create_scene()
{
	logger() << Logger::Info << "Create Scene" << std::endl;
	auto scene = std::make_shared<Scene>();
	
	scene->set_bounds(Vector(-1000, -1000), Vector(1000, 1000));

	// Adding test objects;
	scene->add_object(std::make_shared<BallSceneObject>(Vector(100.0, 100.0)));
	scene->add_object(std::make_shared<BallSceneObject>(Vector(300.0, 400.0)));

	auto test_ball = std::make_shared<BallSceneObject>(Vector(150.0, 200.0));
	test_ball->set_vel(Vector(50, 50));
	scene->add_object(test_ball);

	return scene;
}
