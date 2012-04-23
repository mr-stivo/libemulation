
/**
 * libdiskimage
 * Apple 5.25" Disk Image
 * (C) 2012 by Marc S. Ressl (mressl@umich.edu)
 * Released under the GPL
 *
 * Accesses an Apple 5.25" disk image
 */

#include "DICommon.h"

#include "DIFileBackingStore.h"
#include "DIRAMBackingStore.h"
#include "DI2IMGBackingStore.h"
#include "DIDC42BackingStore.h"

#include "DIDiskStorage.h"
#include "DILogicalDiskStorage.h"
#include "DIFDIDiskStorage.h"
#include "DIV2DDiskStorage.h"

typedef struct 
{
    DITrack *track;
    DIInt index;
} DIApple525Track;

class DIApple525DiskStorage
{
public:
    DIApple525DiskStorage();
    
    bool open(string path);
    bool open(DIData& data);
    bool close();
    
    bool isWriteEnabled();
    string getFormatLabel();
    
    bool readTrack(DIInt headIndex, DIInt trackIndex, DITrack& track);
    bool writeTrack(DIInt headIndex, DIInt trackIndex, DITrack& track);
    
private:
    DIFileBackingStore fileBackingStore;
    DIRAMBackingStore ramBackingStore;
    DI2IMGBackingStore twoIMGBackingStore;
    DIDC42BackingStore dc42BackingStore;
    
    DIDiskStorage dummyDiskStorage;
    DILogicalDiskStorage logicalDiskStorage;
    DIFDIDiskStorage fdiDiskStorage;
    DIV2DDiskStorage v2dDiskStorage;
    
    DIDiskStorage *diskStorage;
    
    vector<DITrack> tracks;
    bool tracksModified;
    
    DIChar *streamTrackData;
    DIInt streamTrackSize;
    DIInt streamOffset;
    DIChar gcrVolume;
    DIChar gcrChecksum;  
    bool gcrError;
    
    bool open(DIBackingStore *backingStore, string pathExtension);
    
    bool checkLogicalDisk(DIBackingStore *backingStore,
                          DITrackFormat& trackFormat, DIInt& trackSize);
    
    DIInt *getSectorOrder(DIInt trackIndex);
    
    bool encodeGCR53Track(DITrack& track, DIInt trackIndex);
    bool encodeGCR62Track(DITrack& track, DIInt trackIndex);
    bool encodeNIBTrack(DITrack& track, DIInt trackIndex);
    bool decodeGCR53Track(DITrack& decodedTrack, DIInt trackIndex);
    bool decodeGCR62Track(DITrack& decodedTrack, DIInt trackIndex);
    
    void writeGCR53AddressField(DIInt trackIndex, DIInt sectorIndex);
    void writeGCR53DataField(DIChar *data);
    bool readGCR53AddressField(DIInt trackIndex, DIInt sectorIndex);
    bool readGCR53DataField(DIChar *data);
    
    void writeGCR62AddressField(DIInt trackIndex, DIInt sectorIndex);
    void writeGCR62DataField(DIChar *data);
    bool readGCR62AddressField(DIInt trackIndex, DIInt sectorIndex);
    bool readGCR62DataField(DIChar *data);
    
    void writeSync(DIInt num, DIInt q3Clocks, DIInt lastQ3Clocks);
    
    void writeFMValue(DIChar value);
    DIChar readFMValue();
    
    void resetGCR();
    bool isGCRError();
    
    void writeGCR53Value(DIChar value);
    void writeGCR53Checksum();
    DIChar readGCR53Value();
    bool validateGCR53Checksum();
    
    void writeGCR62Value(DIChar value);
    void writeGCR62Checksum();
    DIChar readGCR62Value();
    bool validateGCR62Checksum();
    
    void setStreamTrack(DITrack& track);
    void writeNibble(DIChar value);
    void writeNibble(DIChar value, DIInt q3Clocks);
    DIChar readNibble();
};
