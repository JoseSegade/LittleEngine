#pragma once
#ifndef IPUBLISHER_H_
#define IPUBLISHER_H_

#include <unordered_map>
#include <string>
#include <functional>

namespace LittleEngine
{
	class IPublisher
	{
	protected:
		std::unordered_map<std::string, std::function<void(const void*, const size_t)>> subscribers;
	public:
		void subscribe(const char* name, std::function<void(const void*, const size_t)> func)
		{
			if (subscribers.count(name) < 1)
			{
				subscribers[name] = func;
			}
		}

		void removeSuscription(const char* name)
		{
			if (subscribers.count(name) > 0)
			{
				subscribers.erase(name);
			}
		}

	};
}

#endif // !PUBLISHER_H_

