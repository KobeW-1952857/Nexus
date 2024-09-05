#include <iostream>

#include "Nexus.h"

int main() {
	Nexus::Logger::SetLevel(Nexus::LogLevel::Trace);
	Nexus::Logger::Log("Hello, World!", Nexus::LogLevel::Trace);
	Nexus::Logger::Log("Hello, World!", Nexus::LogLevel::Debug);
	Nexus::Logger::Log("Hello, World!", Nexus::LogLevel::Info);
	Nexus::Logger::Log("Hello, World!", Nexus::LogLevel::Warn);
	Nexus::Logger::Log("Hello, World!", Nexus::LogLevel::Error);
	Nexus::Logger::Log("Hello, World!", Nexus::LogLevel::Critical);
}