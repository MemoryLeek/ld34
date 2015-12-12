#ifndef TURNHANDLER_H
#define TURNHANDLER_H

class EntityManager;
class ITurn;

using Function = void (ITurn::*)(const float);

const float TURN_LENGTH = 0.25f;

class TurnHandler
{
	public:
		TurnHandler(EntityManager &entityManager);

		void update(const float delta);
		void execute();

		bool isRunning() const;

	private:
		float getRemainingDelta(const float delta) const;

		void raiseEvent(Function function, const float delta);

		EntityManager &m_entityManager;

		float m_remaining;
};

#endif // TURNHANDLER_H
