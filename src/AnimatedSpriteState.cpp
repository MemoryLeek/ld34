#include "AnimatedSpriteState.h"
#include "AnimatedSpriteSegment.h"

AnimatedSpriteState::AnimatedSpriteState(int frameRate)
	: m_timePerFrame(1.f / frameRate)
	, m_timeSinceLastFrameChange(0)
	, m_start(0)
	, m_end(0)
{

}

void AnimatedSpriteState::setSegment(const int start, const int end)
{
	m_start = start;
	m_end = end;
	m_current = m_start;
}
