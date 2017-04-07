#include "LCWCompression.h"

#include "LittleEndianNumberStream.h"

//void CopyTo(byte[] dest, int offset, int count)
//{
//	Array.Copy(src, this.offset, dest, offset, count);
//	this.offset += count;
//}


//void Copy(Array sourceArray, int sourceIndex, Array destinationArray, int destinationIndex, int length);
void CopyTo(std::vector<uint8_t> & sourceArray, int sourceIndex, std::vector<uint8_t> &  destinationArray, int destinationIndex, int length) {
	int endSourceIndex = sourceIndex + length;
	for (; sourceIndex < endSourceIndex; sourceIndex++, destinationIndex++) {
		destinationArray[destinationIndex] = sourceArray[sourceIndex];
	}
}



//int LCWCompression::DecodeInto(uint8_t * src, uint8_t * dest, int srcOffset = 0, bool reverse = false) {
	int LCWCompression::DecodeInto(std::vector<uint8_t> & src, std::vector<uint8_t> & dest, int srcOffset, bool reverse) {
	//var ctx = new FastByteReader(src, srcOffset);
	
	int destIndex = 0;
	while (true)
	{
		//var i = ctx.ReadByte();
		uint8_t i = src[srcOffset++];
		if ((i & 0x80) == 0)
		{
			// case 2
			//var secondByte = ctx.ReadByte();
			uint8_t secondByte = ReadUInt8(src, srcOffset);
			//var count = ((i & 0x70) >> 4) + 3;
			int count = ((i & 0x70) >> 4) + 3;
			//var rpos = ((i & 0xf) << 8) + secondByte;
			int rpos = ((i & 0xf) << 8) + secondByte;


			//if (destIndex + count > dest.Length)
			//	return destIndex;
			if (destIndex + count > dest.size() )
				return destIndex;


			ReplicatePrevious(dest, destIndex, destIndex - rpos, count);
			destIndex += count;
		}
		else if ((i & 0x40) == 0)
		{
			// case 1
			//var count = i & 0x3F;
			int count = i & 0x3F;

			if (count == 0)
				return destIndex;

			//ctx.CopyTo(dest, destIndex, count);
			CopyTo(src, srcOffset, dest, destIndex, count);
			destIndex += count;
			srcOffset += count;

		}
		else
		{
//			var count3 = i & 0x3F;
			int count3 = i & 0x3F;
			if (count3 == 0x3E)
			{
				// case 4
//				var count = ctx.ReadWord();
				uint16_t  count = ReadUInt16(src, srcOffset);

				//var color = ctx.ReadByte();
				uint8_t color = ReadUInt8(src, srcOffset);

				//for (var end = destIndex + count; destIndex < end; destIndex++)
				//	dest[destIndex] = color;
				for (uint16_t end = destIndex + count; destIndex < end; destIndex++)
					dest[destIndex] = color;

			}
			else if (count3 == 0x3F)
			{
				// case 5
				//var count = ctx.ReadWord();
				uint16_t count = ReadUInt16(src, srcOffset);

				//var srcIndex = reverse ? destIndex - ctx.ReadWord() : ctx.ReadWord();
				uint16_t srcIndex = reverse ? destIndex - ReadUInt16(src, srcOffset) : ReadUInt16(src, srcOffset);

				//if (srcIndex >= destIndex)
				//	throw new NotImplementedException("srcIndex >= destIndex {0} {1}".F(srcIndex, destIndex));
				if (srcIndex >= destIndex)
					throw "srcIndex >= destIndex";


				//for (var end = destIndex + count; destIndex < end; destIndex++)
				//	dest[destIndex] = dest[srcIndex++];
				for (uint16_t end = destIndex + count; destIndex < end; destIndex++)
					dest[destIndex] = dest[srcIndex++];

			}
			else
			{
				// case 3
//				var count = count3 + 3;
				uint16_t  count = count3 + 3;

				//var srcIndex = reverse ? destIndex - ctx.ReadWord() : ctx.ReadWord();
				uint16_t  srcIndex = reverse ? destIndex - ReadUInt16(src, srcOffset) : ReadUInt16(src, srcOffset);

				//if (srcIndex >= destIndex)
				//	throw new NotImplementedException("srcIndex >= destIndex {0} {1}".F(srcIndex, destIndex));
				if (srcIndex >= destIndex)
					throw "srcIndex >= destIndex";

	
				//for (var end = destIndex + count; destIndex < end; destIndex++)
				//	dest[destIndex] = dest[srcIndex++];
				for (uint16_t end = destIndex + count; destIndex < end; destIndex++)
					dest[destIndex] = dest[srcIndex++];

			}
		}
	}

}





//void LCWCompression::ReplicatePrevious(byte[] dest, int destIndex, int srcIndex, int count)
void LCWCompression::ReplicatePrevious(std::vector<uint8_t> &  dest, int destIndex, int srcIndex, int count)
{
	//if (srcIndex > destIndex)
	//	throw new NotImplementedException("srcIndex > destIndex {0} {1}".F(srcIndex, destIndex));
	if (srcIndex > destIndex)
		throw "srcIndex > destIndex";


	if (destIndex - srcIndex == 1)
	{
		//for (var i = 0; i < count; i++)
		//	dest[destIndex + i] = dest[destIndex - 1];
		for (int i = 0; i < count; i++)
			dest[destIndex + i] = dest[destIndex - 1];

	}
	else
	{
		//for (var i = 0; i < count; i++)
		//	dest[destIndex + i] = dest[srcIndex + i];
		for (int i = 0; i < count; i++)
			dest[destIndex + i] = dest[srcIndex + i];

	}
}
