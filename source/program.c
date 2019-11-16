#include "program.h"

int MainThread(int argc, void* argv)
{	
	// If you want the game to be BO2
	if(OSGetTitleID() != 0x0005000010113400)
	{
		log_printf("Not Black Ops II, exiting thread ..\n");
		return 0;
	}

	/*
	*	YOUR CODE HERE
	*/

	return 0;

}