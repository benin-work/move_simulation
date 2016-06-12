#include "stdafx.h"
#include "Scene.h"
#include "graph_objects.h"

namespace move_simulation {

	using namespace simulation;

	Scene::Scene()
	{
	}

	Scene::~Scene()
	{
	}

	void Scene::set_bounds(Vector top_left, Vector bottom_down)
	{
		logger() << Logger::Info << "Set scene bounds [" << top_left << " : " << bottom_down << "]" << std::endl;
		m_bound_top_left = top_left;															  
		m_bound_bottom_right = bottom_down;
	}

	void Scene::draw(HDC hdc)
	{
		// Draw objects
		for (const auto& obj : m_objects)
		{
			obj->draw(hdc);
		}
	}

	void Scene::add_object(const SceneObjectPtr new_object)
	{
		logger() << Logger::Info << "Add object to scene (" << new_object->pos() << ")" << std::endl;
		m_objects.push_back(new_object);
	}

	void Scene::remove_object(const SceneObjectPtr object)
	{
		m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), object));
	}

	Scene::ObjectsList& Scene::objects()
	{
		return m_objects;
	}

} //namespace move_simulation