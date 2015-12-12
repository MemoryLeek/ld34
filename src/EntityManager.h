#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <vector>
#include <unordered_set>

class Entity;

class EntityManager
{
	public:
		void add(Entity *entity);
		void remove(Entity *entity);

		std::unordered_set<Entity *> entities() const;

	private:
		std::unordered_set<Entity *> m_entities;
};

#endif // ENTITYMANAGER_H
