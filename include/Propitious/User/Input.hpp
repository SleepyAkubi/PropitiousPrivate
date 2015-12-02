#ifndef PROPITIOUS_USER_INPUT_HPP
#define PROPITIOUS_USER_INPUT_HPP

#include <Propitious/Common.hpp>
#include <Propitious/Graphics/Window.hpp>

#include <Propitious/Math/Vector2.hpp>

namespace Propitious
{
	enum class PROPITIOUS_EXPORT Key
	{
		Unknown = -1, // Unhandled key
		A = 0,        // The A key
		B,            // The B key
		C,            // The C key
		D,            // The D key
		E,            // The E key
		F,            // The F key
		G,            // The G key
		H,            // The H key
		I,            // The I key
		J,            // The J key
		K,            // The K key
		L,            // The L key
		M,            // The M key
		N,            // The N key
		O,            // The O key
		P,            // The P key
		Q,            // The Q key
		R,            // The R key
		S,            // The S key
		T,            // The T key
		U,            // The U key
		V,            // The V key
		W,            // The W key
		X,            // The X key
		Y,            // The Y key
		Z,            // The Z key
		Num0,         // The 0 key
		Num1,         // The 1 key
		Num2,         // The 2 key
		Num3,         // The 3 key
		Num4,         // The 4 key
		Num5,         // The 5 key
		Num6,         // The 6 key
		Num7,         // The 7 key
		Num8,         // The 8 key
		Num9,         // The 9 key
		Escape,       // The Escape key
		LeftControl,     // The left Control key
		LeftShift,       // The left Shift key
		LeftAlt,         // The left Alt key
		LeftSuper,      // The left OS specific key: window (Windows and Linux), apple (MacOS X), ...
		RightControl,     // The right Control key
		RightShift,       // The right Shift key
		RightAlt,         // The right Alt key
		RightSuper,      // The right OS specific key: window (Windows and Linux), apple (MacOS X), ...
		Menu,         // The Menu key
		LeftBracket,     // The [ key
		RightBracket,     // The ] key
		SemiColon,    // The ; key
		Comma,        // The , key
		Period,       // The . key
		Apostrophe,   // The ' key
		Slash,        // The / key
		BackSlash,    // The \ key
		Equal,        // The = key
		Minus,        // The - key
		Space,        // The Space key
		Return,       // The Return key
		BackSpace,    // The Backspace key
		Tab,          // The Tabulation key
		GraveAccent,  // The ` key
		PageUp,       // The Page up key
		PageDown,     // The Page down key
		End,          // The End key
		Home,         // The Home key
		Insert,       // The Insert key
		Delete,       // The Delete key
		Add,          // The + key
		Subtract,     // The - key
		Multiply,     // The * key
		Divide,       // The / key
		Left,         // Left arrow
		Right,        // Right arrow
		Up,           // Up arrow
		Down,         // Down arrow
		Numpad0,      // The numpad 0 key
		Numpad1,      // The numpad 1 key
		Numpad2,      // The numpad 2 key
		Numpad3,      // The numpad 3 key
		Numpad4,      // The numpad 4 key
		Numpad5,      // The numpad 5 key
		Numpad6,      // The numpad 6 key
		Numpad7,      // The numpad 7 key
		Numpad8,      // The numpad 8 key
		Numpad9,      // The numpad 9 key
		NumpadEnter,  // The numpad Enter key
		F1,           // The F1 key
		F2,           // The F2 key
		F3,           // The F3 key
		F4,           // The F4 key
		F5,           // The F5 key
		F6,           // The F6 key
		F7,           // The F7 key
		F8,           // The F8 key
		F9,           // The F9 key
		F10,          // The F10 key
		F11,          // The F11 key
		F12,          // The F12 key
		F13,          // The F13 key
		F14,          // The F14 key
		F15,          // The F15 key
		Pause,        // The Pause key


		KeyCount      // Keep last -- the total number of keyboard keys
	};

	enum PROPITIOUS_EXPORT MouseButton : u8
	{
		Mouse_1 = 0,
		Mouse_2 = 1,
		Mouse_3 = 2,
		Mouse_4 = 3,
		Mouse_5 = 4,
		Mouse_6 = 5,
		Mouse_7 = 6,
		Mouse_8 = 7,

		Mouse_Left = Mouse_1,
		Mouse_Right = Mouse_2,
		Mouse_Middle = Mouse_3,

		Mouse_Last = Mouse_8,
		Mouse_First = Mouse_1
	};

	enum class PROPITIOUS_EXPORT CursorMode
	{
		Normal,
		Hidden,
		Disabled
	};

	namespace Input
	{
		namespace Imp
		{
			extern f64 scrollX;
			extern f64 scrollY;
		}

		PROPITIOUS_EXPORT bool getKey(Key key);

		PROPITIOUS_EXPORT bool getMouseButton(MouseButton button);

		PROPITIOUS_EXPORT Vector2 getScrollOffset();

		PROPITIOUS_EXPORT Vector2 getCursorPosition();
		//useful Vector2 getCursorPosition(Window& relativeTo);

		PROPITIOUS_EXPORT void setCursorPosition(const Vector2& position);

	}
}

#endif
