#ifndef PACKET_H_INCLUDED
#define PACKET_H_INCLUDED

#include <vector>
#include <stdlib.h>
#include <iostream>

//Parameters
const float GEN_RATE = 0.00005f;

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

	int id;
	int size;
	int fragment;
	int numFragments;
	int srcId;
	int dstId;
	int numCopies;
	
public:
	Packet(int argSrcId, int argSrcDst, int argSize);
};

class Buffer
{
private:
	std::vector<Packet> packetVector;
	
public:
	Buffer(void);
};

class PacketGenerator
{
private:
	static int debugCounter;
	Buffer *buffer;
public:
	PacketGenerator(Buffer *argBuffer);
	void update(void);
};

#endif //PACKET_H_INCLUDED
