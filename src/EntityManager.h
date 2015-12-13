#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <vector>
#include <unordered_set>

class IEntity;

class EntityManager
{
	public:
		void add(IEntity *entity);
		void remove(IEntity *entity);

		std::unordered_set<IEntity *> entities() const;

	private:
		std::unordered_set<IEntity *> m_entities;
};

#endif // ENTITYMANAGER_H
