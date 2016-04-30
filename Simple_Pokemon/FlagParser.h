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
	bool checkFlag(std::string) const;
	void setFlag(std::string, bool);
	void save();
	~FlagParser();
private:
	std::vector<Flag> m_flags;
};

