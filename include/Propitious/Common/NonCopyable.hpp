#ifndef PROPITIOUS_COMMON_NONCOPYABLE
#define PROPITIOUS_COMMON_NONCOPYABLE

#include <Propitious/Common/BasicDefinitions.hpp>

namespace Propitious
{
	class PROPITIOUS_EXPORT NonCopyable
	{
	protected:
		NonCopyable() {}
	private:
		NonCopyable(const NonCopyable&) = delete;
		NonCopyable& operator=(const NonCopyable&) = delete;

		NonCopyable(NonCopyable&&) = delete;
		NonCopyable& operator=(NonCopyable&&) = delete;
	};
}

#endif