#ifndef PROPITIOUS_GRAPHICS_WINDOW_HPP
#define PROPITIOUS_GRAPHICS_WINDOW_HPP

#include <Propitious/Common.hpp>
#include <Propitious/Graphics/Dimensions.hpp>
#include <Propitious/Math/Vector2.hpp>
#include <Propitious/Math/Clock.hpp>
#include <vector>
#include <string>

#if defined(PROPITIOUS_SYSTEM_WINDOWS)
#include <Windows.h>
#endif

namespace Propitious
{
	enum class PROPITIOUS_EXPORT WindowStyle
	{
		Windowed,
		Fullscreen,
		Borderless,
		ExclusiveFullscreen,
	};

	enum class PROPITIOUS_EXPORT WindowMode
	{
		Windowed,
		Fullscreen,
		ExclusiveFullscreen
	};

	class PROPITIOUS_EXPORT Window
	{
	public:

		Window();
		~Window() = default;

		void create(const ::std::string& title,
			const Dimensions& dimensions,
			const WindowStyle style);

		void close();

		bool isOpen() const;

		const Vector2 getPosition() const;
		void setPosition(const Vector2& position);

		const Dimensions getSize() const;
		void setSize(const Dimensions& dimensions);

		const String getTitle() const;
		void setTitle(const String& title);

		const bool getVisible() const;
		void setVisible(bool visible);

		const bool getVerticalSyncEnabled() const;
		void setVerticalSyncEnabled(bool vsync);

		void setFramerateLimit(u32 limit);

		WindowMode getFullscreen();
		void setFullscreen(WindowMode fullscreen);


		void display();

		f32 aspectRatio;

		Time frameTimeLimit;
		Clock clock;

		bool vsync;

		void* extraData;
	};

}

#endif