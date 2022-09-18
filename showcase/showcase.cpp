#include <iostream>
#include <string>
#include <array>
#include "pstl_array.h"
#include "pstl_vector.h"
#include "pstl_random.h"
#include "pstl_chrono.h"
#include "pstl_cryptography.h"

int main()
{
	// Pseudo Random Number Generation Showcase
	std::cout << "Random Number Generation -> " << std::endl;

	std::cout << "PRNG Mersenne Twister Integer: ";
	for (int i = 0; i < 5; i++)
		std::cout << pstl::random::mersenne_twister::randint(52) << " ";

	std::cout << std::endl << "PRNG Mersenne Twister Float: ";
	for (int i = 0; i < 5; i++)
		std::cout << pstl::random::mersenne_twister::randfloat() << " ";
	
	std::cout << std::endl << "PRNG LCG Integer: ";
	for (int i = 0; i < 5; i++)
		std::cout << pstl::random::linear_congruential_generator::randint(2) << " ";

	std::cout << std::endl << "PRNG LCG Float: ";
	for (int i = 0; i < 5; i++)
		std::cout << pstl::random::linear_congruential_generator::randfloat() << " ";

	std::cout << std::endl << "PRNG Middle-Squares Integer: ";
	for (int i = 0; i < 5; i++)
		std::cout << pstl::random::middle_squares::randint(594231) << " ";

	std::cout << std::endl << "PRNG Middle-Squares Float: ";
	for (int i = 0; i < 5; i++)
		std::cout << pstl::random::middle_squares::randfloat(594231) << " ";

	std::cout << std::endl << "PRNG Blum Blum Shub Integer: ";
	for (int i = 0; i < 5; i++)
		std::cout << pstl::random::blum_blum_shub::randint(594231) << " ";

	std::cout << std::endl << "PRNG Blum Blum Shub Float: ";
	for (int i = 0; i < 5; i++)
		std::cout << pstl::random::blum_blum_shub::randfloat(594231) << " ";

	std::cout << std::endl << std::endl << "--------------------" << std::endl << std::endl;

	// Cryptgraphy Showcase

	std::cout << "MD5 hashing (RFC 1321 Test Suite) ->" << std::endl;
	std::string text = "";
	std::cout << pstl::cryptography::hashing::md5::digest(text) << ": " << text << std::endl;
	text = "a";
	std::cout << pstl::cryptography::hashing::md5::digest(text) << ": " << text << std::endl;
	text = "abc";
	std::cout << pstl::cryptography::hashing::md5::digest(text) << ": " << text << std::endl;
	text = "message digest";
	std::cout << pstl::cryptography::hashing::md5::digest(text) << ": " << text << std::endl;
	text = "abcdefghijklmnopqrstuvwxyz";
	std::cout << pstl::cryptography::hashing::md5::digest(text) << ": " << text << std::endl;
	text = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
	std::cout << pstl::cryptography::hashing::md5::digest(text) << ": " << text << std::endl;
	text = "12345678901234567890123456789012345678901234567890123456789012345678901234567890";
	std::cout << pstl::cryptography::hashing::md5::digest(text) << ": " << text << std::endl;

	
	std::cout << std::endl << std::endl << "Basic Caeser Cipher ->" << std::endl;
	std::string caeser = "The quick brown fox jumped over the lazy dog";
	std::cout << "Text: " << caeser << std::endl;
	pstl::cryptography::ciphers::caeser_cipher::encrypt(caeser, 2);
	std::cout << "Encrypted: " << caeser << std::endl;
	pstl::cryptography::ciphers::caeser_cipher::decrypt(caeser, 2);
	std::cout << "Decrypted: " << caeser << std::endl;

	std::cout << std::endl << std::endl << "--------------------" << std::endl << std::endl;

	//Array Showcase

	std::cout << "Arrays From Scratch ->" << std::endl;
	pstl::array<int, 5> intarr = { 1, 2, 3, 4, 5 };
	std::cout << "Initialized Array: ";
	intarr.print();
	intarr.reverse();
	std::cout << "Array Reverse: ";
	intarr.print();
	std::cout << "Negative Indexing: ";
	std::cout << intarr[-3] << ", " << intarr[-11] << std::endl;
	std::cout << "Range Based For Loops using Iterators: ";
	for (auto& item : intarr)
		std::cout << item << " ";

	std::cout << std::endl;
	intarr.fill(10);
	std::cout << "Array Fill: ";
	intarr.print();
	std::cout << "Fill Selected Segment: ";
	intarr.fill(9, intarr.begin() + 1, intarr.end() - 1);
	intarr.print();

	std::cout << "String Arrays - " << std::endl;
	pstl::array<std::string, 5> names = {"John", "Paul", "George", "Ringo", "Prashant"};
	std::cout << "Display Methods: " << std::endl;
	names.print();
	std::cout << names << std::endl;
	std::cout << "String Array Reverse: ";
	names.reverse();
	names.print();
	std::cout << "String Array Negative Indexing: ";
	std::cout << names[-1] << std::endl;

	std::cout << "Array Swaps - " << std::endl;
	pstl::array<int, 5> intarr2 = { 6, 7, 8, 9, 10 };
	intarr2.swap(intarr);
	intarr2.print();
	intarr.print();
	
	std::cout << "Array Swap Segment - " << std::endl;
	intarr.swap(intarr2, intarr.begin() + 1, intarr.end() - 1);
	intarr2.print();
	intarr.print();

	std::cout << "Array Sorting - " << std::endl;
	pstl::array<int, 7> sorttest = { 3, 2, 4, 1, 1, 1, 5};
	std::cout << "Original: ";
	sorttest.print();
	sorttest.sort(pstl::sort_method::bubble, pstl::sort_order::descending);
	std::cout << "Sort Descending: ";
	sorttest.print();
	sorttest.sort(pstl::sort_method::bubble, pstl::sort_order::ascending, sorttest.begin() + 1, sorttest.end() - 1);
	std::cout << "Sort Segment Ascending: ";
	sorttest.print();

	std::cout << std::endl << std::endl << "--------------------" << std::endl << std::endl;
	
	// Vector Showcase
	std::cout << "Vectors From Scratch ->" << std::endl;
	pstl::vector<int> vec2 = { 1, 2, 3, 4, 5 };
	std::cout << "Initialized Vector Direct: ";
	vec2.print();
	std::cout << "Pop Back: ";
	vec2.pop_back();
	vec2.print();

	pstl::vector<const char*> vec3 = { "hello", "my", "name", "is", "Prashant" };
	std::cout << "String Vector: ";
	vec3.print();
	std::cout << "Emplace Back: ";
	vec3.emplace_back("Sinha");
	vec3.print();
	std::cout << "Negative Indexing: ";
	std::cout << vec3[-1] << std::endl;

	std::cout << "Range Based For Loop Using Iterators: ";
	for (auto& item : vec3)
		std::cout << item << " ";

	std::cout << std::endl;
	vec3.sort(pstl::sort_method::bubble, pstl::sort_order::descending, vec3.begin()+1, vec3.end()-1);
	std::cout << "Vector Sort (Segment): ";
	vec3.print();
	std::cout << "Vector Reverse: ";
	vec3.reverse();
	vec3.print();

	std::cout << "Vector Swap: " << std::endl;
	pstl::vector<const char *> vec4 = { "this", "is" , "a", "new", "test", "hello"};
	vec4.swap(vec3);
	vec4.print();
	vec3.print();

	std::cout << std::endl << std::endl << "--------------------" << std::endl << std::endl;

	// Timing Showcase
	std::cout << "PSTL Timer Class (& Timing Comparison) ->" << std::endl;

	{
		pstl::chrono::timer Timer("vector reverse pstl");
		vec3.reverse();
	}

	std::vector<const char*> vec5 = { "this", "is" , "a", "new", "test", "hello" };

	{
		pstl::chrono::timer Timer("vector reverse std");
		std::reverse(vec5.begin(), vec5.end());
	}

	{
		pstl::chrono::timer Timer("vector push back pstl");
		vec3.push_back("newval");
	}

	{
		pstl::chrono::timer Timer("vector push back std");
		vec5.push_back("newval");
	}

	pstl::array<int, 5> speedtest = { 5, 2, 1, 4, 3 };
	std::array<int, 5> speedtest2 = { 5, 2, 1, 4, 3 };

	{
		pstl::chrono::timer Timer("array reverse pstl");
		speedtest.reverse();
	}

	{
		pstl::chrono::timer Timer("array reverse std");
		std::reverse(speedtest2.begin(), speedtest2.end());
	}

	{
		pstl::chrono::timer Timer("array sort pstl");
		speedtest.sort();
	}

	{
		pstl::chrono::timer Timer("array sort std");
		std::sort(speedtest2.begin(), speedtest2.end());
	}


	std::cin.get();
}