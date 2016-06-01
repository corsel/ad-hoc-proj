#ifndef MOBILITY_H_INCLUDED
#define MOBILITY_H_INCLUDED

#include "ext-params.h"
#include "utils.h"

class Mobility
{
private:
	bool isWalking;
	int randTime;
	Utils::Vec2 randWypt;
	float randSpeed;
	static int counter;
	Utils::Vec2 posn;
	
	bool inProximity(Utils::Vec2 argOther);
	
public:
	Mobility(void);
	Mobility(Utils::Vec2 argPosn);
	Utils::Vec2 getPosn(void) const;
	Utils::Vec2 getRandWypt(void) const;
	void update(void);
};

#endif //MOBILITY_H_INCLUDED
