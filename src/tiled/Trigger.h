#ifndef TRIGGER_H
#define TRIGGER_H

#include <map>
#include <string>

#include <SFML/Graphics/Rect.hpp>

namespace Tiled
{
	class Trigger : public sf::IntRect
	{
		public:
			Trigger(const std::string& name, const std::string& type, int x, int y, int width, int height);

			std::string type() const;

			std::string property(const std::string& name) const;
			void setProperty(const std::string& name, const std::string& value);

		private:
			std::string m_type;
			std::map<std::string, std::string> m_properties;
	};
}

#endif // TRIGGER_H
