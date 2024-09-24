#pragma once

#include <GLFW/glfw3.h>

#include "Nexus/Window.h"

namespace Nexus {
class GLFWWindow : public Window {
   public:
	GLFWWindow(const WindowProps& props);
	virtual ~GLFWWindow();

	void onUpdate() override;
	void setVSync(bool enabled) override;
	bool isVSync() const override;

   private:
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