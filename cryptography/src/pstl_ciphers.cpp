#include <iostream>
#include <string>
#include <cstring>
#include "pstl_cryptography.h"

void pstl::cryptography::ciphers::caeser_cipher::encrypt(std::string& str, int shift)
{
	for (auto& letter : str)
	{
		if (std::isalpha(letter))
		{
			auto [start_letter, end_letter] = std::isupper(letter) ? std::make_tuple('A', 'Z') : std::make_tuple('a', 'z');
			letter = letter + (char)shift;
			letter = letter <= end_letter ? letter : letter + start_letter - end_letter - 1;
		}
	}
}

void pstl::cryptography::ciphers::caeser_cipher::decrypt(std::string& str, int shift)
{
	for (auto& letter : str)
	{
		if (std::isalpha(letter))
		{
			auto [start_letter, end_letter] = std::isupper(letter) ? std::make_tuple('A', 'Z') : std::make_tuple('a', 'z');
			letter = letter - (char)shift;
			letter = letter >= start_letter ? letter : letter - start_letter + end_letter + 1;
		}
	}

}