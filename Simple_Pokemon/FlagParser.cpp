#include "FlagParser.h"
#include <iostream>

using namespace std;

FlagParser::FlagParser()
{
	ifstream fichier("data/flags.flag", ios::in);
	string tmp;
	while (getline(fichier, tmp))
	{
		m_flags.push_back(Flag{
		(tmp[2] == '1'),
		tmp.substr(3,3)
		
		});
		
	}

}


FlagParser::~FlagParser()
{
}
