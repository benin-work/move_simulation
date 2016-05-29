#pragma once
#include "PhysSceneObject.h"

namespace move_simulation {

	class BallSceneObject: public PhysSceneObject
	{
	public:
		BallSceneObject();
		explicit BallSceneObject(const Vector pos, const Vector dir = Vector(1.));
		virtual ~BallSceneObject();

		void draw(HDC hdc) const override;
	};

} // 