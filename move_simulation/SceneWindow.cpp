#include "stdafx.h"
#include "SceneWindow.h"
#include "Logger.h"
#include "Scene.h"
#include "graph_objects.h"

namespace move_simulation {

	SceneWindow::SceneWindow()
		: m_hwnd(nullptr)
	{
	}

	SceneWindow::~SceneWindow()
	{
	}

	void SceneWindow::create(HINSTANCE instance /*= GetModuleHandle(nullptr)*/)
	{
		const TCHAR* class_name = TEXT("SceneWindowClass");
		WNDCLASSEX wndclass = {
			sizeof(WNDCLASSEX),
			CS_DBLCLKS,
			WndProc,
			0, 0,
			instance,
			LoadIcon(nullptr, IDI_APPLICATION),
			LoadCursor(nullptr, IDC_ARROW),
			HBRUSH(COLOR_WINDOW + 1),
			nullptr,
			class_name,
			LoadIcon(nullptr, IDI_APPLICATION) };

		logger() << Logger::Info << "Registering class" << std::endl;
		if (RegisterClassEx(&wndclass))
		{
			logger() << Logger::Info << "Creating window" << std::endl;
			m_hwnd = CreateWindowEx(0, class_name, TEXT("Scene"),
				WS_OVERLAPPEDWINDOW,
				CW_USEDEFAULT, CW_USEDEFAULT,
				CW_USEDEFAULT, CW_USEDEFAULT,
				nullptr, nullptr,
				instance, this);
		} else
		{
			logger() << Logger::Error << "Registering class failed!" << std::endl;
		}
	}

	void SceneWindow::show() const
	{
		ShowWindow(m_hwnd, SW_NORMAL);
	}

	void SceneWindow::set_scene(const std::shared_ptr<Scene> scene)
	{
		m_scene = scene;
	}

	void PointToModel(HWND hwnd, RECT& rect)
	{
		HDC hdc = GetDC(hwnd);

		int saved_dc = SaveDC(hdc);
		RECT client_rect;
		GetClientRect(hwnd, &client_rect);
		int win_width = client_rect.right - client_rect.left;
		int win_height = client_rect.bottom + client_rect.top;

		SetMapMode(hdc, MM_ISOTROPIC);
		SetWindowExtEx(hdc, win_width, win_height, nullptr);
		SetViewportExtEx(hdc, win_width, -win_height, nullptr);
		SetViewportOrgEx(hdc, win_width / 20, win_height * 19 / 20, nullptr);

		DPtoLP(hdc, (LPPOINT)&rect, 2);

		RestoreDC(hdc, saved_dc);
		ReleaseDC(hwnd, hdc);
	}

	void SceneWindow::draw() const
	{
		RECT client_rect;
		GetClientRect(hwnd(), &client_rect);
		int win_width = client_rect.right - client_rect.left;
		int win_height = client_rect.bottom + client_rect.top;

		HDC hdc = GetDC(hwnd());
		HDC memhdc = CreateCompatibleDC(hdc);
		HBITMAP membitmap = CreateCompatibleBitmap(hdc, win_width, win_height);
		HBITMAP moldbmp = (HBITMAP)SelectObject(memhdc, membitmap);

		// Clear background
		FillRect(memhdc, &client_rect, (HBRUSH)GetStockObject(WHITE_BRUSH));

		// Main drawing
		draw_scene(memhdc);
		draw_sysinfo(memhdc);

		BitBlt(hdc, 0, 0, win_width, win_height, memhdc, 0, 0, SRCCOPY);

		SelectObject(memhdc, moldbmp);
		DeleteObject(membitmap);
		DeleteDC(memhdc);
		ReleaseDC(hwnd(), hdc);
	}


	void SceneWindow::draw_sysinfo(HDC hdc) const
	{
		RECT client_rect;
		GetClientRect(hwnd(), &client_rect);

		int saved_dc = SaveDC(hdc);

		SetMapMode(hdc, MM_ANISOTROPIC);
		SetWindowExtEx(hdc, client_rect.right - client_rect.left, client_rect.bottom - client_rect.top, nullptr);
		SetViewportOrgEx(hdc, 10, 10, nullptr);
		SetViewportExtEx(hdc, client_rect.right - client_rect.left, client_rect.bottom - client_rect.top, nullptr);
		
		if (m_scene)
		{
			std::wstringstream ss;
			ss << TEXT("Scene objects: ") << m_scene->objects().size();
			TextOut(hdc, 0, 0, ss.str().c_str(), ss.str().size());
		}

		RestoreDC(hdc, saved_dc);
	}

