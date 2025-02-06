#include "Nexus/Window.h"

#include "Nexus/Window/GLFWWindow.h"

namespace Nexus {
Window *Window::create(const WindowProps &props) {
  return new GLFWWindow(props);
}
} // namespace Nexus