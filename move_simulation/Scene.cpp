#include "stdafx.h"
#include "Scene.h"

namespace move_simulation {

	Scene::Scene()
	{
	}

	Scene::~Scene()
	{
	}

	void Scene::draw(HDC hdc)
	{
		HPEN redpen = (HPEN)CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		HPEN oldpen = (HPEN)SelectObject(hdc, redpen);

		Ellipse(hdc, 30, 30, 120, 90);
		RoundRect(hdc, 150, 30, 240, 90, 15, 20);
		Chord(hdc, 270, 30, 360, 90, 270, 45, 360, 45);
		Rectangle(hdc, 150, 110, 230, 160);

		redpen = (HPEN)SelectObject(hdc, oldpen);
		DeleteObject(redpen);
	}

} //namespace move_simulation