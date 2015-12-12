#ifndef TRIGGER_H
#define TRIGGER_H

#include <string>

#include <SFML/Graphics/Rect.hpp>

namespace Tiled
{
	class Trigger : public sf::IntRect
	{
		public:
			Trigger(const std::string& name, const std::string& type, int x, int y, int width, int height);
	};
}

#endif // TRIGGER_H
