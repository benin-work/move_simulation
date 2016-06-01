#pragma once
#include "GraphSceneObject.h"

namespace move_simulation {

	class BallSceneObject: public GraphSceneObject
	{
	public:
		BallSceneObject(const simulation::Vector& pos = simulation::Vector(0));
		void draw(HDC hdc) const override;
	};
	
	class BoxSceneObject: public GraphSceneObject
	{
	public:
		BoxSceneObject(const simulation::Vector& pos = simulation::Vector(0));
		void draw(HDC hdc) const override;
	};

} //  namespace move_simulation