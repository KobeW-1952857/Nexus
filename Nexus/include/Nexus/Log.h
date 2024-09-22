#pragma once

#include <spdlog/spdlog.h>

namespace Nexus {

template <typename... Args>
using format_string = spdlog::format_string_t<Args...>;

enum class LogLevel { Trace, Debug, Info, Warn, Error, Critical, Off };
class Logger {
   public:
	static void setLevel(LogLevel level);

	template <typename... Args>
	static void trace(format_string<Args...> message, Args&&... args) {
		spdlog::trace(message, std::forward<Args>(args)...);
	}

	template <typename... Args>
	static void debug(format_string<Args...> message, Args&&... args) {
		spdlog::debug(message, std::forward<Args>(args)...);
	}

	template <typename... Args>
	static void info(format_string<Args...> message, Args&&... args) {
		spdlog::info(message, std::forward<Args>(args)...);
	}

	template <typename... Args>
	static void warn(format_string<Args...> message, Args&&... args) {
		spdlog::warn(message, std::forward<Args>(args)...);
	}

	template <typename... Args>
	static void error(format_string<Args...> message, Args&&... args) {
		spdlog::error(message, std::forward<Args>(args)...);
	}

	template <typename... Args>
	static void critical(format_string<Args...> message, Args&&... args) {
		spdlog::critical(message, std::forward<Args>(args)...);
	}
};
}  // namespace Nexus