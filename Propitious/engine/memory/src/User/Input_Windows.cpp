#include <Propitious/Common.hpp>

#ifdef PROPITIOUS_SYSTEM_WINDOWS

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "Shlwapi.lib")

#include <Propitious/User/Input.hpp>
#include <Propitious/Math/Vector2.hpp>
#include <Windows.h>
#include <conio.h>

namespace Propitious
{
	namespace Input
	{
		namespace Imp
		{
			HWND processID = nullptr;

			namespace KeyCodes
			{
				const i32 WindowsKey_BackSpace = 8;
				const i32 WindowsKey_Tab = 9;
				const i32 WindowsKey_Return = 13;
				const i32 WindowsKey_Shift = 16;
				const i32 WindowsKey_Control = 17;
				const i32 WindowsKey_Alt = 18;
				const i32 WindowsKey_Pause = 19;
				const i32 WindowsKey_CapsLock = 20;
				const i32 WindowsKey_Escape = 27;
				const i32 WindowsKey_Space = 32;
				const i32 WindowsKey_PageUp = 33;
				const i32 WindowsKey_PageDown = 34;
				const i32 WindowsKey_End = 35;
				const i32 WindowsKey_Home = 36;
				const i32 WindowsKey_Left = 37;
				const i32 WindowsKey_Up = 38;
				const i32 WindowsKey_Right = 39;
				const i32 WindowsKey_Down = 40;
				const i32 WindowsKey_Grave = 41;
				const i32 WindowsKey_PrintScreen = 44;
				const i32 WindowsKey_Insert = 45;
				const i32 WindowsKey_Delete = 46;

				const i32 WindowsKey_0 = 48;
				const i32 WindowsKey_1 = 49;
				const i32 WindowsKey_2 = 50;
				const i32 WindowsKey_3 = 51;
				const i32 WindowsKey_4 = 52;
				const i32 WindowsKey_5 = 53;
				const i32 WindowsKey_6 = 54;
				const i32 WindowsKey_7 = 55;
				const i32 WindowsKey_8 = 56;
				const i32 WindowsKey_9 = 57;
				const i32 WindowsKey_A = 65;
				const i32 WindowsKey_B = 66;
				const i32 WindowsKey_C = 67;
				const i32 WindowsKey_D = 68;
				const i32 WindowsKey_E = 69;
				const i32 WindowsKey_F = 70;
				const i32 WindowsKey_G = 71;
				const i32 WindowsKey_H = 72;
				const i32 WindowsKey_I = 73;
				const i32 WindowsKey_J = 74;
				const i32 WindowsKey_K = 75;
				const i32 WindowsKey_L = 76;
				const i32 WindowsKey_M = 77;
				const i32 WindowsKey_N = 78;
				const i32 WindowsKey_O = 79;
				const i32 WindowsKey_P = 80;
				const i32 WindowsKey_Q = 81;
				const i32 WindowsKey_R = 82;
				const i32 WindowsKey_S = 83;
				const i32 WindowsKey_T = 84;
				const i32 WindowsKey_U = 85;
				const i32 WindowsKey_V = 86;
				const i32 WindowsKey_W = 87;
				const i32 WindowsKey_X = 88;
				const i32 WindowsKey_Y = 89;
				const i32 WindowsKey_Z = 90;
				const i32 WindowsKey_LWin = 91;
				const i32 WindowsKey_RWin = 92;
				const i32 WindowsKey_Menu = 93;
				/* numerical key pad */
				const i32 WindowsKey_NumPad0 = 96;
				const i32 WindowsKey_NumPad1 = 97;
				const i32 WindowsKey_NumPad2 = 98;
				const i32 WindowsKey_NumPad3 = 99;
				const i32 WindowsKey_NumPad4 = 100;
				const i32 WindowsKey_NumPad5 = 101;
				const i32 WindowsKey_NumPad6 = 102;
				const i32 WindowsKey_NumPad7 = 103;
				const i32 WindowsKey_NumPad8 = 104;
				const i32 WindowsKey_NumPad9 = 105;
				const i32 WindowsKey_Multiply = 106;
				const i32 WindowsKey_Add = 107;
				const i32 WindowsKey_Subtract = 109;
				const i32 WindowsKey_Decimal = 110;
				const i32 WindowsKey_Divide = 111;
				/* function keys */
				const i32 WindowsKey_F1 = 112;
				const i32 WindowsKey_F2 = 113;
				const i32 WindowsKey_F3 = 114;
				const i32 WindowsKey_F4 = 115;
				const i32 WindowsKey_F5 = 116;
				const i32 WindowsKey_F6 = 117;
				const i32 WindowsKey_F7 = 118;
				const i32 WindowsKey_F8 = 119;
				const i32 WindowsKey_F9 = 120;
				const i32 WindowsKey_F10 = 121;
				const i32 WindowsKey_F11 = 122;
				const i32 WindowsKey_F12 = 123;
				const i32 WindowsKey_F13 = 124;
				const i32 WindowsKey_F14 = 125;
				const i32 WindowsKey_F15 = 126;
				const i32 WindowsKey_F16 = 127;

