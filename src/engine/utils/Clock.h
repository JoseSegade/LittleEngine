#pragma once
#ifndef CLOCK_H_
#define CLOCK_H_

#include <chrono>

namespace LittleEngine
{
	namespace Utils
	{
		class Clock
		{
		private:
			std::chrono::high_resolution_clock::time_point		prevTime;
			double timeElapsed;
		public:
			Clock();

			void start();
			void pause();
			inline double getTimeElapsed() const { return timeElapsed; };
			void printTimeElapsed();
		};
	}
}

#endif // !CLOCK_H_
