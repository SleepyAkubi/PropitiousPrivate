#include <Propitious/Common.hpp>

#if defined(PROPITIOUS_SYSTEM_WINDOWS)

#pragma comment(lib, "gdi32.lib")

#include <Propitious/Graphics/Window.hpp>
#include <Propitious/Math/Vector2.hpp>
#include <Propitious/Graphics/OpenGL.hpp>
#include <Propitious/Math/Time.hpp>
#include <Propitious/Math/Constants.hpp>
#include <Propitious/Resource/Holders.hpp>
#include <Propitious/Utility/File.hpp>
#include <vector>

#include <Propitious/Graphics/OpenGL.hpp>

namespace Propitious
{
	static Window* currentInstance = nullptr;

	struct WindowHandle
	{
		HWND handle;

		HDC hardwareDeviceContext;
		HDC previousHardwareDeviceContext;

		HGLRC openGLRenderingContext;
		HGLRC previousOpenGLRenderingContext;
	};

	Window::Window()
	{
		currentInstance = this;
	}

	LRESULT CALLBACK windowMessageProcessor(HWND handle, UINT message, WPARAM messageParameter1, LPARAM messageParameter2)
	{
		WindowHandle* windowHandle = (WindowHandle*)currentInstance->extraData;
		switch (message)
		{
		case WM_CREATE:
		{
			windowHandle->hardwareDeviceContext = GetDC(handle);

			PIXELFORMATDESCRIPTOR pixelFormat;
			ZeroMemory(&pixelFormat, sizeof(pixelFormat));

			pixelFormat.nSize = sizeof(pixelFormat);
			pixelFormat.nVersion = 1;
			pixelFormat.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
			pixelFormat.iPixelType = PFD_TYPE_RGBA;
			pixelFormat.cColorBits = 24;
			pixelFormat.cDepthBits = 16;
			pixelFormat.iLayerType = PFD_MAIN_PLANE;

			i32 formatHandle = ChoosePixelFormat(windowHandle->hardwareDeviceContext, &pixelFormat);
			SetPixelFormat(windowHandle->hardwareDeviceContext, formatHandle, &pixelFormat);

			windowHandle->openGLRenderingContext = wglCreateContext(windowHandle->hardwareDeviceContext);

			windowHandle->previousHardwareDeviceContext = wglGetCurrentDC();
			windowHandle->previousOpenGLRenderingContext = wglGetCurrentContext();

			wglMakeCurrent(windowHandle->hardwareDeviceContext, windowHandle->openGLRenderingContext);
		}
		break;
		case WM_DESTROY:
		case WM_QUIT:
		case WM_CLOSE:
		{
			currentInstance->close();
			PostQuitMessage(0);
		}
		break;
		}

		return DefWindowProc(handle, message, messageParameter1, messageParameter2);
	}

