#include "stdafx.h"
#include "Scene.h"
#include "PhysSceneObject.h"

namespace move_simulation {

	Scene::Scene()
	{
	}

	Scene::~Scene()
	{
	}

	void Scene::draw(HDC hdc)
	{
		// Get window rect
		BITMAP bitmap_header;
		memset(&bitmap_header, 0, sizeof(BITMAP));
		HGDIOBJ bitmap_obj = GetCurrentObject(hdc, OBJ_BITMAP);
		GetObject(bitmap_obj, sizeof(BITMAP), &bitmap_header);
		RECT win_rect{0, 0, bitmap_header.bmWidth, bitmap_header.bmHeight};
		
		// Clear background of scene
		FillRect(hdc, &win_rect, (HBRUSH)GetStockObject(WHITE_BRUSH));

		// Draw objects
		for each (const auto& obj in m_objects)
		{
			obj->draw(hdc);
		}
	}

	void Scene::add_object(const SceneObjectPtr new_object)
	{
		m_objects.push_back(new_object);
	}

	Scene::ObjectsList& Scene::objects()
	{
		return m_objects;
	}

} //namespace move_simulation