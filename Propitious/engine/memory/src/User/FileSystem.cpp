#include <Propitious/User/FileSystem.hpp>

namespace Propitious
{
	namespace
	{
		FileSystem fileSystemImplementation;
	}

	FileSystem& defaultFileSystem()
	{
		return fileSystemImplementation;
	}
}