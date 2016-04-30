#pragma once

#include <fstream>
#include <vector>
#include <string>

struct Flag
{
	bool activated;
	std::string ID;
};
class FlagParser
{
public:
	FlagParser();
	~FlagParser();
private:
	std::vector<Flag> m_flags;
};