	void Window::create(const std::string& title,
		const Dimensions& dimensions,
		const WindowStyle style)
	{
		extraData = defaultAllocator().allocate(sizeof(WindowHandle));
		WindowHandle* windowHandle = (WindowHandle*)extraData;
		const a8* cTitle = title.c_str();

		std::string windowClass = "PropitiousWindow" + title;
		const a8* cWindowClass = windowClass.c_str();

		HINSTANCE currentInstance = GetModuleHandle(NULL);

		MSG message;
		WNDCLASS WindowClass;

		std::string iconPath = (getPathToExe() + "\\game.ico");
		const a8* cIconPath = iconPath.c_str();

		HICON gameIconSmall = (HICON)LoadImage(
			NULL,
			cIconPath,
			IMAGE_ICON,
			16,
			16,
			LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_SHARED
			);

		WindowClass.cbClsExtra = 0;
		WindowClass.cbWndExtra = 0;
		WindowClass.hbrBackground = (HBRUSH)GetStockObject(DKGRAY_BRUSH);
		WindowClass.hCursor = LoadCursor(currentInstance, IDC_ARROW);
		WindowClass.hIcon = gameIconSmall;
		WindowClass.hInstance = currentInstance;
		WindowClass.lpfnWndProc = windowMessageProcessor;
		WindowClass.lpszClassName = cWindowClass;
		WindowClass.lpszMenuName = nullptr;
		WindowClass.style = CS_VREDRAW | CS_HREDRAW;

		if (!RegisterClass(&WindowClass))
		{
			// Error Handling
		}

		windowHandle->handle = CreateWindow(
			cWindowClass,
			cTitle,
			WS_MINIMIZEBOX | WS_VISIBLE,
			NULL,
			NULL,
			dimensions.width,
			dimensions.height,
			nullptr,
			nullptr,
			currentInstance,
			nullptr
			);

		if (!windowHandle->handle)
		{
			// Error Handling
		}

		HICON gameIcon = (HICON)LoadImage(
			NULL,
			cIconPath,
			IMAGE_ICON,
			64,
			64,
			LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_SHARED
			);

		SendMessage(windowHandle->handle, WM_SETICON, ICON_SMALL, (LPARAM)gameIconSmall);
		SendMessage(windowHandle->handle, WM_SETICON, ICON_BIG, (LPARAM)gameIcon);

		SendMessage(GetWindow(windowHandle->handle, GW_OWNER), WM_SETICON, ICON_SMALL, (LPARAM)gameIconSmall);
		SendMessage(GetWindow(windowHandle->handle, GW_OWNER), WM_SETICON, ICON_BIG, (LPARAM)gameIcon);

		while (PeekMessage(&message, nullptr, 0, 0, PM_NOREMOVE))
		{
			if (GetMessage(&message, nullptr, 0, 0))
			{
				break;
			}
		}
		DispatchMessage(&message);
		TranslateMessage(&message);

		setVisible(true);
		setFramerateLimit(0);

		aspectRatio = (f32)dimensions.width / (f32)dimensions.height;
	}


	void Window::close()
	{
		WindowHandle* windowHandle = (WindowHandle*)extraData;
		wglMakeCurrent(windowHandle->previousHardwareDeviceContext, windowHandle->previousOpenGLRenderingContext);
		wglDeleteContext(windowHandle->openGLRenderingContext);
		ReleaseDC(windowHandle->handle, windowHandle->hardwareDeviceContext);
		DestroyWindow(windowHandle->handle);
	}

	bool Window::isOpen() const
	{
		return true;
	}

	const Vector2 Window::getPosition() const
	{
		return Vector2{ 0, 0 };
	}
	void Window::setPosition(const Vector2& position)
	{
	}

	const Dimensions Window::getSize() const
	{
		WindowHandle* windowHandle = (WindowHandle*)extraData;
		RECT windowBox;
		GetWindowRect(windowHandle->handle, &windowBox);

		int width = windowBox.right - windowBox.left;
		int height = windowBox.bottom - windowBox.top;

		return Dimensions(width, height);
	}
	void Window::setSize(const Dimensions& dimensions)
	{
	}

	const std::string Window::getTitle() const
	{
		WindowHandle* windowHandle = (WindowHandle*)extraData;
		a8* title = nullptr;
		GetWindowText(windowHandle->handle, title, 2048);
		return title;
	}
	void Window::setTitle(const std::string& title)
	{
		WindowHandle* windowHandle = (WindowHandle*)extraData;
		const a8* cTitle = title.c_str();
		SetWindowText(windowHandle->handle, cTitle);
	}

	const bool Window::getVisible() const
	{
		return true;
	}

	void Window::setVisible(bool visible)
	{
	}

	const bool Window::getVerticalSyncEnabled() const
	{
		return vsync;
	}
	void Window::setVerticalSyncEnabled(bool vsync)
	{
		this->vsync = vsync;
	}

	void Window::setFramerateLimit(u32 limit)
	{
		if (limit > 0)
			frameTimeLimit = seconds(1.0f / (f32)limit);
		else
			frameTimeLimit = Time(seconds(0));
	}

	WindowMode Window::getFullscreen()
	{
		// TODO: FIX ME
		return WindowMode::Windowed;
	}

	void Window::setFullscreen(WindowMode fullscreen)
	{
	}

	void Window::display()
	{
		WindowHandle* windowHandle = (WindowHandle*)extraData;
		SwapBuffers(windowHandle->hardwareDeviceContext);

		if (frameTimeLimit != Time(0))
		{
			Time::snooze(frameTimeLimit - clock.getElapsedTime());
			clock.restart();
		}
	}
}

#endif