#pragma once

#include <functional>
#include <vector>

/**
 * @brief This class allows you to dynamically bind it with a member function of an arbitraty object. Such function should have void return type
 * and it parameters types matching instanced delegate Args types. All binded functions will be executed on delegate instance Broadcast() function call.
 * That class follows the core ideas of Observer (aka Signal-Slot, Publisher-Subsriber) pattern, but it's implemented via composition, rather then via inheritance.
 * You should just add desired delegate to class, everyone can subsribe to it, and at some point the delegate broadcasts, executing all subsribed member function.
 * 
 * @details It's non-complete, a little bit dummy class, that exists only to illustrate the next idea of the project: UI has no need to know about other program, 
 * it just has some events, on which other entities could subsribe. At some point UI fires its events, and all subsribed enteties executes their corresponding actions.
 * In particular, controllers do subscribe to UI events, and react with corresponding actions on such events execution.
 */
template <typename... Args>
class TMulticastDelegate
{

public:

	TMulticastDelegate() = default;

	TMulticastDelegate(const TMulticastDelegate& Other)
	{
		for(std::function<void(Args...)> Function : Other.BindedFunctions)
		{
			BindFunction(Function);
		}
	}

	TMulticastDelegate& operator=(const TMulticastDelegate& Other)
	{
		Clear();

		for(std::function<void(Args...)> Function : Other.BindedFunctions)
		{
			BindFunction(Function);
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

	/** 
	 * Binds arbitrary object member function for futher execution.
	 * Use std::bind(...) as this function argument for proper bind. You can look in the project for examples.
	 * @param[in] Function A member function to bind with.
	 */
	void BindFunction(std::function<void(Args ...)> Function)
	{
		BindedFunctions.push_back(Function);
	}

	/** Clears all delegate's binded functions. */
	void Clear()
	{
		BindedFunctions.clear();
	}

	/** Broadcasts all binded functions for execution. */
	void Broadcast(Args... Arguments)
	{
		for (std::function<void(Args...)> Function : BindedFunctions)
		{
			Function(Arguments...);
		}
	}

private:

	std::vector<std::function<void(Args...)>> BindedFunctions;
};
