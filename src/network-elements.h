#include "utils.h"
#include <list>

class Node
{
private: 
	static bool showAnnotations;
	float range;
	Utils::Vec2 posn;
	std::list<Node*> contactNodes;
	
public:
	Node(void);
	Node(Utils::Vec2 argPosn, float argRange);
	void toggleAnnotations(void);
	void render(void);
};
