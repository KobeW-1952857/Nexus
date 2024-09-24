#pragma once

#include <string>

namespace Nexus {

struct WindowProps {
	std::string title;
	unsigned int width;
	unsigned int height;

	WindowProps(const std::string& title = "Nexus Engine", unsigned int width = 1280,
				unsigned int height = 720)
		: title(title), width(width), height(height) {}
};

class Window {
   public:
	virtual ~Window() = default;
	virtual void onUpdate() = 0;
	virtual void setVSync(bool enabled) = 0;
	virtual bool isVSync() const = 0;

	virtual bool shouldClose() const { return m_shouldClose; }

	static Window* create(const WindowProps& props = WindowProps());

   protected:
	bool m_shouldClose = false;
};
}  // namespace Nexus