				const i32 WindowsKey_NumLock = 144;
				const i32 WindowsKey_ScrollLock = 145;
				const i32 WindowsKey_LShift = 160;
				const i32 WindowsKey_RShift = 161;
				const i32 WindowsKey_LControl = 162;
				const i32 WindowsKey_RControl = 163;
				const i32 WindowsKey_LAlt = 164;
				const i32 WindowsKey_RAlt = 165;
				const i32 WindowsKey_SemiColon = 186;
				const i32 WindowsKey_Equals = 187;
				const i32 WindowsKey_Comma = 188;
				const i32 WindowsKey_UnderScore = 189;
				const i32 WindowsKey_Period = 190;
				const i32 WindowsKey_Slash = 191;
				const i32 WindowsKey_BackSlash = 220;
				const i32 WindowsKey_RightBrace = 221;
				const i32 WindowsKey_LeftBrace = 219;
				const i32 WindowsKey_Apostrophe = 222;
			}

			static i32 WinKey[]
			{
				KeyCodes::WindowsKey_A,
				KeyCodes::WindowsKey_B,
				KeyCodes::WindowsKey_C,
				KeyCodes::WindowsKey_D,
				KeyCodes::WindowsKey_E,
				KeyCodes::WindowsKey_F,
				KeyCodes::WindowsKey_G,
				KeyCodes::WindowsKey_H,
				KeyCodes::WindowsKey_I,
				KeyCodes::WindowsKey_J,
				KeyCodes::WindowsKey_K,
				KeyCodes::WindowsKey_L,
				KeyCodes::WindowsKey_M,
				KeyCodes::WindowsKey_N,
				KeyCodes::WindowsKey_O,
				KeyCodes::WindowsKey_P,
				KeyCodes::WindowsKey_Q,
				KeyCodes::WindowsKey_R,
				KeyCodes::WindowsKey_S,
				KeyCodes::WindowsKey_T,
				KeyCodes::WindowsKey_U,
				KeyCodes::WindowsKey_V,
				KeyCodes::WindowsKey_W,
				KeyCodes::WindowsKey_X,
				KeyCodes::WindowsKey_Y,
				KeyCodes::WindowsKey_Z,
				KeyCodes::WindowsKey_0,
				KeyCodes::WindowsKey_1,
				KeyCodes::WindowsKey_2,
				KeyCodes::WindowsKey_3,
				KeyCodes::WindowsKey_4,
				KeyCodes::WindowsKey_5,
				KeyCodes::WindowsKey_6,
				KeyCodes::WindowsKey_7,
				KeyCodes::WindowsKey_8,
				KeyCodes::WindowsKey_9,
				KeyCodes::WindowsKey_Escape,
				KeyCodes::WindowsKey_LControl,
				KeyCodes::WindowsKey_LShift,
				KeyCodes::WindowsKey_LAlt,
				KeyCodes::WindowsKey_LWin,
				KeyCodes::WindowsKey_RControl,
				KeyCodes::WindowsKey_RShift,
				KeyCodes::WindowsKey_RAlt,
				KeyCodes::WindowsKey_RWin,
				KeyCodes::WindowsKey_Menu,
				KeyCodes::WindowsKey_LeftBrace,
				KeyCodes::WindowsKey_RightBrace,
				KeyCodes::WindowsKey_SemiColon,
				KeyCodes::WindowsKey_Comma,
				KeyCodes::WindowsKey_Period,
				KeyCodes::WindowsKey_Apostrophe,
				KeyCodes::WindowsKey_Slash,
				KeyCodes::WindowsKey_BackSlash,
				KeyCodes::WindowsKey_Equals,
				KeyCodes::WindowsKey_Subtract,
				KeyCodes::WindowsKey_Space,
				KeyCodes::WindowsKey_Return,
				KeyCodes::WindowsKey_BackSpace,
				KeyCodes::WindowsKey_Tab,
				KeyCodes::WindowsKey_Grave,
				KeyCodes::WindowsKey_PageUp,
				KeyCodes::WindowsKey_PageDown,
				KeyCodes::WindowsKey_End,
				KeyCodes::WindowsKey_Home,
				KeyCodes::WindowsKey_Insert,
				KeyCodes::WindowsKey_Delete,
				KeyCodes::WindowsKey_Add,
				KeyCodes::WindowsKey_Subtract,
				KeyCodes::WindowsKey_Multiply,
				KeyCodes::WindowsKey_Divide,
				KeyCodes::WindowsKey_Left,
				KeyCodes::WindowsKey_Right,
				KeyCodes::WindowsKey_Up,
				KeyCodes::WindowsKey_Down,
				KeyCodes::WindowsKey_NumPad0,
				KeyCodes::WindowsKey_NumPad1,
				KeyCodes::WindowsKey_NumPad2,
				KeyCodes::WindowsKey_NumPad3,
				KeyCodes::WindowsKey_NumPad4,
				KeyCodes::WindowsKey_NumPad5,
				KeyCodes::WindowsKey_NumPad6,
				KeyCodes::WindowsKey_NumPad7,
				KeyCodes::WindowsKey_NumPad8,
				KeyCodes::WindowsKey_NumPad9,
				KeyCodes::WindowsKey_Return,
				KeyCodes::WindowsKey_F1,
				KeyCodes::WindowsKey_F2,
				KeyCodes::WindowsKey_F3,
				KeyCodes::WindowsKey_F4,
				KeyCodes::WindowsKey_F5,
				KeyCodes::WindowsKey_F6,
				KeyCodes::WindowsKey_F7,
				KeyCodes::WindowsKey_F8,
				KeyCodes::WindowsKey_F9,
				KeyCodes::WindowsKey_F10,
				KeyCodes::WindowsKey_F11,
				KeyCodes::WindowsKey_F12,
				KeyCodes::WindowsKey_F13,
				KeyCodes::WindowsKey_F14,
				KeyCodes::WindowsKey_F15,
				KeyCodes::WindowsKey_Pause,
			};
		}

		bool getKey(Key key)
		{
			return (GetAsyncKeyState(Imp::WinKey[static_cast<i32>(key)])) != 0;
		}

		// TEMP

		bool getMouseButton(MouseButton button)
		{
			return (GetAsyncKeyState(Imp::WinKey[static_cast<i32>(button)])) != 0;
		}

		Vector2 getScrollOffset()
		{
			// TODO: this.
			return Vector2{ (f32)Imp::scrollX, (f32)Imp::scrollY };
		}

		Vector2 getCursorPosition()
		{
			POINT p;
			ScreenToClient(Imp::processID, &p);

			return Vector2{ (f32)p.x, (f32)p.y };
		}
		//Vector2 getCursorPosition(Window& realtiveTo)
		//{
		//	int x, y;
		//	SDL_GetMouseState(&x, &y);
		//
		//	Vector2 windowPos = realtiveTo.getPosition();
		//
		//	return{ (f32)x - windowPos.x, (f32)y - windowPos.y};
		//}

		void setCursorPosition(const Vector2& position)
		{
			SetCursorPos((i32)position.x, (i32)position.y);
		}

	}
}

#endif