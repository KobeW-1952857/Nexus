#pragma once

#include <spdlog/spdlog.h>

namespace Nexus {

template <typename... Args>
using format_string = spdlog::format_string_t<Args...>;

enum class LogLevel { Trace, Debug, Info, Warn, Error, Critical, Off };
class Logger {
   public:
	static void SetLevel(LogLevel level);

	template <typename... Args>
	static void Log(format_string<Args...> message, LogLevel logLevel = LogLevel::Info,
					Args&&... args) {
		switch (logLevel) {
			case LogLevel::Trace:
				spdlog::trace(message, std::forward<Args>(args)...);
				break;
			case LogLevel::Debug:
				spdlog::debug(message, std::forward<Args>(args)...);
				break;
			case LogLevel::Info:
				spdlog::info(message, std::forward<Args>(args)...);
				break;
			case LogLevel::Warn:
				spdlog::warn(message, std::forward<Args>(args)...);
				break;
			case LogLevel::Error:
				spdlog::error(message, std::forward<Args>(args)...);
				break;
			case LogLevel::Critical:
				spdlog::critical(message, std::forward<Args>(args)...);
				break;
			case LogLevel::Off:
				break;
		}
	}
};
}  // namespace Nexus