#pragma once

#include <functional>
#include <vector>

template <typename... Args>
class TMulticastDelegate
{
public:
	TMulticastDelegate() = default;

	TMulticastDelegate(const TMulticastDelegate& Other)
	{
		for(auto callback : Other.Callbacks)
		{
			AddCallback(callback);
		}
	}

	TMulticastDelegate& operator=(const TMulticastDelegate& Other)
	{
		Clear();

		for(auto callback : Other.Callbacks)
		{
			AddCallback(callback);
		}

		return *this;
	}

	TMulticastDelegate(TMulticastDelegate&& Other) noexcept
	{
		Callbacks = std::move(Other.Callbacks);
	}

	TMulticastDelegate& operator=(TMulticastDelegate&& Other) noexcept
	{
		Callbacks = std::move(Other.Callbacks);
		return *this;
	}

	void AddCallback(const std::function<void(Args ...)>& Callback)
	{
		Callbacks.push_back(Callback);
	}
	
	void Clear()
	{
		Callbacks.clear();
	}

	void Broadcast(Args... Arguments)
	{
		for (const auto& callback : Callbacks)
		{
			callback(Arguments...);
		}
	}

private:
	std::vector<std::function<void(Args...)>> Callbacks;
};
