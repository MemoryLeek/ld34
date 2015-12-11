#include "MenuDefinitionBuilder.h"
#include "Util.h"

MenuDefinitionBuilder::MenuDefinitionBuilder()
{

}

MenuDefinitionBuilder &MenuDefinitionBuilder::entry(const std::string &title)
{
	UNUSED(title);

	return *this;
}

