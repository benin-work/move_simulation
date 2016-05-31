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

	void Scene::set_bounds(Vector top_left, Vector bottom_down)
	{
		logger() << Logger::Info << "Set scene bounds [" << top_left << " : " << bottom_down << "]" << std::endl;
		m_bound_top_left = top_left;															  
		m_bound_bottom_right = bottom_down;
	}

	void Scene::update(const double dt)
	{
		if (m_bound_top_left != m_bound_bottom_right)
		{
			// Simple test for bounds
			for (auto it = m_objects.begin(); it != m_objects.end();)
			{
				const auto& obj = *it;
				if (obj->pos().x() < m_bound_top_left.x() || obj->pos().x() > m_bound_bottom_right.x() || 
					obj->pos().y() < m_bound_top_left.y() || obj->pos().y() > m_bound_bottom_right.y())
				{
					it = m_objects.erase(it);
				}
				else
				{
					++it;
				}
			}
		}
	}

	void Scene::draw(HDC hdc)
	{
		// Draw objects
		for (const auto& obj : m_objects)
		{
			obj->draw(hdc);
		}

		draw_sysinfo(hdc);
	}

	void Scene::add_object(const SceneObjectPtr new_object)
	{
		logger() << Logger::Info << "Add object to scene (" << new_object->pos() << ")" << std::endl;
		m_objects.push_back(new_object);
	}

	void Scene::remove_object(const SceneObjectPtr object)
	{

	}

	Scene::ObjectsList& Scene::objects()
	{
		return m_objects;
	}

	void Scene::draw_sysinfo(HDC hdc)
	{		 
	}
} //namespace move_simulation