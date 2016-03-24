#ifndef PROPITIOUS_MATH_CLOCK_HPP
#define PROPITIOUS_MATH_CLOCK_HPP

#include <Propitious/Common.hpp>
#include <Propitious/Math/Common.hpp>

#include <Propitious/Math/Time.hpp>

namespace Propitious {

	struct Clock
	{
		Time startTime = Time::now();

		inline Time getElapsedTime() const { return Time::now() - startTime; }

		inline Time restart()
		{
			Time now = Time::now();
			Time elapsed = now - startTime;
			startTime = now;

			return elapsed;
		}
	};
}

#endif
