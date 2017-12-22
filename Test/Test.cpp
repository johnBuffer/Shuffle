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
void iterateOnSets(std::vector<N>& vec, std::vector<N> freeSlots, std::vector<N> result, long& counter)
{
	int placed = result.size();
	int length = vec.size();
	
	if (placed == length)
	{
		//printVec(result);
		++counter;
	}
	else
	{
		for (int k(0); k < length; ++k)
		{
			if (freeSlots[k])
			{
				std::vector<N> freeSlots2 = freeSlots;
				std::vector<N> result2 = result;

				result2.push_back(vec[k]);
				freeSlots2[k] = 0;
				iterateOnSets(vec, freeSlots2, result2, counter);
			}
		}
	}
}

template<typename N>
void shuffle(std::vector<N>& vec, long& counter)
{
	std::vector<N> result;
	std::vector<N> freeSlots;

	for (int i(vec.size()); i--;)
	{
		freeSlots.push_back(1);
	}

	iterateOnSets(vec, freeSlots, result, counter);
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

	long counter = 0;
	std::chrono::time_point<std::chrono::system_clock> start, end;
	
	std::cout << "start" << std::endl;
	start = std::chrono::system_clock::now();
	shuffle(vec, counter);
	end = std::chrono::system_clock::now();
	std::cout << "done: " << counter << " shuffles checked" << std::endl;

	double elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	int speed = counter / elapsed_ms * 1000;
	std::cout << "Speed: " << speed << " shuffles/sec (" << counter << " shuffles in " << elapsed_ms << " ms)" << std::endl;

    return 0;
}

