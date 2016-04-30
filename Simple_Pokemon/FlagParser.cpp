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

bool FlagParser::checkFlag(std::string flag) const
{
	for(int i=0;i<m_flags.size();++i)
		if(m_flags[i].ID==flag)
			return m_flags[i].activated;
	return false;
}

void FlagParser::setFlag(std::string flag, bool state)
{
	for (int i = 0; i<m_flags.size(); ++i)
		if (m_flags[i].ID == flag)
			m_flags[i].activated = state;
		
}

void FlagParser::save()
{
	ofstream fichier("data/flags.flag", ios::out | ios::trunc);
	for (int i = 0; i < m_flags.size(); ++i)
		fichier << "0x" << (m_flags[i].activated) << m_flags[i].ID << endl;
	fichier.close();
}


FlagParser::~FlagParser()
{
	
}
