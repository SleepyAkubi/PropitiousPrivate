#ifndef PROPITIOUS_INPUT_FILESYSTEM_HPP
#define PROPITIOUS_INPUT_FILESYSTEM_HPP

#include <Propitious/Common.hpp>
#include <Propitious/Containers/String.hpp>
#include <Propitious/Memory/Common.hpp>

#include <new>
#include <utility>

namespace Propitious
{
	class FileSystem
	{
	public:
		FileSystem() = default;
		virtual ~FileSystem() = default;

		inline FILE* loadFile(const String& filename)
		{
			return fopen(cString(prefixPath + "/" + filename), "rb");
		}

		String prefixPath;
	};

	PROPITIOUS_MEMORY_EXPORT FileSystem& defaultFileSystem();
}
#endif
