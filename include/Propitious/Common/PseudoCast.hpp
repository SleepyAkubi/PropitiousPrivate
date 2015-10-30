#ifndef PROPITIOUS_COMMON_PSEUDOCAST
#define PROPITIOUS_COMMON_PSEUDOCAST

namespace Propitious
{
	template <typename T, typename U>
	inline T pseudo_cast(const U& x)
	{
		T to = T(0);
		memcpy(&to, &x, (sizeof(T) < sizeof(U)) ? sizeof(T) : sizeof(U));
		return to;
	}
}
#endif