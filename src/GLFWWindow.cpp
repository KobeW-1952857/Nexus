#include "Nexus/Window/GLFWWindow.h"

#include <ImGui/backends/imgui_impl_glfw.h>
#include <ImGui/backends/imgui_impl_opengl3.h>

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

#ifdef __APPLE__
	const char* glsl_version = "#version 410";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#else
#error "Unsupported platform! only macOS is supported!"
#endif

	m_window = glfwCreateWindow(m_data.width, m_data.height, m_data.title.c_str(), NULL, NULL);
	if (!m_window) {
		glfwTerminate();
		Logger::error("Failed to create GLFW window!");
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(m_window);
	gladLoadGL(glfwGetProcAddress);
	glfwSetWindowUserPointer(m_window, &m_data);
	setEventCallbacks();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(m_window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
}

GLFWWindow::~GLFWWindow() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

void GLFWWindow::onUpdate() {}

void GLFWWindow::frameStart() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void GLFWWindow::frameEnd() {
	// Rendering
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	// Update and Render additional Platform Windows
	// (Platform functions may change the current OpenGL context, so we save/restore it to make
	// it easier to paste this code elsewhere.
	//  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
	if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}
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

Window* GLFWWindow::onError(const Event<int, const char*>::EventCallback& callback) {
	m_error.on(callback);
	return this;
}

Window* GLFWWindow::onResize(const Event<int, int>::EventCallback& callback) {
	m_resize.on(callback);
	return this;
}

Window* GLFWWindow::onClose(const Event<>::EventCallback& callback) {
	m_close.on(callback);
	return this;
}

Window* GLFWWindow::onFocus(const Event<int>::EventCallback& callback) {
	m_focus.on(callback);
	return this;
}

Window* GLFWWindow::onMoved(const Event<int, int>::EventCallback& callback) {
	m_moved.on(callback);
	return this;
}

Window* GLFWWindow::onScroll(const Event<double, double>::EventCallback& callback) {
	m_scroll.on(callback);
	return this;
}

Window* GLFWWindow::onMouseButton(const Event<int, int, int>::EventCallback& callback) {
	m_mouseButton.on(callback);
	return this;
}

Window* GLFWWindow::onMouseMove(const Event<double, double>::EventCallback& callback) {
	m_mouseMove.on(callback);
	return this;
}

Window* GLFWWindow::onKey(const Event<int, int, int, int>::EventCallback& callback) {
	m_key.on(callback);
	return this;
}

void GLFWWindow::setEventCallbacks() {
	glfwSetErrorCallback([](int error, const char* description) {
		auto windowData =
			static_cast<WindowData*>(glfwGetWindowUserPointer(glfwGetCurrentContext()));
		Logger::error("GLFW Error ({0}): {1}", error, description);
		windowData->window->m_error.invoke(error, description);
	});

	glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window) {
		auto windowData = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
		windowData->window->shouldClose = true;
		windowData->window->m_close.invoke();
	});

	glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
		auto windowData = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
		windowData->width = width;
		windowData->height = height;
		windowData->window->m_resize.invoke(width, height);
	});

	glfwSetWindowFocusCallback(m_window, [](GLFWwindow* window, int focused) {
		auto windowData = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
		windowData->window->m_focus.invoke(focused);
	});

	glfwSetWindowPosCallback(m_window, [](GLFWwindow* window, int x, int y) {
		auto windowData = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
		windowData->window->m_moved.invoke(x, y);
	});

	glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xOffset, double yOffset) {
		auto windowData = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
		windowData->window->m_scroll.invoke(xOffset, yOffset);
	});

	glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods) {
		auto windowData = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
		windowData->window->m_mouseButton.invoke(button, action, mods);
	});

	glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xPos, double yPos) {
		auto windowData = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
		windowData->window->m_mouseMove.invoke(xPos, yPos);
	});

	glfwSetKeyCallback(
		m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			auto windowData = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			windowData->window->m_key.invoke(key, scancode, action, mods);
		});
}
}  // namespace Nexus