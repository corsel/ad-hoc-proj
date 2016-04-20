#ifndef NETWORK_ELEMENTS_H_INCLUDED
#define NETWORK_ELEMENTS_H_INCLUDED

#include "ext-params.h"
#include "utils.h"
#include <vector>

class Node
{
private: 
	bool isWalking;
	int randTime;
	Utils::Vec2 randWypt;
	float randSpeed;
	
	static int counter;
	int id;
	float range;
	Utils::Vec2 posn;
	std::vector<Node*> contactNodes;
	
	bool inProximity(Utils::Vec2 argOther);
	
public:
	Node(void);
	Node(Utils::Vec2 argPosn, float argRange);
	Utils::Vec2 getPosn(void);
	void updateMovement(void);
	void updateContacts(void);
	void renderContacts(void);
};

extern std::vector<Node> nodeVector;

#endif //NETWORK_ELEMENTS_H_INCLUDED
