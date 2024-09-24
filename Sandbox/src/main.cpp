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

#include <stdio.h>
#include <stdlib.h>

static void error_callback(int error, const char* description) {
	fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int test(void) {
	GLFWwindow* window;
	glfwSetErrorCallback(error_callback);

	if (!glfwInit()) exit(EXIT_FAILURE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

	window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetKeyCallback(window, key_callback);

	glfwMakeContextCurrent(window);
	gladLoadGL(glfwGetProcAddress);
	glfwSwapInterval(1);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
}

int main() {
	testLogger();
	testEvent();
	test();
}