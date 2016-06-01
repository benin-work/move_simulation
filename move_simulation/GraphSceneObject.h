#pragma once
#include "../include/PhysObject.h"

namespace move_simulation {

	class GraphSceneObject : public simulation::PhysObject
	{
	public:
		virtual ~GraphSceneObject()
		{}

		GraphSceneObject() 
			:PhysObject(), m_color(RGB(0,0,0)) {}
		
		explicit GraphSceneObject(const simulation::Vector& pos)
			: PhysObject(pos), m_color(RGB(0, 0, 0)) {}

		COLORREF color() const
		{
			return m_color;
		}

		virtual void draw(HDC hdc) const = 0;
	protected:
		COLORREF m_color;
	};

} //  namespace move_simulation