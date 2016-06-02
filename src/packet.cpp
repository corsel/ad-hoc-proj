#include "packet.h"

//Packet class
int Packet::packetCounter = 0;
Packet::Packet(int argSrcId, int argSrcDst, int argSize) {}

//Buffer class
Buffer::Buffer() {}

//PacketGenerator class
int PacketGenerator::debugCounter = 0;
PacketGenerator::PacketGenerator(Buffer *argBuffer)
: buffer(argBuffer) {}
void PacketGenerator::update()
{
	if (rand() % 1000000 > int(GEN_POSS * 1000000))
		return;
	std::cout << "debug - PacketGenerator::update: packet generated with id " << debugCounter++ << "\n";
}
