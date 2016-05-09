#include "ScriptHandle.h"

using namespace std;

ScriptHandle::ScriptHandle():m_msgbox(nullptr), m_conditional_stockage(false), m_current_cursor_place(0)
{
	ifstream fichier("data/dialogues.dial", ios::in);
	//creer un objet msgBox
	string tmp;
	while (getline(fichier, tmp))
		m_file.push_back(tmp);
	fichier.close();
}

void ScriptHandle::loadScript(Script script)
{
	// on parse vite fait le script

	for (int i = 0; i < script.instructions.size(); ++i)
	{
		if (script.instructions[i].script_type == "00")
			m_script_heap.identification = script.instructions[i];
		else if (script.instructions[i].script_type == "03")
			m_script_heap.aspect = script.instructions[i];
		else if (script.instructions[i].script_type == "04")
			m_script_heap.initial_raw_sequence = script.instructions[i];
		else
			m_script_heap.instruction_list.push_back(script.instructions[i]);
	}

}
void ScriptHandle::executeHeap(MsgBox *msgBox,bool* wait)
{	
	

	m_msgbox = msgBox;
	int cursor = (m_current_cursor_place != 0) ? m_current_cursor_place : 0;

	while(cursor < m_script_heap.instruction_list.size())
	{
		auto type = m_script_heap.instruction_list[cursor].script_type;
		if (type == "01")//un dialogue
		{
			m_msgbox->addContent(m_file[hexToInt(m_script_heap.instruction_list[cursor].param)]); 
			m_msgbox->setDrawable(true);
			*wait = true;
			return;

		}
		else if (type == "05") // setFlag

			m_flags.setFlag(m_script_heap.instruction_list[cursor].optionnal_param[1] + m_script_heap.instruction_list[cursor].param,
			(m_script_heap.instruction_list[cursor].optionnal_param[0] == '1'));
		else if (type == "06") // checkFlag
			m_conditional_stockage = m_flags.checkFlag(m_script_heap.instruction_list[cursor].optionnal_param[1] + m_script_heap.instruction_list[cursor].param);
		else if (type == "07") // GOTO
			cursor = hexToInt(m_script_heap.instruction_list[cursor].optionnal_param + m_script_heap.instruction_list[cursor].param);
		else if (type == "08") // IF
		{
			if (m_conditional_stockage)
			{
				
				cursor += hexToInt(m_script_heap.instruction_list[cursor].optionnal_param);
				m_current_cursor_place += hexToInt(m_script_heap.instruction_list[cursor].optionnal_param);
				m_conditional_stockage = false;
			}
				
			else
			{
				cursor += hexToInt(m_script_heap.instruction_list[cursor].param);
				m_current_cursor_place += hexToInt(m_script_heap.instruction_list[cursor].param);
				m_conditional_stockage = false;
			}
				
		}

		cursor++;
		m_current_cursor_place++;
	}
	m_current_cursor_place = 0;
	m_script_heap = {};


	
}
void ScriptHandle::next_action(bool* wait)
{	

	m_msgbox->changeMsg();
	if (m_msgbox->isFinish())
	{
		m_current_cursor_place++;
		*wait = false;
		m_msgbox = nullptr;
	}
	else
		*wait = true;

}
ScriptHandle::~ScriptHandle()
{
}

int ScriptHandle::hexToInt(std::string str)
{
	int res;
	stringstream ss;
	ss << hex << str;
	ss >> res;
	return res;
}
