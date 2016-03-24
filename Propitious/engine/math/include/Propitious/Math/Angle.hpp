#ifndef PROPITIOUS_MATH_ANGLE_HPP
#define PROPITIOUS_MATH_ANGLE_HPP

#include <Propitious/Math/Common.hpp>
#include <Propitious/Math/Unit.hpp>
#include <Propitious/Math/Constants.hpp>
#include <ostream>

namespace Propitious
{
	namespace Impl
	{
		template <class T>
		class Radian;

		// Degree
		template <class T>
		class Degree : public Unit<Degree, T>
		{
		public:
			Degree() {}

			explicit Degree(T value)
			: Unit<Propitious::Impl::Degree, T>(value)
			{
			}

			Degree(Unit<Propitious::Impl::Degree, T> value)
			: Unit<Propitious::Impl::Degree, T>(value)
			{
			}

			template <class U>
			explicit Degree(Unit<Propitious::Impl::Degree, U> value)
			: Unit<Propitious::Impl::Degree, T>(value)
			{
			}

			Degree(Unit<Radian, T> value);
		};

		// Radian
		template <class T>
		class Radian : public Unit<Radian, T>
		{
		public:
			Radian() {}

			explicit Radian(T value)
			: Unit<Propitious::Impl::Radian, T>(value)
			{
			}

			Radian(Unit<Propitious::Impl::Radian, T> value)
			: Unit<Propitious::Impl::Radian, T>(value)
			{
			}
			template <class U>
			explicit Radian(Unit<Propitious::Impl::Radian, U> value)
			: Unit<Propitious::Impl::Radian, T>(value)
			{
			}

			Radian(Unit<Degree, T> value);
		};

		template <class T>
		Degree<T>::Degree(Unit<Radian, T> value)
			//: Unit<Propitious::Impl::Degree, T>(T(360) * T(value) /
			// Constants<T>::tau())
			: Unit<Propitious::Impl::Degree, T>(T(360) * T(value) / Constants<T>::Tau())
		{
		}
		template <class T>
		Radian<T>::Radian(Unit<Degree, T> value)
			//: Unit<Propitious::Impl::Radian, T>(T(value) * Constants<T>::tau() /
			// T(360))
			: Unit<Propitious::Impl::Radian, T>(T(value) * Constants<T>::Tau() / T(360))
		{
		}

	}

	using Radian = Impl::Radian<f32>;
	using Degree = Impl::Degree<f32>;
}

#endif
