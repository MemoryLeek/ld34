#ifndef ITURN
#define ITURN

class ITurn
{
	public:
		virtual void turnStart(const float delta) = 0;
		virtual void turnProgress(const float delta) = 0;
		virtual void turnIdle(const float delta) = 0;
};

#endif // ITURN

