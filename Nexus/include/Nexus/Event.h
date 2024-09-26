#pragma once

#include <functional>
#include <string>
#include <vector>

namespace Nexus {
template <typename... Args>
class Event {
   public:
	using EventCallback = std::function<bool(Args...)>;
	Event() = default;
	Event(const std::string& name) : m_name(name) {}

	std::string toString() const { return m_name.empty() ? "Event" : m_name; };
	inline bool handled() const { return m_handled; }

	Event* on(EventCallback func, bool priority = false) {
		if (priority) {
			m_callbacks.insert(m_callbacks.begin(), std::move(func));
			return this;
		}

		m_callbacks.push_back(std::move(func));
		return this;
	}

	// Don't entirely get this function (copilot wrote it), need to understand it before including
	// 	Event* off(EventCallback func) {
	// 		m_callbacks.erase(std::remove(m_callbacks.begin(), m_callbacks.end(), func),
	//									m_callbacks.end());
	//		return this;
	// }

	void clear() { m_callbacks.clear(); }

	void setName(const std::string& name) { m_name = name; }

	void invoke(Args... args) {
		m_handled = false;
		for (auto& callback : m_callbacks) {
			if (callback(std::forward<Args>(args)...)) {
				m_handled = true;
				break;
			}
		}
	}

   protected:
	bool m_handled = false;
	std::vector<EventCallback> m_callbacks;
	std::string m_name;
};
}  // namespace Nexus