#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "Nexus/Event.h"
#include "Nexus/Window.h"

namespace Nexus {
class GLFWWindow : public Window {
   public:
	GLFWWindow(const WindowProps& props);
	virtual ~GLFWWindow();

	void onUpdate() override;
	void setVSync(bool enabled) override;
	bool isVSync() const override;

	// events
	GLFWWindow* onError(const Event<int, const char*>::EventCallback& callback);
	GLFWWindow* onResize(const Event<int, int>::EventCallback& callback);
	GLFWWindow* onClose(const Event<>::EventCallback& callback);
	GLFWWindow* onFocus(const Event<int>::EventCallback& callback);
	GLFWWindow* onMoved(const Event<int, int>::EventCallback& callback);
	GLFWWindow* onScroll(const Event<double, double>::EventCallback& callback);
	GLFWWindow* onMouseButton(const Event<int, int, int>::EventCallback& callback);
	GLFWWindow* onMouseMove(const Event<double, double>::EventCallback& callback);
	GLFWWindow* onKey(const Event<int, int, int, int>::EventCallback& callback);

   private:
	void setEventCallbacks();

	struct WindowData {
		std::string title;
		unsigned int width, height;
		GLFWWindow* window;
		bool vSync = false;
	};
	WindowData m_data;
	GLFWwindow* m_window;

	// Events
	Event<int, const char*> m_error;
	// * Window events
	Event<int, int> m_resize;
	Event<> m_close;
	Event<int> m_focus;
	Event<int, int> m_moved;
	// * Input events
	// ** Mouse
	Event<double, double> m_scroll;
	Event<int, int, int> m_mouseButton;
	Event<double, double> m_mouseMove;
	// ** Keyboard
	Event<int, int, int, int> m_key;
};
}  // namespace Nexus