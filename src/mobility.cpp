#include "mobility.h"

const int MIN_SPEED = 1;
const int MAX_SPEED = 4;
const int MAX_WAIT = 500;

//Mobility class
bool Mobility::inProximity(Utils::Vec2 argOther)
{
	if (Utils::Vec2::getSqrDistance(posn, argOther) <= Utils::EPSILON * Utils::EPSILON)
		return true;
	else
		return false;	
}
Mobility::Mobility() 
{
	Mobility(Utils::Vec2(0.0f, 0.0f));
}

Mobility::Mobility(Utils::Vec2 argPosn)
: posn(argPosn), isWalking(true) 
{
	randWypt = Utils::Vec2((rand() % (int)FIELD_SIZE.x) - FIELD_SIZE.x / 2.0f, (rand() % (int)FIELD_SIZE.y) - FIELD_SIZE.y / 2.0f);
	randSpeed = 1.0f + rand() % MAX_SPEED;	
}
Utils::Vec2 Mobility::getPosn() const
{
	return posn;
}
Utils::Vec2 Mobility::getRandWypt() const
{
	return randWypt;
}
void Mobility::update()
{
	if (isWalking)
	{
		if (inProximity(randWypt))
		{
			isWalking = false;
			randTime = rand() % MAX_WAIT;
			//std::cout << "debug - Node::updateMovement: node[" << this << "] proximity...\n\trandTime: " << randTime << std::endl;
		}
		else
		{
			Utils::Vec2 tempHeading(randWypt.x - posn.x, randWypt.y - posn.y);
			tempHeading = tempHeading.getNormalized();
			tempHeading *= randSpeed;
			posn += tempHeading / 100.0f;
		}
	}
	else
	{
		if (randTime > 0)
		{
			--randTime;
		}
		else
		{
			randWypt = Utils::Vec2((rand() % (int)FIELD_SIZE.x) - FIELD_SIZE.x / 2.0f, (rand() % (int)FIELD_SIZE.y) - FIELD_SIZE.y / 2.0f);
			randSpeed = rand() % (MAX_SPEED - MIN_SPEED) + MIN_SPEED;
			isWalking = true;
			//std::cout << "debug - Node::updateMovement: node[" << this << "] start walking...\n\trandWypt: <" << randWypt.x << ", " << randWypt.y << ">\n\trandSpeed: " << randSpeed << "\n";
		}
	}
}
