#include "ScriptParser.hpp"

using namespace std;




ScriptParser::ScriptParser()
{
}
Script& ScriptParser::operator[](int i)
{
	if (i > m_file.size())
	{
		return m_file[0];
	}
	return m_file[i];
}

ScriptParser::~ScriptParser()
{
}

void ScriptParser::operate(const char* path)
{
	ifstream fichier(path, ios::in);
	string file;
	while (getline(fichier, file))
	{
		auto arr = split(file, ':');
		vector<Offset> v_off(arr.size());
		int iPlace = 0;
		int iPerso;
		string face;
		for (int i = 0; i < arr.size(); ++i)
		{
			v_off[i].offset = arr[i];
			v_off[i].split();
		}
		// il nous faut le chemin d'accès au personnage + leur pos
		for (int i = 0; i < v_off.size(); ++i) // plus simple a explorer
		{
			if (v_off[i].script_type == "00")
				iPlace = i;
			if (v_off[i].script_type == "03")
			{
				iPerso = i;
				face = v_off[i].param;
			}
				
		}
	
		m_file.push_back(Script{ v_off , "data/personnages/" + v_off[iPerso].optionnal_param + "_" + face + ".png",Position{ stoi(v_off[iPlace].optionnal_param),stoi(v_off[iPlace].param) } }); // stoi et non hexa car la posX et y <<<<< 99
	}
}

int ScriptParser::size() const
{
	return m_file.size();
}

Script ScriptParser::nearScript(int x, int y,DIRECTION dir)
{

	for (int i = 0; i < m_file.size(); ++i)
	{
		cout << (distanceE(m_file[i].position.x * 16, m_file[i].position.y * 16, x, y) )<< endl;
		if (distanceE(m_file[i].position.x * 16, m_file[i].position.y * 16, x, y) <= 16)
		{
			cout << "test" << endl;
			Position tmp;
			switch (dir)
			{
			case DROITE:
				
				tmp.x = double(x);
				tmp.y = double(y) + 16;
				if (tmp.x == m_file[i].position.x * 16 && tmp.y == m_file[i].position.y * 16)
	
					return m_file[i];
				
					
				break;
			case BAS:
				
				tmp.x = double(x) ;
				tmp.y = double(y)+16;
				
				if (tmp.x == m_file[i].position.x*16 && tmp.y == m_file[i].position.y * 16)
				
					return m_file[i];
				
				break;
			case GAUCHE:
				
				tmp.x = double(x) - 16;
				tmp.y = double(y);
				if (tmp.x == m_file[i].position.x * 16 && tmp.y == m_file[i].position.y * 16)
				
					return m_file[i];
				
				break;
			case HAUT:
				
				tmp.x = double(x);
				tmp.y = double(y) - 16;
				if (tmp.x == m_file[i].position.x * 16 && tmp.y == m_file[i].position.y * 16)
				
					return m_file[i];
				
				break;
			case NONE:
				break;

			}

		}
	}
	return Script();
}
