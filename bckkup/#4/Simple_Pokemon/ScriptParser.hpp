#pragma once
#include <string>
#include <iostream>
#include "Utility.hpp"


enum  DIRECTION { DROITE, BAS, GAUCHE, HAUT , NONE};

struct Offset // pour eviter de déclarer une autre classe
{
	std::string offset;

	std::string script_type;
	std::string optionnal_param;
	std::string param;

	bool operator==(Offset & a)
	{
		return (a.offset == offset);
	}


	void split()
	{
		script_type = "";
		optionnal_param = "";
		optionnal_param = "";
		param = "";
		script_type += offset[2];
		script_type+=offset[3];
		optionnal_param += offset[4];
		optionnal_param+=offset[5];
		param += offset[6];
		param+=offset[7];
	}
};

struct Script
{
	std::vector<Offset> instructions;
	std::string m_perso_path;
	Position position;

};
class ScriptParser
{
public:
	ScriptParser();
	Script &operator[](int);
	void operate(const char*);
	int size() const;
	std::string getID(int) const;
	
	~ScriptParser();
private:
	std::vector<Script> m_file;	
};
