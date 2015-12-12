#ifndef ANIMATEDSPRITESEGMENT_H
#define ANIMATEDSPRITESEGMENT_H

class AnimatedSpriteSegment
{
	public:
		AnimatedSpriteSegment(int start, int end);

		int start() const;
		int end() const;

	private:
		int m_start;
		int m_end;
};

#endif // ANIMATEDSPRITESEGMENT_H
