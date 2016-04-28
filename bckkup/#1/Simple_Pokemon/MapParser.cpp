#include "MapParser.hpp"
#include <sstream>

#include <iostream>

using namespace std;

MapParser::MapParser(const char * ini_file,int mapID):m_file("")
{
	CSimpleIni ini;
	stringstream strValue1;
	stringstream strValue2;

	ini.SetUnicode();
	ini.LoadFile(ini_file);

	string mapID_s = "";
	mapID_s = to_string(mapID);

	auto val_w_c_char= ini.GetValue(mapID_s.c_str(), "taille_largeur", "default");
	auto val_h_c_char = ini.GetValue(mapID_s.c_str(), "taille_hauteur", "default");
	
	strValue1 << val_w_c_char;
	strValue1 >> m_w;

	strValue2 << val_h_c_char;
	strValue2 >> m_h;

	ifstream fichier(ini.GetValue(mapID_s.c_str(), "emplacement", "default"), ios::in);
	getline(fichier, m_file);


	fichier.close();	

	m_scr_parse.operate(ini.GetValue(mapID_s.c_str(), "scripts", "default"));
}

const int * MapParser::getMap() 
{


	m_map = new int[m_w*m_h];
	
	auto array = split(m_file, ',');
	for (int i = 0; i < m_w*m_h; ++i)
		m_map[i] = stoi(array[i]);
	

	return static_cast<const int*>(m_map);
}

ScriptParser MapParser::getParser() const
{
	return m_scr_parse;
}



MapParser::~MapParser()
{
	delete [] m_map;
}