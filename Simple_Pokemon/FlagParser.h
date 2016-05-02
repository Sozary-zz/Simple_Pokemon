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
	Flag operator[](int n) const
	{
		if (n < m_flags.size())
			return m_flags[n];
		return m_flags[0];
	}
private:
	std::vector<Flag> m_flags;
};

