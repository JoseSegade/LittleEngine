#include "Clock.h"

LittleEngine::Utils::Clock::Clock() : prevTime(), timeElapsed(0)
{
}

void LittleEngine::Utils::Clock::start()
{
	prevTime = std::chrono::high_resolution_clock::now();
}

void LittleEngine::Utils::Clock::pause()
{
	std::chrono::high_resolution_clock::time_point currentTime = std::chrono::high_resolution_clock::now();
	timeElapsed = std::chrono::duration<double>(currentTime - prevTime).count();
}

void LittleEngine::Utils::Clock::printTimeElapsed()
{
	printf("Time Elapsed: %f\n", timeElapsed);
}
