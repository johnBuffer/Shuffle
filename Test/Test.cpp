// Test.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <string>
#include <map>
#include <unordered_map>
#include "utf8\utf8.h"

typedef std::map<std::string, std::vector<unsigned short>> w2smap;
typedef std::map<std::vector<unsigned short>, std::string> s2wmap;

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
void iterateOnSets(std::vector<N>& vec, size_t placed)
{	
	size_t length = vec.size();
	if (placed != length)
	{
		std::vector<N> vec2 = vec;
		iterateOnSets(vec2, placed + 1);

		for (size_t i(placed + 1); i < length; ++i)
		{
			vec2 = vec;
			std::swap(vec2[i], vec2[placed]);
			iterateOnSets(vec2, placed+1);
		}
	}
}

template<typename N>
void shuffle(std::vector<N>& vec)
{
	iterateOnSets(vec, 0);
}

long fact(int n)
{
	long result = 1;
	for (int i(1); i<n; ++i)
		result *= i+1;
	
	return result;
}

void loadDict(const std::string& filename, s2wmap& snd2str, w2smap& str2snd)
{
	std::ifstream file(filename);

	if (file.is_open())
	{
		std::string line;
		int invalid = 0;
		while (std::getline(file, line))
		{
			if (line[0] != '#')
			{
				size_t sep = line.find('_');
				std::string word = line.substr(0, sep);
				std::string sound = line.substr(sep + 1);

				std::string::iterator end_it = utf8::find_invalid(line.begin(), line.end());
				if (end_it != line.end()) {
					//std::cout << "Invalid UTF-8" << std::endl;
					++invalid;
					//std::cout << "This part is fine: " << std::string(line.begin(), end_it) << "\n";
				}
				else
				{
					std::vector<unsigned short> utf16line;
					utf8::utf8to16(line.begin(), end_it, back_inserter(utf16line));

					snd2str[utf16line] = word;
					str2snd[word] = utf16line;
				}

			}
			else
			{
				//std::cout << "Commented line skipped" << std::endl;
			}
		}

		std::cout << snd2str.size() << " words loaded (" << invalid << " invalid UTF-8 words)" << std::endl;
		file.close();
	}
}

void parseStr(const std::string& str, s2wmap& s2w, w2smap& w2s)
{
	auto& it = w2s.find(str);
	if (it != w2s.end())
	{
		std::vector<unsigned short> snd = it->second;
		auto& it2 = s2w.find(snd);
		if (it2 != s2w.end())
		{
			std::cout << "Found: " << it2->second << std::endl;
		}
		else
		{
			std::cout << "Word not found..." << std::endl;
		}
	}
	else
	{
		std::cout << "Sound not found..." << std::endl;
	}
}

int main()
{
	std::map<std::vector<int>, int> lol;

	s2wmap snd2str;
	w2smap str2snd;

	loadDict("dict.txt", snd2str, str2snd);

	parseStr(u8"albinos", snd2str, str2snd);

	std::vector<int> vec;
	int n = 9;
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
	long counter = fact(n);

	for (int i(n_tests); i--;)
	{
		std::chrono::time_point<std::chrono::system_clock> start, end;

		std::cout << "starting test [" << n_tests-i << "]" << std::endl;
		start = std::chrono::system_clock::now();
		shuffle(vec);
		end = std::chrono::system_clock::now();

		double elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
		meanTime += elapsed_ms;

		double speed = counter / elapsed_ms * 1000;
		meanSpeed += speed;
	}

	std::cout << "\n=============================" << std::endl;
	std::cout << n << " elements" << std::endl;
	std::cout << "Speed: " << meanSpeed / double(n_tests) << " shuffles/sec" << std::endl;
	std::cout << counter << " shuffles in " << meanTime / double(n_tests) << " ms" << std::endl;
	std::cout << "=============================\n" << std::endl;

    return 0;
}

