#ifndef PROPITIOUS_COMMON_HPP
#define PROPITIOUS_COMMON_HPP

#include <cstdint>
#include <cstddef>

#include <cassert>
#include <functional>
#include <fstream>
#include <iostream>
#include <memory>
#include <stack>
#include <stdexcept>
#include <string>

#include <tchar.h>

#include <Propitious/Common/BasicDefinitions.hpp>
#include <Propitious/Common/Messages.hpp>
#include <Propitious/Common/Modifiers.hpp>
#include <Propitious/Common/DebugOnly.hpp>
#include <Propitious/Common/MakeUnique.hpp>
#include <Propitious/Common/PseudoCast.hpp>
#include <Propitious/Common/OperatingSystems.hpp>
#include <Propitious/Common/Architectures.hpp>
#include <Propitious/Common/Compilers.hpp>
#include <Propitious/Common/Charsets.hpp>
#include <Propitious/Common/NonCopyable.hpp>
#include <Propitious/Common/Types.hpp>

namespace Propitious
{
#pragma message( PROPITIOUS_WARNING("P-100") "Todo: Fix this class, maybe when C++42 comes around?")
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

#include <Propitious/Memory/Allocator.hpp>

#endif