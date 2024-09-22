#include <iostream>

#include "Nexus.h"

void testLogger() {
	Nexus::Logger::SetLevel(Nexus::LogLevel::Trace);
	Nexus::Logger::Log("Hello, World!", Nexus::LogLevel::Trace);
	Nexus::Logger::Log("Hello, World!", Nexus::LogLevel::Debug);
	Nexus::Logger::Log("Hello, World!", Nexus::LogLevel::Info);
	Nexus::Logger::Log("Hello, World!", Nexus::LogLevel::Warn);
	Nexus::Logger::Log("Hello, World!", Nexus::LogLevel::Error);
	Nexus::Logger::Log("Hello, World!", Nexus::LogLevel::Critical);
}

bool testEventCallback(int x) {
	Nexus::Logger::Log("function: Value: {0}", Nexus::LogLevel::Info, x);
	return false;
}

void testEvent() {
	Nexus::Event<int> event;
	event.on([](int x) -> bool {
		Nexus::Logger::Log("lambda: Value: {0}", Nexus::LogLevel::Info, x);
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