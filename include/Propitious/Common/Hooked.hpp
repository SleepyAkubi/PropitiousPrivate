#ifndef PROPITIOUS_COMMON_HOOKED_HPP
#define PROPITIOUS_COMMON_HOOKED_HPP

#include <functional>

namespace Propitious
{
	template <typename T>
	class Hooked : private NonCopyable
	{
	public:
		using SetFunction = std::function<void(T&, const T&)>;
		using GetFunction = std::function<T(T&)>;

		Hooked(T value, SetFunction setHook, GetFunction getHook)
			: data(value)
			, setHook(setHook)
			, getHook(getHook)
		{}

		T& operator=(const T& value)
		{
			setHook(data, value);
			return data;
		}

		T operator*()
		{
			return getHook(data);
		}

		T data;
		SetFunction setHook;
		GetFunction getHook;
	};
}

#endif