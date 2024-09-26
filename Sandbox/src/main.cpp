#include <iostream>

#include "Nexus.h"

void testLogger() {
	Nexus::Logger::setLevel(Nexus::LogLevel::Trace);
	Nexus::Logger::trace("Hello, World!");
	Nexus::Logger::debug("Hello, World!");
	Nexus::Logger::info("Hello, World!");
	Nexus::Logger::warn("Hello, World!");
	Nexus::Logger::error("Hello, World!");
	Nexus::Logger::critical("Hello, World!");
}

bool testEventCallback(int x) {
	Nexus::Logger::info("function: Value: {0}", x);
	return false;
}

void testEvent() {
	Nexus::Event<int> event;
	event.on([](int x) -> bool {
		Nexus::Logger::info("lambda: Value: {0}", x);
		return false;
	});
	event.on(testEventCallback);

	event.invoke(42);
}

#include "Nexus/Window/GLFWWindow.h"

void test() {
	auto window = Nexus::Window::create();
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	window
		->onResize([](int width, int height) -> bool {
			glViewport(0, 0, width, height);
			Nexus::Logger::info("Window resized to {0}x{1}", width, height);
			return false;
		})
		->onResize([](int width, int height) -> bool {
			Nexus::Logger::info("Second resize callback: {0}x{1}", width, height);
			return true;
		})
		->onResize([](int width, int height) -> bool {
			Nexus::Logger::info("Third resize callback: {0}x{1}", width, height);
			return false;
		})
		->onClose([]() -> bool {
			Nexus::Logger::info("Window closed");
			return false;
		})
		->onError([](int error, const char* description) -> bool {
			Nexus::Logger::error("GLFW Error ({0}): {1}", error, description);
			return true;
		})
		->onKey([](int key, int scancode, int action, int mods) -> bool {
			Nexus::Logger::info("Key: {0}, Scancode: {1}, Action: {2}, Mods: {3}", key, scancode,
								action, mods);
			return false;
		});

	while (!window->shouldClose()) {
		glClear(GL_COLOR_BUFFER_BIT);

		window->onUpdate();
	}

	delete window;
}

int main() {
	testLogger();
	testEvent();
	test();
}