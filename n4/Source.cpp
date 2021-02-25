#include <iostream>
#include <set>
#include <random>
#include <string>
#include <chrono>
#include <vector>

#include <boost\functional\hash.hpp>


std::multiset < std::string > make_random_words(std::size_t N, std::size_t length) // length = 10 - good enough
{
    std::uniform_int_distribution <> letter(97, 122);
    std::default_random_engine e(static_cast <std::size_t> (
        std::chrono::system_clock::now().time_since_epoch().count()));

    std::multiset < std::string > words;

    for (std::string s(length, '_'); std::size(words) < N; words.insert(s))
        for (auto& c : s)
            c = letter(e);

    return words;
}




unsigned int RSHash(const char* str, unsigned int length)
{
	unsigned int b = 378551;
	unsigned int a = 63689;
	unsigned int hash = 0;
	unsigned int i = 0;

	for (i = 0; i < length; ++str, ++i)
	{
		hash = hash * a + (*str);
		a = a * b;
	}

	return hash;
}

unsigned int JSHash(const char* str, unsigned int length)
{
	unsigned int hash = 1315423911;
	unsigned int i = 0;

	for (i = 0; i < length; ++str, ++i)
	{
		hash ^= ((hash << 5) + (*str) + (hash >> 2));
	}

	return hash;
}

unsigned int PJWHash(const char* str, unsigned int length)
{
	const unsigned int BitsInUnsignedInt = (unsigned int)(sizeof(unsigned int) * 8);
	const unsigned int ThreeQuarters = (unsigned int)((BitsInUnsignedInt * 3) / 4);
	const unsigned int OneEighth = (unsigned int)(BitsInUnsignedInt / 8);
	const unsigned int HighBits =
		(unsigned int)(0xFFFFFFFF) << (BitsInUnsignedInt - OneEighth);
	unsigned int hash = 0;
	unsigned int test = 0;
	unsigned int i = 0;

	for (i = 0; i < length; ++str, ++i)
	{
		hash = (hash << OneEighth) + (*str);

		if ((test = hash & HighBits) != 0)
		{
			hash = ((hash ^ (test >> ThreeQuarters)) & (~HighBits));
		}
	}

	return hash;
}

unsigned int ELFHash(const char* str, unsigned int length)
{
	unsigned int hash = 0;
	unsigned int x = 0;
	unsigned int i = 0;

	for (i = 0; i < length; ++str, ++i)
	{
		hash = (hash << 4) + (*str);

		if ((x = hash & 0xF0000000L) != 0)
		{
			hash ^= (x >> 24);
		}

		hash &= ~x;
	}

	return hash;
}

unsigned int BKDRHash(const char* str, unsigned int length)
{
	unsigned int seed = 131; /* 31 131 1313 13131 131313 etc.. */
	unsigned int hash = 0;
	unsigned int i = 0;

	for (i = 0; i < length; ++str, ++i)
	{
		hash = (hash * seed) + (*str);
	}

	return hash;
}

unsigned int SDBMHash(const char* str, unsigned int length)
{
	unsigned int hash = 0;
	unsigned int i = 0;

	for (i = 0; i < length; ++str, ++i)
	{
		hash = (*str) + (hash << 6) + (hash << 16) - hash;
	}

	return hash;
}

unsigned int DJBHash(const char* str, unsigned int length)
{
	unsigned int hash = 5381;
	unsigned int i = 0;

	for (i = 0; i < length; ++str, ++i)
	{
		hash = ((hash << 5) + hash) + (*str);
	}

	return hash;
}

unsigned int DEKHash(const char* str, unsigned int length)
{
	unsigned int hash = length;
	unsigned int i = 0;

	for (i = 0; i < length; ++str, ++i)
	{
		hash = ((hash << 5) ^ (hash >> 27)) ^ (*str);
	}

	return hash;
}

unsigned int APHash(const char* str, unsigned int length)
{
	unsigned int hash = 0xAAAAAAAA;
	unsigned int i = 0;

	for (i = 0; i < length; ++str, ++i)
	{
		hash ^= ((i & 1) == 0) ? ((hash << 7) ^ (*str) * (hash >> 3)) :
			(~((hash << 11) + ((*str) ^ (hash >> 5))));
	}

	return hash;
}

