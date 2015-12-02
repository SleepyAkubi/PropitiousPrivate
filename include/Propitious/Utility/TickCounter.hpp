#ifndef PROPITIOUS_UTILITY_TICKCOUNTER_HPP
#define PROPITIOUS_UTILITY_TICKCOUNTER_HPP

#include <Propitious/Common.hpp>
#include <Propitious/Math/Clock.hpp>

namespace Propitious 
{
	struct PROPITIOUS_EXPORT TickCounter
	{
		usize tick;
		f64 tickRate;
		Clock clock;
	};

	inline bool update(TickCounter& counter, Time period)
	{
		bool reset = false;
		if (counter.clock.getElapsedTime() >= period)
		{
			counter.tickRate = counter.tick * (1.0f / period.asSeconds());
			counter.tick = 0;
			reset = true;
			counter.clock.restart();
		}

		counter.tick++;

		return reset;
	}

}
#endif
