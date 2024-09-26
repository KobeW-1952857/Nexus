#include "Nexus/Window/GLFWWindow.h"

#include <glad/gl.h>

#include "Nexus/Log.h"

namespace Nexus {
static bool s_glfwInitialized = false;

Window* Window::create(const WindowProps& props) { return new GLFWWindow(props); }

GLFWWindow::GLFWWindow(const WindowProps& props) {
	m_data.title = props.title;
	m_data.width = props.width;
	m_data.height = props.height;
	m_data.window = this;

	if (!s_glfwInitialized && !glfwInit()) {
		Logger::error("Failed to initialize GLFW!");
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

	m_window = glfwCreateWindow(m_data.width, m_data.height, m_data.title.c_str(), NULL, NULL);
	if (!m_window) {
		glfwTerminate();
		Logger::error("Failed to create GLFW window!");
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(m_window);

	gladLoadGL(glfwGetProcAddress);

	glfwSetWindowUserPointer(m_window, &m_data);

	glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window) {
		// m_shouldClose = true;
		auto windowData = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
		windowData->window->m_shouldClose = true;
	});

	glfwSetErrorCallback([](int error, const char* description) {
		Logger::error("GLFW Error ({0}): {1}", error, description);
	});
}

GLFWWindow::~GLFWWindow() {
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

void GLFWWindow::onUpdate() {
	glfwSwapBuffers(m_window);
	glfwPollEvents();
}

void GLFWWindow::setVSync(bool enabled) {
	if (enabled) {
		glfwSwapInterval(1);
	} else {
		glfwSwapInterval(0);
	}

	m_data.vSync = enabled;
}

bool GLFWWindow::isVSync() const { return m_data.vSync; }
}  // namespace Nexus