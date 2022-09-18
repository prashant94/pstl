#pragma once

#include <chrono>
#include <string>

namespace pstl::chrono
{
	class timer
	{
	public:
		timer();
		timer(const std::string& str);
		~timer();
	private:
		std::string name;
		std::chrono::time_point<std::chrono::steady_clock> start, end;
		std::chrono::duration<float> duration;
	};
}