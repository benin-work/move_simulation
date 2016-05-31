#pragma once
#include "PhysObject.h"

namespace move_simulation {

	class GraphSceneObject : public PhysObject
	{
	public:
		GraphSceneObject() :PhysObject() 
		{}
		
		explicit GraphSceneObject(const Vector& pos)
			: PhysObject(pos)
		{}

		virtual void draw(HDC hdc) const = 0;
	};

} //  namespace move_simulation