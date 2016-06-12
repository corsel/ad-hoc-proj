#ifndef PACKET_H_INCLUDED
#define PACKET_H_INCLUDED

#include "ext-params.h"
#include "utils.h"
#include "network-elements.h"
#include <vector>
#include <stdlib.h>
#include <iostream>

class Node; //forward declaration...

//Parameters
const float GEN_RATE = 0.0005f;

const int MIN_PACKET_SIZE = 500;
const int MAX_PACKET_SIZE = 1000;
const int MAX_FRAG_SIZE = 200;
const int HEADER_SIZE = 30;

const int BUFFER_SIZE = 10000;
const int SAW_COPIES = 5; //saw: spray and wait
const int SAW_TTL = 1000;

const int BANDWIDTH = 200;
const float FADE = 2.0f;
//

class Packet
{
private:
	static int packetCounter;
	friend class Buffer;
	
	int id;
	int size;
	int fragment;
	int numFragments;
	int srcId;
	int dstId;
	int numCopies;
	unsigned long int timeOfDeath;
	Utils::Color color;
	
public:
	Packet(void);
	Packet(int argSrcId, int argDstId, int argSize);
	Packet binarySplit(void);
	int getId(void) const;
	int getSrc(void) const;
	int getDst(void) const;
};

class Buffer
{
private:
	Node * const parentNode;
	std::vector<Packet> packetVector;
	int size;
	int used;
	
public:
	Buffer(Node *argParentNode = NULL);
	void syncBuffers(Buffer *argOther);
	bool push(Packet argPacket);
	void updatePackets(int argPacketId = -1);
};

class PacketGenerator
{
protected:
	static int debugCounter;
	Packet *returnPacket;
public:
	PacketGenerator(void);
	~PacketGenerator(void);
	virtual Packet *update(int argSrc, int argDst) = 0;
};

class RandomPacketGenerator : public PacketGenerator
{
private:
public:
	RandomPacketGenerator(void);
	~RandomPacketGenerator(void);
	Packet *update(int argSrc, int argDst); //virtual implementation
};

class NPacketGenerator : public PacketGenerator
{
private:
	static int numPackets;
	int limPackets;
	
public:
	NPacketGenerator(int argLimPackets);
	~NPacketGenerator(void);
	Packet *update(int argSrc, int argDst); //virtual implementation
};

#endif //PACKET_H_INCLUDED
