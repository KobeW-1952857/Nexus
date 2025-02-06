#include "Nexus/Window.h"

#include "Nexus/Log.h"
#include "Nexus/Window/GLFWWindow.h"
#include <memory>
namespace Nexus {
Window::API Window::s_api = Window::API::GLFW;

std::unique_ptr<Window> Window::create(const WindowProps &props) {
  switch (s_api) {
  case Window::API::None:
    Logger::error("Window API is not set!");
    return nullptr;
  case Window::API::GLFW:
    return std::make_unique<GLFWWindow>(props);
  }
}
} // namespace Nexus