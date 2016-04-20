#include "network-elements.h"

const float WIRELESS_RANGE = 4.0f;
const int MAX_SPEED = 3;
const int MAX_WAIT = 500;

//Node class
int Node::counter = 0;
bool Node::inProximity(Utils::Vec2 argOther)
{
	if (Utils::Vec2::getSqrDistance(posn, argOther) <= Utils::EPSILON * Utils::EPSILON)
		return true;
	else
		return false;	
}
Node::Node() 
: posn(Utils::Vec2(0.0f, 0.0f)), range(3.0f), isWalking(true)
{
	id = counter++;
	randWypt = Utils::Vec2((rand() % (int)FIELD_SIZE.x) - FIELD_SIZE.x / 2.0f, (rand() % (int)FIELD_SIZE.y) - FIELD_SIZE.y / 2.0f);
	randSpeed = 1.0f + rand() % MAX_SPEED;
}
Node::Node(Utils::Vec2 argPosn, float argRange)
: posn(argPosn), range(argRange), isWalking(true)
{
	id = counter++;
	randWypt = Utils::Vec2((rand() % (int)FIELD_SIZE.x) - FIELD_SIZE.x / 2.0f, (rand() % (int)FIELD_SIZE.y) - FIELD_SIZE.y / 2.0f);
	randSpeed = 1.0f + rand() % MAX_SPEED;
	
}
Utils::Vec2 Node::getPosn()
{
	return posn;
}
void Node::updateMovement()
{
	if (isWalking)
	{
		if (inProximity(randWypt))
		{
			isWalking = false;
			randTime = rand() % MAX_WAIT;
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
			randSpeed = rand() % MAX_SPEED;
			isWalking = true;
		}
	}
}
void Node::updateContacts()
{
	contactNodes.clear();
	for (int i = 0; i < nodeVector.size(); i++)
	{
		if (nodeVector[i].id == id)
			continue;
		if (Utils::Vec2::getSqrDistance(posn, nodeVector[i].posn) <= WIRELESS_RANGE * WIRELESS_RANGE)
			contactNodes.push_back(&nodeVector[i]);
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
		glVertex2f(posn.x, posn.y);
		glVertex2f(contactNodes[i]->posn.x, contactNodes[i]->posn.y);
	}
	//Waypoints
	glColor3f(0.15f, 0.15f, 0.2f);
	glVertex2f(posn.x, posn.y);
	glVertex2f(randWypt.x, randWypt.y);
	glEnd();
	glPopMatrix();
	glPopAttrib();
}

std::vector<Node> nodeVector;
