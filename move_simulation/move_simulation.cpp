// move_simulation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Logger.h"

#include "Scene.h"
#include "SceneWindow.h"
#include "World.h"
#include "graph_objects.h"

using namespace move_simulation;


int main()
{
	// Initialize logging
	logger().init(Logger::Info, &std::cout);

	logger() << Logger::Info << "Create Scene" << std::endl;
	auto main_scene = std::make_shared<Scene>();
	
	logger() << Logger::Info << "Create World" << std::endl;
	auto world = std::make_shared<World>();
	world->init();
	world->add_scene(main_scene);

	main_scene->add_object(std::make_shared<BallSceneObject>(Vector(100.0, 100.0)));
	
	auto test_ball = std::make_shared<BallSceneObject>(Vector(150.0, 200.0));
	test_ball->set_vel(Vector(500, -500));
	main_scene->add_object(test_ball);
	
	main_scene->add_object(std::make_shared<BallSceneObject>(Vector(300.0, 400.0)));

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