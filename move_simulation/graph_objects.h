#pragma once
#include "GraphSceneObject.h"

namespace move_simulation {

	class BallSceneObject: public GraphSceneObject
	{
	public:
		BallSceneObject(const Vector& pos = Vector(0));
		void draw(HDC hdc) const override;
	};

} //  namespace move_simulation