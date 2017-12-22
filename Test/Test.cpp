// Test.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <chrono>

template<typename N>
void printVec(const std::vector<N>& vec)
{
	for (const N& elem : vec)
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;
}

template<typename N>
void iterateOnSets(std::vector<N>& vec, size_t placed, long& counter)
{
	int length = vec.size();
	
	if (placed == length)
	{
		//printVec(vec);
		++counter;
	}
	else
	{
		std::vector<N> vec2 = vec;
		iterateOnSets(vec2, placed + 1, counter);
		for (int k(placed+1); k < length; ++k)
		{
			vec2 = vec;
			std::swap(vec2[k], vec2[placed]);
			iterateOnSets(vec2, placed+1, counter);
		}
	}
}

template<typename N>
void shuffle(std::vector<N>& vec, long& counter)
{
	iterateOnSets(vec, 0, counter);
}

int main()
{
	std::vector<int> vec;
	int n = 10;
	for (int i(n); i--;)
	{
		vec.push_back(n-i);
	}

	/*std::vector<char> vec;
	vec.push_back('A');
	vec.push_back('B');
	vec.push_back('C');
	vec.push_back('D');
	vec.push_back('E');*/

	int n_tests = 20;
	double meanTime = 0;
	double meanSpeed = 0;
	long counter = 0;

	for (int i(n_tests); i--;)
	{
		counter = 0;
		std::chrono::time_point<std::chrono::system_clock> start, end;

		std::cout << "starting test [" << n_tests-i << "]" << std::endl;
		start = std::chrono::system_clock::now();
		shuffle(vec, counter);
		end = std::chrono::system_clock::now();

		double elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

		meanTime += elapsed_ms;

		double speed = counter / elapsed_ms * 1000;

		meanSpeed += speed;
	}

	std::cout << "\n=============================" << std::endl;
	std::cout << n << " elements" << std::endl;
	std::cout << "Speed: " << meanSpeed / double(n_tests) << " shuffles/sec" << std::endl;
	std::cout << counter << " shuffles in " << meanTime / double(n_tests) << " ms)" << std::endl;
	std::cout << "=============================\n" << std::endl;

    return 0;
}

