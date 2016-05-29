#pragma once

namespace move_simulation {

	class Scene;

	class SceneWindow
	{
	public:
		SceneWindow();
		~SceneWindow();

		void create(HINSTANCE instance = GetModuleHandle(nullptr));
		void show() const;

		void set_scene(const std::shared_ptr<Scene> scene);

		void draw() const;
		
		HWND hwnd() const;

	private:
		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

		void draw_scene(HDC hdc) const;
		void draw_sysinfo(HDC hdc) const;

	private:
		HWND m_hwnd;
		std::shared_ptr<Scene> m_scene;
	};

} // namespace move_simulation