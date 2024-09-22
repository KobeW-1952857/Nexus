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

int main() {
	testLogger();
	testEvent();
	return 0;
}