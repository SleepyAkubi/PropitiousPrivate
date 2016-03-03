#ifndef PROPITIOUS_USB_DEVICE_HPP
#define PROPITIOUS_USB_DEVICE_HPP

#include <Propitious/Common.hpp>

namespace Propitious
{
	namespace USB
	{
		struct DeviceHandle;

		
#ifdef PROPITIOUS_SYSTEM_WINDOWS
		struct DeviceHandle
		{
			void* handle = INVALID_HANDLE_VALUE;
			DCB deviceControlBlock = { 0 };
			HANDLE threadHandle;
		};
#endif

		struct Device
		{
			b8 isValid = false;
			DeviceHandle handle{};
			std::function<void(void* data)> readCallback;
		};

		bool PROPITIOUS_EXPORT make(Device& usbdevice, std::function<void(void* data)> readCallback, u16 portNumber, u32 baudRate = 9600, u16 byteSize = 8, b8 parity = false, u16 stopBits = 1, b8 blockOtherDevices = true);

		namespace Implementation
		{
			bool PROPITIOUS_EXPORT write(Device& usbdevice, const void* data, u8 length);
		}


		template <typename T>
		bool write(Device& usbdevice, const T* data, Allocator::vol size)
		{
			return Implementation::write(usbdevice, data, size);
		}
	}
}

#endif
