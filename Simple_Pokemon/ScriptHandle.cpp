#include "ScriptHandle.h"

using namespace std;

ScriptHandle::ScriptHandle():m_msgbox(nullptr), m_conditional_stockage(false), m_current_cursor_place(0), m_current_if_cond(false), m_if_state(false)
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
	
	cout << endl;
	m_msgbox = msgBox;
	int cursor = (m_current_cursor_place != 0) ? m_current_cursor_place : 0;

	while(cursor < m_script_heap.instruction_list.size())
	{
		auto type = m_script_heap.instruction_list[cursor].script_type;
		if (type == "01")//un dialogue
		{
			
			if (m_current_if_cond)
			{
			
				if ((m_conditional_stockage && m_if_state)||(!m_conditional_stockage && !m_if_state))
				{
				
					m_msgbox->addContent(m_file[hexToInt(m_script_heap.instruction_list[cursor].param)]);
					m_msgbox->setDrawable(true);
					*wait = true;
					return;
				}

			}
			else
			{
				
				m_msgbox->addContent(m_file[hexToInt(m_script_heap.instruction_list[cursor].param)]);
				m_msgbox->setDrawable(true);
				*wait = true;
				return;
			}
			

		}
		else if (type == "05") // setFlag
		{
			
			if (m_current_if_cond)
			{
				
				if ((m_conditional_stockage && m_if_state) || (!m_conditional_stockage && !m_if_state))
				{
					
					m_flags.setFlag(m_script_heap.instruction_list[cursor].optionnal_param[1] + m_script_heap.instruction_list[cursor].param,
						(m_script_heap.instruction_list[cursor].optionnal_param[0] == '1'));
				}
			}
			else
			{
				
				m_flags.setFlag(m_script_heap.instruction_list[cursor].optionnal_param[1] + m_script_heap.instruction_list[cursor].param,
					(m_script_heap.instruction_list[cursor].optionnal_param[0] == '1'));
			}
		}
			
		else if (type == "06") // checkFlag
		{
			if (m_current_if_cond)
			{
				if ((m_conditional_stockage && m_if_state) || (!m_conditional_stockage && !m_if_state))
				{
					m_conditional_stockage = m_flags.checkFlag(m_script_heap.instruction_list[cursor].optionnal_param[1] + m_script_heap.instruction_list[cursor].param);

				}
			}
			else
			{
				m_conditional_stockage = m_flags.checkFlag(m_script_heap.instruction_list[cursor].optionnal_param[1] + m_script_heap.instruction_list[cursor].param);
				
			}
		}
		else if (type == "07") // GOTO
		{
			if (m_current_if_cond)
			{
				if ((m_conditional_stockage && m_if_state) || (!m_conditional_stockage && !m_if_state))
				{
					cursor = hexToInt(m_script_heap.instruction_list[cursor].optionnal_param + m_script_heap.instruction_list[cursor].param);

				}
			}
			else
			{
				cursor = hexToInt(m_script_heap.instruction_list[cursor].optionnal_param + m_script_heap.instruction_list[cursor].param);

			}
		}
		else if (type == "08") // IF
		{
			if (m_script_heap.instruction_list[cursor].param == "01")
			{
				
				if (m_conditional_stockage)
				{
					
					m_if_state = true;
					m_current_if_cond = true;
				}
				else // on doit sauter jusqu au prochain endif
				{
					
					auto tmp_curs = jumpUntilNewENDIF(cursor);
					cursor = (tmp_curs == -1) ? cursor : tmp_curs;
				}
			}
			else
			{
				
				if (!m_conditional_stockage)
				{
					
					m_if_state = false;
					m_current_if_cond = true;
				}
				else // on doit sauter jusqu au prochain endif
				{
					
					auto tmp_curs = jumpUntilNewENDIF(cursor);
					cursor = (tmp_curs == -1) ? cursor : tmp_curs;
				}
				
			}

		}
		else if (type == "09")
		{
			
			m_current_if_cond = false;
			m_conditional_stockage = false;
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

int ScriptHandle::jumpUntilNewENDIF(int actual)
{
	while (actual < m_script_heap.instruction_list.size() && m_script_heap.instruction_list[actual].script_type != "09")
		actual++;
	return (actual>= m_script_heap.instruction_list.size())?-1:actual;
}
