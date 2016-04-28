#pragma once
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "Player.h"
#include "iniParser\SimpleIni.h"
class Collision
{
public:
	Collision();
	Collision(const char *, int, ScriptParser);
	bool collision(int,int) ;
	~Collision();
private:
	int m_w;
	int m_h;
	ScriptParser m_scripts;
	std::vector<std::vector<std::string>> m_col;
};

