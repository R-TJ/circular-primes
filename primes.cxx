#include <iostream>
#include <cmath>
#include "boost/multiprecision/cpp_int.hpp"
#include <mutex>
#include <thread>
#include <vector>

using namespace boost::multiprecision;

bool check_prime(cpp_int n)
{
	if (n < 2)
	[[unlikely]]{
		return false;
	}

	cpp_int t = n % 10;
	if(t == 2 || t == 4 || t == 5 || t == 6 || t == 8 || t == 0)
	{
		if(n == 2)[[unlikely]]{
		return true;
		}
		return false;
	}

	cpp_int root = boost::multiprecision::sqrt(n);
	for (cpp_int i = 2; i <= root; i++)
	{
		if (n % i == 0)
			return false;
	}

	return true;
}

bool running = true;
std::mutex mtx;
cpp_int n = 2;

void check_for_primes()
{
	while(running)
	{
		mtx.lock();
		cpp_int temp = n;
		n++;
		mtx.unlock();
		
		cpp_int num = temp;

		size_t digits = temp.str().size();
     		bool total_prime = true;

		cpp_int pow = boost::multiprecision::pow(static_cast<cpp_int>(10), static_cast<unsigned long long>(digits) - 1);
		for (int j = 0; j < digits; j++)
		{
			if (!check_prime(temp))
			{
				total_prime = false;
				break;
			}

			temp = temp / 10 + (temp % 10) * pow;// boost::multiprecision::pow(static_cast<cpp_int>(10), static_cast<unsigned long long>(digits) - 1);
		}

		if(total_prime)
		{
			std::cout << num << "\n";
		}
	}
}

int main(int argc, char* argv[])
{
	std::vector<std::thread> threads;
	for(int i = 0; i < std::stoi(argv[1]); i++)
	{
		threads.emplace_back(check_for_primes);
	}

	n = boost::multiprecision::pow((cpp_int)10, std::stoi(argv[2]));

		std::cin.get();

	running = false;

	for(auto& thread : threads)
	{
		thread.join();
	}
	
	std::cout << n << "\n";

	return 0;
}
