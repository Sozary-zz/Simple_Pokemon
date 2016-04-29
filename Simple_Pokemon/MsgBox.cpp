#include "MsgBox.h"
#include <iostream>
using namespace std;

MsgBox::MsgBox() :m_can_be_drawn(false), m_texte(), m_next(8,3), m_draw_next(false), m_finished(false)
{
	m_surface_texture.loadFromFile("tiles/msgbox.png");
	m_surface.setTexture(m_surface_texture);
	m_surface.setPosition(5, 260);
	m_surface.setScale(.65, .55);

	m_font.loadFromFile("data/fonts/gill-sans-w04-book.woff");
	m_texte[0].setFont(m_font);
	m_texte[1].setFont(m_font);
	m_texte[0].setCharacterSize(12);
	m_texte[1].setCharacterSize(12);
	m_texte[0].setColor(sf::Color::Black);
	m_texte[1].setColor(sf::Color::Black);
	m_texte[0].setPosition(20, 265);
	m_texte[1].setPosition(20, 282);

	m_next.setFillColor(sf::Color::Red);
	m_next.rotate(180.f);
	m_next.setPosition(280, 285);
	m_next.setOutlineThickness(1.2);
	m_next.setOutlineColor(sf::Color(125,125,125));
}

bool MsgBox::canBeDrawn() const
{
	return m_can_be_drawn;
}

void MsgBox::addContent(string text)
{
	
	format(text);
	cout << "New perso" << endl;
	m_internal_clock.restart();
	if (m_buffer.size() % 2 != 0) // pour avoir des msgbox complets
		m_buffer.push_back("");

	if (m_buffer.size() > 0)
	{
	
		for (int i = 0; i < 2; ++i)
		{
			m_texte[i].setString(m_buffer[0]);
			m_buffer.erase(m_buffer.begin());
		}
		
		if (m_buffer.size() > 0)
		{
			m_draw_next = true;
		}
		else
			m_finished = true;
		
	}
	else
		m_finished = true;
	
}

void MsgBox::setDrawable(bool state)
{
	if (state)
		m_can_be_drawn = true;
	else
		m_can_be_drawn = false;
}

void MsgBox::changeMsg()
{		
		m_internal_clock.restart();
		if (m_finished)
			m_can_be_drawn = false;

		if (m_buffer.size() > 0)
		{
			display();
			for (int i = 0; i < 2; ++i)
			{
				m_texte[i].setString(m_buffer[0]);
				m_buffer.erase(m_buffer.begin());
			}
			
			if (m_buffer.size() > 0)
			{
				if (m_buffer.size() % 2 != 0) 
					m_buffer.push_back("");
				m_draw_next = true;
			}
				
			else
			{

				m_finished = true;
			}
				

		}
		else
		{
			m_finished = true;
		}	
		
}

bool MsgBox::isFinish() const
{
	return (m_finished);
}

sf::Int32 MsgBox::getElapsed() const
{
	return m_internal_clock.getElapsedTime().asMilliseconds();
}



void MsgBox::clear()
{
	m_can_be_drawn=false;   m_draw_next=false; m_finished=false;
	m_buffer.clear();
	m_texte->setString("");
}

MsgBox::~MsgBox()
{
}

void MsgBox::format(string text) // formatage du texte
{
	string tmp="";
	m_buffer.clear();
	bool saut = false;
	for (int i = 0; i < text.size(); ++i)
	{
		if (text[i] == '|' && text[i + 1] == 'n') // saut de ligne
		{
			saut = true;
			m_buffer.push_back(tmp);
			tmp = "";
		}
		else
		{
			if (!saut)
				tmp += text[i];
			else
				saut = false;
			
		}
	}
	m_buffer.push_back(tmp);


}


void MsgBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// on applique la transformation
	states.transform *= getTransform();
	target.draw(m_surface, states);


	target.draw(m_texte[0], states);
	target.draw(m_texte[1], states);

	if (m_draw_next)
		target.draw(m_next,states);

}

void MsgBox::display()
{
	for (int i = 0; i < m_buffer.size(); ++i)
		cout << m_buffer[i] << "|"<<endl;
	cout <<"/"<< endl;
}
