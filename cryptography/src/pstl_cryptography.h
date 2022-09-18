#pragma once

#include <string>
#include <array>
#include <vector>

namespace pstl::cryptography::ciphers
{
	class caeser_cipher
	{
	public:
		static void encrypt(std::string& str, int shift = 1);
		static void decrypt(std::string& str, int shift = 1);
	protected:
		caeser_cipher() = delete;
		~caeser_cipher() = delete;
	};
}

namespace pstl::cryptography::hashing
{
	class md5
	{
	public:
		static std::string digest(std::string str);
	protected:
		md5() = delete;
		~md5() = delete;
	private:
		constexpr static std::array<uint32_t, 64> make_k_array();
		static std::vector<char> padder(std::string str);
		static void init();
	private:
		static const std::array<uint32_t, 64> k_array;
		static const std::array<uint32_t, 64> s_array;
		inline static std::array<uint64_t, 16> m_array;
		inline static uint32_t a0 = 0x67452301;
		inline static uint32_t b0 = 0xefcdab89;
		inline static uint32_t c0 = 0x98badcfe;
		inline static uint32_t d0 = 0x10325476;
	};
}


