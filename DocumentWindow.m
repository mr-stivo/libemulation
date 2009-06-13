
/**
 * OpenEmulator
 * Mac OS X Document Window
 * (C) 2009 by Marc S. Ressl (mressl@umich.edu)
 * Released under the GPL
 */

#import "DocumentWindow.h"

@implementation DocumentWindow

- (BOOL)canBecomeKeyWindow
{
	return YES;
}
/*
- (void)keyDown:(NSEvent *)theEvent
{
    // your code here
}

- (void)keyUp:(NSEvent *)theEvent
{
    // your code here
}
*/
- (BOOL)validateUserInterfaceItem:(id)item
{
	if ([item action] == @selector(performClose:))
		return YES;

	return YES;
}

- (void)performClose:(id)sender
{
	[[self windowController] performClose:sender];
}

@end