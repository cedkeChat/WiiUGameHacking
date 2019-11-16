#include "main.h"

void QuickTextDisplay(const char *text)
{
	OSScreenInit();
	OSScreenEnableEx(1, 1);
	OSScreenClearBufferEx(1, 0);
	OSScreenSetBufferEx(1, (void*)0xF4000000);
	OSScreenPutFontEx(1, 0, 0, text);
	OSScreenFlipBuffersEx(1);
}

int Installer(int agrc, char **argv)
{
	log_printf("Creating our background thread..\n");

	// Allocate our thread/thread stack
	uint8_t *stack = (uint8_t*)MEM2_alloc(0x1000, 0x10);
	OSThread *thread = (OSThread*)MEM2_alloc(0x1000, 0x10);

	// Create a detached thread on core 2 and affinitized to a single core
	bool ret = OSCreateThread(thread, MainThread, 0, NULL, (uint32_t)stack + 0x1000, 0x1000, 0, ((1 << 2) | 8 | 16));
	if(!ret)
	{
		log_printf("Couldn't create our thread, exiting ...\n");
		QuickTextDisplay("Couldn't create our thread, exiting ..");
		os_sleep(2);
		return 0;
	}

	// If we're in MiiMaker we go to the WiiU Menu
	if(OSGetTitleID() == 0x000500101004A100 || OSGetTitleID() == 0x000500101004A000 || OSGetTitleID() == 0x000500101004A200)
	{
		log_print("We're in the Homebrew Channel, abort.");
		SYSLaunchMenu();
		return -3;
	}



	// Otherwise we create our thread and we return
	OSSetThreadName(thread, "GameHackingThread");
	OSResumeThread(thread);

	return -3;
}