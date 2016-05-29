#include "stdafx.h"
#include "BaseSceneObject.h"

namespace move_simulation {

	BaseSceneObject::BaseSceneObject()
	{
	}

	BaseSceneObject::BaseSceneObject(const Vector pos, const Vector dir)
		: m_pos(pos)
		, m_dir(dir)
	{
	}

	
	BaseSceneObject::~BaseSceneObject()
	{
	}

	const Vector& BaseSceneObject::pos() const
	{
		return m_pos;
	}

	void BaseSceneObject::set_pos(const Vector new_pos)
	{
		m_pos = new_pos;
	}

	const Vector& BaseSceneObject::dir() const
	{
		return m_dir;
	}

	void BaseSceneObject::set_dir(const Vector new_dir)
	{
		m_dir = new_dir;
	}

} // namespace move_simulation