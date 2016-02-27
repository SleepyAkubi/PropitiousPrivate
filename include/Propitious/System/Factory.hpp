#ifndef PROPITIOUS_SYSTEM_FACTORY_HPP
#define PROPITIOUS_SYSTEM_FACTORY_HPP

#include <Propitious/Common.hpp>
#include <Propitious/Containers/hashmap.hpp>

namespace Propitious
{
	struct FactoryEntry
	{
		const a8* reference;
		void*(const a8*) functionPtr;
	};

	struct Factory
	{
		HashMap<> foo;
	};

	Factory factory;

	class FactoryDefinition
	{
		FactoryDefinition()
		{

		}
	};

#define DECLARE_CLASS(name, classname)\n
	static FactoryDefinition()
}

#endif