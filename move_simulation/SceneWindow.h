#pragma once

namespace move_simulation {

	class Scene;
	class GraphSceneObject;

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
		// Forward static method 
		static LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

		void draw_scene(HDC hdc) const;
		void draw_sysinfo(HDC hdc) const;

	private:
		HWND m_hwnd;
		std::shared_ptr<Scene> m_scene;

		std::shared_ptr<GraphSceneObject> m_active_object;

		// Scene window sys_info
		mutable simulation::TimePoint m_prev_time;
		mutable double m_update_duration;
		mutable double m_update_show_time;
		mutable std::wstringstream m_sys_info;
	};

} // namespace move_simulation