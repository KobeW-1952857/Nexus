#include "Nexus/Log.h"

namespace Nexus {
void Logger::setLevel(LogLevel level) {
	switch (level) {
		case LogLevel::Trace:
			spdlog::set_level(spdlog::level::trace);
			break;
		case LogLevel::Debug:
			spdlog::set_level(spdlog::level::debug);
			break;
		case LogLevel::Info:
			spdlog::set_level(spdlog::level::info);
			break;
		case LogLevel::Warn:
			spdlog::set_level(spdlog::level::warn);
			break;
		case LogLevel::Error:
			spdlog::set_level(spdlog::level::err);
			break;
		case LogLevel::Critical:
			spdlog::set_level(spdlog::level::critical);
			break;
		case LogLevel::Off:
			spdlog::set_level(spdlog::level::off);
			break;
	}
}
}  // namespace Nexus