	void SceneWindow::draw_scene(HDC hdc) const
	{	
		// Draw axis
		int saved_dc = SaveDC(hdc);

		RECT client_rect;
		GetClientRect(hwnd(), &client_rect);
		int win_width = client_rect.right - client_rect.left;
		int win_height = client_rect.bottom + client_rect.top;

		SetMapMode(hdc, MM_ISOTROPIC);
		SetWindowExtEx(hdc, win_width, win_height, nullptr);
		SetViewportExtEx(hdc, win_width, -win_height, nullptr);
		SetViewportOrgEx(hdc, win_width / 20, win_height * 19 / 20, nullptr);

		HPEN black_pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		HPEN old_pen = (HPEN)SelectObject(hdc, black_pen);
		
		MoveToEx(hdc, 0, 0, nullptr);
		LineTo(hdc, 0, win_height * 8 / 10);

		MoveToEx(hdc, 0, 0, nullptr);
		LineTo(hdc, win_width * 8 / 10, 0);
		
		SelectObject(hdc, old_pen);
		DeleteObject(black_pen);

		// Draw scene objects
		if (m_scene)
		{
			m_scene->draw(hdc);
		}

		if (m_active_object)
		{
			m_active_object->draw(hdc);
			MoveToEx(hdc, static_cast<int>(m_active_object->pos().x()), 
				static_cast<int>(m_active_object->pos().y()), nullptr);

			POINT cur_point{0, 0};
			GetCursorPos(&cur_point);
			ScreenToClient(m_hwnd, &cur_point);
			RECT rect_pos{ cur_point.x, cur_point.y, 0, 0 };
			PointToModel(m_hwnd, rect_pos);

			LineTo(hdc, rect_pos.left, rect_pos.top);
		}

		RestoreDC(hdc, saved_dc);
	}

	HWND SceneWindow::hwnd() const
	{
		return m_hwnd;
	}

	LRESULT SceneWindow::WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		SceneWindow* my_wnd = nullptr;

		if (uMsg == WM_NCCREATE) {
			LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lParam);
			my_wnd = static_cast<SceneWindow*>(lpcs->lpCreateParams);
			SetWindowLongPtr(hwnd, GWLP_USERDATA,
				reinterpret_cast<LONG_PTR>(my_wnd));
		}
		else {
			my_wnd = reinterpret_cast<SceneWindow*>(
				GetWindowLongPtr(hwnd, GWLP_USERDATA));
		}

		if (my_wnd) 
			return my_wnd->WindowProc(hwnd, uMsg, wParam, lParam);

		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	LRESULT SceneWindow::WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		switch (msg)
		{
		case WM_CLOSE:
			logger() << Logger::Info << "Close window: " << hwnd << std::endl;
			DestroyWindow(hwnd);
			return 0L;

		case WM_DESTROY:
			logger() << Logger::Info << "Destroing window: " << hwnd << std::endl;
			PostQuitMessage(0);
			return 0L;

		case WM_LBUTTONDOWN:
		{
			logger() << Logger::Info << "Mouse left button down (" << LOWORD(lparam)
				<< ',' << HIWORD(lparam) << ")" << std::endl;

			if (m_scene)
			{
				RECT pos{ LOWORD(lparam), HIWORD(lparam) };
				PointToModel(hwnd, pos);

				m_active_object = std::make_shared<BallSceneObject>(Vector(pos.left, pos.top));
			}

			break;
		}
		case WM_LBUTTONUP:
		{
			logger() << Logger::Info << "Mouse left button up (" << LOWORD(lparam)
				<< ',' << HIWORD(lparam) << ")" << std::endl;	

			if (m_active_object)
			{
				RECT pos{ LOWORD(lparam), HIWORD(lparam) };
				PointToModel(hwnd, pos);
				
				m_active_object->set_vel(
					Vector(pos.left - m_active_object->pos().x(),
						pos.top - m_active_object->pos().y()));
				m_scene->add_object(m_active_object);
				m_active_object.reset();
			}
			break;
		}
		case WM_SIZE:
		case WM_SIZING:
			/*winwidth = LOWORD(lparam);
			winheight = HIWORD(lparam);*/
			draw();
			break;

		case WM_PAINT:
			{
				PAINTSTRUCT ps;	
				BeginPaint(hwnd, &ps);
				EndPaint(hwnd, &ps);
				return 0L;
			}
		}

		return DefWindowProc(hwnd, msg, wparam, lparam);
	}


} //namespace move_simulation