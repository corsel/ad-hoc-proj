#ifndef PACKET_H_INCLUDED
#define PACKET_H_INCLUDED

#include "ext-params.h"
#include "utils.h"
#include <vector>
#include <stdlib.h>
#include <iostream>

//Parameters
const float GEN_RATE = 0.0001f;

const int MIN_PACKET_SIZE = 500;
const int MAX_PACKET_SIZE = 1000;
const int MAX_FRAG_SIZE = 200;
const int HEADER_SIZE = 30;

const int BUFFER_SIZE = 10000;
const int SAW_COPIES = 5; //saw: spray and wait

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
	Utils::Color color;
	
public:
	Packet(void);
	Packet(int argSrcId, int argDstId, int argSize);
	int getId(void) const;
	int getSrc(void) const;
	int getDst(void) const;
};

class Buffer
{
private:
	std::vector<Packet> packetVector;
	int size;
	int used;
	
public:
	Buffer(void);
	void syncBuffers(Buffer *argOther);
	bool receive(Packet const *argPacket);
	void renderPackets(int argPacketId = -1) const;
};

class PacketGenerator
{
protected:
	static int debugCounter;
	Packet *returnPacket;
public:
	PacketGenerator(void);
	~PacketGenerator(void);
	virtual Packet const *update(int argSrc, int argDst) = 0;
};

class RandomPacketGenerator : public PacketGenerator
{
private:
public:
	RandomPacketGenerator(void);
	~RandomPacketGenerator(void);
	Packet const *update(int argSrc, int argDst); //virtual implementation
};

class NPacketGenerator : public PacketGenerator
{
private:
	static int numPackets;
	int limPackets;
	
public:
	NPacketGenerator(int argLimPackets);
	~NPacketGenerator(void);
	Packet const *update(int argSrc, int argDst); //virtual implementation
};

#endif //PACKET_H_INCLUDED