int main()
{
	int N = 1000;
	
	std::multiset<std::string> w = make_random_words(N, 3);


    //00 - RS Hash Function

	std::set<int> h0;

	std::vector <unsigned int> v0;

	int k0 = 0;

	for (auto i : w)
	{
		if ((h0.insert(RSHash(i.c_str(), i.size())).second) == false)
		{
			k0 += 1;
		}
		v0.push_back(k0);
	}

	//for (auto i : v0)
	//{
	//	std::cout << i << ", ";
	//}

	std::cout << std::endl;


	//01 - JS Hash Function

	std::set<int> h1;

	std::vector <unsigned int> v1;

	int k1 = 0;

	for (auto i : w)
	{
		if ((h1.insert(JSHash(i.c_str(), i.size())).second) == false)
		{
			k1 += 1;
		}
		v1.push_back(k1);
	}

	//for (auto i : v1)
	//{
	//	std::cout << i << ", ";
	//}

	std::cout << std::endl;


	//02 - PJW Hash Function

	std::set<int> h2;

	std::vector <unsigned int> v2;

	int k2 = 0;

	for (auto i : w)
	{
		if ((h2.insert(PJWHash(i.c_str(), i.size())).second) == false)
		{
			k2 += 1;
		}
		v2.push_back(k2);
	}

	//for (auto i : v2)
	//{
	//	std::cout << i << ", ";
	//}

	std::cout << std::endl;

	
	//03 - ELF Hash Function

	std::set<int> h3;

	std::vector <unsigned int> v3;

	int k3 = 0;

	for (auto i : w)
	{
		if ((h3.insert(ELFHash(i.c_str(), i.size())).second) == false)
		{
			k3 += 1;
		}
		v3.push_back(k3);
	}

	//for (auto i : v3)
	//{
	//	std::cout << i << ", ";
	//}

	std::cout << std::endl;


	//04 - BKDR Hash

	std::set<int> h4;

	std::vector <unsigned int> v4;

	int k4 = 0;

	for (auto i : w)
	{
		if ((h4.insert(BKDRHash(i.c_str(), i.size())).second) == false)
		{
			k4 += 1;
		}
		v4.push_back(k4);
	}

	//for (auto i : v4)
	//{
	//	std::cout << i << ", ";
	//}

	std::cout << std::endl;


	//05 - SDBM Hash

	std::set<int> h5;

	std::vector <unsigned int> v5;

	int k5 = 0;

	for (auto i : w)
	{
		if ((h5.insert(SDBMHash(i.c_str(), i.size())).second) == false)
		{
			k5 += 1;
		}
		v5.push_back(k5);
	}

	//for (auto i : v5)
	//{
	//	std::cout << i << ", ";
	//}

	std::cout << std::endl;


	//06 - DJBH 

	std::set<int> h6;

	std::vector <unsigned int> v6;

	int k6 = 0;

	for (auto i : w)
	{
		if ((h6.insert(DJBHash(i.c_str(), i.size())).second) == false)
		{
			k6 += 1;
		}
		v6.push_back(k6);
	}

	//for (auto i : v6)
	//{
	//	std::cout << i << ", ";
	//}

	std::cout << std::endl;


	//07 - DEK

	std::set<int> h7;

	std::vector <unsigned int> v7;

	int k7 = 0;

	for (auto i : w)
	{
		if ((h7.insert(DEKHash(i.c_str(), i.size())).second) == false)
		{
			k7 += 1;
		}
		v7.push_back(k7);
	}

	//for (auto i : v7)
	//{
	//	std::cout << i << ", ";
	//}

	std::cout << std::endl;

	//08 - AP Hash

	std::set<int> h8;

	std::vector <unsigned int> v8;

	int k8 = 0;

	for (auto i : w)
	{
		if ((h8.insert(APHash(i.c_str(), i.size())).second) == false)
		{
			k8 += 1;
		}
		v8.push_back(k8);
	}

	for (auto i : v8)
	{
		std::cout << i << ", ";
	}

	std::cout << std::endl;

	return EXIT_SUCCESS;
}