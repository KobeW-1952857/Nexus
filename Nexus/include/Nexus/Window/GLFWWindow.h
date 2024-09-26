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

	virtual void onUpdate() override;
	virtual void setVSync(bool enabled) override;
	virtual bool isVSync() const override;

	// events
	virtual Window* onError(const Event<int, const char*>::EventCallback& callback) override;
	virtual Window* onResize(const Event<int, int>::EventCallback& callback) override;
	virtual Window* onClose(const Event<>::EventCallback& callback) override;
	virtual Window* onFocus(const Event<int>::EventCallback& callback) override;
	virtual Window* onMoved(const Event<int, int>::EventCallback& callback) override;
	virtual Window* onScroll(const Event<double, double>::EventCallback& callback) override;
	virtual Window* onMouseButton(const Event<int, int, int>::EventCallback& callback) override;
	virtual Window* onMouseMove(const Event<double, double>::EventCallback& callback) override;
	virtual Window* onKey(const Event<int, int, int, int>::EventCallback& callback) override;

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
};
}  // namespace Nexus