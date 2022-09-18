#include <iostream>
#include <chrono>
#include "pstl_chrono.h"

pstl::chrono::timer::timer()
{
	start = std::chrono::high_resolution_clock::now();
}

pstl::chrono::timer::timer(const std::string& str)
	: name(str) 
{
	start = std::chrono::high_resolution_clock::now();
}

pstl::chrono::timer::~timer()
{
	end = std::chrono::high_resolution_clock::now();
	duration = end - start;
	float ms = duration.count() * 1000.0f;
	if (name.empty())
		std::cout << "Timer took: " << ms << " ms" << std::endl;
	else
		std::cout << name << " | " << "Timer took: " << ms << " ms" << std::endl;
}