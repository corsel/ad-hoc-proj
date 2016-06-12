#include "packet.h"

//Packet class
int Packet::packetCounter = 0;
Packet::Packet() {}
Packet::Packet(int argSrcId, int argDstId, int argSize)
: srcId(argSrcId), dstId(argDstId), size(argSize), id(Packet::packetCounter++), numCopies(SAW_COPIES), color(Utils::Color::getRandomColor()), timeOfDeath(0) {}
Packet Packet::binarySplit()
{
	Packet returnPacket = *this;
	returnPacket.numCopies = numCopies / 2;
	numCopies = numCopies / 2 + numCopies % 2;
	if (returnPacket.numCopies == 1)
		returnPacket.timeOfDeath = globalFrame + SAW_TTL;
	if (numCopies == 1)
		timeOfDeath = globalFrame + SAW_TTL;
	return returnPacket;
}
int Packet::getId() const {	return id; }
int Packet::getSrc() const { return srcId; }
int Packet::getDst() const { return dstId; }

//Buffer class
Buffer::Buffer(Node *argParentNode /* = NULL */)
: size(BUFFER_SIZE), parentNode(argParentNode) {}
void Buffer::syncBuffers(Buffer *argOther)
{
	for (int i = 0; i < argOther->packetVector.size(); i++)
	{
		bool skipPacketFlag = false;
		if (argOther->packetVector[i].numCopies == 1) 
			skipPacketFlag = true;
		for (int j = 0; j < packetVector.size(); j++)
		{
			if (argOther->packetVector[i].dstId == parentNode->id)
			{
				std::cout << "debug - Buffer::syncBuffers: destination reached; packet id: " << packetVector[i].id << std::endl;
				argOther->packetVector.erase(argOther->packetVector.begin() + i);
				skipPacketFlag = true;
			}
			if (argOther->packetVector[i].id == packetVector[j].id)
				skipPacketFlag = true;
		}
		if (!skipPacketFlag)
		{
			//std::cout << "debug - Buffer::syncBuffers: transaction occured; packet id: " << argOther->packetVector[i].id << std::endl;
			push(argOther->packetVector[i].binarySplit());
		}
	}
}
bool Buffer::push(Packet argPacket)
{
	if (size < argPacket.size + used)
	{
		std::cout << "debug - Buffer::push: buffer full, dropping packet " << argPacket.id << ".\n";
		return false;
	}
	packetVector.push_back(argPacket);
}
void Buffer::updatePackets(int argPacketId /*-1*/)
{
	glPushMatrix();
	for (int i = 0; i < packetVector.size(); i++)
	{
		if (packetVector[i].timeOfDeath <= globalFrame && packetVector[i].timeOfDeath > 0)
		{
			std::cout << "debug - Buffer::updatePackets: ttl reached, dropping packet " << packetVector[i].id << " from node " << parentNode->id << std::endl;
			packetVector.erase(packetVector.begin() + i);
			for (int k = 0; k < packetVector.size(); k++)
				std::cout << "\telement " << k << ": " << packetVector[i].id << std::endl;
		}
		if (argPacketId == -1 || argPacketId == packetVector[i].id)
		{
			glTranslatef(0.6f, 0.4f, 0.0f);
			glColor3f(packetVector[i].color.red, packetVector[i].color.green, packetVector[i].color.blue);
			Utils::drawEnvelope(packetVector[i].numCopies);
		}
	}
	glPopMatrix();
}

//PacketGenerator class
int PacketGenerator::debugCounter = 0;
PacketGenerator::PacketGenerator() { returnPacket = new Packet(); }
PacketGenerator::~PacketGenerator() { delete returnPacket; }

//RandomPacketGenerator class
RandomPacketGenerator::RandomPacketGenerator()
: PacketGenerator() {}
RandomPacketGenerator::~RandomPacketGenerator() {}
Packet *RandomPacketGenerator::update(int argSrc, int argDst)
{
	if (rand() % 1000000 > int(GEN_RATE * 1000000))
		return NULL;
	*returnPacket = Packet(argSrc, argDst, MIN_PACKET_SIZE + rand() % (MAX_PACKET_SIZE - MIN_PACKET_SIZE));
	std::cout << "debug - PacketGenerator::update: packet generated:\n\tid: " << returnPacket->getId() << "\n\tsrc: " << returnPacket->getSrc() << "\n\tdst: " << returnPacket->getDst() << std::endl;
	return returnPacket;
}

//NPacketGenerator class
int NPacketGenerator::numPackets = 0;
NPacketGenerator::NPacketGenerator(int argLimPackets)
: limPackets(argLimPackets), PacketGenerator() {}
NPacketGenerator::~NPacketGenerator() {}
Packet *NPacketGenerator::update(int argSrc, int argDst) 
{
	if (NPacketGenerator::numPackets > limPackets)
		return NULL;
	if (rand() % 1000000 > int(GEN_RATE * 1000000))
		return NULL;
	*returnPacket = Packet(argSrc, argDst, MIN_PACKET_SIZE + rand() % (MAX_PACKET_SIZE - MIN_PACKET_SIZE));
	std::cout << "debug - PacketGenerator::update: packet generated:\n\tid: " << returnPacket->getId() << "\n\tsrc: " << returnPacket->getSrc() << "\n\tdst: " << returnPacket->getDst() << std::endl;
	NPacketGenerator::numPackets++;
	return returnPacket;
}
