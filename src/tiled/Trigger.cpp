#include "Trigger.h"

using namespace Tiled;

Trigger::Trigger(const std::string &name, const std::string &type, int x, int y, int width, int height)
	: sf::IntRect(x, y, width, height)
{
}

