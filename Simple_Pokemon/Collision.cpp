#include "Collision.h"
#include <iostream>
using namespace std;
Collision::Collision(){}
Collision::Collision(const char * ini_file, int mapID, ScriptParser scripts):m_scripts(scripts)
{
	string content;
	CSimpleIni ini;
	stringstream strValue1;
	stringstream strValue2;

	ini.SetUnicode();
	ini.LoadFile(ini_file);

	string mapID_s = "";
	mapID_s = to_string(mapID);

	auto val_w_c_char = ini.GetValue(mapID_s.c_str(), "taille_largeur", "default");
	auto val_h_c_char = ini.GetValue(mapID_s.c_str(), "taille_hauteur", "default");

	strValue1 << val_w_c_char;
	strValue1 >> m_w;

	strValue2 << val_h_c_char;
	strValue2 >> m_h;

	ifstream fichier(ini.GetValue(mapID_s.c_str(), "collision", "default"), ios::in);
	getline(fichier, content);


	fichier.close();
	
	m_col.resize(m_h);
	int k = 0;
	for (int i = 0; i < m_h; ++i)
		m_col[i].resize(m_w);

	for (int i = 0; i < m_h; ++i)
	
		for (int j = 0; j < m_w; ++j)
		{
			
			m_col[i][j] = content[k];
			k+=2;
		}
	
}

bool Collision::collision(int x, int y) 
{
	bool indice = false;
	[&](bool* n) {
		for (int i = 0; i < m_scripts.size(); ++i)
			if (distanceE(x, y, m_scripts[i].position.x, m_scripts[i].position.y+1) == 0)
				*n= true;		
	}(&indice);

	
	if (x >= 0 && x < m_w && y >= 0 && y < m_h)
	{
		if (m_col[y][x] == "1" || indice)
			return true;
	}
	else
		return true;

	return false;
}


Collision::~Collision()
{
}
