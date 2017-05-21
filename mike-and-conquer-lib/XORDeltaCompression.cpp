#include "XORDeltaCompression.h"

#include "LittleEndianNumberStream.h"

int XORDeltaCompression::DecodeInto(std::vector<uint8_t> & src, std::vector<uint8_t> & dest, int srcOffset)
{
	//var ctx = new FastByteReader(src, srcOffset);
	//var destIndex = 0;
	unsigned int destIndex = 0;

	while (true)
	{
		//var i = ctx.ReadByte();
		uint8_t i = src[srcOffset++];
		if ((i & 0x80) == 0)
		{
			//var count = i & 0x7F;
			uint8_t count = i & 0x7F;
			if (count == 0)
			{
				// case 6
				//count = ctx.ReadByte();
				count = ReadUInt8(src, srcOffset);
				//var value = ctx.ReadByte();
				uint8_t value = ReadUInt8(src, srcOffset);
				//for (var end = destIndex + count; destIndex < end; destIndex++)
				//	dest[destIndex] ^= value;
				for (uint16_t end = destIndex + count; destIndex < end; destIndex++)
					dest[destIndex] ^= value;

			}
			else
			{
				// case 5
				//for (var end = destIndex + count; destIndex < end; destIndex++)
				//	dest[destIndex] ^= ctx.ReadByte();
				for (uint16_t end = destIndex + count; destIndex < end; destIndex++)
					dest[destIndex] ^= ReadUInt8(src, srcOffset);

			}
		}
		else
		{
			//var count = i & 0x7F;
			uint16_t count = i & 0x7F;

			if (count == 0)
			{
				//count = ctx.ReadWord();
				count = ReadUInt16(src, srcOffset);
				if (count == 0)
					return destIndex;

				if ((count & 0x8000) == 0)
				{
					// case 2
					destIndex += count & 0x7FFF;
				}
				else if ((count & 0x4000) == 0)
				{
					// case 3
					//for (var end = destIndex + (count & 0x3FFF); destIndex < end; destIndex++)
					//	dest[destIndex] ^= ctx.ReadByte();
					for (uint16_t end = destIndex + (count & 0x3FFF); destIndex < end; destIndex++)
						dest[destIndex] ^= ReadUInt8(src, srcOffset);

				}
				else
				{
					// case 4
					//var value = ctx.ReadByte();
					uint8_t value = ReadUInt8(src, srcOffset);
					//for (var end = destIndex + (count & 0x3FFF); destIndex < end; destIndex++)
					//	dest[destIndex] ^= value;
					for (uint16_t end = destIndex + (count & 0x3FFF); destIndex < end; destIndex++)
						dest[destIndex] ^= value;

				}
			}
			else
			{
				// case 1
				destIndex += count;
			}
		}
	}
}
