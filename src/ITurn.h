#ifndef ITURN
#define ITURN

class ITurn
{
	public:
		virtual bool turnStart(const float delta) = 0;
		virtual bool turnProgress(const float delta) = 0;
		virtual bool turnEnd(const float delta) = 0;
};

#endif // ITURN

