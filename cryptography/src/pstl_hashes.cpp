#include <iostream>
#include <array>
#include <string>
#include <cmath>
#include <vector>
#include <format>
#include "pstl_cryptography.h"

const std::array<uint32_t, 64> pstl::cryptography::hashing::md5::s_array = {
    7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
    5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
    4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
    6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21
};

constexpr std::array<uint32_t, 64> pstl::cryptography::hashing::md5::make_k_array()
{
    std::array<uint32_t, 64> output;
    for (int i = 0; i < output.max_size(); i++)
        output[i] = std::floor(0x100000000 * std::abs(std::sin(i + 1)));
    return output;
}

const std::array<uint32_t, 64> pstl::cryptography::hashing::md5::k_array = pstl::cryptography::hashing::md5::make_k_array();

std::vector<char> pstl::cryptography::hashing::md5::padder(std::string str)
{
	std::vector<char> padded(str.begin(), str.end());
	union length_pad
	{
		uint64_t whole;
		uint8_t parts[8];
	} length;
	length.whole = padded.size() * 8;
	padded.emplace_back(0x80);
	int extra_over_chunks = (padded.size() % 64);
	int zero_pad = extra_over_chunks < 56 ? 56 - extra_over_chunks : 56 - extra_over_chunks + 64;
	for (int i = 0; i < zero_pad; i++)
		padded.emplace_back(0x00);
	for (auto& length_byte : length.parts)
		padded.emplace_back(length_byte);
	return padded;
}

void pstl::cryptography::hashing::md5::init()
{
	a0 = 0x67452301;
	b0 = 0xefcdab89;
	c0 = 0x98badcfe;
	d0 = 0x10325476;
}

// Based on RFC 1321
// https://www.ietf.org/rfc/rfc1321.txt
// 1992
std::string pstl::cryptography::hashing::md5::digest(std::string str)
{
	init();
	std::vector<char> padded_message = padder(str);
	uint32_t num_chunks = padded_message.size() / 64;
	for (int i = 0; i < num_chunks; i++)
	{
		uint32_t A = a0;
		uint32_t B = b0;
		uint32_t C = c0;
		uint32_t D = d0;
		union chunk
		{
			char in_chars[64];
			uint32_t in_ints[16];
		} current_chunk;

		for (int k = 0; k < 64; k++)
			current_chunk.in_chars[k] = padded_message[k + i * 64];
	
		for (int k = 0; k < 16; k++)
			m_array[k] = current_chunk.in_ints[k];

		for (int j = 0; j < 64; j++)
		{
			uint32_t F, g;
			if (j < 16)
			{	
				F = (B & C) | ((~B) & D);
				g = j;
			}
			else if (j < 32)
			{
				F = (B & D) | (C & (~D));
				g = (5 * j + 1) % 16;
			}
			else if (j < 48)
			{
				F = B ^ C ^ D;
				g = (3 * j + 5) % 16;
			}
			else if (j < 64)
			{
				F = C ^ (B | (~D));
				g = (7 * j) % 16;
			}
			F = F + A + m_array[g] + k_array[j];
			A = D;
			D = C;
			C = B;
			B = B + std::rotl(F, s_array[j]);
		}
		a0 += A;
		b0 += B;
		c0 += C;
		d0 += D;
	}
	std::string output;
	for (auto var : { &a0, &b0, &c0, &d0 })
	{
		*var = (((*var) >> 24) | (((*var) & 0x00FF0000) >> 8) | (((*var) & 0x0000FF00) << 8) | ((*var) << 24));
		output += std::format("{:08x}", *var);
	}
	return output;

}
