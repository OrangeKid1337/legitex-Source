#pragma once
#include "main.hpp"

void createOverlay()
{
	scene->create();
}

void createLoop()
{
	cheat->entityLoop();
}

int main()
{
	if (init->cheat())
	{
		std::thread newrth(createOverlay);
		newrth.detach();
		std::thread newrth2(createLoop);
		newrth2.detach();
		cheat->Aimbot();
		
	}
	return TRUE;
}