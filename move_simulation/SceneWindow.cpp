#include "stdafx.h"
#include "SceneWindow.h"
#include "Logger.h"
#include "Scene.h"

namespace move_simulation {

	SceneWindow::SceneWindow()
		: m_hwnd(nullptr)
		, m_scene(nullptr)
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
			WindowProc,
			0, 0,
			instance,
			LoadIcon(nullptr, IDI_APPLICATION),
			LoadCursor(nullptr, IDC_ARROW),
			nullptr, //HBRUSH(COLOR_WINDOW + 1),
			nullptr,
			class_name,
			LoadIcon(nullptr, IDI_APPLICATION) };

		logger() << Logger::Info << "Registering class " << class_name << "...";
		if (RegisterClassEx(&wndclass))
		{
			logger() << "Ok" << std::endl;
			logger() << "Creating window" << std::endl;
			m_hwnd = CreateWindowEx(0, class_name, TEXT("Scene"),
				WS_OVERLAPPEDWINDOW,
				CW_USEDEFAULT, CW_USEDEFAULT,
				CW_USEDEFAULT, CW_USEDEFAULT,
				nullptr, nullptr,
				instance, nullptr);
		} else
		{
			logger() << Logger::Error << "Registering class " << class_name << " failed!" << std::endl;
		}
	}

	void SceneWindow::show() const
	{
		ShowWindow(m_hwnd, SW_NORMAL);
	}

	void SceneWindow::set_scene(Scene* scene)
	{
		m_scene = scene;
	}

	void SceneWindow::draw() const
	{
		RECT client_rect;
		GetClientRect(hwnd(), &client_rect);
		int win_width = client_rect.right - client_rect.left;
		int win_height = client_rect.bottom + client_rect.top;

		HDC memhdc;
		HDC hdc;
		HBITMAP membitmap;
		hdc = GetDC(hwnd());
		memhdc = CreateCompatibleDC(hdc);
		membitmap = CreateCompatibleBitmap(hdc, win_width, win_height);
		HBITMAP moldbmp = (HBITMAP)SelectObject(memhdc, membitmap);

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
	}

	void SceneWindow::draw_scene(HDC hdc) const
	{
		if (m_scene == nullptr)
			return;
		
		m_scene->draw(hdc);
	}

	HWND SceneWindow::hwnd() const
	{
		return m_hwnd;
	}

	LRESULT SceneWindow::WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		switch (msg)
		{
		case WM_CLOSE:
			logger() << Logger::Info << "Close window: " << hwnd;
			DestroyWindow(hwnd);
			return 0L;

		case WM_DESTROY:
			logger() << Logger::Info << "Destroing window: " << hwnd;
			PostQuitMessage(0);
			return 0L;

		case WM_LBUTTONDOWN:
			logger() << Logger::Info << "\nMouse left button down (" << LOWORD(lparam)
				<< ',' << HIWORD(lparam) << ")\n";

		case WM_PAINT:
		{
			PAINTSTRUCT ps;	
			BeginPaint(hwnd, &ps);
			EndPaint(hwnd, &ps);
			return 0L;
		}

		default:
			logger() << Logger::Info << '.';
		}

		return DefWindowProc(hwnd, msg, wparam, lparam);
	}


} //namespace move_simulation