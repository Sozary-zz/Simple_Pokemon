#pragma once
#include "SFML\Graphics.hpp"
#include <vector>
#include <string>

class MsgBox: public sf::Drawable, public sf::Transformable
{
public:
	MsgBox();
	bool canBeDrawn() const;
	void addContent(std::string);
	void setDrawable(bool);
	void changeMsg();
	bool isFinish() const;
	~MsgBox();
private:
	bool m_can_be_drawn;

	sf::Sprite m_surface;
	sf::Texture m_surface_texture;
	sf::CircleShape m_next;

	sf::Font m_font;
	sf::Text m_texte[2]; // que deux lignes de texte
	std::vector<std::string> m_buffer; // le surplus de ligne

	bool m_draw_next;

	bool m_finished;
private:
	void format(std::string);
	virtual void draw(sf::RenderTarget&, sf::RenderStates ) const;
};

