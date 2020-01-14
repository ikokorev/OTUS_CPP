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
		for(auto Func : Other.BindedFunctions)
		{
			AddFunction(Func);
		}
	}

	TMulticastDelegate& operator=(const TMulticastDelegate& Other)
	{
		Clear();

		for(auto Func : Other.BindedFunctions)
		{
			AddFunction(Func);
		}

		return *this;
	}

	TMulticastDelegate(TMulticastDelegate&& Other) noexcept
	{
		BindedFunctions = std::move(Other.BindedFunctions);
	}

	TMulticastDelegate& operator=(TMulticastDelegate&& Other) noexcept
	{
		Clear();

		BindedFunctions = std::move(Other.BindedFunctions);
		return *this;
	}

	void AddFunction(std::function<void(Args ...)> Function)
	{
		BindedFunctions.push_back(Function);
	}

	// void RemoveFunction(std::function<void(Args ...)> Function) should I implement it via Set?
	// {

	// }

	void Clear()
	{
		BindedFunctions.clear();
	}

	void Broadcast(Args... args)
	{
		for (auto Func : BindedFunctions)
		{
			Func(args...);
		}
	}

private:

	std::vector<std::function<void(Args...)>> BindedFunctions;
};
