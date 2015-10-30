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



	/* Do Not Use Until We Get Get Operators*/
	template <typename T>
	class Hooked : private NonCopyable
	{
	public:
		using Function = std::function<void(const T&, const T&)>;
		Hooked(T& value, Function hook) : reference(value), hook(hook) {}

		T& operator=(const T& value)
		{
			hook(reference, value);
			reference = value;
		}

		T& reference;
		Function hook;
	};

}

#include <Propitious/Memory/Allocator.hpp>

#endif