#pragma once

#include "Nexus/Event.h"

#include <ImGui/imgui.h>
#include <memory>
#include <string>

namespace Nexus {

struct WindowProps {
  std::string title;
  unsigned int width;
  unsigned int height;

  WindowProps(const std::string &title = "Nexus Engine",
              unsigned int width = 1280, unsigned int height = 720)
      : title(title), width(width), height(height) {}
};

class Window {
public:
  enum class API { None, GLFW };
  static API s_api;

public:
  virtual ~Window() = default;
  virtual void onUpdate() = 0;
  virtual void frameStart() = 0;
  virtual void frameEnd() = 0;
  virtual void setVSync(bool enabled) = 0;
  virtual bool isVSync() const = 0;

  // events
  virtual void
  onError(const Event<int, const char *>::EventCallback &callback) = 0;
  virtual void onResize(const Event<int, int>::EventCallback &callback) = 0;
  virtual void onClose(const Event<>::EventCallback &callback) = 0;
  virtual void onFocus(const Event<int>::EventCallback &callback) = 0;
  virtual void onMoved(const Event<int, int>::EventCallback &callback) = 0;
  virtual void
  onScroll(const Event<double, double>::EventCallback &callback) = 0;
  virtual void
  onMouseButton(const Event<int, int, int>::EventCallback &callback) = 0;
  virtual void
  onMouseMove(const Event<double, double>::EventCallback &callback) = 0;
  virtual void
  onKey(const Event<int, int, int, int>::EventCallback &callback) = 0;

  virtual void whileOpen(std::function<void()> callback) = 0;

  static std::unique_ptr<Window>
  create(const WindowProps &props = WindowProps());

  bool shouldClose = false;

protected:
  // Events
  Event<int, const char *> m_error;
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
} // namespace Nexus

#include "Nexus/Window/GLFWWindow.h"