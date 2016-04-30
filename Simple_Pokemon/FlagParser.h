#pragma once

#include <fstream>
#include <vector>

struct Flag
{

};
class FlagParser
{
public:
	FlagParser();
	~FlagParser();
private:
	std::vector<Flag> m_flags;
};

