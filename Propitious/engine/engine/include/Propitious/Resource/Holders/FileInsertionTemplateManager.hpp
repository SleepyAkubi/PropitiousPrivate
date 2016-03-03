#ifndef PROPITIOUS_RESOURCE_FILEINSERTIONTEMPLATEMANAGER_HPP
#define PROPITIOUS_RESOURCE_FILEINSERTIONTEMPLATEMANAGER_HPP

#include <Propitious/Common.hpp>
#include <Propitious/Resource/ResourceManager.hpp>

#include <memory>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <string>

namespace Propitious
{
	template <class Resource, class Identifier>
	class FileInsertionTemplateManager : public ResourceManager<Resource, Identifier>
	{
	public:
		String getPath()
		{
			return path;
		}
		void setPath(const String& newPath)
		{
			path = newPath;
		}
	private:
		String path;
	};
}

#endif