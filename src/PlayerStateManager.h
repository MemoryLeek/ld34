#ifndef PLAYERSTATEMANAGER_H
#define PLAYERSTATEMANAGER_H

class PlayerState
{
	public:
		PlayerState();

		bool isGoalReached() const;
		void setIsGoalReached(bool isGoalReached);

	private:
		bool m_isGoalReached;
};

#endif // PLAYERSTATEMANAGER_H
