#include "stdafx.h"
#include "graph_objects.h"

namespace move_simulation {

	BallSceneObject::BallSceneObject(const Vector& pos /* = Vector(0)*/)
		: GraphSceneObject(pos)
	{
	}

	void BallSceneObject::draw(HDC hdc)	const
	{
		HPEN obj_pen = (HPEN)CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		HPEN old_pen = (HPEN)SelectObject(hdc, obj_pen);
		
		HBRUSH obj_brush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
		HBRUSH old_brush = (HBRUSH)SelectObject(hdc, obj_brush);

		const double rad = 15.0;
		Ellipse(hdc, 
			static_cast<int>(pos().x() - rad), 
			static_cast<int>(pos().y() - rad),
			static_cast<int>(pos().x() + rad),
			static_cast<int>(pos().y() + rad));
		

		SelectObject(hdc, (HBRUSH)GetStockObject(WHITE_BRUSH));

		Ellipse(hdc,
			static_cast<int>(pos().x()),
			static_cast<int>(pos().y()),
			static_cast<int>(pos().x() + rad * 2 / 3),
			static_cast<int>(pos().y() + rad * 2 / 3));

		SelectObject(hdc, old_pen);
		SelectObject(hdc, old_brush);

		DeleteObject(obj_pen);
		DeleteObject(obj_brush);
	}

} // namespace move_simulation