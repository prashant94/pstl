# pstl

This is my attempt at creating several features from the C++ STL from scratch, along with some other standard algorithms like crypographic ciphers and hashes, pseudo random number generators etc. PSTL is Prashant's STL. The utilities generally have some extra features not present in the original STL. Extra featues include things like negative indexing on arrays and vectors, similar to Python. But most of these are not ready for production deployment. This is just a sandbox for me to improve my C++ skills. The code for each segment is separated into individual projects

Most of the exact functionalities and usage is present and defined in the "Showcase" project, but a sample of some of the methods are provided below.

&nbsp;
# Table of Contents
- [pstl](#pstl)
- [Table of Contents](#table-of-contents)
- [Currently available features](#currently-available-features)
  - [**1. Pseudo Random Number Generators**](#1-pseudo-random-number-generators)
    - [**1.1 Mersenne Twister**](#11-mersenne-twister)
    - [**1.2 Linear Congruential Generator**](#12-linear-congruential-generator)
    - [**1.3 Blum Blum Shub**](#13-blum-blum-shub)
    - [**1.4 Middle Squares Method**](#14-middle-squares-method)
  - [**2. Cryptography**](#2-cryptography)
    - [**2.1 Hashing - MD5**](#21-hashing---md5)
    - [**2.2 Ciphers - Simple Caeser**](#22-ciphers---simple-caeser)
  - [**3. Arrays from Scratch**](#3-arrays-from-scratch)
    - [**3.1 Initialization**](#31-initialization)
    - [**3.2 Display & Print methods**](#32-display--print-methods)
    - [**3.3 Reverse (Full and Segment)**](#33-reverse-full-and-segment)
    - [**3.4 Negative Indexing**](#34-negative-indexing)
    - [**3.5 Range Based For Loops Using Iterators**](#35-range-based-for-loops-using-iterators)
    - [**3.6 Swap (Full and Segment)**](#36-swap-full-and-segment)
    - [**3.7 Fill (Full and Segment)**](#37-fill-full-and-segment)
    - [**3.8 Sort (Full and Segment)**](#38-sort-full-and-segment)
  - [**4. Vectors from Scratch**](#4-vectors-from-scratch)
    - [**4.1 Initialization**](#41-initialization)
    - [**4.2 Push Back and Pop Back**](#42-push-back-and-pop-back)
    - [**4.2 Emplace Back**](#42-emplace-back)
  - [**5. Timers & Chrono**](#5-timers--chrono)
    - [**5.1 Scoped Timer**](#51-scoped-timer)
- [Licence](#licence)

&nbsp;
# Currently available features

## **1. Pseudo Random Number Generators**

All PRNG classes are static singletons and have a randint and a randfloat method. The randfloat method returns a value between 0 and 1. Examples are given for first 2, but the pattern is the same for the other classes as well

### **1.1 Mersenne Twister**

Usage: 
```c++
for (int i = 0; i < 5; i++)
		std::cout << pstl::random::mersenne_twister::randfloat() << " ";
```
Sample Output:
```
0.420684 0.618422 0.827845 0.0982845 0.635213
```

### **1.2 Linear Congruential Generator**

Usage: 
```c++
for (int i = 0; i < 5; i++)
		std::cout << pstl::random::linear_congruential_generator::randfloat() << " ";
```
Sample Output:
```
0.826898 0.914796 0.850389 0.619592 0.992774
```

### **1.3 Blum Blum Shub**

### **1.4 Middle Squares Method**

&nbsp;
#

## **2. Cryptography**

### **2.1 Hashing - MD5**

Follows RFC 1321 (https://www.ietf.org/rfc/rfc1321.txt). The usage and outputs from the original RFC test suite are given below.

Usage:
```c++
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
```

Output:

```
d41d8cd98f00b204e9800998ecf8427e:
0cc175b9c0f1b6a831c399e269772661: a
900150983cd24fb0d6963f7d28e17f72: abc
f96b697d7cb7938d525a2f31aaf161d0: message digest
c3fcd3d76192e4007dfb496cca67e13b: abcdefghijklmnopqrstuvwxyz
d174ab98d277d9f5a5611c2c9f419d9f: ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789
57edf4a22be3c955ac49da2e2107b67a: 12345678901234567890123456789012345678901234567890123456789012345678901234567890
```

### **2.2 Ciphers - Simple Caeser**

Usage:

```c++
std::string caeser = "The quick brown fox jumped over the lazy dog";
std::cout << "Text: " << caeser << std::endl;
pstl::cryptography::ciphers::caeser_cipher::encrypt(caeser, 2);
std::cout << "Encrypted: " << caeser << std::endl;
pstl::cryptography::ciphers::caeser_cipher::decrypt(caeser, 2);
std::cout << "Decrypted: " << caeser << std::endl;
```

Output:

```
Text: The quick brown fox jumped over the lazy dog
Encrypted: Vjg swkem dtqyp hqz lworgf qxgt vjg ncba fqi
Decrypted: The quick brown fox jumped over the lazy dog
```

&nbsp;
#

## **3. Arrays from Scratch**

Arrays here are fixed sized objects with stack allocated memory of a given type.

### **3.1 Initialization**

```c++
pstl::array<int, 5> intarr = { 1, 2, 3, 4, 5 };
pstl::array<std::string, 5> names = {"John", "Paul", "George", "Ringo", "Prashant"};
pstl::array<char, 5> chararray;
```

### **3.2 Display & Print methods**

Usage (any of the two below will work on array of any type): 

```c++
names.print();
std::cout << intarr << std::endl;
```

Output:

```
John, Paul, George, Ringo, Prashant,
1, 2, 3, 4, 5,
```

### **3.3 Reverse (Full and Segment)**

Usage:

```c++
intarr.reverse(intarr.begin() + 1,intarr.end() - 1); //reverse segment
names.reverse(); //full reverse
intarr.print();
names.print();
```

Output:

```
1, 4, 3, 2, 5,
Prashant, Ringo, George, Paul, John,
```

### **3.4 Negative Indexing**

Usage:

```c++
std::cout << names[-1] << " " << intarr[-2] << std::endl;
```

Output

```
John 2
```

### **3.5 Range Based For Loops Using Iterators**

Usage:

```c++
for (auto& item : intarr)
	std::cout << item << " ";
```

Output

```
1, 4, 3, 2, 5,
```

### **3.6 Swap (Full and Segment)**

Usage:

```c++
pstl::array<int, 5> intarr2 = { 6, 7, 8, 9, 10 };
intarr2.swap(intarr);
intarr2.print();
intarr.print();
intarr.swap(intarr2, intarr.begin() + 1, intarr.end() - 1); //swap segment
intarr.print();
```

Output

```
1, 4, 3, 2, 5,
6, 7, 8, 9, 10,
6, 4, 3, 2, 10,
```

### **3.7 Fill (Full and Segment)**

Usage:

```c++
intarr.fill(10);
intarr.print();
intarr.fill(9, intarr.begin() + 1, intarr.end() - 1);
intarr.print();
```

Output

```
10, 10, 10, 10, 10,
10, 9, 9, 9, 10,
```

### **3.8 Sort (Full and Segment)**

Sorting currently only supports using selection or bubble sort. More will be added later.

Usage:

```c++
pstl::array<int, 7> sorttest = { 3, 2, 4, 1, 1, 1, 5};
std::cout << "Original: ";
sorttest.print();
sortest.sort();
std::cout << "Sorted: ";
sortest.print()
sorttest.sort(pstl::sort_method::bubble, pstl::sort_order::descending);
std::cout << "Sort Descending: ";
sorttest.print();
sorttest.sort(pstl::sort_method::bubble, pstl::sort_order::ascending, sorttest.begin() + 1, sorttest.end() - 1);
std::cout << "Sort Segment Ascending: ";
sorttest.print();
```

Output

```
Original: 3, 2, 4, 1, 1, 1, 5,
Sorted: 1, 1, 1, 2, 3, 4, 5,
Sort Descending: 5, 4, 3, 2, 1, 1, 1,
Sort Segment Ascending: 5, 1, 1, 2, 3, 4, 1,
```

&nbsp;
#

## **4. Vectors from Scratch**

Vectors here are dynamically allocated arrays of a given type. The memory allocation is on the heap. The size of vector adjusts as new elements are pushed back. Most of the functions which are available for arrays also work exactly the same for vectors, including reversing, sorting, negative indexing, swapping, printing etc. So syntax similar to the one above can be used directly. But the vector class does provide some extra functions to push_back and pop_back elements. Also provides an emplace_back method which creates the object in memory. Details of these below

### **4.1 Initialization**

```c++
pstl::vector<int> intvector = { 1, 2, 3, 4, 5 };
pstl::vector<std::string> namesvec;
```

### **4.2 Push Back and Pop Back**

Usage: 

```c++
intvector.print();
intvector.push_back(6);
std::cout << "Push Back: ";
intvector.print();
std::cout << "Pop Back: ";
intvector.pop_back();
intvector.print();
```

Output:

```
1, 2, 3, 4, 5,
Push Back: 1, 2, 3, 4, 5, 6,
Pop Back: 1, 2, 3, 4, 5,
```

### **4.2 Emplace Back**

Usage: 

```c++
pstl::vector<const char*> vec3 = { "hello", "my", "name", "is", "Prashant" };
std::cout << "Const char Vector: ";
vec3.print();
std::cout << "Emplace Back: ";
vec3.emplace_back("Sinha");
vec3.print();
```

Output:

```
Const char Vector: hello, my, name, is, Prashant,
Emplace Back: hello, my, name, is, Prashant, Sinha,
```

&nbsp;
#

## **5. Timers & Chrono**

Timing functions. Timings for all the above implemented functions are also shown in the sandbox showcase project, as demonstration of how to use this.

### **5.1 Scoped Timer**

Usage: 

```c++
{
    pstl::chrono::timer Timer("vector reverse pstl");
    vec3.reverse();
}
```

Output:

```
vector reverse pstl | Timer took: 0.0003 ms
```




# Licence
MIT License

Copyright (c) 2022 Prashant Sinha

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.