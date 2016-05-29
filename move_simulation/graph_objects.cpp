#include "stdafx.h"
#include "graph_objects.h"

namespace move_simulation {

	BallSceneObject::BallSceneObject()
	{
	}

	BallSceneObject::BallSceneObject(const Vector pos, const Vector dir /*= Vector(1.)*/)
		: PhysSceneObject(pos, dir)
	{
	}

	BallSceneObject::~BallSceneObject()
	{
	}

	void BallSceneObject::draw(HDC hdc)	const
	{
		HPEN obj_pen = (HPEN)CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		HPEN old_pen = (HPEN)SelectObject(hdc, obj_pen);
		
		HBRUSH obj_brush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
		HBRUSH old_brush = (HBRUSH)SelectObject(hdc, obj_brush);

		const double drad = 10.0;
		Ellipse(hdc, 
			static_cast<int>(pos().x - drad), 
			static_cast<int>(pos().y - drad),
			static_cast<int>(pos().x + drad),
			static_cast<int>(pos().y + drad));
		
		obj_pen = (HPEN)SelectObject(hdc, old_pen);
		obj_brush = (HBRUSH)SelectObject(hdc, old_brush);
		DeleteObject(obj_pen);
		DeleteObject(obj_brush);
	}

} // namespace move_simulation