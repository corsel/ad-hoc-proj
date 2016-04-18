#include "network-elements.h"

Node::Node() {}
Node::Node(Utils::Vec2 argPosn, float argRange)
: posn(argPosn), range(argRange) {}
void Node::toggleAnnotations()
{
	showAnnotations != showAnnotations;
}
void Node::render()
{
}
