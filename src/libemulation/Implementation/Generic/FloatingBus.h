
/**
 * libemulation
 * Floating bus
 * (C) 2010 by Marc S. Ressl (mressl@umich.edu)
 * Released under the GPL
 *
 * Controls a generic floating bus
 */

#include "OEComponent.h"

class FloatingBus : public OEComponent
{
public:
    FloatingBus();
    
    bool setValue(string name, string value);
    
    OEChar read(OEAddress address);
    
private:
    bool randomMode;
    
    OEChar busValue;
};
