#include <iostream>
#include <cmath>
#include <array>
#include "pstl_random.h"

std::array<uint32_t, 624> pstl::random::mersenne_twister::make_initial_array(int seed)
{
	std::array<uint32_t, 624> result;
	result[0] = seed;
	for (int i = 1; i < state_size; i++)
		result[i] = 1812433253UL * (result[i - 1] ^ (result[i - 1] >> 30)) + i;
	twist(result);
	return result;
}

uint32_t pstl::random::mersenne_twister::randint(int seed)
{
	static int next = 0;
	static std::array<uint32_t, state_size> state = make_initial_array(seed);

	if (next >= state_size)
	{
		twist(state);
		next = 0;
	}

	uint32_t result = state[next++];
	result ^= result >> 11;
	result ^= (result << 7) & 0x9d2c5680;
	result ^= (result << 15) & 0xefc60000;
	result ^= result >> 18;
	return result;
}

void pstl::random::mersenne_twister::twist(std::array<uint32_t, 624>& new_array)
{
	const int m = 397;
	const int first_half = state_size - m;

	int i;
	for (i = 0; i < first_half; i++)
	{
		uint32_t bits = (new_array[i] & 0x80000000) | (new_array[i + 1] & 0x7fffffff);
		new_array[i] = new_array[i + m] ^ (bits >> 1) ^ ((bits & 1) * 0x9908b0df);
	}

	for (; i < state_size - 1; i++)
	{
		uint32_t bits = (new_array[i] & 0x80000000) | (new_array[i + 1] & 0x7fffffff);
		new_array[i] = new_array[i - first_half] ^ (bits >> 1) ^ ((bits & 1) * 0x9908b0df);
	}

	uint32_t bits = (new_array[i] & 0x80000000) | (new_array[0] & 0x7fffffff);
	new_array[i] = new_array[m - 1] ^ (bits >> 1) ^ ((bits & 1) * 0x9908b0df);
}

float pstl::random::mersenne_twister::randfloat(int seed)
{
	uint32_t result = randint(seed);
	float output = (double)result / 0xFFFFFFFF;
	return output;
}

uint32_t pstl::random::linear_congruential_generator::randint(int seed)
{	
	static uint32_t xn = seed;
	xn = (a * xn + c) % m;
	return xn;
}

double pstl::random::linear_congruential_generator::randfloat(int seed)
{
	return (double)randint(seed) / m;
}

uint32_t pstl::random::middle_squares::count_digits(uint64_t num)
{
	int digits = 0;
	while (num > 0)
	{
		digits++;
		num = num / 10;
	}
	return digits;
}

uint64_t pstl::random::middle_squares::randint(int seed)
{
	static uint64_t xn = seed;
	xn = xn == 0 ? seed : xn;
	uint32_t count_init = count_digits(xn);
	xn *= xn;
	uint32_t count_end = count_digits(xn);
	uint32_t count_diff = count_end - count_init;
	int exp = std::pow(10, count_diff);
	xn = count_diff % 2 == 0 ? (xn / count_diff) % exp : ((xn * 10) / count_diff) % exp;
	return xn;
}

double pstl::random::middle_squares::randfloat(int seed)
{
	uint64_t val = randint(seed);
	uint32_t len = count_digits(val);
	return (double)val / std::pow(10, len);
}

uint32_t pstl::random::blum_blum_shub::randint(int seed)
{
	static uint32_t xn = seed;
	xn = (xn * xn) % m;
	return xn;
}

double pstl::random::blum_blum_shub::randfloat(int seed)
{
	return (double)randint(seed) / m;
}

