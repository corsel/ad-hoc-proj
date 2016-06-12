#include "network-elements.h"

//Node class
void Node::updateMovement()
{
	mobility.update();
}
void Node::updateContacts()
{
	std::vector<Node*> tempNodeVector = NodeContainer::getInstance()->getNodeVector();
	contactNodes.clear();
	for (int i = 0; i < tempNodeVector.size(); i++)
	{
		if (tempNodeVector[i]->id == id)
			continue;
		if (Utils::Vec2::getSqrDistance(getPosn(), tempNodeVector[i]->getPosn()) <= WIRELESS_RANGE * WIRELESS_RANGE)
		{
			contactNodes.push_back(tempNodeVector[i]);
		}
	}
	for (int i = 0; i < contactNodes.size(); i++)
	{
		//std::cout << "debug - Node::updateContacts: syncing buffers: " << id << " - " << contactNodes[i]->id << std::endl;
		contactNodes[i]->buffer.syncBuffers(&buffer);
	}
}
void Node::renderContacts()
{
	glPushAttrib(GL_LINE_BIT);
	glPushMatrix();
	glLineWidth(2.0f);
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.5f, 0.0f);
	for (int i = 0; i < contactNodes.size(); i++)
	{
		glVertex2f(getPosn().x, getPosn().y);
		glVertex2f(contactNodes[i]->getPosn().x, contactNodes[i]->getPosn().y);
	}
	glEnd();
	glPopMatrix();
	glPopAttrib();
}
void Node::renderWypts()
{
	//Waypoints
	glPushAttrib(GL_LINE_BIT);
	glPushMatrix();
	glColor3f(0.25f, 0.25f, 0.3f);
	glVertex2f(getPosn().x, getPosn().y);
	glVertex2f(mobility.getRandWypt().x, mobility.getRandWypt().y);
	glEnd();
	glPopMatrix();
	glPopAttrib();
}
Node::Node() 
: range(3.0f)
{
	generator = new NPacketGenerator(NUM_PACKETS);
	id = NodeContainer::getInstance()->getNewId();
}
Node::Node(Utils::Vec2 argPosn, float argRange)
: range(argRange), mobility(Mobility(argPosn))
{
	generator = new NPacketGenerator(NUM_PACKETS);
	id = NodeContainer::getInstance()->getNewId();
}
Node::~Node() {}
Utils::Vec2 Node::getPosn()
{
	return mobility.getPosn();
}
void Node::update()
{
	updateMovement();
	updateContacts();
	
	Packet *tempPacket = generator->update(id, NodeContainer::getRandomDst(id));
	if (tempPacket)
		buffer.push(*tempPacket);
	
	if (showContacts)
		renderContacts();
	if (showWypts)
		renderWypts();
}
void Node::renderPackets(int argPacketId) const 
{
	buffer.renderPackets();
}

//NodeContainer singleton class
NodeContainer *NodeContainer::instance = NULL;
int NodeContainer::idCounter = 0;
NodeContainer::NodeContainer() {}
NodeContainer *NodeContainer::getInstance()
{
	if (instance == NULL)
		instance = new NodeContainer;
	return instance;
}
void NodeContainer::init(int argNumNodes)
{
	srand(time(NULL));
	Utils::Vec2 tempVec2;
	Node tempNode;
	for (int i = 0; i < argNumNodes; i++)
	{
		tempVec2 = Utils::Vec2(rand() % (int)FIELD_SIZE.x - (int)FIELD_SIZE.x / 2.0f, rand() % (int)FIELD_SIZE.y - (int)FIELD_SIZE.y / 2.0f);
		tempNode = Node(tempVec2, 2.0f);
		nodeVector.push_back(new Node(tempNode));
	}
}
void NodeContainer::update()
{
	for (int i = 0; i < nodeVector.size(); i++)
	{
		nodeVector[i]->update();
	}
}
int NodeContainer::getNewId()
{
	return idCounter++;
}
std::vector<Node*> NodeContainer::getNodeVector() const
{
	return nodeVector;
}
int NodeContainer::getRandomDst(int argExcludedId) //static
{
	int tempId = rand() % (NodeContainer::idCounter - 1);
	return (tempId < argExcludedId ? tempId : tempId + 1);
}
