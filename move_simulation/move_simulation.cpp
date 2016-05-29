// move_simulation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Logger.h"

#include "Scene.h"
#include "SceneWindow.h"

using namespace move_simulation;

int main()
{
	// Initialize logging
	logger().init(Logger::Info, &std::cout);

	// Create main scene
	Scene main_scene;
	
	logger() << Logger::Info << "Create Scene window" << std::endl;
	SceneWindow scene_window;
	scene_window.create();
	scene_window.set_scene(&main_scene);
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
			scene_window.draw();
		}
	}

	return static_cast<int>(msg.wParam);
}