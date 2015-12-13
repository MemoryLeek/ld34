#ifndef MAPSELECTIONCONTEXT_H
#define MAPSELECTIONCONTEXT_H

#include <vector>
#include <string>

class MapSelectionContext
{
	public:
		MapSelectionContext();

		std::string current() const;

		void nextMap();

	private:
		std::vector<std::string> m_maps;

		int m_current;
};

#endif // MAPSELECTIONCONTEXT_H
