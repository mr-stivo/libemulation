
/**
 * libemulation
 * Apple II Address Decoder
 * (C) 2012 by Marc S. Ressl (mressl@umich.edu)
 * Released under the GPL
 *
 * Controls an Apple II Address Decoder
 */

#include "AppleIIEAddressDecoder.h"

#include "AppleIIInterface.h"

AppleIIEAddressDecoder::AppleIIEAddressDecoder() : AppleIIAddressDecoder()
{
}

bool AppleIIEAddressDecoder::postMessage(OEComponent *sender, int message, void *data)
{
    switch (message)
    {
        case ADDRESSDECODER_MAP:
            return addMemoryMap(externalMemoryMaps, (MemoryMap *) data);
            
        case ADDRESSDECODER_UNMAP:
            return removeMemoryMap(externalMemoryMaps, (MemoryMap *) data);
            
        case APPLEII_MAP_SLOT:
            return addMemoryMap(ioMemoryMaps, (MemoryMap *) data);
            
        case APPLEII_UNMAP_SLOT:
            return removeMemoryMap(ioMemoryMaps, (MemoryMap *) data);
    }
    
    return false;
}

void AppleIIEAddressDecoder::updateReadWriteMap(OEAddress startAddress, OEAddress endAddress)
{
    AddressDecoder::updateReadWriteMap(internalMemoryMaps, startAddress, endAddress);
    AddressDecoder::updateReadWriteMap(ioMemoryMaps, startAddress, endAddress);
    AddressDecoder::updateReadWriteMap(cxxxMemoryMaps, startAddress, endAddress);
    AddressDecoder::updateReadWriteMap(externalMemoryMaps, startAddress, endAddress);
}

