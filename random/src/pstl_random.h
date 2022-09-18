#pragma once
#include <array>

namespace pstl::random
{
	class linear_congruential_generator
	{
	public:
		static uint32_t randint(int seed = 0);
		static double randfloat(int seed = 0);
	protected:
		linear_congruential_generator() = delete;
		~linear_congruential_generator() = delete;
	private:
		static const uint32_t m = 2147483648; // 2^31
		static const uint32_t c = 12345;
		static const uint32_t a = 1103515245;
	};

	class middle_squares
	{
	public:
		static uint64_t randint(int seed = 1234);
		static double randfloat(int seed = 0);
	protected:
		middle_squares() = delete;
		~middle_squares() = delete;
	private:
		static uint32_t count_digits(uint64_t num);
	};

	class blum_blum_shub
	{
	public:
		static uint32_t randint(int seed = 0);
		static double randfloat(int seed = 0);
	protected:
		blum_blum_shub() = delete;
		~blum_blum_shub() = delete;
	private:
		static const uint64_t p = 30000000091;
		static const uint64_t q = 40000000003;
		static const uint64_t m = p * q;
	};

	class mersenne_twister
	{
	public:
		static uint32_t randint(int seed = 5489);
		static float randfloat(int seed = 5489);
	private:
		mersenne_twister() = delete;
		~mersenne_twister() = delete;
		static std::array<uint32_t, 624> make_initial_array(int seed);
		static void twist(std::array<uint32_t, 624> &new_array);
	private:
		static const uint32_t state_size = 624;
	};
}