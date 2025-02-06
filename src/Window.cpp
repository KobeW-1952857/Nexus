#include "Nexus/Window.h"

#include "Nexus/Window/GLFWWindow.h"
#include <memory>

namespace Nexus {
std::unique_ptr<Window> Window::create(const WindowProps &props) {
  return std::make_unique<GLFWWindow>(props);
}
} // namespace Nexus