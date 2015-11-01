#ifndef PROPITIOUS_MATH_TIME_HPP
#define PROPITIOUS_MATH_TIME_HPP

#define _CRT_SECURE_NO_WARNINGS

#include <Propitious/Common.hpp>
#include <Propitious/Containers/String.hpp>
#include <Propitious/Math/Functions/trivial.hpp>
#include <chrono>
#include <thread>
#include <ctime>

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
		inline const a8* format(const a8* format = "%d/%m/%Y") const
		{
			static a8 buffer[1024];
			f32 seconds = asSeconds();
			time_t secondsCeiling = Math::floor(seconds);
			tm* time = gmtime((&secondsCeiling));
			strftime(buffer, 1024, format, time);
			return buffer;
		}

		static Time now()
		{
#ifdef PROPITIOUS_SYSTEM_WINDOWS	
			FILETIME filetime;
			GetSystemTimeAsFileTime(&filetime);
			u64 tt = filetime.dwHighDateTime;
			tt <<= 32;
			tt |= filetime.dwLowDateTime;
			tt /= 10;
			tt -= 11644473600000000ULL;

			return Time(tt);

#else
			auto now = std::chrono::high_resolution_clock::now().time_since_epoch();
			return Time((u64)(std::chrono::duration_cast<std::chrono::microseconds>(now).count()));
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

	inline Time seconds(f32 amount) { return Time((u64)(amount * 1000000)); }

	inline Time milliseconds(u32 amount) { return Time((u64)(amount * 1000)); }

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