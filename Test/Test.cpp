// Test.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>

void printVec(const std::vector<int>& vec)
{
	for (const int& elem : vec)
	{
		std::cout << elem << ' ';
	}
	std::cout << std::endl;
}

void iterateOnSets(std::vector<int>& vec, std::vector<int> freeSlots, std::vector<int> result)
{
	int placed = result.size();
	int length = vec.size();
	
	if (placed == length)
	{
		printVec(result);
	}
	else
	{
		for (int k(0); k < length; ++k)
		{
			if (freeSlots[k])
			{
				std::vector<int> freeSlots2 = freeSlots;
				std::vector<int> result2 = result;

				result2.push_back(vec[k]);
				freeSlots2[k] = 0;
				iterateOnSets(vec, freeSlots2, result2);
			}
		}
	}
}

void shuffle(std::vector<int>& vec)
{
	std::vector<int> result;
	std::vector<int> freeSlots;

	for (int i(vec.size()); i--;)
	{
		freeSlots.push_back(1);
	}

	iterateOnSets(vec, freeSlots, result);
}

int main()
{
	std::vector<int> vec;
	for (int i(9); i--;)
	{
		vec.push_back(9-i);
	}

	shuffle(vec);

    return 0;
}

