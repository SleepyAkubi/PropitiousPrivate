#ifndef PROPITIOUS_MATH_TIME_HPP
#define PROPITIOUS_MATH_TIME_HPP

#include <Propitious/Common.hpp>
#include <chrono>
#include <thread>

#ifdef PROPITIOUS_SYSTEM_WINDOWS
#include <Windows.h>
#endif

namespace Propitious
{
	class PROPITIOUS_EXPORT Time
	{
	public:
		Time()
			: m_microseconds(0)
		{}

		inline f32 asSeconds() const
		{
			return m_microseconds.count() / 1000000.0f;
		}
		inline i32 asMilliseconds() const
		{
			return static_cast<u32>(m_microseconds.count() / 1000);
		}
		inline i64 asMicroseconds() const
		{
			return static_cast<u32>(m_microseconds.count());
		}

		static Time now()
		{
#ifdef PROPITIOUS_SYSTEM_WINDOWS	
			HANDLE currentThread = GetCurrentThread();
			DWORD_PTR previousMask = SetThreadAffinityMask(currentThread, 1);

			static LARGE_INTEGER s_frequency;
			QueryPerformanceFrequency(&s_frequency);

			LARGE_INTEGER time;
			QueryPerformanceCounter(&time);

			SetThreadAffinityMask(currentThread, previousMask);

			return Time(static_cast<i64>(1e6 * time.QuadPart / s_frequency.QuadPart));

#else
			auto now = std::chrono::high_resolution_clock::now().time_since_epoch();
			return Time(static_cast<i64>(std::chrono::duration_cast<std::chrono::microseconds>(now).count()));
#endif
		}
		static void snooze(Time time)
		{
			std::this_thread::sleep_for(std::chrono::microseconds(time.asMicroseconds()));
		}

		explicit Time(u64 microseconds)
			: m_microseconds(std::chrono::microseconds(microseconds))
		{}
	private:
		std::chrono::microseconds m_microseconds;
	};

	inline Time seconds(f32 amount) { return Time(static_cast<u64>(amount * 1000000)); }

	inline Time milliseconds(u32 amount) { return Time(static_cast<u64>(amount * 1000)); }

	inline Time microseconds(u64 amount) { return Time(amount); }

	inline bool operator==(Time left, Time right)
	{
		return left.asMicroseconds() == right.asMicroseconds();
	}

	inline bool operator!=(Time left, Time right)
	{
		return left.asMicroseconds() != right.asMicroseconds();
	}

	inline bool operator<(Time left, Time right)
	{
		return left.asMicroseconds() < right.asMicroseconds();
	}

	inline bool operator>(Time left, Time right)
	{
		return left.asMicroseconds() > right.asMicroseconds();
	}

	inline bool operator<=(Time left, Time right)
	{
		return left.asMicroseconds() <= right.asMicroseconds();
	}

	inline bool operator>=(Time left, Time right)
	{
		return left.asMicroseconds() >= right.asMicroseconds();
	}

	//Time operator-(Time right) { return microseconds(-right.asMicroseconds()); }

	inline Time operator+(Time left, Time right)
	{
		return microseconds(left.asMicroseconds() + right.asMicroseconds());
	}

	inline Time operator-(Time left, Time right)
	{
		return microseconds(left.asMicroseconds() - right.asMicroseconds());
	}

	inline Time& operator+=(Time& left, Time right) { return left = left + right; }

	inline Time& operator-=(Time& left, Time right) { return left = left - right; }

	inline Time operator*(Time left, f32 right)
	{
		return seconds(left.asSeconds() * right);
	}

	inline Time operator*(Time left, u64 right)
	{
		return microseconds(left.asMicroseconds() * right);
	}

	inline Time operator*(f32 left, Time right)
	{
		return seconds(left * right.asSeconds());
	}

	inline Time operator*(u64 left, Time right)
	{
		return microseconds(right.asMicroseconds() * left);
	}

	inline Time& operator*=(Time& left, f32 right) { return left = left * right; }

	inline Time& operator*=(Time& left, u64 right) { return left = left * right; }

	inline Time operator/(Time left, f32 right)
	{
		return seconds(left.asSeconds() / right);
	}

	inline Time operator/(Time left, u64 right)
	{
		return microseconds(left.asMicroseconds() / right);
	}

	inline Time& operator/=(Time& left, f32 right) { return left = left / right; }

	inline Time& operator/=(Time& left, u64 right) { return left = left / right; }

	inline f32 operator/(Time left, Time right)
	{
		return left.asSeconds() / right.asSeconds();
	}

	inline Time operator%(Time left, Time right)
	{
		return microseconds(left.asMicroseconds() % right.asMicroseconds());
	}

	inline Time& operator%=(Time& left, Time right) { return left = left % right; }

}



#endif