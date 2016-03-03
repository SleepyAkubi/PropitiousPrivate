#include <Propitious/USB/Device.hpp>
#include <Propitious/Containers/String.hpp>
#include <Windows.h>

#include <string> // REMOVE THIS WHEN PROP. STRING IS DONE

namespace Propitious
{
	namespace USB
	{
		bool make(Device& usbdevice, std::function<void(void* data)> readCallback, u16 portNumber, u32 baudRate, u16 byteSize, b8 parity, u16 stopBits, b8 blockOtherDevices)
		{
			usbdevice.readCallback = readCallback;
			std::string portName = "\\\\.\\COM" + std::to_string(portNumber);
			const a8* portNameCString = portName.c_str();
			usbdevice.handle.handle =
				CreateFileA(
					portNameCString,
					GENERIC_READ | GENERIC_WRITE,
					!blockOtherDevices,
					0,
					OPEN_EXISTING,
					0,
					0);
			std::cout << usbdevice.handle.handle << std::endl;
			if (usbdevice.handle.handle == INVALID_HANDLE_VALUE)
			{
				MessageBoxA(0, "INVALID HANDLE!", "Error!", MB_OK);
				u8 test = (i8)GetLastError();
				return false;
			}

			usbdevice.handle.deviceControlBlock.DCBlength = sizeof(DCB);
			if (!GetCommState(usbdevice.handle.handle, &usbdevice.handle.deviceControlBlock))
			{
				MessageBoxA(0, "FAILED TO GET COMM STATE!", "Error!", MB_OK);
				u8 test = (i8)GetLastError();
				return false;
			}

			usbdevice.handle.deviceControlBlock.BaudRate = baudRate;
			usbdevice.handle.deviceControlBlock.ByteSize = (BYTE)byteSize;
			usbdevice.handle.deviceControlBlock.Parity = parity;
			usbdevice.handle.deviceControlBlock.fParity = parity;
			if (stopBits == 1)
				usbdevice.handle.deviceControlBlock.StopBits = ONESTOPBIT;
			else if (stopBits == 2)
				usbdevice.handle.deviceControlBlock.StopBits = TWOSTOPBITS;
			else
				usbdevice.handle.deviceControlBlock.StopBits = ONE5STOPBITS;

			if (!SetCommState(usbdevice.handle.handle, &usbdevice.handle.deviceControlBlock))
			{
				MessageBoxA(0, "FAILED TO SET COMM STATE!", "Error!", MB_OK);
				u8 test = (i8)GetLastError();
				return false;
			}

			if (!SetCommMask(usbdevice.handle.handle, EV_TXEMPTY | EV_RXCHAR))
			{
				MessageBoxA(0, "FAILED TO SET COMM MASK!", "Error!", MB_OK);
				u8 test = (i8)GetLastError();
				return false;
			}

			return usbdevice.isValid = true;
		}

		b8 Implementation::write(Device& usbdevice, const void* data, u8 length)
		{
			if (!usbdevice.isValid)
				return false;
			if (usbdevice.handle.handle == INVALID_HANDLE_VALUE)
				return false;
			if (data == nullptr)
				return false;
			DWORD bytesWritten;
			b8 response = WriteFile(usbdevice.handle.handle, data, length, &bytesWritten, 0);
			if (response == false)
			{
				u8 test = (i8)GetLastError();
				std::string text = "Failed to write: " + std::to_string(test);
				MessageBoxA(0, text.c_str(), "Error!", MB_OK);
				return false;
			}
			return true;
		}
	}
}