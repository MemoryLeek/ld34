#ifndef MENUDEFINITIONBUILDER_H
#define MENUDEFINITIONBUILDER_H

#include <string>

#include "MenuDefinition.h"

class MenuDefinitionBuilder
{
	public:
		MenuDefinitionBuilder();

		MenuDefinitionBuilder &entry(const std::string &title);

	private:
		MenuDefinition m_definition;
};

#endif // MENUDEFINITIONBUILDER_H
