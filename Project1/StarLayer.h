#ifndef _STARLAYER_H
#define _STARLAYER_H
#include "Star.h"

class StarLayer {

private:
	static const int STAR_COUNT = 20;
	Star* mStars[STAR_COUNT];

public:
	StarLayer(int layer);
	~StarLayer();

	void Update();
	void Render();
};

#endif
