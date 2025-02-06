#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

#include "Nexus/Event.h"
#include "Nexus/Window.h"

namespace Nexus {
class GLFWWindow : public Window {
public:
  GLFWWindow(const WindowProps &props);
  virtual ~GLFWWindow();

  virtual void onUpdate() override;
  virtual void frameStart() override;
  virtual void frameEnd() override;
  virtual void setVSync(bool enabled) override;
  virtual bool isVSync() const override;

  // events
  virtual void
  onError(const Event<int, const char *>::EventCallback &callback) override;
  virtual void
  onResize(const Event<int, int>::EventCallback &callback) override;
  virtual void onClose(const Event<>::EventCallback &callback) override;
  virtual void onFocus(const Event<int>::EventCallback &callback) override;
  virtual void onMoved(const Event<int, int>::EventCallback &callback) override;
  virtual void
  onScroll(const Event<double, double>::EventCallback &callback) override;
  virtual void
  onMouseButton(const Event<int, int, int>::EventCallback &callback) override;
  virtual void
  onMouseMove(const Event<double, double>::EventCallback &callback) override;
  virtual void
  onKey(const Event<int, int, int, int>::EventCallback &callback) override;

  virtual void whileOpen(std::function<void()> callback) override;

private:
  void setEventCallbacks();

  struct WindowData {
    std::string title;
    unsigned int width, height;
    GLFWWindow *window;
    bool vSync = false;
  };
  WindowData m_data;
  GLFWwindow *m_window;
};
} // namespace Nexus