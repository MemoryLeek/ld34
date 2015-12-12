#ifndef ANIMATEDSPRITESTATE_H
#define ANIMATEDSPRITESTATE_H

class AnimatedSpriteSegment;

class AnimatedSpriteState
{
	friend class AnimatedSprite;

	public:
		AnimatedSpriteState(int frameRate);

		void setSegment(const int start, const int end);

	private:
		float m_timePerFrame;
		float m_timeSinceLastFrameChange;

		int m_start;
		int m_end;
		int m_current;
};

#endif // ANIMATEDSPRITESTATE_H
