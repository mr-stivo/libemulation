
/**
 * libemulator
 * Apple II Video
 * (C) 2010-2012 by Marc S. Ressl (mressl@umich.edu)
 * Released under the GPL
 *
 * Generates Apple II video
 */

#include "OEComponent.h"
#include "OEImage.h"

#include "ControlBusInterface.h"

class AppleIIVideo : public OEComponent
{
public:
    AppleIIVideo();
    
	bool setValue(string name, string value);
	bool getValue(string name, string& value);
	bool setRef(string name, OEComponent *ref);
    bool setData(string name, OEData *data);
	bool init();
    void update();
    
    bool postMessage(OEComponent *sender, int message, void *data);
    
    void notify(OEComponent *sender, int notification, void *data);
    
	OEChar read(OEAddress address);
	void write(OEAddress address, OEChar value);
	
private:
    OEComponent *controlBus;
    OEComponent *gamePort;
	OEComponent *monitor;
    
    // Settings
    OEInt model;
    OEInt revision;
    OEInt videoSystem;
	string characterSet;
    OEInt flashFrameNum;
    OEInt mode;
    
    bool revisionUpdated;
    bool videoSystemUpdated;
    
    // Tables
    vector<OEIntPoint> pos;
    vector<OEIntPoint> count;
    
    vector<OEInt> textOffset;
    vector<OEInt> hiresOffset;
    
    // Memory
    OEComponent *vram0000;
    OEAddress vram0000Offset;
    OEComponent *vram1000;
    OEAddress vram1000Offset;
    OEComponent *vram2000;
    OEAddress vram2000Offset;
    OEComponent *vram4000;
    OEAddress vram4000Offset;
    
    OEData dummyMemory;
    
    OEChar *textMemory[2];
    OEChar *hblMemory[2];
    OEChar *hiresMemory[2];
    
    // Drawing
    bool videoEnabled;
    bool colorKiller;
    
    map<string, OEData> text40Font;
    map<string, OEData> text80Font;
    OEData loresFont;
    OEData hires40Font;
    OEData hires80Font;
    
    OEImage image;
    OEChar *imagep;
    OEInt imageWidth;
    bool imageModified;
    
    void (AppleIIVideo::*draw)(OESInt y, OESInt x0, OESInt x1);
    OEChar *drawMemory1;
    OEChar *drawMemory2;
    OEChar *drawFont;
    
    // Timing
    OEInt vertTotal;
    OEInt vertStart;
    
    OELong frameStart;
    OEInt frameCycleNum;
    
    OEInt currentTimer;
    OELong lastCycles;
    OEInt pendingCycles;
    
    bool flash;
    OEInt flashCount;
    
    // State
    ControlBusPowerState powerState;
    bool monitorConnected;
    OEInt videoInhibitCount;
    bool an2;
    
    void initOffsets();
    
    bool loadTextFont(string name, OEData *data);
    void buildLoresFont();
    void buildHires40Font();
    void buildHires80Font();
    
    void initVideoRAM(OEComponent *ram, OEAddress &start);
    void updateImage();
    void updateClockFrequency();
    
    void updateMonitorConnected();
    
    void setMode(OEInt mask, bool value);
    void configureDraw();
    void drawText40Line(OESInt y, OESInt x0, OESInt x1);
    void drawText80Line(OESInt y, OESInt x0, OESInt x1);
    void drawLores40Line(OESInt y, OESInt x0, OESInt x1);
    void drawHires40Line(OESInt y, OESInt x0, OESInt x1);
    void drawHires80Line(OESInt y, OESInt x0, OESInt x1);
    void updateVideoEnabled();
    void refreshVideo();
    void updateVideo();
    
    void updateTiming();
    void scheduleNextTimer(OESLong cycles);
    OEIntPoint getCount();
    OEChar readFloatingBus();
    
    void copy(wstring *s);
};
