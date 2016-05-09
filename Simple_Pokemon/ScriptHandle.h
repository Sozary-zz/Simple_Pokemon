#pragma once
#include "ScriptParser.hpp"
#include "MsgBox.h"
#include <fstream>
#include <sstream>
#include "FlagParser.h"

struct ScriptHeap
{
	Offset identification; // 0x00 ID du perso
	Offset aspect; // 0x03 Tete perso, position perso
	Offset initial_raw_sequence; // 0x04 les mouvements de bases

	std::vector<Offset> instruction_list; // le reste
};
class ScriptHandle
{
public:
	ScriptHandle();
	void loadScript(Script); // le script  DOIT  forcément etre trié (une pile, c est une pile, un point c est tout)
	void executeHeap(MsgBox*,bool*); //  d autres param incoming!
	void next_action(bool*);
	FlagParser m_flags;
	~ScriptHandle();
private:
	ScriptHeap m_script_heap;
	MsgBox* m_msgbox;
	std::vector<std::string> m_file;
	bool m_conditional_stockage;

private:
	int hexToInt(std::string);
};

