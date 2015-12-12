#include "AnimatedSpriteSegment.h"

AnimatedSpriteSegment::AnimatedSpriteSegment(int start, int end)
	: m_start(start)
	, m_end(end)
{

}

int AnimatedSpriteSegment::start() const
{
	return m_start;
}

int AnimatedSpriteSegment::end() const
{
	return m_end;
}
