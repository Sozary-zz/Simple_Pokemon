#include "Utility.hpp"
#include <iostream>
using namespace std;
std::vector<std::string> split(std::string text, char sep){
	std::vector<std::string> tokens;
	std::size_t start = 0, end = 0;
	while ((end = text.find(sep, start)) != std::string::npos) {
		std::string temp = text.substr(start, end - start);
		if (temp != "") tokens.push_back(temp);
		start = end + 1;
	}
	std::string temp = text.substr(start);
	if (temp != "") tokens.push_back(temp);
	return tokens;
}

int distanceE(int a, int b, int c, int d)
{
	return abs(c-a)+abs(d-b);
}

