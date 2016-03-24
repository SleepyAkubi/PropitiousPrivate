#ifndef PROPITIOUS_RESOURCE_RESOURCEMANAGER_HPP
#define PROPITIOUS_RESOURCE_RESOURCEMANAGER_HPP

#include <Propitious/Common.hpp>
#include <Propitious/Containers/hashmap.hpp>

#include <memory>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <string>

namespace Propitious
{
	template <class Resource, class Identifier>
	class ResourceManager
	{
	public:
		using ResourceType = Resource;
		//using uptr = std::unique_ptr<Resource>;
		//using uniquify = make_unique<Resource>();

		ResourceManager(FileSystem& filesystem = defaultFileSystem())
			: m_resources()
			, filesystem(filesystem)
		{}
		~ResourceManager() {}

		ResourceManager(const ResourceManager&) = delete;
		ResourceManager& operator=(const ResourceManager&) = delete;

		bool insert(Identifier id, Resource* resource)
		{
			if (has(id))
				return false;

			auto inserted = m_resources.insert(std::make_pair(id, std::move(resource)));
			Assert(inserted.second);

			return true;
		}

		std::unique_ptr<Resource> erase(const Resource& resource)
		{
			auto found = std::find_if(m_resources.begin(),
				m_resources.end()
				[&resource](Resource* res)
			{
				return res.get();
			});

			if (found != m_resources.end())
			{
				auto result = std::move(*found);

				m_resources.erase(found);

				return result;
			}

			return nullptr;
		}

		std::unique_ptr<Resource> erase(Identifier id)
		{
			auto found = m_resources.find(id);

			if (found != m_resources.end())
			{
				auto result = std::move(*found);

				m_resources.erase(found);

				return result;
			}

			return nullptr;
		}

		bool has(const Resource& resource)
		{
			auto found = std::find_if(m_resources.begin(),
				m_resources.end()
				[&resource](Resource* res)
			{
				return res.get();
			});

			if (found != m_resources.end())
				return true;

			return false;
		}

		bool has(Identifier id)
		{
			auto found = m_resources.find(id);

			if (found != m_resources.end())
				return true;

			return false;
		}

		Resource& get(Identifier id)
		{
			auto found = m_resources.find(id);
			Assert(found != m_resources.end());
			return *found->second;
		}
		const Resource& get(Identifier id) const
		{
			auto found = m_resources.find(id);
			Assert(found != m_resources.end());
			return *found->second;
		}
		FileSystem& filesystem;
	private:
		std::unordered_map<Identifier, Resource*> m_resources;

	};
}

#endif
