#ifndef NETWORK_ELEMENTS_H_INCLUDED
#define NETWORK_ELEMENTS_H_INCLUDED

#include "ext-params.h"
#include "utils.h"
#include "packet.h"
#include "mobility.h"
#include <vector>

const int NUM_PACKETS = 3;

class Node
{
private: 
	Mobility mobility;
	Buffer buffer;
	PacketGenerator *generator;
	int id;
	float range;
	std::vector<Node*> contactNodes;
	
	void updateMovement(void);
	void updateContacts(void);
	void renderContacts(void);
	void renderWypts(void);
	
public:
	Node(void);
	Node(Utils::Vec2 argPosn, float argRange);
	~Node(void);
	Utils::Vec2 getPosn(void);
	void update(void);
	void renderPackets(int argPacketId = -1) const;
};


class NodeContainer //Singleton
{
private:
	static NodeContainer *instance;
	std::vector<Node*> nodeVector;
	static int idCounter;
	
	NodeContainer(void);
	
public:
	static NodeContainer* getInstance(void);
	void init(int argNumNodes);
	void update(void);
	int getNewId(void);
	static int getRandomDst(int argExcludedId);
	std::vector<Node*> getNodeVector(void) const;
};

#endif //NETWORK_ELEMENTS_H_INCLUDED
