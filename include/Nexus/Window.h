#pragma once

#include "Nexus/Event.h"

#include <ImGui/imgui.h>
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
  virtual ~Window() = default;
  virtual void onUpdate() = 0;
  virtual void frameStart() = 0;
  virtual void frameEnd() = 0;
  virtual void setVSync(bool enabled) = 0;
  virtual bool isVSync() const = 0;

  // events
  virtual Window *
  onError(const Event<int, const char *>::EventCallback &callback) = 0;
  virtual Window *onResize(const Event<int, int>::EventCallback &callback) = 0;
  virtual Window *onClose(const Event<>::EventCallback &callback) = 0;
  virtual Window *onFocus(const Event<int>::EventCallback &callback) = 0;
  virtual Window *onMoved(const Event<int, int>::EventCallback &callback) = 0;
  virtual Window *
  onScroll(const Event<double, double>::EventCallback &callback) = 0;
  virtual Window *
  onMouseButton(const Event<int, int, int>::EventCallback &callback) = 0;
  virtual Window *
  onMouseMove(const Event<double, double>::EventCallback &callback) = 0;
  virtual Window *
  onKey(const Event<int, int, int, int>::EventCallback &callback) = 0;

  virtual void whileOpen(std::function<void()> callback) = 0;

  static Window *create(const WindowProps &props = WindowProps());

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