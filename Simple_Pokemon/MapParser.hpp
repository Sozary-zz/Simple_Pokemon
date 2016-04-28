#pragma once
#include "ScriptParser.hpp"
#include "iniParser\SimpleIni.h"


class MapParser
{
public:
	MapParser(const char*,int); // appelle aussi scriptParser
	const int* getMap() ;
	ScriptParser getParser() const;
	~MapParser();
private:
	int m_w;
	int m_h;
	std::string m_file;
	int* m_map;
	ScriptParser m_scr_parse;

};

