#ifndef TURNHANDLER_H
#define TURNHANDLER_H

class EntityManager;

class TurnHandler
{
	public:
		TurnHandler(EntityManager &entityManager);

		void execute();

	private:
		EntityManager &m_entityManager;
};

#endif // TURNHANDLER_H
